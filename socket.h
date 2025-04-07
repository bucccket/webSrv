#pragma once

#define SOCKET_OK 0
#define SOCKET_ERROR_SOCKET 1
#define SOCKET_ERROR_BIND 2
#define SOCKET_ERROR_LISTEN 3
#define SOCKET_ERROR_ACCEPT 4
#define SOCKET_ERROR_READ 5
#define SOCKET_ERROR_WRITE 6

int SocketOpen(int *tcpSocket);
struct sockaddr_in *get_hostAddr(void);
