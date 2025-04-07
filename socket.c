#include "socket.h"

#include "args.h"
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct sockaddr_in hostAddr;

struct sockaddr_in *get_hostAddr(void) { return &hostAddr; }

int SocketOpen(int *tcpSocket) {

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("TCP Socket");
    return SOCKET_ERROR_SOCKET;
  }
  struct arguments args = get_args();
  if (args.useReuseAddr) {
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  }

  // Bind
  hostAddr.sin_family = AF_INET;
  hostAddr.sin_port = htons(args.port);
  hostAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sockfd, (struct sockaddr *)&hostAddr, sizeof(hostAddr))) {
    perror("TCP bind");
    return SOCKET_ERROR_BIND;
  }

  // Listen
  if (listen(sockfd, SOMAXCONN)) {
    perror("TCP listen");
    return SOCKET_ERROR_LISTEN;
  }
  printf("Listening on port %d\n", args.port);

  *tcpSocket = sockfd;

  return SOCKET_OK;
}
