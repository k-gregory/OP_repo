#include "httprequest.h"

#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client {
  int fd;
  HTTPRequest* req;
  int can_write;
  int has_to_write;
} Client;

#define EVENT_POOL 20

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

const char* ans = "\
HTTP/1.0 200 OK\r\n\
Server: Apache\r\n\
Content-Language: uk\r\n\
Content-Type: text/html; charset=utf-8\r\n\
Content-Length: 1\r\n\
\r\n\
x";

int setnonblock(int fd){
  int flags;

  flags = fcntl(fd, F_GETFL);
  if(flags == -1){
    fputs("Can't get flags\n", stderr);
    exit(EXIT_FAILURE);
  }

  if(fcntl(fd,F_SETFL, flags | O_NONBLOCK) == -1){
    fputs("Can't set O_NONBLOCK\n",stderr);
    exit(EXIT_FAILURE);
  }

  return fd;
}

int create_in_listener_nb(int port){
  struct sockaddr_in addr;
  int fd;

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd == -1){
    fputs("Can't create socket\n", stderr);
    exit(EXIT_FAILURE);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
    fputs("Can't bind\n", stderr);
    exit(EXIT_FAILURE);
  }

  return fd;
}

int main(void){
  int listener_fd, epoll_fd;
  struct epoll_event ev;
  struct epoll_event events[EVENT_POOL];
  Client clients[40]; /*Todo: replace with map*/
  size_t n_clients;
  int got_events;

  n_clients = 0;

  listener_fd = create_in_listener_nb(8082);
  epoll_fd = epoll_create1(0);

  ev.events = EPOLLIN;
  ev.data.ptr = NULL;
  ev.data.fd = listener_fd;
  if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener_fd, & ev) == -1){
    fputs("Can't add listener to epoll", stderr);
    goto EXIT;
  }

  if(listen(listener_fd, SOMAXCONN) == 0){
    printf("Listening on fd %d\n", listener_fd);
  } else {
    perror("Listen");
    goto EXIT;
  };
  

  while(1){
    int i;
    got_events = epoll_wait(epoll_fd, events, EVENT_POOL, -1);
    for(i = 0; i < got_events; i++){
      if(events[i].data.fd == listener_fd &&
	  events[i].events & EPOLLIN){ /*Got accept*/
	Client* new_client;
	
	new_client = &clients[n_clients];
	new_client->fd = accept(listener_fd, NULL, NULL);
	setnonblock(new_client->fd);
	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.fd = new_client->fd;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_client->fd, &ev);
	printf("Connected %d\n", new_client->fd);
      } 
      else if(events[i].events & EPOLLIN) { /*Got something in*/
	ssize_t received;
	int sender_fd;
	char recv_buff[1024];
	sender_fd = events[i].data.fd;
	printf("Receiving from %d\n",sender_fd);
	received = recv(sender_fd, recv_buff, 1023, 0);
	recv_buff[received] = '\0';
	printf("Received %d bytes:\n%s\n", received,recv_buff);
      }
      else if(events[i].events & EPOLLOUT) { /*Can write to buffer*/
	printf("Can write to %d, events: %d\n",events[i].data.fd,events[i].events);
	send(events[i].data.fd,ans,strlen(ans),0);
      }
      else {
	puts("Some unknown shit happened");
	printf("FD: %d, events: %d\n",events[i].data.fd,events[i].events);
      }
    }
  }

#ifdef KILL_THIS_CODE
  while(1){
    int i;
    got_events = epoll_wait(epoll_fd, events, EVENT_POOL, -1);
    for(i =  0; i < got_events; i++){
      if(events[i].data.fd == listener_fd &&
	 events[i].events & EPOLLIN){ /* Got accept*/
	int accepted_fd;
	Client* new_client;
	accepted_fd = accept(listener_fd, NULL, NULL);
	printf("Connected %d\n", accepted_fd);
	setnonblock(accepted_fd);
	ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
	ev.data.fd = accepted_fd;
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, accepted_fd, &ev);

	new_client = &clients[n_clients++];
	new_client->fd = accepted_fd;
	new_client->req = http_request_new();
	new_client->can_write = 0;
	new_client->has_to_write = 0;
      } else if(events[i].events & EPOLLIN){ /*Got something from client*/
	HTTPRequest* req;
	ssize_t got_len;
	char got_buff[1000];
	req = http_request_new();
	
	printf("Got something from %d\n", events[i].data.fd);
	got_len = recv(events[i].data.fd, got_buff, LEN(got_buff) - 1, 0);
	got_buff[got_len] = '\0';
	http_request_parse_feed(req, got_buff, got_len);
	
	puts(http_request_get_uri(req));

	http_request_free(req);
      } else if(events[i].events & EPOLLOUT){ /*Can write to client*/
	size_t cid;
	Client* wc;
	puts("Can write");
	for(cid = 0; cid < n_clients; cid++)
	  if(events[i].data.fd == clients[cid].fd)
	    wc = &clients[cid];

	//	send(wc->fd,"Lel\r\n\r\n",7,0);
	send(wc->fd,ans,strlen(ans),0);
      }
    }
    printf("%d\n",got_events);
  }
#endif

 EXIT:
  close(listener_fd);
  close(epoll_fd);
  exit(EXIT_FAILURE);
}
