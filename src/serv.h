/*
 Copyright (C) 2011 Cem Saldırım <bytesong@gmail.com>

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#ifndef _SERV_H
#define _SERV_H

#define SRV_EACCEPT   1
#define SRV_ESOCKET   2
#define SRV_ENOBLOCK  4
#define SRV_EEVINIT   8
#define SRV_EEVADD    16
#define SRV_ECLOSE    32
#define SRV_ESHUT     64

#define SRV_EVENTRD   1
#define SRV_EVENTWR   2

typedef struct _srv {
    int fdlistener, maxevents, backlog;
    int szreadbuf, szwritebuf;
    unsigned int newfd_event_flags;

    int (*hnd_read)(struct _srv *, int);
    int (*hnd_write)(struct _srv *, int);
    int (*hnd_accept)(struct _srv *, int, char *, int);
    int (*hnd_hup)(struct _srv *, int);
    int (*hnd_rdhup)(struct _srv *, int);
    int (*hnd_error)(struct _srv *, int, int);

    /* Pointer to the event_t structure declared in srv_run() */
    void *ev;
} srv_t;

int srv_init(srv_t *);

int srv_run(srv_t *, char *, char *);
int srv_read(int, char *, int);
int srv_write(int, char *, int);
int srv_readall(int, char *, int);
int srv_writeall(int, char *, int);

int srv_connect(char *, char *);
int srv_closeconn(int);

int srv_set_backlog(srv_t *, int);
int srv_set_maxevents(srv_t *, int);

int srv_notify_event(srv_t *, int, unsigned int);
int srv_newfd_notify_event(srv_t *, unsigned int);

int srv_hnd_read(srv_t *, int (*)(srv_t *, int));
int srv_hnd_write(srv_t *, int (*)(srv_t *, int));
int srv_hnd_accept(srv_t *, int (*)(srv_t *, int, char *, int));
int srv_hnd_hup(srv_t *, int (*)(srv_t *, int));
int srv_hnd_rdhup(srv_t *, int (*)(srv_t *, int));
int srv_hnd_error(srv_t *, int (*)(srv_t *, int, int));

int srv_get_listenerfd(srv_t *);

#endif
