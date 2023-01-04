/**************************************************************************
 File name:  list.c
 Author:     Liam Henry
 Date:		 	 9.28.16
 Class:		   CS300
 Assignment: Linked Lists
 Purpose:    Implementation for a list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 errorCode 	    - identifies the list error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszListErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	lstLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	  macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS
}

/**************************************************************************
 Function: 	 	lstCreate

 Description: Initializes the first, header and current to null. Sets
 	 	 	 	 	 	 	numElements to 0

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstCreate (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstCreate", ERROR_NO_LIST_CREATE);
	}
	psList->psFirst = NULL;
	psList->psLast = NULL;
	psList->psCurrent = NULL;
	psList->numElements = 0;
}

/**************************************************************************
 Function: 	 	lstTerminate

 Description: Sets the first, last, and current to null. Sets numElements
 	 	 	 	 	 	 	to 0

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstTerminate (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}

	ListElementPtr psTemp;

	if (lstIsEmpty (psList))
	{
		psList->psCurrent = psList->psFirst = psList->psLast = NULL;
		psList->numElements = 0;
	}
	else
	{
		lstFirst (psList);
		for (int i = 0; i < psList->numElements; i++)
		{
			psTemp = psList->psCurrent;
			free (psList->psCurrent->pData);
			lstNext (psList);
			free(psTemp);
		}
		psList->psCurrent = psList->psFirst = psList->psLast = NULL;
		psList->numElements = 0;
	}
}

/**************************************************************************
 Function: 	 	lstSize

 Description: Returns the number of elements in the list

 Parameters:	psList - a pointer to a list

 Returned:	  Number of elements in the list
 *************************************************************************/
int lstSize (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstTerminate", ERROR_INVALID_LIST);
	}
	return psList->numElements;
}

/**************************************************************************
 Function: 	 	lstIsEmpty

 Description: Checks if the list is empty

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if list is empty, otherwise false
 *************************************************************************/
bool lstIsEmpty (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstTerminate", ERROR_INVALID_LIST);
	}

	if (lstSize (psList) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**************************************************************************
 Function: 	 	lstPeek

 Description: Looks at the value that psCurrent is pointing to

 Parameters:	psList  -  list struct
 	 	 	 	 	 	  pBuffer -  character pointer used to store the data that
 	 	 	 	 	 	 	 	 	 	 	 	 psCurrent is pointing to

 Returned:	  pBuffer
 *************************************************************************/
void* lstPeek (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstPeek", ERROR_INVALID_LIST);
	}
	if (lstIsEmpty (psList))
	{
		processError ("lstPeek", ERROR_EMPTY_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstPeek", ERROR_NULL_PTR);
	}
	if (psList->psCurrent == NULL)
	{
		processError ("lstPeek", ERROR_NO_CURRENT);
	}

	memcpy (pBuffer, psList->psCurrent->pData, size);

	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstInsertAfter

 Description: Inserts an element into the list

 Parameters:	psList  -  list struct
 	 	 	 	 	 	  pBuffer -  character pointer used to store the data that
 	 	 	 	 	 	 	 	 	 	 	 	 psCurrent is pointing to
 	 	 	 	 	 	 	size		-  size of memory to be allocated

 Returned:	  none
 *************************************************************************/
void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstInsertAfter", ERROR_INVALID_LIST);
	}
	if (!(lstIsEmpty (psList)) && psList->psCurrent == NULL)
	{
		processError ("lstInsertAfter", ERROR_NO_CURRENT);
	}
	if (pBuffer == NULL)
	{
		processError ("lstInsertAfter", ERROR_NULL_PTR);
	}

	ListElementPtr psTemp = (ListElementPtr) malloc (sizeof(ListElement));
	psTemp->pData = (void*) malloc (size);

	psTemp->psNext = NULL;

	memcpy (psTemp->pData, pBuffer, size);

	if (lstIsEmpty (psList)) {
		psList->psCurrent = psList->psFirst = psList->psLast = psTemp;
	}
	else if (psList->psCurrent == psList->psLast)
	{
		psList->psCurrent->psNext = psTemp;
		psList->psCurrent = psTemp;
		psList->psLast = psTemp;
	}
	else {
		psTemp->psNext = psList->psCurrent->psNext;
		psList->psCurrent->psNext = psTemp;
		psList->psCurrent = psTemp;
	}

	psList->numElements++;
}

/**************************************************************************
 Function: 	 		lstFirst

 Description: 	psCurrent is changed to the first element

 Parameters:		psList  -  list struct

 Returned:	  	none
 *************************************************************************/
