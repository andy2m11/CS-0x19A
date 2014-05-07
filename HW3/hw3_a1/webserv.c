#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <signal.h>

#include "server_constants.h"
////////////////////////////////////////////////////////
struct sigaction act;

static int from_signal;

///////////////////////////////////////

void servConn (int port) {

  int sd, new_sd;
  struct sockaddr_in name, cli_name;
  int sock_opt_val = 1;
  int cli_len;
  char data[BUFLEN];		/* Our receive data buffer. */
  int head_id, send_ok;
  struct sockaddr_storage client_addr;
  FILE *fp; 
  char request[BUFSIZ];
  
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("(servConn): socket() error");
    exit (-1);
  }

  if (setsockopt (sd, SOL_SOCKET, SO_REUSEADDR, (char *) &sock_opt_val,
		  sizeof(sock_opt_val)) < 0) {
    perror ("(servConn): Failed to set SO_REUSEADDR on INET socket");
    exit (-1);
  }

  name.sin_family = AF_INET;
  name.sin_port = htons (port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if (bind (sd, (struct sockaddr *)&name, sizeof(name)) < 0) {
    perror ("(servConn): bind() error");
    exit (-1);
  }

  listen (sd, 5);
  for (;;) {
      cli_len = sizeof (cli_name);
      new_sd = accept (sd, (struct sockaddr *) &cli_name, &cli_len);
      printf ("Assigning new socket descriptor:  %d\n", new_sd);
      
      if (new_sd < 0) {
	perror ("(servConn): accept() error");
	exit (-1);
      }
      
      fprintf(stderr,"====%s \n", data);    
      if (fork () == 0) {	// Child process.
	fp=fdopen(new_sd,"r");
	//read request
	fgets(request,BUFSIZ,fp);
	printf("request=%s\n",request);
	SD_parse(request,new_sd); //process client request
	fclose(fp);

	exit (0);
      } 
      close (new_sd);
  }

}


int main (int argc, char **argv) {
  
  int pnum;
  if (argc != 2) {
    perror("Port number required as the only argument");
    exit(-1);
  } 
  else {
    pnum = atoi(argv[1]);
  }

  servConn (pnum);		/* Server port. */

  return 0;
}

//////////////////////////////////////////////////////

