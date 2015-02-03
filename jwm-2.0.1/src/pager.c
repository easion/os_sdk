/**
 * @file pager.c
 * @author Joe Wingbermuehle
 * @date 2004-2007
 *
 * @brief Pager tray component.
 *
 */

#include "jwm.h"
#include "pager.h"

#include "client.h"
#include "clientlist.h"
#include "color.h"
#include "cursor.h"
#include "desktop.h"
#include "event.h"
#include "main.h"
#include "tray.h"

/** Structure to represent a pager tray component. */
typedef struct PagerType {

   TrayComponentType *cp;  /**< Common tray component data. */

   int deskWidth;          /**< Width of a desktop. */
   int deskHeight;         /**< Height of a desktop. */
   double scalex;          /**< Horizontal scale factor. */
   double scaley;          /**< Vertical scale factor. */
   LayoutType layout;      /**< Layout of the desktops. */

   Pixmap buffer;          /**< Buffer for rendering the pager. */

   struct PagerType *next; /**< Next pager in the list. */

} PagerType;

static PagerType *pagers;

static int shouldStopMove;

static void Create(TrayComponentType *cp);

static void SetSize(TrayComponentType *cp, int width, int height);

static int GetPagerDesktop(PagerType *pp, int x, int y);

static void ProcessPagerButtonEvent(TrayComponentType *cp,
   int x, int y, int mask);

static void StartPagerMove(TrayComponentType *cp, int x, int y);

static void StopPagerMove(ClientNode *np,
   int x, int y, int desktop, int hmax, int vmax);

static void PagerMoveController(int wasDestroyed);

static void DrawPagerClient(const PagerType *pp, const ClientNode *np);

/** Initialize pager data. */
void InitializePager() {
   pagers = NULL;
}

/** Startup the pager. */
void StartupPager() {
}

/** Shutdown the pager. */
void ShutdownPager() {

   PagerType *pp;

   for(pp = pagers; pp; pp = pp->next) {
      JXFreePixmap(display, pp->buffer);
   }

}

/** Release pager data. */
void DestroyPager() {

   PagerType *pp;

   while(pagers) {
      pp = pagers->next;
      Release(pagers);
      pagers = pp;
   }

}

/** Create a new pager tray component. */
TrayComponentType *CreatePager() {

   TrayComponentType *cp;
   PagerType *pp;

   pp = Allocate(sizeof(PagerType));
   pp->next = pagers;
   pagers = pp;

   cp = CreateTrayComponent();
   cp->object = pp;
   pp->cp = cp;
   cp->Create = Create;
   cp->SetSize = SetSize;
   cp->ProcessButtonPress = ProcessPagerButtonEvent;

   return cp;
}

/** Initialize a pager tray component. */
void Create(TrayComponentType *cp) {

   PagerType *pp;

   Assert(cp);

   pp = (PagerType*)cp->object;

   Assert(pp);

   Assert(cp->width > 0);
   Assert(cp->height > 0);

   cp->pixmap = JXCreatePixmap(display, rootWindow, cp->width,
      cp->height, rootDepth);
   pp->buffer = cp->pixmap;

}

/** Set the size of a pager tray component. */
void SetSize(TrayComponentType *cp, int width, int height) {

   PagerType *pp;

   Assert(cp);

   pp = (PagerType*)cp->object;

   Assert(pp);

   if(width) {

      /* Vertical pager, compute height from width. */
      cp->width = width;
      pp->deskWidth = width;
      pp->deskHeight = (cp->width * rootHeight) / rootWidth;
      cp->height = (pp->deskHeight + 1) * desktopCount;
      pp->layout = LAYOUT_VERTICAL;

   } else if(height) {

      /* Horizontal pager, compute width from height. */
      cp->height = height;
      pp->deskHeight = height;
      pp->deskWidth = (cp->height * rootWidth) / rootHeight;
      cp->width = (pp->deskWidth + 1) * desktopCount;
      pp->layout = LAYOUT_HORIZONTAL;

   } else {
      Assert(0);
   }

   pp->scalex = (double)(pp->deskWidth - 2) / rootWidth;
   pp->scaley = (double)(pp->deskHeight - 2) / rootHeight;

}

