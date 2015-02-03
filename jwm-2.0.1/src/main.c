/**
 * @file main.c
 * @author Joe Wingbermuehle
 * @date 2004-2006
 *
 * @brief The main entry point and related JWM functions.
 *
 */

#include "jwm.h"
#include "main.h"
#include "lex.h"
#include "parse.h"
#include "help.h"
#include "error.h"
#include "event.h"

#include "border.h"
#include "client.h"
#include "color.h"
#include "command.h"
#include "cursor.h"
#include "confirm.h"
#include "font.h"
#include "hint.h"
#include "group.h"
#include "key.h"
#include "icon.h"
#include "outline.h"
#include "taskbar.h"
#include "tray.h"
#include "traybutton.h"
#include "popup.h"
#include "pager.h"
#include "swallow.h"
#include "screen.h"
#include "root.h"
#include "desktop.h"
#include "place.h"
#include "clock.h"
#include "dock.h"
#include "misc.h"
#include "background.h"

Display *display = NULL;
Window rootWindow;
int rootWidth, rootHeight;
int rootDepth;
int rootScreen;
Colormap rootColormap;
Visual *rootVisual;
GC rootGC;
int colormapCount;

int shouldExit = 0;
int shouldRestart = 0;
int isRestarting = 0;
int initializing = 0;

unsigned int desktopCount = 4;
unsigned int currentDesktop = 0;

char *exitCommand = NULL;

int borderWidth = DEFAULT_BORDER_WIDTH;
int titleHeight = DEFAULT_TITLE_HEIGHT;

unsigned int doubleClickSpeed;
unsigned int doubleClickDelta;

FocusModelType focusModel = FOCUS_SLOPPY;

XContext clientContext;
XContext frameContext;

#ifdef USE_SHAPE
int haveShape;
int shapeEvent;
#endif


static const char *CONFIG_FILE = "/jwmrc";

static void Initialize();
static void Startup();
static void Shutdown();
static void Destroy();

static void OpenConnection();
static void CloseConnection();
static void StartupConnection();
static void ShutdownConnection();
static void EventLoop();
static void HandleExit();
static void DoExit(int code);
static void SendRestart();
static void SendExit();

static char *configPath = NULL;
static char *displayString = NULL;

/** The main entry point. */
int main(int argc, char *argv[]) {

   char *temp;
   int x;

   StartDebug();

   /* Get the name of the user's local configuration file. */
   temp = getenv("HOME");
   if(temp) {
      configPath = Allocate(strlen(temp) + strlen(CONFIG_FILE) + 1);
      strcpy(configPath, temp);
      strcat(configPath, CONFIG_FILE);
   } else {
      configPath = CopyString(CONFIG_FILE);
   }

   /* Parse command line options. */
   for(x = 1; x < argc; x++) {
      if(!strcmp(argv[x], "-v")) {
         DisplayAbout();
         DoExit(0);
      } else if(!strcmp(argv[x], "-h")) {
         DisplayHelp();
         DoExit(0);
      } else if(!strcmp(argv[x], "-p")) {
         Initialize();
         ParseConfig(configPath);
         DoExit(0);
      } else if(!strcmp(argv[x], "-restart")) {
         SendRestart();
         DoExit(0);
      } else if(!strcmp(argv[x], "-exit")) {
         SendExit();
         DoExit(0);
      } else if(!strcmp(argv[x], "-display") && x + 1 < argc) {
         displayString = argv[++x];
      } else {
         DisplayUsage();
         DoExit(1);
      }
   }

   /* The main loop. */
   StartupConnection();
   do {

      isRestarting = shouldRestart;
      shouldExit = 0;
      shouldRestart = 0;

      /* Prepare JWM components. */
      Initialize();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

      /* Parse the configuration file. */
      ParseConfig(configPath);

	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

      /* Start up the JWM components. */
      Startup();

	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

      /* The main event loop. */
      EventLoop();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

      /* Shutdown JWM components. */
      Shutdown();

      /* Perform any extra cleanup. */
      Destroy();

   } while(shouldRestart);
   ShutdownConnection();

   /* If we have a command to execute on shutdown, run it now. */
   if(exitCommand) {
      execl(SHELL_NAME, SHELL_NAME, "-c", exitCommand, NULL);
      Warning("exec failed: (%s) %s", SHELL_NAME, exitCommand);
      DoExit(1);
   } else {
      DoExit(0);
   }

   /* Control shoud never get here. */
   return -1;

}

