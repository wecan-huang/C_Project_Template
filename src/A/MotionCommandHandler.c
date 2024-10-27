/**
 * @file		MotionCommandHandler.c
 * @author		WK
 * @brief		This file is for handling motion command.
 * @date		2024/09/24
 * @version		1.00
 *
 */

#ifndef _MotionCommandHandler_c_
#define _MotionCommandHandler_c_

/******************************************************************************/
/*------------------------Included Dependency---------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "MacroDefine.h"
#include "EXTERN_MACRO_C2000.h"
#include "TypeDefine.h"
#include "B/UnitConvert.h"
#include "A/MotionQueue.h"
//#include "C/PRADB_SpdProfile.h"
#include "A/MotionCommandHandler.h"

/******************************************************************************/
/*------------------------Macros----------------------------------------------*/
/******************************************************************************/
//TODO: Un-done interface.
#define PRDB_flGetMaxOperateVelHz() (10)
#define MULTIPLY_LOAD_GEAR_RATIO_INV(Value) ((Float32)(Value) * 1)

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
* @brief	Description : Constructor function for set the target profile for absolute move.
*
* - @param	[in] stTarget : The target position, velocity, deceleration and acceleration.
* - @param	[in] emSourceType : The motion source type.
* - @param	[in] blIsImmediate : If TRUE, the motion command will be executed immediately, otherwise return FALSE.
* - @retval	Bool : Return TRUE if the motion command is pushed successfully, otherwise return FALSE.
*/
Bool MC_blAbsMove(tMOTION_TARGET stTarget, MS_TYPE emSourceType, Bool blIsImmediate)
{
	Float32 flAccTime = INT_1MS;
	Float32 flDecTime = INT_1MS;
	tQUEUE_CMD_STRUCT stAbsCmdData;

	if(blIsImmediate == TRUE)
	{
		MQ_voFlushMotionQueue();
	}

	stAbsCmdData.emMotionCmd = emMCT_MoveAbs;
	stAbsCmdData.emMotionSource = emSourceType;
	stAbsCmdData.unValue1.sl = stTarget.slTargetPos;
	stAbsCmdData.unValue2.fl = UC_flHz2Rdps(stTarget.flTargetVel);

	/* Prevent the denominator to be zero */
	flAccTime = MAX(stTarget.flTargetAcc, flAccTime);
	stAbsCmdData.unValue3.fl = UC_flHz2Rdps(stTarget.flTargetVel) / flAccTime;
	
	/* Prevent the denominator to be zero */
	flDecTime = MAX(stTarget.flTargetDec, flDecTime);
	stAbsCmdData.unValue4.fl = UC_flHz2Rdps(stTarget.flTargetVel) / flDecTime;

	return MQ_blPushMotionQueue(&stAbsCmdData);
}

/*!
* @brief	Description : Constructor function for set the target profile for relative move.
*
* - @param	[in] stTarget : The target position, velocity, deceleration and acceleration.
* - @param	[in] emSourceType : The motion source type.
* - @param	[in] blIsImmediate : If TRUE, the motion command will be executed immediately, otherwise return FALSE.
* - @retval	Bool : Return TRUE if the motion command is pushed successfully, otherwise return FALSE.
*/
Bool MC_blRelMove(tMOTION_TARGET stTarget, MS_TYPE emSourceType, Bool blIsImmediate)
{
	Float32 flAccTime = INT_1MS;
	Float32 flDecTime = INT_1MS;
	tQUEUE_CMD_STRUCT stRelCmdData;

	if(blIsImmediate == TRUE)
	{
		MQ_voFlushMotionQueue();
	}
	
	stRelCmdData.emMotionCmd = emMCT_MoveRel;
	stRelCmdData.emMotionSource = emSourceType;
	stRelCmdData.unValue1.sl = stTarget.slTargetPos;
	stRelCmdData.unValue2.fl = UC_flHz2Rdps(stTarget.flTargetVel);

	/* Prevent the denominator to be zero */
	flAccTime = MAX(stTarget.flTargetAcc, flAccTime);
	stRelCmdData.unValue3.fl = UC_flHz2Rdps(stTarget.flTargetVel) / flAccTime;

	/* Prevent the denominator to be zero */
	flDecTime = MAX(stTarget.flTargetDec, flDecTime);
	stRelCmdData.unValue4.fl = UC_flHz2Rdps(stTarget.flTargetVel) / flDecTime;

	return MQ_blPushMotionQueue(&stRelCmdData);
}

