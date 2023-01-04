/**************************************************************************
 File name:  queue.c
 Author:     Liam Henry
 Date:		 	 10.30.16
 Class:		   CS300
 Assignment: Queue
 Purpose:    Implementation for a queue of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/queue.h"
#include "../../PriorityQueueADT/include/pqueue.h"

char gszQErrors[NUMBER_OF_Q_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the list error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	lstLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void queueLoadErrorMessages ()
{
	LOAD_Q_ERRORS
}

/**************************************************************************
 Function: 	 	queueCreate

 Description:	creates the queue by creating the pqueue

 Parameters:	psQueue - pointer to a queue

 Returned:	 	None
 *************************************************************************/
void queueCreate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueCreate", ERROR_NO_Q_CREATE);
	}

	pqueueCreate(&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueTerminate

 Description: terminates the queue

 Parameters:	psQueue - pointer to a queue

 Returned:	 	None
 *************************************************************************/
void queueTerminate (QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueTerminate", ERROR_NO_Q_TERMINATE);
	}
	pqueueTerminate(&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueSize

 Description: returns the number of elements in the queue

 Parameters:	psQueue - pointer to a pqueue

 Returned:	 	int
 *************************************************************************/
int queueSize (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueSize", ERROR_INVALID_Q);
	}
	return pqueueSize(&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueIsEmpty

 Description: If Q is empty, return true; otherwise, return false

 Parameters:	psQueue - pointer to a pqueue

 Returned:	 	bool
 *************************************************************************/
bool queueIsEmpty (const QueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("queueIsEmpty", ERROR_INVALID_Q);
	}
	return pqueueIsEmpty(&psQueue->sTheQueue);
}

/**************************************************************************
 Function: 	 	queueEnqueue

 Description: enqueue a queue element

 Parameters:	psQueue   - pointer to a queue
 	 	 	 	 	 	  *pBuffer  - pointer to data
 	 	 	 	 	 	  size 		  - size of data being passed in

 Returned:	 	None
 *************************************************************************/
void queueEnqueue (QueuePtr psQueue, const void *pBuffer, int size)
{
	if (NULL == psQueue)
	{
		processError ("queueEnqueue", ERROR_INVALID_Q);
	}
	if (pBuffer == NULL)
	{
		processError ("queueEnqueue", ERROR_NULL_Q_PTR);
	}

	int priority = 0;

	pqueueEnqueue(&psQueue->sTheQueue, pBuffer, size, priority);
}

/**************************************************************************
 Function: 	 	queueDequeue

 Description: Remove the element from the front of a non-empty queue

 Parameters:	psQueue   - pointer to a queue
 	 	 	 	 	 	  *pBuffer  - pointer to data
 	 	 	 	 	 	  size 		  - size of data being passed in

 Returned:	 	data value from the element that is deleted
 *************************************************************************/
void *queueDequeue (QueuePtr psQueue, void *pBuffer, int size)
{
	if (NULL == psQueue)
	{
		processError ("queueDequeue", ERROR_INVALID_Q);
	}
	if (pBuffer == NULL)
	{
		processError ("queueDequeue", ERROR_NULL_Q_PTR);
	}
	if (pqueueIsEmpty(&psQueue->sTheQueue))
	{
		processError ("queueDequeue", ERROR_EMPTY_Q);
	}

	int priority;
	pqueueDequeue(&psQueue->sTheQueue, pBuffer, size, &priority);

	return pBuffer;
}

/**************************************************************************
 Function: 	 	queuePeek

 Description: The value of the first element is returned through
							the argument list

 Parameters:	psQueue   - pointer to a pqueue
 	 	 	 	 	 	  *pBuffer  - pointer to data
 	 	 	 	 	 	  size 		  - size of data being passed in

 Returned:	 	value of the element
 *************************************************************************/
void *queuePeek (QueuePtr psQueue, void *pBuffer, int size)
{
	if (NULL == psQueue)
	{
		processError ("queuePeek", ERROR_INVALID_Q);
	}
	if (pBuffer == NULL)
	{
		processError ("queuePeek", ERROR_NULL_Q_PTR);
	}
	if (pqueueIsEmpty(&psQueue->sTheQueue))
	{
		processError ("queuePeek", ERROR_EMPTY_Q);
	}

	int priority;
	pqueuePeek (&psQueue->sTheQueue, pBuffer, size, &priority);

	return pBuffer;
}