/** Exit with the specified status code. */
void DoExit(int code) {

   Destroy();

   if(configPath) {
      Release(configPath);
      configPath = NULL;
   }
   if(exitCommand) {
      Release(exitCommand);
      exitCommand = NULL;
   }

   StopDebug();
   exit(code);
}

/** Main JWM event loop. */
void EventLoop() {

   XEvent event;

   /* Loop processing events until it's time to exit. */
   while(!shouldExit) {
      WaitForEvent(&event);
      ProcessEvent(&event);
   }

   /* Give windows (swallow windows especially) time to map. */
   usleep(RESTART_DELAY);

   /* Process events one last time. */
   while(JXPending(display) > 0) {
      WaitForEvent(&event);
      ProcessEvent(&event);
   }

}

/** Open a connection to the X server. */
void OpenConnection() {
	int     cycles;

	for (cycles = 0; cycles < 50; cycles++) { 
		display = JXOpenDisplay(displayString);
		if (!display)
		{
			usleep(500000);
		}
		else
			break;
	}

   //display = JXOpenDisplay(displayString);
   if(!display) {
      if(displayString) {
         printf("error: could not open display %s\n", displayString);
      } else {
         printf("error: could not open display\n");
      }
      DoExit(1);
   }

   rootScreen = DefaultScreen(display);
   rootWindow = RootWindow(display, rootScreen);
   rootWidth = DisplayWidth(display, rootScreen);
   rootHeight = DisplayHeight(display, rootScreen);
   rootDepth = DefaultDepth(display, rootScreen);
   rootColormap = DefaultColormap(display, rootScreen);
   rootVisual = DefaultVisual(display, rootScreen);
   rootGC = DefaultGC(display, rootScreen);
   colormapCount = MaxCmapsOfScreen(ScreenOfDisplay(display, rootScreen));

   XSetGraphicsExposures(display, rootGC, False);

}

/** Prepare the connection. */
void StartupConnection() {

   XSetWindowAttributes attr;
   int temp;

   initializing = 1;
   OpenConnection();

#if 0
   XSynchronize(display, True);
#endif

   JXSetErrorHandler(ErrorHandler);

   clientContext = XUniqueContext();
   frameContext = XUniqueContext();

   /* Set the events we want for the root window.
    * Note that asking for SubstructureRedirect will fail
    * if another window manager is already running.
    */
   attr.event_mask
      = SubstructureRedirectMask
      | SubstructureNotifyMask
      | PropertyChangeMask
      | ColormapChangeMask
      | ButtonPressMask
      | ButtonReleaseMask
      | PointerMotionMask | PointerMotionHintMask;
   JXChangeWindowAttributes(display, rootWindow, CWEventMask, &attr);

   signal(SIGTERM, HandleExit);
   signal(SIGINT, HandleExit);
   signal(SIGHUP, HandleExit);

#ifdef USE_SHAPE
   haveShape = JXShapeQueryExtension(display, &shapeEvent, &temp);
   if (haveShape) {
      Debug("shape extension enabled");
   } else {
      Debug("shape extension disabled");
   }
#endif

   initializing = 0;

}

/** Close the X server connection. */
void CloseConnection() {
   JXFlush(display);
   JXCloseDisplay(display);
}

/** Close the X server connection. */
void ShutdownConnection() {
   CloseConnection();
}

/** Signal handler. */
void HandleExit() {
   signal(SIGTERM, HandleExit);
   signal(SIGINT, HandleExit);
   signal(SIGHUP, HandleExit);
   shouldExit = 1;
}

/** Initialize data structures.
 * This is called before the X connection is opened.
 */
void Initialize() {
   InitializeBackgrounds();
   InitializeBorders();
   InitializeClients();
   InitializeClock();
   InitializeColors();
   InitializeCommands();
   InitializeCursors();
   InitializeDesktops();
#ifndef DISABLE_CONFIRM
   InitializeDialogs();
#endif
   InitializeDock();
   InitializeFonts();
   InitializeGroups();
   InitializeHints();
   InitializeIcons();
   InitializeKeys();
   InitializeOutline();
   InitializePager();
   InitializePlacement();
   InitializePopup();
   InitializeRootMenu();
   InitializeScreens();
   InitializeSwallow();
   InitializeTaskBar();
   InitializeTray();
   InitializeTrayButtons();
}