/** Get the desktop for a pager given a set of coordinates. */
int GetPagerDesktop(PagerType *pp, int x, int y) {

   if(pp->layout == LAYOUT_HORIZONTAL) {
      return x / (pp->deskWidth + 1);
   } else {
      return y / (pp->deskHeight + 1);
   }

}

/** Process a button event on a pager tray component. */
void ProcessPagerButtonEvent(TrayComponentType *cp, int x, int y, int mask) {

   PagerType *pp;

   switch(mask) {
   case Button1:
   case Button2:

      /* Change to the selected desktop. */
      pp = (PagerType*)cp->object;
      ChangeDesktop(GetPagerDesktop(pp, x, y));
      break;

   case Button3:

      /* Move a client and possibly change its desktop. */
      StartPagerMove(cp, x, y);
      break;

   case Button4:

      /* Change to the previous desktop. */
      PreviousDesktop();
      break;

   case Button5:

      /* Change to the next desktop. */
      NextDesktop();
      break;

   default:
      break;
   }
}

/** Start a pager move operation. */
void StartPagerMove(TrayComponentType *cp, int x, int y) {

   XEvent event;
   PagerType *pp;
   ClientNode *np;
   int layer;
   int desktop;
   int cx, cy;
   int cwidth, cheight;

   int north, south, east, west;
   int oldx, oldy;
   int oldDesk;
   int startx, starty;
   int hmax, vmax;

   pp = (PagerType*)cp->object;

   /* Determine the selected desktop. */
   desktop = GetPagerDesktop(pp, x, y);
   if(pp->layout == LAYOUT_HORIZONTAL) {
      x -= desktop * (pp->deskWidth + 1);
   } else {
      y -= desktop * (pp->deskHeight + 1);
   }

   /* Find the client under the specified coordinates. */
   for(layer = LAYER_TOP; layer >= LAYER_BOTTOM; layer--) {
      for(np = nodes[layer]; np; np = np->next) {

         /* Skip this client if it isn't mapped. */
         if(!(np->state.status & STAT_MAPPED)) {
            continue;
         }

         /* Skip this client if it isn't on the selected desktop. */
         if(np->state.status & STAT_STICKY) {
            if(currentDesktop != desktop) {
               continue;
            }
         } else {
            if(np->state.desktop != desktop) {
               continue;
            }
         }

         /* Get the offset and size of the client on the pager. */
         cx = (int)((double)np->x * pp->scalex + 1.0);
         cy = (int)((double)np->y * pp->scaley + 1.0);
         cwidth = (int)((double)np->width * pp->scalex);
         cheight = (int)((double)np->height * pp->scaley);

         /* Normalize the offset and size. */
         if(cx + cwidth > pp->deskWidth) {
            cwidth = pp->deskWidth - cx;
         }
         if(cy + cheight > pp->deskHeight) {
            cheight = pp->deskHeight - cy;
         }
         if(cx < 0) {
            cwidth += cx;
            cx = 0;
         }
         if(cy < 0) {
            cheight += cy;
            cy = 0;
         }

         /* Skip the client if we are no longer in bounds. */
         if(cwidth <= 0 || cheight <= 0) {
            continue;
         }

         /* Check the y-coordinate. */
         if(y < cy || y > cy + cheight) {
            continue;
         }

         /* Check the x-coordinate. */
         if(x < cx || x > cx + cwidth) {
            continue;
         }

         /* Found it. Exit. */
         goto ClientFound;

      }
   }

   /* Client wasn't found. Just return. */
   return;

ClientFound:

   Assert(np);

   /* The selected client was found. Now make sure we can move it. */
   if(!(np->state.border & BORDER_MOVE)) {
      return;
   }

   /* If the client is maximized, unmaximize it. */
   hmax = 0;
   if(np->state.status & STAT_HMAX) {
      hmax = 1;
   }
   vmax = 0;
   if(np->state.status & STAT_VMAX) {
      vmax = 1;
   }
   if(hmax || vmax) {
      MaximizeClient(np, 0, 0);
   }

   GetBorderSize(np, &north, &south, &east, &west);

   /* Start the move. */
   GrabMouseForMove();

   np->controller = PagerMoveController;
   shouldStopMove = 0;

   oldx = np->x;
   oldy = np->y;
   oldDesk = np->state.desktop;

   startx = x;
   starty = y;

   if(!(GetMouseMask() & Button3Mask)) {
      StopPagerMove(np, oldx, oldy, oldDesk, hmax, vmax);
   }

   for(;;) {

      WaitForEvent(&event);

      if(shouldStopMove) {
         np->controller = NULL;
         return;
      }

      switch(event.type) {
      case ButtonRelease:

         /* Done when the 3rd mouse button is released. */
         if(event.xbutton.button == Button3) {
            StopPagerMove(np, oldx, oldy, oldDesk, hmax, vmax);
            return;
         }
         break;

      case MotionNotify:

         SetMousePosition(event.xmotion.x_root, event.xmotion.y_root);

         /* Get the mouse position on the pager. */
         x = event.xmotion.x_root - cp->screenx;
         y = event.xmotion.y_root - cp->screeny;

         /* Don't move if we are off of the pager. */
         if(x < 0 || x > cp->width) {
            break;
         }
         if(y < 0 || y > cp->height) {
            break;
         }

         /* Determine the new client desktop. */
         desktop = GetPagerDesktop(pp, x, y);
         if(pp->layout == LAYOUT_HORIZONTAL) {
            x -= pp->deskWidth * desktop;
         } else {
            y -= pp->deskHeight * desktop;
         }

         /* If this client isn't sticky and now on a different desktop
          * change the client's desktop. */
         if(!(np->state.status & STAT_STICKY)) {
            if(desktop != oldDesk) {
               SetClientDesktop(np, (unsigned int)desktop);
               oldDesk = desktop;
            }
         }

         /* Get new client coordinates. */
         oldx = startx + (x - startx);
         oldx /= pp->scalex;
         oldx -= (np->width + east + west) / 2;
         oldy = starty + (y - starty);
         oldy /= pp->scaley;
         oldy -= (np->height + north + south) / 2;

         /* Move the window. */
         np->x = oldx;
         np->y = oldy;
         JXMoveWindow(display, np->parent, np->x - west, np->y - north);
         SendConfigureEvent(np);
         UpdatePager();

         break;

      default:
         break;
      }

   }

}

