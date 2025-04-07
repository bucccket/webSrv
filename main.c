#include "args.h"
#include "file.h"
#include "socket.h"
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 0x2000 // 8k buffer
static char buffer[BUFFER_SIZE];
static char httpHeader[] = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Connection: keep-alive\r\n\r\n";

int main(int argc, char **argv) {
  printf("Launched\n");
  parse_args(argc, argv);

  struct arguments args = get_args();

  int tcpSocket = 0;
  if (SocketOpen(&tcpSocket)) {
    exit(1);
  }

  // Main Loop
  for (;;) {
    struct sockaddr_in *hostAddr = get_hostAddr();
    int hostAddrLen = 0;
    int acceptedTcpSocket = accept(tcpSocket, (struct sockaddr *)hostAddr,
                                   (socklen_t *)&hostAddrLen);

    if (acceptedTcpSocket < 0) {
      perror("Webserver accept");
      return 4;
    }

    if (read(acceptedTcpSocket, buffer, BUFFER_SIZE) < 0) {
      perror("Webserver read");
      continue;
    }
    printf("%s\n", buffer);

    if (write(acceptedTcpSocket, httpHeader, strlen(httpHeader)) < 0) {
      perror("Webserver write");
      continue;
    }

    struct File file;
    if (openFile("./html/index.html", &file)) {
      exit(1);
    }
    if (write(acceptedTcpSocket, file.data, file.size) < 0) {
      perror("Webserver write");
      continue;
    }
    closeFile(&file);

    close(acceptedTcpSocket);
  }

  return 0;
}
