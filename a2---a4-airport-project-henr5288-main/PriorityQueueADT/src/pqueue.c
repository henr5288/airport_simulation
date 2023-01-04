/**************************************************************************
 File name:  pqueue.c
 Author:     Liam Henry
 Date:		 	 10.11.16
 Class:		   CS300
 Assignment: Priority Queue
 Purpose:    Implementation for a queue of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/pqueue.h"
#include "../../ListADT/include/list.h"

char gszPQErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 errorCode 	    - identifies the list error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszPQErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	lstLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void pqueueLoadErrorMessages ()
{
	LOAD_PQ_ERRORS
}

/**************************************************************************
 Function: 	 	pqueueCreate

 Description:	creates the priority queue by creating the list

 Parameters:	psQueue - pointer to a pqueue

 Returned:	 	None
 *************************************************************************/
void pqueueCreate (PriorityQueuePtr psQueue)
{
	if (NULL == psQueue) {
		processError ("psqueueCreate", ERROR_NO_PQ_CREATE);
	}

	lstCreate(&(psQueue->sTheList));
}

/**************************************************************************
 Function: 	 	pqueueTerminate

 Description: terminates the priority queue

 Parameters:	psQueue - pointer to a pqueue

 Returned:	 	None
 *************************************************************************/
void pqueueTerminate (PriorityQueuePtr psQueue)
{
	if (NULL == psQueue)
	{
		processError ("psqueueTerminate", ERROR_NO_PQ_TERMINATE);
	}

	if (!lstIsEmpty(&psQueue->sTheList))
	{
		PriorityQueueElement pqElem;

		lstFirst(&psQueue->sTheList);
		for  (int i = 0; i < lstSize(&psQueue->sTheList); i++)
		{
			lstPeek(&psQueue->sTheList, &pqElem, sizeof(pqElem));
			free(pqElem.pData);
			lstNext(&psQueue->sTheList);
		}
	}
	lstTerminate(&psQueue->sTheList);
}

/**************************************************************************
 Function: 	 	pqueueEnqueue

 Description: enqueue a queue element

 Parameters:	psQueue   - pointer to a pqueue
 	 	 	 	 	 	  *pBuffer  - pointer to data
 	 	 	 	 	 	  size 		  - size of data being passed in
 	 	 	 	 	 	  priority  - pointer to priority of element

 Returned:	 	None
 *************************************************************************/
void pqueueEnqueue (PriorityQueuePtr psQueue, const void *pBuffer,
										int size, int priority)
{
	if (NULL == psQueue)
	{
		processError ("pqueueEnqueue", ERROR_INVALID_PQ);
	}
	if (NULL == pBuffer)
	{
		processError ("pqueueEnqueue", ERROR_NULL_PQ_PTR);
	}

	PriorityQueueElement psQTemp;

	PriorityQueueElement pqElem;

	psQTemp.pData = (void*) malloc (size);

	memcpy (psQTemp.pData, pBuffer, size);

	psQTemp.priority = priority;

	if (lstIsEmpty(&psQueue->sTheList))
	{
		lstInsertAfter(&(psQueue->sTheList), &psQTemp, sizeof(PriorityQueueElement));
	}
	else
	{
		lstFirst(&psQueue->sTheList);
		lstPeek(&psQueue->sTheList, &pqElem, sizeof(PriorityQueueElement));
		for (int i = 0; i < lstSize(&psQueue->sTheList); i++)
		{
			lstPeek(&psQueue->sTheList, &pqElem, sizeof(PriorityQueueElement));
			if (priority < pqElem.priority)
			{
				lstInsertBefore(&psQueue->sTheList, &psQTemp, sizeof(PriorityQueueElement));
				i = lstSize(&psQueue->sTheList);
			}
			else if (i == lstSize(&psQueue->sTheList) - 1)
			{
				lstInsertAfter(&(psQueue->sTheList), &psQTemp, sizeof(PriorityQueueElement));
				i = lstSize(&psQueue->sTheList);
			}
			else
			{
				lstNext(&psQueue->sTheList);
			}
		}
	}
}

/**************************************************************************
 Function: 	 	pqueueSize

 Description: returns the number of elements in the PQ

 Parameters:	psQueue - pointer to a pqueue

 Returned:	 	int
 *************************************************************************/