void lstFirst (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstInsertAfter", ERROR_INVALID_LIST);
	}
	if (lstIsEmpty (psList))
	{
		processError ("lstFirst", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psFirst;
}

/**************************************************************************
 Function: 	 	lstNext

 Description: psCurrent is changed to the successor of the current
 	 	 	 	 	 	 	element pointed to by psCurrent

 Parameters:	psList  -  list struct

 Returned:	  none
 *************************************************************************/
void lstNext (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstNext", ERROR_INVALID_LIST);
	}
	if (!(lstIsEmpty (psList)) && NULL == psList->psCurrent)
	{
		processError ("lstNext", ERROR_NO_CURRENT);
	}
	if (lstIsEmpty (psList))
	{
		processError ("lstNext", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psCurrent->psNext;
}

/**************************************************************************
 Function: 	 	lstHasCurrent

 Description: checks if psCurrent is pointing to NULL or not

 Parameters:	psList  -  list struct

 Returned:	  bool based on if psCurrent is pointing to NULL
 *************************************************************************/
bool lstHasCurrent (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstHasCurrent", ERROR_INVALID_LIST);
	}

	if (psList->psCurrent == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**************************************************************************
 Function: 	 	lstUpdateCurrent

 Description: The value of pBuffer is copied into the current element

 Parameters:	psList  -  list struct
 	 	 	 	 	 	 	pBuffer -	 void pointer
 	 	 	 	 	 	 	size		-  size to be malloc'd

 Returned:	  bool based on if psCurrent is pointing to NULL
 *************************************************************************/
void lstUpdateCurrent (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstUpdateCurrent", ERROR_INVALID_LIST);
	}
	if (lstIsEmpty(psList))
	{
		processError ("lstUpdateCurrent", ERROR_EMPTY_LIST);
	}
	if (pBuffer == NULL)
	{
		processError ("lstUpdateCurrent", ERROR_NULL_PTR);
	}
	if (!(lstIsEmpty (psList)) && psList->psCurrent == NULL)
	{
		processError ("lstUpdateCurrent", ERROR_NO_CURRENT);
	}

	free(psList->psCurrent->pData);

	ListElementPtr psTemp = psList->psCurrent;

	psTemp->pData = (void*) malloc (size);

	memcpy (psTemp->pData, pBuffer, size);
}

/**************************************************************************
 Function: 	 	lstHasNext

 Description: Returns true if the current node pointed to by psCurrent
 					 		has a successor; otherwise, false is returned

 Parameters:	psList  -  list struct

 Returned:	  bool based on if psNext is pointing to NULL
 *************************************************************************/
bool lstHasNext (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstUpdateCurrent", ERROR_INVALID_LIST);
	}

	if (psList->psCurrent->psNext == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**************************************************************************
 Function: 	 	lstPeekNext

 Description: The data value of psCurrent's successor is returned

 Parameters:	psList  -  list struct
 	 	 	 	 	 	 	pBuffer -	 void pointer
 	 	 	 	 	 	 	size		-  size to be malloc'd

 Returned:	  pBuffer
 *************************************************************************/
void *lstPeekNext (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstPeekNext", ERROR_INVALID_LIST);
	}
	if (lstIsEmpty (psList))
	{
		processError ("lstPeekNext", ERROR_EMPTY_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstPeekNext", ERROR_NULL_PTR);
	}
	if (psList->psCurrent == NULL)
	{
		processError ("lstPeekNext", ERROR_NO_CURRENT);
	}
	if (psList->psCurrent->psNext == NULL)
	{
		processError ("lstPeekNext", ERROR_NO_NEXT);
	}

	memcpy (pBuffer, psList->psCurrent->psNext->pData, size);

	return pBuffer;
}

/**************************************************************************
 Function: 	 	lstDeleteCurrent

 Description: The data value of psCurrent's successor is returned

 Parameters:	psList  -  list struct
 	 	 	 	 	 	 	pBuffer -	 void pointer
 	 	 	 	 	 	 	size		-  size to be malloc'd

 Returned:	  pBuffer
 *************************************************************************/
void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstDeleteCurrent", ERROR_INVALID_LIST);
	}
	if (lstIsEmpty(psList))
	{
		processError ("lstDeleteCurrent", ERROR_EMPTY_LIST);
	}
	if (pBuffer == NULL)
	{
		processError ("lstDeleteCurrent", ERROR_NULL_PTR);
	}
	if (!(lstIsEmpty (psList)) && psList->psCurrent == NULL)
	{
		processError ("lstDeleteCurrent", ERROR_NO_CURRENT);
	}

	ListElementPtr psTemp;

	memcpy (pBuffer, psList->psCurrent->pData, size);

	psTemp = psList->psFirst;

	if (psList->psCurrent == psList->psFirst ||
			psList->psCurrent->psNext != NULL)
	{
		if (psList->psCurrent == psList->psFirst && !(lstIsEmpty(psList)))
		{
			psList->psFirst = psList->psCurrent->psNext;
			free(psList->psCurrent->pData);
			free(psList->psCurrent);
			psList->psCurrent = psList->psFirst;
		}
		else
		{
			while (psTemp != NULL && psTemp->psNext != psList->psCurrent)
			{
				psTemp = psTemp->psNext;
			}

			if (psList->psCurrent == psList->psLast)
			{
				psTemp->psNext = NULL;
				psList->psLast = psTemp;
			}
			else
			{
				psTemp->psNext = psList->psCurrent->psNext;
			}
			free(psList->psCurrent->pData);
			free(psList->psCurrent);
		}
	}
	else if (psList->psCurrent == psList->psLast)
	{
		while (psTemp != NULL && psTemp->psNext != psList->psCurrent)
		{
			psTemp = psTemp->psNext;
		}
		psTemp->psNext = NULL;
		psList->psLast = psTemp;
		free(psList->psCurrent->pData);
		free(psList->psCurrent);
	}
	else
	{
		free(psList->psCurrent->pData);
		free(psList->psCurrent);
		psList->psCurrent = psList->psFirst = psList->psLast = NULL;
	}

	psList->numElements--;

	return pBuffer;

}

/**************************************************************************
 Function: 	 	lstInsertBefore

 Description: The data value of psCurrent's successor is returned

 Parameters:	psList  -  list struct
 	 	 	 	 	 	 	pBuffer -	 void pointer
 	 	 	 	 	 	 	size		-  size to be malloc'd

 Returned:	  pBuffer
 *************************************************************************/
void lstInsertBefore (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstInsertBefore", ERROR_INVALID_LIST);
	}
	if (pBuffer == NULL)
	{
		processError ("lstInsertBefore", ERROR_NULL_PTR);
	}
	if (!(lstIsEmpty (psList)) && psList->psCurrent == NULL)
	{
		processError ("lstInsertBefore", ERROR_NO_CURRENT);
	}

	ListElementPtr psPrev;
	ListElementPtr psTemp = (ListElementPtr) malloc (sizeof(ListElement));
	psTemp->pData = (void*) malloc (size);

	psTemp->psNext = NULL;

	psPrev = psList->psFirst;

	memcpy (psTemp->pData, pBuffer, size);

	if (!(lstIsEmpty(psList)))
	{
		if (psList->psCurrent == psList->psFirst)
		{
			psTemp->psNext = psList->psCurrent;
			psList->psFirst = psTemp;
			psList->psCurrent = psTemp;
			psList->numElements++;
		}
		else
		{
			while (psPrev->psNext != psList->psCurrent)
			{
				psPrev = psPrev->psNext;
			}
			psPrev->psNext = psTemp;
			psTemp->psNext = psList->psCurrent;
			psList->numElements++;
			psList->psCurrent = psTemp;
		}
	}
	else
	{
		free(psTemp->pData);
		free(psTemp);
		lstInsertAfter(psList, pBuffer, size);
	}
}