/** Stop an active pager move. */
void StopPagerMove(ClientNode *np,
   int x, int y, int desktop, int hmax, int vmax) {

   int north, south, east, west;

   Assert(np);
   Assert(np->controller);

   /* Release grabs. */
   (np->controller)(0);

   np->x = x;
   np->y = y;

   GetBorderSize(np, &north, &south, &east, & west);
   JXMoveWindow(display, np->parent, np->x - west, np->y - north);
   SendConfigureEvent(np);

   /* Restore the maximized state of the client. */
   if(hmax || vmax) {
      MaximizeClient(np, hmax, vmax);
   }

   /* Redraw the pager. */
   UpdatePager();

}

/** Client-terminated pager move. */
void PagerMoveController(int wasDestroyed) {

   JXUngrabPointer(display, CurrentTime);
   JXUngrabKeyboard(display, CurrentTime);
   shouldStopMove = 1;

}

/** Update the pager. */
void UpdatePager() {

   PagerType *pp;
   ClientNode *np;
   Pixmap buffer;
   int width, height;
   int deskWidth, deskHeight;
   unsigned int x;

   if(shouldExit) {
      return;
   }

   for(pp = pagers; pp; pp = pp->next) {

      buffer = pp->cp->pixmap;
      width = pp->cp->width;
      height = pp->cp->height;
      deskWidth = pp->deskWidth;
      deskHeight = pp->deskHeight;

      /* Draw the background. */
      JXSetForeground(display, rootGC, colors[COLOR_PAGER_BG]);
      JXFillRectangle(display, buffer, rootGC, 0, 0, width, height);

      /* Highlight the current desktop. */
      JXSetForeground(display, rootGC, colors[COLOR_PAGER_ACTIVE_BG]);
      if(pp->layout == LAYOUT_HORIZONTAL) {
         JXFillRectangle(display, buffer, rootGC,
            currentDesktop * (deskWidth + 1), 0,
            deskWidth, height);
      } else {
         JXFillRectangle(display, buffer, rootGC,
            0, currentDesktop * (deskHeight + 1),
            width, deskHeight);
      }

      /* Draw the clients. */
      for(x = LAYER_BOTTOM; x <= LAYER_TOP; x++) {
         for(np = nodeTail[x]; np; np = np->prev) {
            DrawPagerClient(pp, np);
         }
      }

      /* Draw the desktop dividers. */
      JXSetForeground(display, rootGC, colors[COLOR_PAGER_FG]);
      for(x = 1; x < desktopCount; x++) {
         if(pp->layout == LAYOUT_HORIZONTAL) {
            JXDrawLine(display, buffer, rootGC,
               (deskWidth + 1) * x - 1, 0,
               (deskWidth + 1) * x - 1, height);
         } else {
            JXDrawLine(display, buffer, rootGC,
               0, (deskHeight + 1) * x - 1,
               width, (deskHeight + 1) * x - 1);
         }
      }

      /* Tell the tray to redraw. */
      UpdateSpecificTray(pp->cp->tray, pp->cp);

   }

}

