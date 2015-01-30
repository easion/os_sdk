#ifndef WebSrv_h
#define WebSrv_h

#include "SDL_net.h"
#include "begin_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize/Cleanup of the WebSrv API
   SDL AND SDLNet must be initialized before calls to functions in this library,
   because this library uses utility functions from the SDL library.
*/

/* DATA */

typedef enum {
	WEBSRV_INVALID,
	WEBSRV_URL,
	WEBSRV_MULTIPART
} WebSrvEncoding;

struct _WebSrvParams {
	char *name;		//the name in the form
	char *filename;	//for files in POST
	char *data;		//the data sent in the form
	int size;		//the length in bytes of the data
};

typedef struct _WebSrvParams WebSrvParams;

struct _WebSrvURL {
	char          *url;  		/* unparsed */
	char          *host;		/* host connected to */
	Uint16         port;		/* 80 if blank... */
	char          *path;		/* dirname, "/" is minimal */
	char          *file;		/* basename */
	WebSrvEncoding encoding;	/* from Content-type in header */
	WebSrvParams  *params;		/* from POST or GET form data */
	int            num_params;	/* length of params */
};

typedef struct _WebSrvURL WebSrvURL;

/*
struct _WebSrvClient;
typedef struct _WebSrvClient WebSrvClient;
typedef (int *WebSrvClientCallback)(WebSrvClient *client);
*/

struct _WebSrvClient {
	TCPsocket sock;			/* the client socket */
/*	WebSrvClientCallback callback;*/
	WebSrvURL url;			/* from GET */
	unsigned char *post;	/* POST data here (this is NULL terminated at [post_length]) */
	int post_length;		/* length of post (you can add one for the NULL I tack on...) */
	char *boundary;			/* boundary for multipart post */
	
	void *state;			/* user stuff goes here */
};

typedef struct _WebSrvClient WebSrvClient;

struct _WebSrv {
	TCPsocket sock;			/* the server socket */
	WebSrvClient **clients;	/* all connected clients are here */
	int num_clients;		/* length of clients */
	SDLNet_SocketSet set;	/* socket select set */

	void *state;			/* user stuff here, server wide */
};

typedef struct _WebSrv WebSrv;



/* FUNCTIONS */

/* Create a new WebSrv */
extern DECLSPEC WebSrv *WebSrv_Create();

/* start the WebSrv (on IPADDR_ANY)
 * port is the port to listen on
 */
extern DECLSPEC TCPsocket WebSrv_Open(WebSrv *websrv, Uint16 port);

/* poll for a connection
 * timeout is in milliseconds (0 = no wait)
 * returns 0 if nothing is ready,
 *        the number of sockets connecting (1),
 *        -1 on error
 * see also: comments on SDLNet_CheckSockets in SDL_net.h
 */
extern DECLSPEC int WebSrv_Poll(WebSrv *websrv, Uint32 timeout);

/*
/ * process all ready clients * /
extern DECLSPEC int WebSrv_RunAllClients(WebSrv websrv);

/ * process this client (if ready for writing) * /
extern DECLSPEC int WebSrv_RunClient(WebSrv websrv, WebSrvClient client);
*/

/* accept connection and parse HTTP and GET */
extern DECLSPEC WebSrvClient *WebSrv_Accept(WebSrv *websrv);

/* send standard HTTP responses 
 * returns 0 on success, -1 for error
 * 200 OK
 * 404 Error
 * etc...
 */
extern DECLSPEC int WebSrv_SendHTTPResponse(WebSrvClient *client, Uint32 code);

#define WebSrv_ClientSend(client, data, len) \
		SDLNet_TCP_Send(client->sock, data, len)
#define WebSrv_ClientSendString(client, str) \
		SDLNet_TCP_Send(client->sock, str, strlen(str))
/* stdarg version for writing to the client
 * max output size is 4095 bytes! (null at 4096th byte...always)
 * otherwise, functionally the same as printf
 */
extern DECLSPEC int WebSrv_ClientSendVString(WebSrvClient *client, const char *format, ...);

/* en/dehexify the %hex characters into a string
 * returns a new char * (which you should free when you're done with it)
 */
extern DECLSPEC char *WebSrv_enhex(const char *str);
extern DECLSPEC char *WebSrv_dehex(const char *str);

/* close the client connection 
 * free your client->state before calling this
 *      (or keep your state data pointer somewhere else ;)
 * this frees the clients data, so don't try using the client data after this!
 */
extern DECLSPEC void WebSrv_CloseClient(WebSrv *websrv, WebSrvClient *client);

/* stop the WebSrv 
 * this closes all open connections
 * free all your client->state(s) and websrv->state before calling this 
 *      (or keep your state data pointer(s) somewhere else ;)
 * you can still open the websrv again after this, as it is not free'd
 */
extern DECLSPEC void WebSrv_Close(WebSrv *websrv);

/* stop (if needed) and free the memory for this WebSrv
 * this is a final destructor, you have to create a new server to start again.
 */
extern DECLSPEC void WebSrv_Destroy(WebSrv *websrv);



/* INTERNALS (may be used, but not that handy for users) */

/* parse the url.url filling in the url struct */
extern DECLSPEC int WebSrv_ParseURL(WebSrvURL *url);
/* parse the GET(URL) style parameters from buf into url.params and url.num_params */
extern DECLSPEC void WebSrv_ParseParams(WebSrvURL *url, const char *buf);
/* parse the Multipart style parameters from client->post 
 *       into client->url.params and client->url.num_params
 */
extern DECLSPEC void WebSrv_ParseMultipart(WebSrvClient *client);

/* read a line from the connected client (used in POST type connections) */
extern DECLSPEC char *WebSrv_ClientReadLine(WebSrvClient *client);

/* free the URL struct (used in WebSrv_CloseClient) */
extern DECLSPEC void WebSrv_FreeURL(WebSrvURL *url);

#ifdef __cplusplus
} /*extern "C"*/
#endif
#include "close_code.h"

#endif /*WebSrv_h*/
