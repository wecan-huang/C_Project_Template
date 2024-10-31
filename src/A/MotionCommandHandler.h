/**
 * @file		MotionCommandHandler.h
 * @author		WK
 * @brief		This file is for handling motion command.
 * @date		2024/09/24
 * @version		1.00
 *
 */

#ifndef _MotionCommandHandler_h_
#define _MotionCommandHandler_h_

/******************************************************************************/
/*------------------------Includes--------------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Enumerations----------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Structures------------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Global variables------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Public Functions------------------------------------*/
/******************************************************************************/
extern Bool MC_blAbsMove(tMOTION_TARGET stTarget, MS_TYPE emSourceType, Bool blIsImmediate);
extern Bool MC_blRelMove(tMOTION_TARGET stTarget, MS_TYPE emSourceType, Bool blIsImmediate);
extern Bool MC_blDirectProfileMove(tMOTION_TARGET stTarget, MS_TYPE emSourceType);
extern Bool MC_blDecMotion(tMOTION_TARGET stTarget, MS_TYPE emSourceType, Bool blIsImmediate, MP_TYPE emMotionProfile);

#endif /* _MotionCommandHandler_h_ */
