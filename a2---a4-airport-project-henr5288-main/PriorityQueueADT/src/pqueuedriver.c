/*******************************************************************************
 File name:  pqueuedriver.c
 Author:     Liam Henry
 Date:		   10.11.21
 Class:		   CS300
 Assignment: Priority Queue
 Purpose:    Driver for testing pqueue of generic elements
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pqueue.h"

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
void printList (ListPtr psList)
{
	PriorityQueueElement sElem;
	int size = lstSize(psList);
	int data, priority;

	printf("\n\nPriorityQueue: data, priority\n");

	lstFirst(psList);
	for (int i = 0; i < size; i++)
	{
		lstPeek(psList, &sElem, sizeof(PriorityQueueElement));
		priority = sElem.priority;
		data = *((int*) sElem.pData);
		printf("%d %d\n", data, priority);
		lstNext(psList);
	}
}

/**************************************************************************
 Function: 	 	main

 Description: test all the functionality of the priority queue

 Parameters:	none
 Returned:	 	none
 *************************************************************************/
int main () {

	int numVal = 7;
	int priority = 1;
	int qSize;
	int valBuffer;
	int prioBuffer;
	int priorityChange = 5;

	PriorityQueue sTheQueue;

	puts ("Driver Start");

	pqueueLoadErrorMessages();
	lstLoadErrorMessages();
	success("Loaded Error Messages");

	//Testing enqueue and terminate right after
	pqueueCreate(&sTheQueue);
	success("PQueue Created");
	pqueueTerminate(&sTheQueue);
	success("PQueue Terminated");

	//Testing that pqueueCreate creates an empty pqueue
	pqueueCreate(&sTheQueue);
	success("PQueue Created");
	//pqueueCreate(NULL);

	//Testing to make sure that the queue is empty and testing pqueueSize func
	assert(pqueueSize(&sTheQueue) == 0, "pqueue size is 0",
			"pqueue size is not 0");

	//Testing pqueueIsEmpty
	assert(pqueueIsEmpty(&sTheQueue), "pqueue is empty",
			"pqueue function failed");
	//pqueueIsEmpty(NULL);

	//Testing one pqueueEnqueue
	pqueueEnqueue(&sTheQueue, &numVal, sizeof(numVal), priority);
	success("Elements Enqueued");
	qSize = 1;
	//pqueueEnqueue(NULL, &numVal, sizeof(numVal), priority);
	//pqueueEnqueue(&sTheQueue, NULL, sizeof(numVal), priority);

	//Testing that pqueueSize is working with at least one element
	assert(pqueueSize(&sTheQueue) == qSize, "pqueue has correct num elements",
				"pqueue has incorrect num elements");

	//Testing pqueueTerminate with NULL
	pqueueTerminate(&sTheQueue);
	//pqueueTerminate(NULL);
	assert(pqueueIsEmpty(&sTheQueue), "pqueue is empty", "pq terminate failed");

	//Testing more than one pqueueEnqueue
	qSize = 5;
	pqueueCreate(&sTheQueue);
	success("PQueue Created");

	for (int i = 0; i < qSize; i++)
	{
		pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);
		++numVal;
		++priority;
	}
	success("Elements Enqueued");

	assert(pqueueSize(&sTheQueue) == qSize, "pqueue has correct num elements",
				"pqueue has incorrect num elements");

	pqueueTerminate(&sTheQueue);
	success("PQueue Terminated");

	//Testing pqueueEnqueue with different priorities
	pqueueCreate(&sTheQueue);
	qSize = 4;

	numVal = 7;
	priority = 1;
	pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);

	numVal = 8;
	priority = 0;
	pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);

	numVal = 9;
	priority = 2;
	pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);

	numVal = 10;
	priority = 1;
	pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);

	success("Elements Enqueued");

	assert(pqueueSize(&sTheQueue) == qSize, "pqueue has correct num elements",
			"pqueue has incorrect num elements");

	pqueueTerminate(&sTheQueue);
	success("PQueue Terminated");

	//Testing pqueueChangePriority
	pqueueCreate(&sTheQueue);
	success("PQueue Created");
	numVal = 10;
	priority = 0;
	qSize = 5;

	for (int i = 0; i < qSize; i++)
	{
		pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);
		numVal++;
		priority++;
	}
	success("Elements Enqueued");

	assert(pqueueSize(&sTheQueue) == qSize, "pqueue has correct num elements",
			"pqueue has incorrect num elements");

	//pqueueChangePriority(NULL, priorityChange);
	pqueueChangePriority(&sTheQueue, priorityChange);

	pqueueTerminate(&sTheQueue);
	success("PQueue Terminated");

	//Testing pqueueDequeue with one element
	pqueueCreate(&sTheQueue);
	success("PQueue Created");
	numVal = 6;
	priority = 1;
	qSize = 1;

	pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);
	success("Elements Enqueued");

	assert(pqueueSize(&sTheQueue) == qSize, "pqueue has correct num elements",
			"pqueue has incorrect num elements");

	pqueueDequeue(&sTheQueue, &valBuffer, sizeof(int), &prioBuffer);
	success("Element Dequeued");

	assert(pqueueIsEmpty(&sTheQueue), "pqueue is empty",
			"pqueue is not empty");

	pqueueTerminate(&sTheQueue);
	success("PQueue Terminated");

	//Testing pqueueDequeue with multiple elements
	pqueueCreate(&sTheQueue);
	success("PQueue Created");
	numVal = 7;
	priority = 0;
	qSize = 4;

	for (int i = 0; i < qSize; i++)
	{
		pqueueEnqueue(&sTheQueue, &numVal, sizeof(int), priority);
		numVal++;
		priority++;
	}
	success("Elements Enqueued");

	assert(pqueueSize(&sTheQueue) == qSize, "pqueue has correct num elements",
			"pqueue has incorrect num elements");

	for (int i = 0; i < qSize; i++)
	{
		pqueueDequeue(&sTheQueue, &valBuffer, sizeof(int), &prioBuffer);
	}
	success("Elements Dequeued");

	assert(pqueueIsEmpty(&sTheQueue), "pqueue is empty",
			"pqueue is not empty");

	pqueueTerminate(&sTheQueue);
	success("PQueue Terminated");

	puts("\nProgram End");

	return 0;
}

