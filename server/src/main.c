#include <stdio.h>
#include <unistd.h>
#include <resolv.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "server.h"

int main(void)
{
  int sock_fd, newsock_fd, cli_len, n;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_fd < 0) {
    perror("Error opening socket");
    exit(1);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(4000);

  if (bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("Error binding socket");
    exit(1);
  }

  if (listen(sock_fd, 5) < 0) {
    perror("Error listening socket");
    exit(1);
  }

  cli_len = sizeof(cli_addr);

  newsock_fd = accept(sock_fd, (struct sockaddr *) &cli_addr, (socklen_t *) &cli_len);

  if (newsock_fd < 0) {
    perror("Error accepting socket");
    exit(1);
  }

  bzero(buffer,256);
  n = read(newsock_fd, buffer, 255);

  if (n < 0) {
    perror("Error reading the socket");
    exit(1);
  }

  printf("message = %s\n", buffer);

  n = write(newsock_fd,"I got your message",18);

  if (n < 0) {
    perror("Error writing in socket");
    exit(1);
  }

  return (0);
}
