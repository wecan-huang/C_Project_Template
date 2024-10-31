/**
 * @file		main.c
 * @author		WK
 * @brief		This file is for demo.
 * @date		2024/10/09
 * @version		1.00
 *
 */

#ifndef _main_c_
#define _main_c_

/******************************************************************************/
/*------------------------Included Dependency---------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include "MacroDefine.h"
#include "TypeDefine.h"
#include "A/MotionQueue.h"
#include "A/MotionCommandHandler.h"

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
* @brief	Description : main function
*
* - @param	[in] void
* - @retval	int
*/
int main(int argc, char *argv[]) 
{
	/* Initialize Motion Command Handler */
	MQ_voPowerOnInit();
	
	Bool result = FALSE;
	tMOTION_TARGET stTarget = {0, 1000, 100, 50}; // example target
	
	for(int i = 1; i < argc; i++)
	{
		/* call process */
		printf("Start..., argv[%d]: %s\n", i, argv[i]);

		/* Enqueue */
		result = FALSE;
		switch (argv[i][1])
		{
			case 'A': //MC_blAbsMove
				result = MC_blAbsMove(stTarget, emMST_UART, FALSE);
				break;
			case 'R': //MC_blRelMove
				result = MC_blRelMove(stTarget, emMST_UART, FALSE);
				break;
			case 'P': //MC_blDirectProfileMove
				result = MC_blDirectProfileMove(stTarget, emMST_UART);
				break;
			case 'D': //MC_blDecMotion
				result = MC_blDecMotion(stTarget, emMST_UART, FALSE, emMPT_QuickStop);
				break;
			default:
				break;
		}
		printf("Enqueue result %d, \n",result);
		printf("- - - - - - - - - - - - -\n");
	}
	printf("===========================\n");
	for(int i = 1; i < argc; i++)
	{
		/* Dequeue */
		tQUEUE_CMD_STRUCT *stQueueData;
		result = MQ_blPullMotionQueue(&stQueueData);
		printf("Dequeue result[%d] %d, \n",i, result);
		printf("Dequeue data[%d]:\n emMotionCmd = %d\n emMotionSource = %d\n unValue1 = %d\n unValue2 = %f\n unValue3 = %f\n unValue4 = %f\n",
				i,
				stQueueData->emMotionCmd,
				stQueueData->emMotionSource,
				stQueueData->unValue1.sl,
				stQueueData->unValue2.fl,
				stQueueData->unValue3.fl,
				stQueueData->unValue4.fl);
		printf("- - - - - - - - - - - - -\n");
	}

    return 0;
}


#endif /* _main_c_ */
