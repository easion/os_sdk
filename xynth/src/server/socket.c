/***************************************************************************
    begin                : Sun Feb 2 2003
    copyright            : (C) 2003 - 2007 by Alper Akcan
    email                : distchx@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of the  *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include <sys/stat.h>
#include "../lib/xynth_.h"
#include "server.h"

#if !defined(IPC_UDS) && !defined(IPC_TCP) && !defined(IPC_PIPE)
	#error "You must select at least one of IPC_UDS, IPC_TCP, IPC_PIPE"
#endif

#define s_socket_recv(a, b, c)	if (s_socket_api_recv(a, b, c) != c) { return -1; }
#define s_socket_send(a, b, c)	if (s_socket_api_send(a, b, c) != c) { return -1; }

int s_server_socket_listen_new (int id)
{
	int i;
	int j;
	s_pollfd_t *ip;
	s_pollfd_t *jp;

	s_socket_recv(server->client[id].soc, &server->client[id].type, sizeof(S_WINDOW));
	s_socket_recv(server->client[id].soc, &server->client[id].pid, sizeof(int));
	s_socket_recv(server->client[id].soc, &server->client[id].buf, sizeof(s_rect_t));
	/* just to close childs before their parent, socket listen order is in pollfds list order.
	 */
	if (server->client[id].pid >= 0) {
		ip = s_pollfd_find(server->window, server->client[id].soc);
		jp = s_pollfd_find(server->window, server->client[server->client[id].pid].soc);
		if ((ip != NULL) && (jp != NULL)) {
			i = s_list_get_pos(server->window->pollfds->list, ip);
			j = s_list_get_pos(server->window->pollfds->list, jp);
			if (j < i) {
				s_list_remove(server->window->pollfds->list, i);
				s_list_add(server->window->pollfds->list, ip, j);
			}
		}
	}
	s_server_window_new(id);
	s_socket_send(server->client[id].soc, &server->client[id].buf, sizeof(s_rect_t));
	s_socket_send(server->client[id].soc, &server->client[id].win, sizeof(s_rect_t));

	return 0;
}

int s_server_socket_listen_display (int id)
{
	s_soc_data_display_t *data;
	data = (s_soc_data_display_t *) s_calloc(1, sizeof(s_soc_data_display_t));

	data->bytesperpixel = server->window->surface->bytesperpixel;
	data->bitsperpixel = server->window->surface->bitsperpixel;
	data->colors = server->window->surface->colors;
	data->blueoffset = server->window->surface->blueoffset;
	data->greenoffset = server->window->surface->greenoffset;
	data->redoffset = server->window->surface->redoffset;
	data->bluelength = server->window->surface->bluelength;
	data->greenlength = server->window->surface->greenlength;
	data->redlength = server->window->surface->redlength;
	data->bluemask = server->window->surface->bluemask;
	data->greenmask = server->window->surface->greenmask;
	data->redmask = server->window->surface->redmask;

	data->linear_buf = (unsigned int) server->window->surface->linear_buf;
	data->matrix = (unsigned int) server->window->surface->matrix;

	data->linear_mem_size = server->window->surface->linear_mem_size;
	data->linear_mem_base = server->window->surface->linear_mem_base;
	data->linear_buf_width = server->window->surface->linear_buf_width;
	data->linear_buf_pitch = server->window->surface->linear_buf_pitch;
	data->linear_buf_height = server->window->surface->linear_buf_height;
	data->shm_mid = server->window->surface->shm_mid;
	data->id = id;

	data->shm_sid = server->window->surface->shm_sid;
	data->need_expose = server->window->surface->need_expose;

	strncpy(data->device, server->driver->device, S_FNAME_MAX);

	//printf("s_server_socket_listen_parse: do SOC_DATA_DISPLAY\n");



	if (s_socket_api_send(server->client[id].soc, data, sizeof(s_soc_data_display_t)) != sizeof(s_soc_data_display_t)) {
	printf("s_server_socket_listen_display: send SOC_DATA_DISPLAY error\n");
		s_free(data);
		return -1;
	}

	s_free(data);
	return 0;
}

