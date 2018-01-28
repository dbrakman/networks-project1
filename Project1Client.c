/* Project1Client.c
 *  David Brakman
 */
#include "NetworkHeader.h"

/* function declarations */

int main (int argc, char *argv[]) {

  /* There are certainly slicker ways of doing this,
   * but I figured there's no need to make the code
   * any more confusing than it has to be at this point.
   */

  /* Argument parsing variables */
  char* firstName;
  char *lastName;
  char *serverHost = SERVER_HOST;
  unsigned short serverPort = atoi(SERVER_PORT);
  char *servPortString;
  char c;
  int i;

  if ((argc < 5) || (argc > 7)) {
    printf("Error: Usage Project0Client [-s <server IP>[:<port>]] -f <firstName> -l <lastName>\n");
    exit(1);
  }

  for (i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      c = argv[i][1];

      /* found an option, so look at next
       * argument to get the value of 
       * the option */
      switch (c) {
      case 'f':
	firstName = argv[i+1];
	break;
      case 'l':
	lastName = argv[i+1];
	break;
      case 's':
	serverHost = strtok(argv[i+1],":");
	if ((servPortString = strtok(NULL, ":")) != NULL) {
	  serverPort = htons(atoi(servPortString));
	} else {
      serverPort = atoi(SERVER_PORT);
    }
	break;
      default:
	break;
      }
    }
  }

  /* Your networking code starts here */
  const int ADDRESS_FAMILY = AF_INET;
  
  /* 1. Create Socket descriptor */
  int sock = socket(ADDRESS_FAMILY, SOCK_STREAM, IPPROTO_TCP);

  /* 2a. Prepare Address Structure */
  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));  // Initialize all fields (including unused) to 0
  servAddr.sin_family = ADDRESS_FAMILY;
  servAddr.sin_addr.s_addr = inet_addr(serverHost);
  servAddr.sin_port = serverPort;

  /* 2b. Connect to server */
  if (connect(sock, (const struct sockaddr*) &servAddr, sizeof(servAddr)) < 0){
      char msgBuf[SHORT_BUFFSIZE];
      sprintf(msgBuf, "Call on connect(%u, %p, %lu) failed\n", sock, &servAddr, sizeof(servAddr));
      DieWithError(msgBuf);
  }

  /* 3a. Create/Format HELLO message */
  char msgBuf[MAXLINE];
  int preTerminatorLen = sprintf(msgBuf, "%s HELLO %s %s\n", CUSTOM_PROTOCOL_VERSION, firstName,
                             lastName);
  
  /* 3b. Send HELLO message */
  int bytesSent = send(sock, (const void*) msgBuf, preTerminatorLen, 0);
  if (bytesSent != preTerminatorLen){
      DieWithError("send(%u, %p, %d, 0) sent %d bytes but expected to send %d bytes\n");
  }
  
  close(sock);    
  printf("%s %s, %s:%s (%hu)\n", firstName, lastName, serverHost, servPortString, serverPort);
  return 0;
}



