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

void requester(queue *reqQ, queue * resQ)
{
	FILE* URLFile;
	void* payload;

	while(1)
	{
		fileName = popQueue(q);

		if(!fileName)
		{
			break;
		}

		fileName = (char*)fileName;

		if(access(fileName, F_OK))
		{
			fprintf(stderr, "The input file %s couldn't be read\n", fileName);
			continue;
		}

		URLFile = fopen(fileName, 'r');

	}
}

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

	initQueue(&nameFiles, numInFile, resOut);

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