int s_server_socket_listen_configure (int id)
{
	int i;
	int j = 0;
        s_soc_data_configure_t *data;
        data = (s_soc_data_configure_t *) s_calloc(1, sizeof(s_soc_data_configure_t));

	if (s_socket_api_recv(server->client[id].soc, data, sizeof(s_soc_data_configure_t)) != sizeof(s_soc_data_configure_t)) {
		s_free(data);
		return -1;
	}

	server->client[id].resizeable = data->resizeable;
	server->client[id].alwaysontop = data->alwaysontop;
	server->client[id].cursor = data->cursor;
/*	server->client[id].min_w = data->min_w;
	server->client[id].min_h = data->min_h;
	server->client[id].max_w = data->max_w;
	server->client[id].max_h = data->max_h;*/

	if (data->form & WINDOW_NOFORM) {
		data->rnew.x += (server->client[id].win.x - server->client[id].buf.x);
		data->rnew.y += (server->client[id].win.y - server->client[id].buf.y);
		data->rnew.w += (server->client[id].win.w - server->client[id].buf.w);
		data->rnew.h += (server->client[id].win.h - server->client[id].buf.h);
	}

	if (strlen(data->title) > 0) {
		if ((server->client[id].title.str == NULL) ||
		    (j = strcmp(server->client[id].title.str, data->title)) != 0) {
			s_free(server->client[id].title.str);
			server->client[id].title.str = strdup(data->title);
			s_server_window_title(id, server->client[id].title.str);
			s_server_window_calculate(id);
		}
	}
	
	s_server_window_move_resize(id, &(data->rnew));

	if (j) {
		if (!(server->client[id].type & WINDOW_TEMP)) {
			for (i = 0; i < S_CLIENTS_MAX; i++) {
				if (server->client[i].type & WINDOW_DESKTOP) {
					s_server_socket_request(SOC_DATA_DESKTOP, i);
				}
			}
		}
	}

	s_free(data);
	return 0;
}

int s_server_socket_listen_stream (int id)
{
	s_soc_data_stream_t *data;
	data = (s_soc_data_stream_t *) s_calloc(1, sizeof(s_soc_data_stream_t));
	if (s_socket_api_recv(server->client[id].soc, data, sizeof(s_soc_data_stream_t)) != sizeof(s_soc_data_stream_t)) {
		s_free(data);
		return -1;
	}
	if (data->blen != 0) {
		data->buf = (char *) s_malloc(data->blen + 1);
		if (s_socket_api_recv(server->client[id].soc, data->buf, data->blen) != data->blen) {
			s_free(data->buf);
			s_free(data);
			return -1;
		}
		bpp_putbox_o(server->window->surface, id, data->rect.x, data->rect.y, data->rect.w, data->rect.h, data->buf, data->rect.w);
		s_free(data->buf);
	}
	s_server_surface_update(&(data->rect));
	s_free(data);
	return 0;
}

int s_server_socket_listen_close_server (int id)
{
	if (server->client[id].type & WINDOW_DESKTOP) {
		s_server_quit(server->window);
	}
	return 0;
}

int s_server_socket_listen_close (int id)
{
	s_server_window_close_id(id);
	return 0;
}

int s_server_socket_listen_show (int id)
{
	int i;
	int rid = -1;
	s_soc_data_show_t *data;
	data = (s_soc_data_show_t *) s_calloc(1, sizeof(s_soc_data_show_t));
	if (s_socket_api_recv(server->client[id].soc, data, sizeof(s_soc_data_show_t)) != sizeof(s_soc_data_show_t)) {
		s_free(data);
		return -1;
	}

	if (data->title[0] != '\0') {
		for (i = 0; i < S_CLIENTS_MAX; i++) {
			if (server->client[i].title.str != NULL &&
			    strcmp(server->client[i].title.str, data->title) == 0) {
				rid = i;
			}
		}
	} else {
		rid = data->id;
	}

	if (rid >= 0) {
		if (data->show == -1) {
			s_server_window_hide_id(rid);
		} else {
			s_server_pri_set(SURFACE_FOCUS, rid);
		}
	}
	s_free(data);
	return 0;
}

int s_server_socket_listen_event (int id)
{
	s_video_input_data_keybd_t keybd;
	s_soc_data_event_t *data;
	data = (s_soc_data_event_t *) s_calloc(1, sizeof(s_soc_data_event_t));
	if (s_socket_api_recv(server->client[id].soc, data, sizeof(s_soc_data_event_t)) != sizeof(s_soc_data_event_t)) {
		s_free(data);
		return -1;
	}
	server->window->event->type = REMOTE_EVENT;
	switch (data->type & (KEYBD_EVENT | MOUSE_EVENT)) {
		case KEYBD_EVENT:
			memset(&keybd, 0, sizeof(s_video_input_data_keybd_t));
			keybd.ascii = data->keybd.ascii;
			keybd.button = data->keybd.button;
			keybd.keycode = data->keybd.keycode;
			keybd.scancode = data->keybd.keycode;
			keybd.state = data->type & (KEYBD_PRESSED | KEYBD_RELEASED);
			s_server_event_parse_keyboard(&keybd);
			s_server_event_changed();
			break;
	}
	s_free(data);
	return 0;
}

