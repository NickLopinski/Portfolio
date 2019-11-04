#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage(char *argname)
{
	fprintf(stderr, "Usage: %s <requester thread count> <resolver thread count> <resolver output file name> <input files>\n", argname);
	printf("For extra help, use the -h flag\n");
	exit(1);
}

// void requester(queue *reqQ, queue *resQ)
// {
// 	char URL[1024];

// 	FILE *URLFile = NULL;
// 	char *payload = NULL;

// 	size_t payloadSize = 0;


// 	while(1)
// 	{
// 		fileName = popQueue(q);

// 		if(!fileName)
// 		{
// 			break;
// 		}

// 		fileName = (char*)fileName;

// 		URLFile = fopen(fileName, 'r');

// 		if(!URLFile)
// 		{
// 			fprintf(stderr, "The input file %s couldn't be read: %s\n", fileName, strerror(errno));
// 			continue;
// 		}

// 		while(fgets(URL, sizeof(URL), URLFile))
// 		{
// 			payloadSize = sizeof(strlen(URL)+1);

// 			payload = (char*)malloc(payloadSize);
// 			if(payload == NULL)
// 			{
// 				fprintf(stderr, "Error performing malloc for the contents of %s: %s\n", fileName, strerror(errno));
// 				exit(1);
// 			}
 
// 			memset(payload, '\0', sizeof(*payload));
// 			strncpy(payload, URL, payloadSize);

// 			pushQueue(resQ, payload);
// 		}

// 	}
// }

void resolver(queue *q)
{
	// Read the URLs from the resolver queue, perform a DNS query, and write the IPs to the output file
}

int main(int argc, char *argv[])
{
	queue nameFiles;
	//queue sharedArray;

	char *reqOut = NULL, *resOut = NULL;	// Name of resolver output file
	char input[2] = "\0\0";		// Character for y/n inputs
	int numReq = 0, numRes = 0, numInFile = 0;	// Requester thread, resolver thread, and input file count

	
	if(argc < 4)	// Check number of user arguments
	{
		usage(argv[0]);
	}
	else if(argc == 4)
	{
		fprintf(stderr, "No input files specified. Exiting...\n");
		return 0;
	}

	numReq = atoi(argv[1]);
	numRes = atoi(argv[2]);

	if(numReq == 0 || numRes == 0)	// Check if valid thread counts were given
	{
		printf("Invalid thread count given\n");
		usage(argv[0]);
	}

	resOut = argv[3];

	if(!access(resOut, F_OK))
	{
		printf("The output file %s already exists. Would you like to overwrite it? (y/n)\n>", resOut);
		scanf("%1s", input);
		if(*input == 'n' || *input == 'N') return 1;
	}

	numInFile = argc - 4;	// Should add subtraction of flags later on



	if(!initQueue(&nameFiles, numInFile, resOut))
	{
		return 1;
	}



	for(int i = argc-numInFile; i < argc; i++)
	{
		pushQueue(&nameFiles, &argv[i]);
	}

	for(int i = 0; i < nameFiles.size; i++)
	{
		printf("%s\n", (char*)popQueue(&nameFiles));
	}

	destroyQueue(&nameFiles);

	return 0;
}





