/**
 * @file desktop.h
 * @author Joe Wingbermuehle
 * @date 2004-2006
 *
 * @brief Header for the desktop management functions.
 *
 */

#include "jwm.h"
#include "desktop.h"
#include "main.h"
#include "client.h"
#include "clientlist.h"
#include "hint.h"
#include "pager.h"
#include "taskbar.h"
#include "error.h"
#include "menu.h"
#include "misc.h"
#include "background.h"

char **desktopNames = NULL;

static int showingDesktop;

/** Initialize desktop data. */
void InitializeDesktops() {
}

/** Startup desktop support. */
void StartupDesktops() {

   unsigned int x;

   if(desktopNames == NULL) {
      desktopNames = Allocate(desktopCount * sizeof(char*));
      for(x = 0; x < desktopCount; x++) {
         desktopNames[x] = NULL;
      }
   }
   for(x = 0; x < desktopCount; x++) {
      if(desktopNames[x] == NULL) {
         desktopNames[x] = Allocate(4 * sizeof(char));
         snprintf(desktopNames[x], 4, "%d", x + 1);
      }
   }

   showingDesktop = 0;

}

/** Shutdown desktop support. */
void ShutdownDesktops() {
}

/** Release desktop data. */
void DestroyDesktops() {

   unsigned int x;

   if(desktopNames) {
      for(x = 0; x < desktopCount; x++) {
         Release(desktopNames[x]);
      }
      Release(desktopNames);
      desktopNames = NULL;
   }

}

/** Change to the next desktop. */
void NextDesktop() {
   ChangeDesktop((currentDesktop + 1) % desktopCount);
}

/** Change to the previous desktop. */
void PreviousDesktop() {
   if(currentDesktop > 0) {
      ChangeDesktop(currentDesktop - 1);
   } else {
      ChangeDesktop(desktopCount - 1);
   }
}

/** Change to the specified desktop. */
void ChangeDesktop(unsigned int desktop) {

   ClientNode *np;
   unsigned int x;

   if(desktop >= desktopCount) {
      return;
   }

   if(currentDesktop == desktop && !initializing) {
      return;
   }

   for(x = 0; x < LAYER_COUNT; x++) {
      for(np = nodes[x]; np; np = np->next) {
         if(np->state.status & STAT_STICKY) {
            continue;
         }
         if(np->state.desktop == desktop) {
            ShowClient(np);
         } else if(np->state.desktop == currentDesktop) {
            HideClient(np);
         }
      }
   }

   currentDesktop = desktop;

   SetCardinalAtom(rootWindow, ATOM_NET_CURRENT_DESKTOP, currentDesktop);
   SetCardinalAtom(rootWindow, ATOM_WIN_WORKSPACE, currentDesktop);

   RestackClients();

   UpdatePager();
   UpdateTaskBar();

   LoadBackground(desktop);

}

/** Create a desktop menu. */
Menu *CreateDesktopMenu(unsigned int mask) {

   Menu *menu;
   MenuItem *item;
   int x;

   menu = Allocate(sizeof(Menu));
   menu->itemHeight = 0;
   menu->items = NULL;
   menu->label = NULL;

   for(x = desktopCount - 1; x >= 0; x--) {

      item = Allocate(sizeof(MenuItem));
      item->type = MENU_ITEM_NORMAL;
      item->iconName = NULL;
      item->submenu = NULL;
      item->next = menu->items;
      menu->items = item;

      item->action.type = MA_DESKTOP;
      item->action.data.i = x;

      item->name = Allocate(strlen(desktopNames[x]) + 3);
      if(mask & (1 << x)) {
         strcpy(item->name, "[");
         strcat(item->name, desktopNames[x]);
         strcat(item->name, "]");
      } else {
         strcpy(item->name, " ");
         strcat(item->name, desktopNames[x]);
         strcat(item->name, " ");
      }

   }

   return menu;

}

/** Toggle the "show desktop" state. */
void ShowDesktop() {

   ClientNode *np;
   int layer;

   for(layer = 0; layer < LAYER_COUNT; layer++) {
      for(np = nodes[layer]; np; np = np->next) {

         /* Skip "nolist" items. */
         if(np->state.status & STAT_NOLIST) {
            continue;
         }

         if(showingDesktop) {
            if(np->state.status & STAT_SDESKTOP) {
               RestoreClient(np, 0);
            }
         } else if(np->state.desktop == currentDesktop
             || (np->state.status & STAT_STICKY)) {
            if(np->state.status & (STAT_MAPPED | STAT_SHADED)) {
               MinimizeClient(np);
               np->state.status |= STAT_SDESKTOP;
            }
         }
      }
   }

   showingDesktop = !showingDesktop;

   RestackClients();

}

/** Set the number of desktops to use. */
void SetDesktopCount(const char *str) {

   if(!str) {
      Warning("invalid desktop count");
      return;
   }

   desktopCount = atoi(str);
   if(   desktopCount < MIN_DESKTOP_COUNT
      || desktopCount > MAX_DESKTOP_COUNT) {

      Warning("invalid desktop count: \"%s\"", str);
      desktopCount = DEFAULT_DESKTOP_COUNT;

   }

}

/** Set the name for a desktop. */
void SetDesktopName(unsigned int desktop, const char *str) {

   unsigned int x;

   if(!str) {
      Warning("empty Desktops Name tag");
      return;
   }

   Assert(desktop >= 0);
   Assert(desktop < desktopCount);

   if(!desktopNames) {
      desktopNames = Allocate(desktopCount * sizeof(char*));
      for(x = 0; x < desktopCount; x++) {
         desktopNames[x] = NULL;
      }
   }

   Assert(desktopNames[desktop] == NULL);

   desktopNames[desktop] = CopyString(str);

}