/**************************************************************************
 Function: 	 	lstLast

 Description: If the list is not empty, psCurrent is changed to psLast

 Parameters:	psList  -  list struct

 Returned:	  none
 *************************************************************************/
void lstLast (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstLast", ERROR_INVALID_LIST);
	}
	if (lstIsEmpty (psList))
	{
		processError ("lstLast", ERROR_EMPTY_LIST);
	}

	psList->psCurrent = psList->psLast;
}

/**************************************************************************
 Function: 	 	lstReverse

 Description: Reverses the list

 Parameters:	psList  -  list struct

 Returned:	  none
 *************************************************************************/
void lstReverse(ListPtr psList)
{
	ListElementPtr psTemp;
	ListElementPtr psTemp1;
	ListElementPtr psPrev;

	psTemp = psList->psLast;
	psPrev = psList->psLast;

	while (psPrev->psNext != psTemp)
	{
		psPrev = psPrev->psNext;
		psTemp = psTemp->psNext;
	}

	while (psPrev != NULL && psPrev->psNext != psList->psFirst)
	{
		psPrev = psPrev->psNext;
	}

	for (int i = 0; i < lstSize(psList); i++)
	{
		while (psPrev != NULL && psPrev->psNext != psTemp)
		{
			//psTemp->psNext = psPrev;
			//psTemp
		}

		//psTemp->psNext



	}



	psTemp1 = psList->psLast;
	psList->psLast = psList->psFirst;
	psList->psFirst = psTemp1;
}