int s_server_socket_listen_window_close (int soc)
{
        s_pollfd_t *pfd;
	int id = s_server_id_find(soc);

	s_socket_api_close(soc);
	if (id >= 0) {
		if ((pfd = s_pollfd_find(server->window, soc)) == NULL) {
			debugf(DSER | DFAT, "Could not find any pollfd entry for Client[%d].soc[%d]", id, soc);
		}
		s_pollfd_del(server->window, pfd);
		s_pollfd_uninit(pfd);

		debugf(DSER, "Client[%d] closed the connection", id);

		s_server_id_del(id);
		s_server_pri_del(id);
	}

	return 0;
}

int s_server_socket_listen_parse (int soc)
{
	S_SOC_DATA soc_data;
	struct pollfd pollfd;
	int id = s_server_id_find(soc);

	if (id == -1) {
		return -1;
	}

	pollfd.fd = soc;
	pollfd.events = POLLIN;
	pollfd.revents = 0;

	if ((s_socket_api_poll(&pollfd, 1, 0) <= 0) ||
	    (pollfd.revents != POLLIN)) {
		goto end;
	}

	if (s_socket_api_recv(soc, &soc_data, sizeof(soc_data)) != sizeof(soc_data)) {
		return -1;
	}

	switch (soc_data) {
		case SOC_DATA_NEW:
			return s_server_socket_listen_new(id);
		case SOC_DATA_SHOW:
			return s_server_socket_listen_show(id);
		case SOC_DATA_DISPLAY:
			//printf("s_server_socket_listen_parse: got SOC_DATA_DISPLAY\n");
			return s_server_socket_listen_display(id);
		case SOC_DATA_FORMDRAW:
			s_server_window_form(id, &server->client[id].win);
			return 0;
		case SOC_DATA_CONFIGURE:
			return s_server_socket_listen_configure(id);
		case SOC_DATA_EXPOSE:
			return s_server_socket_listen_stream(id);
		case SOC_DATA_EVENT:
			return s_server_socket_listen_event(id);
		case SOC_DATA_CLOSE:
			return s_server_socket_listen_close(id);
			break;
		case SOC_DATA_CLOSE_SERVER:
			return s_server_socket_listen_close_server(id);
		case SOC_DATA_DESKTOP:
		case SOC_DATA_NOTHING:
			break;
	}

end:	return 0;
}

int s_server_socket_client_in_f (s_window_t *window, s_pollfd_t *pfd)
{
	return s_server_socket_listen_parse(pfd->fd);
}

int s_server_socket_client_ierr_f (s_window_t *window, s_pollfd_t *pfd)
{
	return s_server_socket_listen_window_close(pfd->fd);
}

int s_server_socket_listen_accept (int soc)
{
        int s;
	int id;
	s_pollfd_t *pfd;
	s_sockaddr_t client;
	socklen_t client_len = sizeof(client);

	s = s_socket_api_accept(soc, (s_sockaddr_t *) &client, &client_len);
	if (s < 0) {
		debugf(DSER | DSYS, "Can not accept new connection %d",soc);
		exit(1);
		return -1;
	}

	debugf(DSER, "Accepted new connection");

	id = s_server_id_get();
	if (id != -1) {
		server->client[id].soc = s;
		server->client[id].pid = -1;
		s_pollfd_init(&pfd);
		pfd->fd = s;
		pfd->pf_in = s_server_socket_client_in_f;
		pfd->pf_err = s_server_socket_client_ierr_f;
		s_pollfd_add(server->window, pfd);
		debugf(DSER, "Client[%d] connection established", id);
		return 0;
	}

	debugf(DSER, "MAX amounts of clients reached, closing requesting socket");
	s_server_socket_listen_window_close(s);

	return -1;
}

int s_server_socket_request_event (int id)
{
	s_soc_data_event_t *data;
	data = (s_soc_data_event_t *) s_calloc(1, sizeof(s_soc_data_event_t));

	data->type = server->window->event->type;
	data->mouse = *(server->window->event->mouse);
	data->keybd = *(server->window->event->keybd);
	//printf("s_server_socket_request_event go line %d,data->type=%x\n",__LINE__,data->type);
	
	if (s_socket_api_send(server->client[id].soc, data, sizeof(s_soc_data_event_t)) != sizeof(s_soc_data_event_t)) {
		s_free(data);
		return -1;
	}

	s_free(data);
	return 0;
}

int s_server_socket_request_close (int id)
{
	debugf(DSER, "Close request sent to Client[%d]", id);
	return 0;
}

