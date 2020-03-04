#include <stdio.h>
#include <stdlib.h>
/* You will to add includes here */
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
// Included to get the support library
#include <calcLib.h>

#define PORT "9034"
#define BUF_SIZE 500

using namespace std;

int initCalcLib(void);
int randomInt(void);
double randomFloat(void);
char* randomType(void);

const double ROUNDING = 0.001;

int main(int argc, char* argv[]) {

	if (argc < 2)
	{
		printf("Too few arguments\nExpected: <port>");
		exit(0);
	}

	initCalcLib();

	struct addrinfo guide, * serverInfo, * p;
	uint16_t numBytes;
	uint16_t socketFileDescriptor;
	uint16_t listenFD;
	uint8_t returnValue;

	double fval[2];

	double result;
	double clientResult;

	guide.ai_family = AF_INET;
	guide.ai_socktype = SOCK_STREAM;
	guide.ai_flags = AI_PASSIVE;

	// getaddrinfo(IP, Port, Mall, Lagring), kommer få ut -1 om något gick fel, 0 ifall det gick rätt

	if ((returnValue = getaddrinfo(NULL, argv[1], &guide, &serverInfo)) != 0)
	{
		// %s = vill ha in en sträng efter ,
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(returnValue));
		exit(0);
	}

	for (p = serverInfo; p != NULL; p = p->ai_next)
	{
		if ((socketFileDescriptor = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1)
		{
			printf("listener: socket: %s\n", gai_strerror(errno));
			continue;
		}

		if (bind(sockFD, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockFD);
			printf("listener error: bind: %s\n", gai_strerror(errno));
			continue;
		}

		break;
	}


	// Om socket inte lyckas skapas.

	if (p == NULL)
	{
		printf("Could not create socket.");
		exit(0);
	}

}
