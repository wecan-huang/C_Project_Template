/**
 * @file		Queue.h
 * @author		WK
 * @brief		This file is for ring queue implementation, refer from
 * 				Data Structures: A Pseudocode Approach with C, Second Edition.
 * @date		2024/09/24
 * @version		1.00
 *
 */

#ifndef _Queue_h_
#define _Queue_h_

/******************************************************************************/
/*------------------------Includes--------------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Enumerations----------------------------------------*/
/******************************************************************************/
#define QUEUE_MAX_SIZE (256U)  // sizeof(UBYTE)
#define QUEUE_ITEM_MAX_SIZE (256U) // sizeof(UBYTE)

/******************************************************************************/
/*------------------------Structures------------------------------------------*/
/******************************************************************************/
/// @brief Queue structure
typedef struct
{
	void *voItemBufPtr; // Item buffer pointer
	UBYTE ubItemSize;	// Item size in bytes
	UBYTE ubFront;		// Queue front index that points to the first inserted item
	UBYTE ubRear;		// Queue rear index that points to the next available inserted space
	UBYTE ubSize;		// Queue size
	UBYTE ubCapacity;	// Queue capacity
} tQUEUE;

/// @brief Create queue input structure
typedef struct
{
	tQUEUE *stQPtr;		// Queue pointer that will be created
	void *voItemBufPtr; // Item buffer pointer
	UBYTE ubItemSize;	// Item size in bytes
	UBYTE ubQCapacity;	// Queue capacity
} tCREATE_Q_ST_IN;

/// @brief Dequeue output structure
typedef struct
{
	void *voItemPtr; // dequeued item pointer
	Bool blSuccess;	 // dequeue success flag
} tDE_Q_ST_OUT;

/// @brief Enqueue input structure
typedef struct
{
	tQUEUE *stQPtr;				 // created queue header pointer
	void const *const voItemPtr; // enqueue item pointer
} tEN_Q_ST_IN;


/******************************************************************************/
/*------------------------Global variables------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Public Functions------------------------------------*/
/******************************************************************************/
extern Bool QUE_blCreateQueue(tCREATE_Q_ST_IN *stInPtr);
extern tDE_Q_ST_OUT QUE_stDeQueue(tQUEUE *stInPtr);
extern Bool QUE_blEnQueue(tEN_Q_ST_IN *stInPtr);
extern Bool QUE_blEmptyQueue(tQUEUE * stInPtr);
extern UBYTE QUE_ubGetQueueCnt(tQUEUE *stInPtr);


#endif /* _Queue_h_ */
