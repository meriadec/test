#include <stdio.h>
#include <string.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>

#include "server.h"

void err_exit (char * str)
{
  printf("> %s: %s\n", str, strerror(errno));
  exit(1);
}

int main(void)
{
  int soc;
  const struct sockaddr addr;

  if ((soc = socket(PF_LOCAL, SOCK_STREAM, 0)) == -1) { err_exit("socket"); }

  if (bind(soc, &addr, 0) == -1) { err_exit("bind"); }

  if (listen(soc, MAX_CON) == -1) { err_exit("listen"); }

  //int ret = select(soc, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout);
  return (0);
}
