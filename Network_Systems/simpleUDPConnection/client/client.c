/*	
	Written by Nick Lopinski
	
	

	Client side code for a simple UDP connection that can share and edit files on the server with basic HTTP Methods
	Methods implemented:
	GET <filename>
	PUT <filename>
	DELETE <filename>
	LS (this is a custom method that displays the server's directory)

	To exit the program, type EXIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <dirent.h> //Included to access directory information
#include <sys/stat.h>   //Included to use stat() to check for directories


#define BUFFER_SIZE 1024


int main(int argc, char **argv)
{
	char buf[BUFFER_SIZE];

	struct addrinfo hint;
	struct addrinfo *result, *server;

	int sockfd, s;

	
	// Checks command line arguments
	if(argc != 3)
	{
		fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       	exit(EXIT_FAILURE);
	}

/*
	struct addrinfo {
	  int     ai_flags;          // AI_PASSIVE, AI_CANONNAME, ...
	  int     ai_family;         // AF_xxx
	  int     ai_socktype;       // SOCK_xxx
	  int     ai_protocol;       // 0 (auto) or IPPROTO_TCP, IPPROTO_UDP 

	  socklen_t  ai_addrlen;     // length of ai_addr
	  char   *ai_canonname;      // canonical name for nodename
	  struct sockaddr  *ai_addr; // binary address
	  struct addrinfo  *ai_next; // next structure in linked list
	};
*/

	// The hint structure specifies criteria that must be met in the connection

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // argv[1] is the hostname		argv[2] is the service port number
    // getaddrinfo will perform a DNS query for the specified location and store
    // all connections in a linked list saved in result
    s = getaddrinfo(argv[1], argv[2], &hint, &result);

    // Testing for successful DNS query
    if(s != 0)
    {
    	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    	exit(EXIT_FAILURE);
    }

    server = result;

    // Loops through the linked list from getaddrinfo to find an available connection
    while(server != NULL)
    {
    	sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

    	if(sockfd != -1)
    	{
    		if(connect(sockfd, server->ai_addr, server->ai_addrlen) == 0)
    			break;
    	}

    	close(sockfd);
    	server = server->ai_next;
    }

    if(server == NULL)
    {
    	fprintf(stderr, "Connection unavailable\n");
    	exit(EXIT_FAILURE);
    }

    // Frees the structs in result. They are no longer necessary because at this point
    // the program will exit from failure or we will have a connection to the server.
    freeaddrinfo(result);






    while(1)
    {
    	// Insert command code here
    }

	return 0;
}






