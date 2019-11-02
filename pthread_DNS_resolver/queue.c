#include "queue.h"


/*
 *	Function initQueue
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@params: elemCount is the number of array elements in the queue array.
 *	@params: fileName is the name of the log file to be opened for the queue.
 *			 If no log file name is specified, it should contain NULL.
 *	@return: N/A
 *
 *	Description: Initializes the queue structure by adding the memory for the 
 *				 queue array (defaulting all memory to zero), and setting all
 *				 structure members to their base values. 
 *				 This queue structure assumes you will be storing string 
 *				 pointers in the array.
 */
void initQueue(queue* q, int elemCount, void* fileName)
{
	q->array = malloc(sizeof(void*) * elemCount);
	if(q->array == NULL)
	{
		perror("Error performing malloc for queue");
		exit(1);
	}
	memset(q->array, 0, elemCount);

	q->front = 0;
	q->end = 0;
	q->size = elemCount;


	if((char*)fileName)	// Checks to see if fileName is valid
	{
		q->logFile = fopen((char*)fileName, "w");

		if(q->logFile == NULL)
		{
			fprintf(stderr, "Error opening file %s: %s\n", (char*)fileName, strerror(errno));
			exit(1);
		}
	}
	else
	{
		q->logFile = NULL;
	}


}


/*
 *	Function destroyQueue
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: N/A
 * 
 *	Description: Closes the file being held by the struct and frees any memory
 *				 allocated to the array or the struct.
 */
void destroyQueue(queue *q)
{	
	while(!isQueueEmpty(q))
	{
		popQueue(q);
	}


	free(q->array);

	if(q->logFile)
	{
		fclose(q->logFile);
	}

}


/*
 *	Function isQueueEmpty
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: returns a non-zero integer if the queue is empty or 0 if it isn't.
 *
 *	Description: Helper function used to check if the queue is empty.
 */
int isQueueEmpty(queue* q)
{
	if(q->front == q->end && !(q->array[q->front]))
	{
		return 1;
	}
	return 0;
}


/*
 *	Function isQueueFull
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: returns a non-zero integer if the queue is full or 0 if it isn't.
 *
 *	Description: Helper function used to check if the queue is full.
 */
int isQueueFull(queue* q)
{
	if(q->front == q->end && q->array[q->front])
	{
		return 1;
	}
	return 0;
}


/*
 *	Function popQueue
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: Returns the value stored in the address being popped from queue.
 *
 *	Description: Removes the value in the first position of the queue.
 */
void* popQueue(queue* q)
{	
	char* value;

	if(isQueueEmpty(q))
	{
		return NULL;
	}

	value = *((char**)(q->array[q->front]));
	// free(q->array[q->front]);	will need later once argv's are reconstructed for flags
	q->array[q->front] = NULL;
	q->front = ((q->front + 1) % q->size);

	return value;	// Returns the dereferenced value stored at address
}


/*
 *	Function pushQueue
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@params: value is a pointer to a string value.
 *	@return: Returns a non-zero interger if element is successfully pushed
 *			 or 0 if the queue is full.
 *
 *	Description: Appends the memory address of a string value to the queue.
 */
int pushQueue(queue* q, char** address)
{
	if(isQueueFull(q))
	{
		return 0;
	}

	q->array[q->end] = (void*)address;
	q->end = ((q->end + 1) % q->size);
	return 1;
}