/** Startup the various JWM components.
 * This is called after the X connection is opened.
 */
void Startup() {

   /* This order is important. */

   StartupCommands();

   /* First we grab the server to prevent clients from changing things
    * while we're still loading. */
   JXGrabServer(display);

   StartupScreens();

   StartupGroups();
   StartupColors();
   StartupIcons();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupBackgrounds();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupFonts();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupCursors();
   StartupOutline();

   StartupPager();
   StartupClock();
   StartupTaskBar();
   StartupTrayButtons();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupDock();
   StartupTray();
   StartupKeys();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupDesktops();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupHints();
 	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
  StartupBorders();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupPlacement();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupClients();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

#  ifndef DISABLE_CONFIRM
      StartupDialogs();
#  endif
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);
   StartupPopup();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

   StartupRootMenu();

   SetDefaultCursor(rootWindow);
   ReadCurrentDesktop();
   JXFlush(display);
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

   RestackClients();

   /* Allow clients to do their thing. */
   JXSync(display, True);
   JXUngrabServer(display);

   StartupSwallow();
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

   DrawTray();

   /* Send expose events. */
   ExposeCurrentDesktop();

   /* Draw the background (if backgrounds are used). */
   LoadBackground(currentDesktop);
	  printf("jwm: %s got line %d\n", __FILE__,__LINE__);

}

/** Shutdown the various JWM components.
 * This is called before the X connection is closed.
 */
void Shutdown() {

   /* This order is important. */

   ShutdownSwallow();

   ShutdownOutline();
#  ifndef DISABLE_CONFIRM
      ShutdownDialogs();
#  endif
   ShutdownPopup();
   ShutdownKeys();
   ShutdownPager();
   ShutdownRootMenu();
   ShutdownDock();
   ShutdownTray();
   ShutdownTrayButtons();
   ShutdownTaskBar();
   ShutdownClock();
   ShutdownBorders();
   ShutdownClients();
   ShutdownBackgrounds();
   ShutdownIcons();
   ShutdownCursors();
   ShutdownFonts();
   ShutdownColors();
   ShutdownGroups();
   ShutdownDesktops();

   ShutdownPlacement();
   ShutdownHints();
   ShutdownScreens();

   ShutdownCommands();

}

/** Clean up memory.
 * This is called after the X connection is closed.
 * Note that it is possible for this to be called more than once.
 */
void Destroy() {
   DestroyBackgrounds();
   DestroyBorders();
   DestroyClients();
   DestroyClock();
   DestroyColors();
   DestroyCommands();
   DestroyCursors();
   DestroyDesktops();
#ifndef DISABLE_CONFIRM
   DestroyDialogs();
#endif
   DestroyDock();
   DestroyFonts();
   DestroyGroups();
   DestroyHints();
   DestroyIcons();
   DestroyKeys();
   DestroyOutline();
   DestroyPager();
   DestroyPlacement();
   DestroyPopup();
   DestroyRootMenu();
   DestroyScreens();
   DestroySwallow();
   DestroyTaskBar();
   DestroyTray();
   DestroyTrayButtons();
}

/** Send _JWM_RESTART to the root window. */
void SendRestart() {

   XEvent event;

   OpenConnection();

   memset(&event, 0, sizeof(event));
   event.xclient.type = ClientMessage;
   event.xclient.window = rootWindow;
   event.xclient.message_type = JXInternAtom(display, "_JWM_RESTART", False);
   event.xclient.format = 32;

   JXSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);

   CloseConnection();

}

/** Send _JWM_EXIT to the root window. */
void SendExit() {

   XEvent event;

   OpenConnection();

   memset(&event, 0, sizeof(event));
   event.xclient.type = ClientMessage;
   event.xclient.window = rootWindow;
   event.xclient.message_type = JXInternAtom(display, "_JWM_EXIT", False);
   event.xclient.format = 32;

   JXSendEvent(display, rootWindow, False, SubstructureRedirectMask, &event);

   CloseConnection();
}

