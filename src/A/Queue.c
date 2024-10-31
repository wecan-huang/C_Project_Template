/**
 * @file		Queue.c
 * @author		WK
 * @brief		This file is for ring queue function implementation, refer from 
 * 				Data Structures: A Pseudocode Approach with C, Second Edition.
 * @date		2024/09/24
 * @version		1.00
 *
 */

#ifndef _Queue_c_
#define _Queue_c_

/******************************************************************************/
/*------------------------Included Dependency---------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "MacroDefine.h"
#include "TypeDefine.h"
#include "A/Queue.h"

/******************************************************************************/
/*------------------------Macros----------------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Enumerations----------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Data Structures-------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Global variables------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Function Prototypes---------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Function Implementations----------------------------*/
/******************************************************************************/

/*!
* @brief	Description : Constructor function for ring queue initialization.
*
* - @param	[in] stInPtr : The created queue structure including queue structure, item buffer, item size and queue capacity.
* - @retval	Bool : Return TRUE if the queue is created successfully, otherwise return FALSE.
*/
Bool QUE_blCreateQueue(tCREATE_Q_ST_IN *stInPtr)
{
	Bool blResult = FALSE;
	if (stInPtr!=NULL)
	{
		if ((stInPtr->stQPtr != NULL) && (stInPtr->voItemBufPtr != NULL) &&
			(stInPtr->ubItemSize <= QUEUE_ITEM_MAX_SIZE) &&
			(stInPtr->ubQCapacity <= QUEUE_MAX_SIZE))
		{
			tQUEUE *stOutPtr = NULL;
			blResult = TRUE;
			stOutPtr = stInPtr->stQPtr;
			stOutPtr->ubItemSize = stInPtr->ubItemSize;
			stOutPtr->ubCapacity = stInPtr->ubQCapacity;
			stOutPtr->voItemBufPtr = stInPtr->voItemBufPtr;
			stOutPtr->ubFront = 0;
			stOutPtr->ubRear = 0;
			stOutPtr->ubSize = 0;
		}
		else
		{
			// return FALSE
		}
	}
	else
	{
		// return FALSE
	}

	return blResult;
}

/*!
* @brief	Description : Constructor function for get and delete an element at the front of the ring queue.
*
* - @param	[in] stQPtr : The ring queue pointer.
* - @retval	tDE_Q_ST_OUT : The dequeued structure including success flag and the dequeued item pointer.
*/
tDE_Q_ST_OUT QUE_stDeQueue(tQUEUE *stInPtr)
{
	tDE_Q_ST_OUT stOut = {.blSuccess = FALSE, .voItemPtr = NULL};
	if (stInPtr!= NULL)
	{
		if ((stInPtr->ubSize != 0) && (stInPtr->voItemBufPtr!=NULL))
		{
			stOut.blSuccess = TRUE; // set success flag to TRUE
			stOut.voItemPtr = (void *)(stInPtr->voItemBufPtr + stInPtr->ubFront * stInPtr->ubItemSize); // store the front element pointer
			stInPtr->ubFront = (stInPtr->ubFront + 1) % stInPtr->ubCapacity;						 // move the front pointer to the next element
			stInPtr->ubSize--;																// decrease the size of the queue
		}
		else
		{
			// return FALSE
		}
	}
	else
	{
		// return FALSE
	}

	return stOut;
}

/*!
* @brief	Description : Constructor function for add an element at the rear of the ring queue.
*
* - @param	[in] stInPtr : The enqueued structure including the queue pointer and the enqueued item pointer.
* - @retval	Bool : Return TRUE if the element is added successfully, otherwise return FALSE.
*/
Bool QUE_blEnQueue(tEN_Q_ST_IN *stInPtr)
{
	Bool blResult = FALSE;
	if (stInPtr!= NULL)
	{
		tQUEUE *stQInPtr = stInPtr->stQPtr;
		if (stQInPtr!=NULL)
		{
			if ((stQInPtr->ubSize < stQInPtr->ubCapacity) && (stQInPtr->voItemBufPtr!=NULL))
			{
				blResult = TRUE;
				memcpy(stQInPtr->voItemBufPtr + stQInPtr->ubRear * stQInPtr->ubItemSize, stInPtr->voItemPtr, stQInPtr->ubItemSize);				  // copy the element to the rear position of the queue
				stQInPtr->ubRear = (stQInPtr->ubRear + 1) % stQInPtr->ubCapacity;																  // move the rear pointer to the next element
				stQInPtr->ubSize++;																												  // increase the size of the queue
			}
			else
			{
				// return FALSE
			}
		}
		else
		{
			// return FALSE
		}
	}
	else
	{
		// return FALSE
	}

	return blResult;
}

/*!
* @brief	Description : Constructor function for clear queue.
*
* - @param	[out] stInPtr : The ring queue pointer.
* - @retval	Bool : Return TRUE if the queue is empty successfully, otherwise return FALSE.
*/
Bool QUE_blEmptyQueue(tQUEUE *stInPtr)
{
	Bool blResult = FALSE;
	if (stInPtr!= NULL)
	{
		stInPtr->ubFront = stInPtr->ubRear = 0; // reset front and rear pointers to 0
		stInPtr->ubSize = 0; // reset size to 0
		blResult = TRUE; // set success flag to TRUE
	}
	else
	{
		// return FALSE
	}

	return blResult;
}

/*!
* @brief	Description : Constructor function for get element count in the ring queue.
*
* - @param	[in] stInPtr : The ring queue pointer.
* - @retval	UBYTE : Return the number of elements in the ring queue.
*/
UBYTE QUE_ubGetQueueCnt(tQUEUE *stInPtr)
{
	UBYTE ubResult = 0;
	if (stInPtr != NULL)
	{
		ubResult = stInPtr->ubSize; // return number of elements
	}
	else
	{
		// return FALSE
	}

	return ubResult;
}

#endif /* _Queue_c_ */