int pqueueSize (const PriorityQueuePtr psQueue)
{
	if (psQueue == NULL)
	{
		processError ("psqueueSize", ERROR_INVALID_PQ);
	}

	return lstSize(&(psQueue->sTheList));
}

/**************************************************************************
 Function: 	 	pqueueIsEmpty

 Description: If PQ is empty, return true; otherwise, return false

 Parameters:	psQueue - pointer to a pqueue

 Returned:	 	bool
 *************************************************************************/
bool pqueueIsEmpty (const PriorityQueuePtr psQueue)
{
	if (psQueue == NULL)
	{
		processError ("pqueueIsEmpty", ERROR_INVALID_PQ);
	}
	return lstIsEmpty(&(psQueue->sTheList));
}

/**************************************************************************
 Function: 	 	pqueuePeek

 Description: The priority and value of the first element is returned through
							the argument list

 Parameters:	psQueue   - pointer to a pqueue
 	 	 	 	 	 	  *pBuffer  - pointer to data
 	 	 	 	 	 	  size 		  - size of data being passed in
 	 	 	 	 	 	  *priority - pointer to priority of element

 Returned:	 	value of the element
 *************************************************************************/
void *pqueuePeek (PriorityQueuePtr psQueue, void *pBuffer, int size,
								 int *priority)
{
	if (psQueue == NULL)
	{
		processError ("pqueuePeek", ERROR_INVALID_PQ);
	}
	if (pBuffer == NULL)
	{
		processError ("psqueuPeek", ERROR_NULL_PQ_PTR);
	}
	if (lstIsEmpty(&(psQueue->sTheList)))
	{
		processError ("pqueuePeek", ERROR_EMPTY_PQ);
	}

	PriorityQueueElement pqElem;

	lstFirst(&psQueue->sTheList);
	lstPeek(&psQueue->sTheList, &pqElem, sizeof(pqElem));

	memcpy(pBuffer, pqElem.pData, size);

	*priority = pqElem.priority;

	return pBuffer;
}

/**************************************************************************
 Function: 	 	pqueueChangePriority

 Description: The priority of all elements is increased by the amount in
							change

 Parameters:	psQueue - pointer to a pqueue
 	 	 	 	 	 	  change  - value to increase priority

 Returned:	 	none
 *************************************************************************/
void pqueueChangePriority (PriorityQueuePtr psQueue, int change)
{
	if (psQueue == NULL)
	{
		processError ("pqueueChangePriority", ERROR_INVALID_PQ);
	}

	PriorityQueueElement pqElem;

	lstFirst(&psQueue->sTheList);

	for (int i = 0; i < lstSize(&psQueue->sTheList); i++)
	{
		lstPeek(&psQueue->sTheList, &pqElem, sizeof(PriorityQueueElement));

		pqElem.priority = pqElem.priority + change;
		lstUpdateCurrent(&psQueue->sTheList, &pqElem, sizeof(PriorityQueueElement));

		lstNext(&psQueue->sTheList);
	}
}

/**************************************************************************
 Function: 	 	pqueueDequeue

 Description: Remove the element from the front of a non-empty queue

 Parameters:	psQueue   - pointer to a pqueue
 	 	 	 	 	 	  *pBuffer  - pointer to data
 	 	 	 	 	 	  size 		  - size of data being passed in
 	 	 	 	 	 	  *priority - pointer to priority of element

 Returned:	 	data value from the element that is deleted
 *************************************************************************/
void *pqueueDequeue (PriorityQueuePtr psQueue, void *pBuffer,
														int size, int  *pPriority)
{
	if (psQueue == NULL)
	{
		processError ("pqueueDequeue", ERROR_INVALID_PQ);
	}
	if (pBuffer == NULL)
	{
		processError ("pqueueDequeue", ERROR_NULL_PQ_PTR);
	}
	if (lstIsEmpty(&(psQueue->sTheList)))
	{
		processError ("pqueueDequeue", ERROR_EMPTY_PQ);
	}

	PriorityQueueElement psTemp;

	lstFirst(&psQueue->sTheList);

	lstDeleteCurrent(&psQueue->sTheList, &psTemp, sizeof(PriorityQueueElement));

	memcpy(pBuffer, psTemp.pData, size);
	*pPriority = psTemp.priority;

	free(psTemp.pData);

	return pBuffer;
}