/** Draw a client on the pager. */
void DrawPagerClient(const PagerType *pp, const ClientNode *np) {

   int x, y;
   int width, height;
   int deskOffset;
   ColorType fillColor;

   /* Don't draw the client if it isn't mapped. */
   if(!(np->state.status & STAT_MAPPED)) {
      return;
   }

   /* Determine the desktop for the client. */
   if(np->state.status & STAT_STICKY) {
      deskOffset = currentDesktop;
   } else {
      deskOffset = np->state.desktop;
   }
   if(pp->layout == LAYOUT_HORIZONTAL) {
      deskOffset *= pp->deskWidth + 1;
   } else {
      deskOffset *= pp->deskHeight + 1;
   }

   /* Determine the location and size of the client on the pager. */
   x = (int)((double)np->x * pp->scalex + 1.0);
   y = (int)((double)np->y * pp->scaley + 1.0);
   width = (int)((double)np->width * pp->scalex);
   height = (int)((double)np->height * pp->scaley);

   /* Normalize the size and offset. */
   if(x + width > pp->deskWidth) {
      width = pp->deskWidth - x;
   }
   if(y + height > pp->deskHeight) {
      height = pp->deskHeight - y;
   }
   if(x < 0) {
      width += x;
      x = 0;
   }
   if(y < 0) {
      height += y;
      y = 0;
   }

   /* Return if there's nothing to do. */
   if(width <= 0 || height <= 0) {
      return;
   }

   /* Move to the correct desktop on the pager. */
   if(pp->layout == LAYOUT_HORIZONTAL) {
      x += deskOffset;
   } else {
      y += deskOffset;
   }

   /* Draw the client outline. */
   JXSetForeground(display, rootGC, colors[COLOR_PAGER_OUTLINE]);
   JXDrawRectangle(display, pp->cp->pixmap, rootGC, x, y, width, height);

   /* Fill the client if there's room. */
   if(width > 1 && height > 1) {
      if((np->state.status & STAT_ACTIVE)
         && (np->state.desktop == currentDesktop
         || (np->state.status & STAT_STICKY))) {
         fillColor = COLOR_PAGER_ACTIVE_FG;
      } else {
         fillColor = COLOR_PAGER_FG;
      }
      JXSetForeground(display, rootGC, colors[fillColor]);
      JXFillRectangle(display, pp->cp->pixmap, rootGC, x + 1, y + 1,
         width - 1, height - 1);
   }

}