int s_server_socket_request_expose (int id, s_rect_t *changed)
{
	s_soc_data_expose_t *data;
	data = (s_soc_data_expose_t *) s_calloc(1, sizeof(s_soc_data_expose_t));

	data->pri = s_server_id_pri(id);
	data->buf = server->client[id].buf;
	data->win = server->client[id].win;
	data->changed = *changed;
	data->linear_buf_width = server->window->surface->linear_buf_width;
	data->linear_buf_pitch = server->window->surface->linear_buf_pitch;
	data->linear_buf_height = server->window->surface->linear_buf_height;

	if (s_socket_api_send(server->client[id].soc, data, sizeof(s_soc_data_expose_t)) != sizeof(s_soc_data_expose_t)) {
		s_free(data);
		return -1;
	}

	s_free(data);
	return 0;
}

int s_server_socket_request_desktop (int id)
{
	int i;
	int p;
	s_soc_data_desktop_t *data;
	
	data = (s_soc_data_desktop_t *) s_calloc(1, sizeof(s_soc_data_desktop_t));

	for (i = 0; i < S_CLIENTS_MAX; i++) {
		if ((p = s_server_id_pri(i)) >= 0) {
			if (!(server->client[i].type & WINDOW_TEMP)) {
				data->client[data->count].id = i;
				data->client[data->count].pri = p;
				strcpy(data->client[data->count].title, server->client[i].title.str);
				data->count++;
			}
		}
	}
	if (s_socket_api_send(server->client[id].soc, data, sizeof(s_soc_data_desktop_t)) != sizeof(s_soc_data_desktop_t)) {
		s_free(data);
		return -1;
	}
	free(data);

	return 0;
}

int s_server_socket_request (S_SOC_DATA req, int id, ...)
{
	va_list ap;
	int ret = 0;
	s_rect_t *changed;
	struct pollfd pollfd;


	if (server->window->running <= 0) {
	printf("s_server_socket_request error line %d\n",__LINE__);
		return -1;
	}
	if (id < 0 || id >= S_CLIENTS_MAX) {
	printf("s_server_socket_request error line %d\n",__LINE__);
		return -1;
	}
        if (server->client[id].soc < 0) {
	printf("s_server_socket_request error line %d\n",__LINE__);
        	return -1;
        }
	pollfd.fd = server->client[id].soc;
	pollfd.events = POLLOUT;
	pollfd.revents = 0;

	if (s_socket_api_poll(&pollfd, 1, 1000) <= 0) {
		goto err;
	}
	if (pollfd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
		/* socket_listen will take over
		   we dont handle here, to avoid the recursiveness of pri_set_
		 */
	printf("s_server_socket_request error line %d\n",__LINE__);
		return -1;
	}
	if (pollfd.revents != POLLOUT) {
err:		debugf(DSER, "Error occured when requesting (%d) from client[%d]. Closing it [revents: %d]", req, id, pollfd.revents);
		s_server_socket_listen_window_close(server->client[id].soc);
	printf("s_server_socket_request error line %d\n",__LINE__);
		return -1;
	}

	if (s_socket_api_send(server->client[id].soc, &req, sizeof(req)) != sizeof(req)) {
	printf("s_server_socket_request error line %d\n",__LINE__);
		return -1;
	}
	switch (req) {
		case SOC_DATA_EVENT:
			ret = s_server_socket_request_event(id);
			break;
		case SOC_DATA_CLOSE:
			ret = s_server_socket_request_close(id);
			break;
		case SOC_DATA_EXPOSE:
			va_start(ap, id);
			changed = (s_rect_t *) va_arg(ap, s_rect_t *);
			ret = s_server_socket_request_expose(id, changed);
			va_end(ap);
			break;
		case SOC_DATA_DESKTOP:
			ret = s_server_socket_request_desktop(id);
			break;
		case SOC_DATA_NEW:
		case SOC_DATA_SHOW:
		case SOC_DATA_DISPLAY:
		case SOC_DATA_NOTHING:
		case SOC_DATA_FORMDRAW:
		case SOC_DATA_CONFIGURE:
		case SOC_DATA_CLOSE_SERVER:
			break;
	}

	return ret;
}

int s_server_socket_uninit (s_window_t *window, s_pollfd_t *pfd)
{
	s_socket_api_close(pfd->fd);
#if defined(IPC_UDS)
	unlink(S_SERVER_SOC_NAME);
#endif
	return 0;
}

int s_server_socket_in_f (s_window_t *window, s_pollfd_t *pfd)
{
	return s_server_socket_listen_accept(pfd->fd);
}

