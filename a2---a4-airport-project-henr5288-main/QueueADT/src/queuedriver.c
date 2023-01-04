/*******************************************************************************
 File name:  queuedriver.c
 Author:     Liam Henry
 Date:		   10.30.21
 Class:		   CS300
 Assignment: Queue
 Purpose:    Driver for testing queue of generic elements
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/queue.h"

/**************************************************************************
 Function: 	 	success

 Description: print a success message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void success (char * szStr)
{
	printf ("SUCCESS: %s\n", szStr);
}

/**************************************************************************
 Function: 	 	failure

 Description: print a failure message

 Parameters:	szStr - the message to print
 Returned:	 	none
 *************************************************************************/
static void failure (char * szStr)
{
	printf ("FAILURE: %s\n", szStr);
	exit (EXIT_FAILURE);
}

/****************************************************************************
 Function: 	 	assert

 Description: if the expression is true, assert success; otherwise, assert
 	 	 	 	 	 	 	failure

 Parameters:	szStr - the message to print

 Returned:	 	none
 ****************************************************************************/
static void assert (bool bExpression, char *pTrue, char *pFalse)
{
	if (bExpression)
	{
		success (pTrue);
	}
	else
	{
		failure (pFalse);
	}
}

/**************************************************************************
 Function: 	 	printList

 Description: Prints the queue for simplicity

 Parameters:	psList - the list of data to be printed

 Returned:	 	none
 *************************************************************************/
//void printList (ListPtr psList)
//{
//	PriorityQueueElement sElem;
//	int size = lstSize(psList);
//	int data, priority;
//
//	printf("\n\nPriorityQueue: data, priority\n");
//
//	lstFirst(psList);
//	for (int i = 0; i < size; i++)
//	{
//		lstPeek(psList, &sElem, sizeof(PriorityQueueElement));
//		priority = sElem.priority;
//		data = *((int*) sElem.pData);
//		printf("%d %d\n", data, priority);
//		lstNext(psList);
//	}
//}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the queue

 Parameters:	none
 Returned:	 	none
 *************************************************************************/
int main ()
{
	int numVal = 8;
	int valBuffer;
	int qSize;

	Queue sTheQueue;

	puts("Diver Start");

	pqueueLoadErrorMessages();
	lstLoadErrorMessages();
	queueLoadErrorMessages();
	success("Loaded Error Messages");

	// Testing creation of queue and terminate right after each other
	//queueCreate(NULL);
	queueCreate(&sTheQueue);
	success("Queue Created");
	//queueTerminate(NULL);
	queueTerminate(&sTheQueue);
	success("Queue Terminated");

	// Testing if queueCreate makes an empty queue
	queueCreate(&sTheQueue);
	success("Queue Created");

	// Testing queueSize
	assert(queueSize(&sTheQueue) == 0, "Queue size is zero",
			"Queue is not zero");
	//queueSize(&sTheQueue);

	// Testing queueIsEmpty
	assert(queueIsEmpty(&sTheQueue), "Queue is empty", "Queue is not empty");
	//queueIsEmpty(NULL);

	// Testing one queueEnqueue
	queueEnqueue(&sTheQueue, &numVal, sizeof(int));
	success("Elements Enqueued");
	qSize = 1;

	//queueEnqueue(NULL, numVal, sizeof(int));
	//queueEnqueue(&sTheQueue, NULL, sizeof(int));

	assert(queueSize(&sTheQueue) == qSize, "Queue size is correct",
			"Queue size is incorrect");

	// Testing queuePeek with one element
	queuePeek(&sTheQueue, &valBuffer, sizeof(int));

	queueTerminate(&sTheQueue);

	// Testing more than one queueEnqueue
	queueCreate(&sTheQueue);
	success("Queue Created");
	qSize = 5;

	for (int i = 0; i < qSize; i++)
	{
		queueEnqueue(&sTheQueue, &numVal, sizeof(int));
		numVal++;
	}
	success("Elements Enqueued");

	assert(queueSize(&sTheQueue) == qSize, "Queue size is correct",
			"Queue size is incorrect");

	//printf("\n\n%d\n\n", queueSize(&sTheQueue));

	queueTerminate(&sTheQueue);
	success("Queue Terminated");

	// Testing queueDequeue with one element
	queueCreate(&sTheQueue);
	success("Queue Created");
	qSize = 1;
	numVal = 13;

	queueEnqueue(&sTheQueue, &numVal, sizeof(int));
	success("Element Enqueued");

	queueDequeue(&sTheQueue, &valBuffer, sizeof(int));
	success("Element Dequeued");
	assert(queueIsEmpty(&sTheQueue), "Queue is empty", "Queue is not empty");

	assert(valBuffer == numVal, "Dequeue value correct",
			"Dequeue value incorrect");

	queueTerminate(&sTheQueue);
	success("Queue Terminated");

	// Testing queueDequeue with multiple elements
	queueCreate(&sTheQueue);
	success("Queue Created");
	qSize = 8;
	numVal = 1;

	for (int i = 0; i < qSize; i++)
	{
		queueEnqueue(&sTheQueue, &numVal, sizeof(int));
		numVal++;
	}
	success("Elements Enqueued");

	assert(queueSize(&sTheQueue) == qSize, "Queue size is correct",
			"Queue size is incorrect");

	for (int i = 0; i < qSize; i++)
	{
		queueDequeue(&sTheQueue, &valBuffer, sizeof(int));
	}
	success("Elements Dequeued");

	assert(queueIsEmpty(&sTheQueue), "Queue is empty", "Queue is not empty");

	queueTerminate(&sTheQueue);
	success("Queue Terminated");

	puts("Driver End");

	return 0;
}