/*!
* @brief	Description : Constructor function for set the target profile for relative move without profile.
*
* - @param	[in] stTarget : The target position, velocity, deceleration and acceleration.
* - @param	[in] emSourceType : The motion source type.
* - @retval	Bool : Return TRUE if the motion command is pushed successfully, otherwise return FALSE.
*/
Bool MC_blDirectProfileMove(tMOTION_TARGET stTarget, MS_TYPE emSourceType)
{
	tQUEUE_CMD_STRUCT stRelCmdData;
	stRelCmdData.emMotionCmd = emMCT_MoveRel;
	stRelCmdData.emMotionSource = emSourceType;

	stRelCmdData.unValue1.sl = stTarget.slTargetPos;

	/* the second parameter is meant as the velocity */
	stRelCmdData.unValue2.fl = UC_flHz2Rdps(stTarget.flTargetVel);

	/* these three parameters are useless */
	stRelCmdData.unValue3.sl = INTEGER_ZERO;
	stRelCmdData.unValue4.sl = INTEGER_ZERO;

	return MQ_blPushMotionQueue(&stRelCmdData);
}

/*!
* @brief	Description : Constructor function for execute deceleration motion.
*
* - @param	[in] stTarget : The target position, velocity, deceleration and acceleration.
* - @param	[in] emSourceType : The motion source type.
* - @param	[in] blIsImmediate : If TRUE, the motion command will be executed immediately, otherwise return FALSE.
* - @param	[in] emMotionProfile : The motion profile type.
* - @retval	Bool : Return TRUE if the motion command is pushed successfully, otherwise return FALSE.
*/
Bool MC_blDecMotion(tMOTION_TARGET stTarget, MS_TYPE emSourceType, Bool blIsImmediate, MP_TYPE emMotionProfile)
{
	Float32 flAccTime = INT_1MS;
	Float32 flDecTime = INT_1MS;
	tQUEUE_CMD_STRUCT stDecCmdData;

	if(blIsImmediate == TRUE)
	{
		MQ_voFlushMotionQueue();
	}

	stDecCmdData.emMotionCmd = emMCT_DecMotion;
	stDecCmdData.emMotionSource = emSourceType;

	/* these two parameters are useless */
	stDecCmdData.unValue1.fl = FLOAT_ZERO;
	stDecCmdData.unValue2.fl = FLOAT_ZERO;

	/* Prevent the denominator to be zero */
	flAccTime = MAX(stTarget.flTargetAcc, flAccTime);
	stDecCmdData.unValue3.fl = UC_flHz2Rdps(stTarget.flTargetVel) / flAccTime;

	if (emMotionProfile == emMPT_QuickStop)
	{
		//flDecTime = (Float32)SPDPR_stObjPtr->ulQuickStopTime;//TODO
		flDecTime = 1;
		stDecCmdData.unValue4.fl = UC_flHz2Rdps(MULTIPLY_LOAD_GEAR_RATIO_INV(PRDB_flGetMaxOperateVelHz())) / flDecTime;	//TODO MULTIPLY_LOAD_GEAR_RATIO_INV()介面未實作
	}
	else
	{
		/* Prevent the denominator to be zero */
    	flDecTime = MAX(stTarget.flTargetDec, flDecTime);
		stDecCmdData.unValue4.fl = UC_flHz2Rdps(stTarget.flTargetVel) / flDecTime;
	}

	return MQ_blPushMotionQueue(&stDecCmdData);
}


#endif /* _MotionCommandHandler_c_ */
