#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct queue_s{
	FILE* logFile;	// Pointer to the output file assigned to the queue

	void** array;	// Array of pointers used for the queue

	int front, end;	// The front and back queue buffers, respectively
	int size;	// Length of the array

} queue;

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
void initQueue(queue* q, int elemCount, void* fileName);


/*
 *	Function destroyQueue
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: N/A
 * 
 *	Description: Closes the file being held by the struct and frees any memory
 *				 allocated to the array or the struct.
 */
void destroyQueue(queue* q);


/*
 *	Function isQueueEmpty
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: returns a non-zero integer if the queue is empty or 0 if it isn't.
 *
 *	Description: Helper function used to check if the queue is empty.
 */
int isQueueEmpty(queue* q);


/*
 *	Function isQueueFull
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: returns a non-zero integer if the queue is full or 0 if it isn't.
 *
 *	Description: Helper function used to check if the queue is full.
 */
int isQueueFull(queue* q);


/*
 *	Function popQueue
 *-----------------------------------------------------------------------------
 *	@params: q is a pointer to a queue structure.
 *	@return: Returns the value stored in the address being popped from queue.
 *
 *	Description: Removes the value in the first position of the queue.
 */
void* popQueue(queue* q);


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
int pushQueue(queue* q, char** address);

#endif