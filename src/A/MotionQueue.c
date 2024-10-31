/**
 * @file		MotionQueue.c
 * @author		WK
 * @brief		This file is for process motion command with queue.
 * @date		2024/09/24
 * @version		1.00
 *
 */

#ifndef _MotionQueue_c_
#define _MotionQueue_c_

/******************************************************************************/
/*------------------------Included Dependency---------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MacroDefine.h"
#include "TypeDefine.h"
#include "A/Queue.h"
#include "A/MotionQueue.h"

/******************************************************************************/
/*------------------------Macros----------------------------------------------*/
/******************************************************************************/
#define MOTION_QUEUE_MAX_SIZE	(10U)

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
static tQUEUE S_stMotionQueue;	/* \brief Motion queue */
static tQUEUE_CMD_STRUCT S_stMotionQueueData[MOTION_QUEUE_MAX_SIZE];	/* \brief Motion queue data */
static Bool S_blQueueAvailable = FALSE;	/* \brief Motion queue available flag */

/******************************************************************************/
/*------------------------Function Implementations----------------------------*/
/******************************************************************************/
#define ENABLE_INTERRUPTS		/* TODO 根據平台給EINT方式 */
#define DISABLE_INTERRUPTS		/* TODO 根據平台給DINT方式 */
/*!
* @brief	Description : Constructor function for module power on initialization.
*
* - @param	void
* - @retval	void
*/
void MQ_voPowerOnInit(void)
{
	tCREATE_Q_ST_IN stIn = {
		.stQPtr = &S_stMotionQueue,
		.voItemBufPtr = (void *)S_stMotionQueueData,
		.ubItemSize = sizeof(tQUEUE_CMD_STRUCT),
		.ubQCapacity = MOTION_QUEUE_MAX_SIZE,
	};
	DISABLE_INTERRUPTS;
	S_blQueueAvailable = QUE_blCreateQueue(&stIn);
	ENABLE_INTERRUPTS;
}

/*!
* @brief	Description : Constructor function for check if the motion queue is busy.
*
* - @param	void
* - @retval Bool : Return TRUE if the motion queue is full, otherwise return FALSE.
*/
Bool MQ_blIsMotionQueueBusy(void)
{
	return (QUE_ubGetQueueCnt(&S_stMotionQueue) >= MOTION_QUEUE_MAX_SIZE);
}

/*!
* @brief	Description : Constructor function for pulling motion command from the motion queue.
*
* - @param	[out] stQueueDataPtr : The pointer to store the pulled motion command.
* - @retval	Bool : Return TRUE if the motion queue is empty, otherwise return FALSE.
*/
Bool MQ_blPullMotionQueue(tQUEUE_CMD_STRUCT **stQueueDataPtr)
{
	Bool blResult = FALSE;
	tDE_Q_ST_OUT stOut = {
		.blSuccess = FALSE,
		.voItemPtr = NULL,
	};
	if(stQueueDataPtr!=NULL)
	{
		DISABLE_INTERRUPTS;
		stOut = QUE_stDeQueue(&S_stMotionQueue);
		ENABLE_INTERRUPTS;
		if (stOut.blSuccess == TRUE)
		{
			*stQueueDataPtr = (tQUEUE_CMD_STRUCT *)stOut.voItemPtr;
		}
		else
		{
			//return FALSE
		}
	}
	else
	{
		//return FALSE
	}
	return stOut.blSuccess;
}

/*!
* @brief	Description : Constructor function for pushing motion command to the motion queue.
*
* - @param	[in] stQueueDataPtr : The pointer to the motion command to be pushed.
* - @retval	Bool : Return TRUE if the motion command is pushed successfully, otherwise return FALSE.
*/
Bool MQ_blPushMotionQueue(tQUEUE_CMD_STRUCT * stQueueDataPtr)
{
	Bool blResult = FALSE;
	tEN_Q_ST_IN stIn = {
		.stQPtr = &S_stMotionQueue,
		.voItemPtr = (void *)stQueueDataPtr,
	};
	if (stIn.voItemPtr != NULL)
	{
		DISABLE_INTERRUPTS;
		blResult = QUE_blEnQueue(&stIn);
		ENABLE_INTERRUPTS;
	}
	else
	{
		//return FALSE
	}
	return blResult;
}

/*!
* @brief	Description : Constructor function for flushing the motion queue.
*
* - @param	void
* - @retval	void
*/
void MQ_voFlushMotionQueue(void)
{
	DISABLE_INTERRUPTS;
	QUE_blEmptyQueue(&S_stMotionQueue);
	ENABLE_INTERRUPTS;
}

#endif /* _MotionQueue_c_ */