int s_server_socket_ierr_f (s_window_t *window, s_pollfd_t *pfd)
{
        return 0;
}

int s_server_socket_init_uds (void)
{
#if defined(IPC_UDS)
	int fd;
	struct sockaddr_un soc = {AF_UNIX, S_SERVER_SOC_NAME};
	int len = sizeof(soc.sun_family) + strlen(soc.sun_path);

	fd = s_socket_api_socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd < 0) {
		debugf(DSER | DSYS | DFAT, "Can not open listening socket");
	}
	if (s_socket_api_bind(fd, (s_sockaddr_t *) &soc, len) == -1) {
		debugf(DSER | DSYS | DFAT, "Can not bind listening socket");
	}
	if (s_socket_api_listen(fd, S_CLIENTS_MAX) == -1) {
		debugf(DSER | DSYS | DFAT, "Listen socket");
	}
	return fd;
#else
	return -1;
#endif
}

int s_server_socket_init_tcp (void)
{
#if defined(IPC_TCP)
	int fd;
	int len;
	struct sockaddr_in soc;

	len = sizeof(soc);
        soc.sin_family = AF_INET;
	soc.sin_addr.s_addr = htonl(S_SERVER_SOC_ALLOW);
	soc.sin_port = htons(S_SERVER_SOC_PORT);

	fd = s_socket_api_socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		debugf(DSER | DSYS | DFAT, "Can not open listening socket");
	}
	if (s_socket_api_bind(fd, (s_sockaddr_t *) &soc, len) == -1) {
		debugf(DSER | DSYS | DFAT, "Can not bind listening socket");
	}
	if (s_socket_api_listen(fd, S_CLIENTS_MAX) == -1) {
		debugf(DSER | DSYS | DFAT, "Listen socket");
	}
	return fd;
#else
	return -1;
#endif
}

int s_server_socket_init_pipe (void)
{
#if defined(IPC_PIPE)
	int fd;
	s_sockaddr_t soc = {AF_PIPE, S_SERVER_SOC_PIPE};
	int len = sizeof(soc.sa_family) + strlen(soc.sa_addr);

	fd = s_socket_api_socket(AF_PIPE, SOCK_STREAM, 0);
	if (fd < 0) {
		debugf(DSER | DSYS | DFAT, "Can not open listening socket");
	}
	if (s_socket_api_bind(fd, (s_sockaddr_t *) &soc, len) == -1) {
		debugf(DSER | DSYS | DFAT, "Can not bind listening socket");
	}
	if (s_socket_api_listen(fd, S_CLIENTS_MAX) == -1) {
		debugf(DSER | DSYS | DFAT, "Listen socket");
	}
	return fd;
#else
	return -1;
#endif
}

void s_server_socket_init (void)
{
	int fd[3];
	s_pollfd_t *pfd;
	
	if (s_socket_api_init()) {
		debugf(DSER | DSYS | DFAT, "Sockets API initilization failed!");
	}

	fd[0] = s_server_socket_init_uds();
	fd[1] = s_server_socket_init_tcp();
	fd[2] = s_server_socket_init_pipe();

	if ((fd[0] < 0) && (fd[1] < 0) && (fd[2] < 0)) {
		debugf(DSER | DFAT, "Could not open any listening socket");
	}
	s_socket_init_wakeup(server->window);
	if (fd[0] >= 0) {
		debugf(DSER, "Listening on local socket : %s", S_SERVER_SOC_NAME);
		s_pollfd_init(&pfd);
		pfd->fd = fd[0];
		pfd->pf_in = s_server_socket_in_f;
		pfd->pf_err = s_server_socket_ierr_f;
		pfd->pf_close = s_server_socket_uninit;
		s_pollfd_add(server->window, pfd);
	}
	if (fd[1] >= 0) {
		debugf(DSER, "Listening on TCP : %s:%d", S_SERVER_SOC_ADDR, S_SERVER_SOC_PORT);
		s_pollfd_init(&pfd);
		pfd->fd = fd[1];
		pfd->pf_in = s_server_socket_in_f;
		pfd->pf_err = s_server_socket_ierr_f;
		pfd->pf_close = s_server_socket_uninit;
		s_pollfd_add(server->window, pfd);
	}
	if (fd[2] >= 0) {
		debugf(DSER, "Listening on PIPE : %s", S_SERVER_SOC_PIPE);
		s_pollfd_init(&pfd);
		pfd->fd = fd[2];
		pfd->pf_in = s_server_socket_in_f;
		pfd->pf_err = s_server_socket_ierr_f;
		pfd->pf_close = s_server_socket_uninit;
		s_pollfd_add(server->window, pfd);
	}
}
