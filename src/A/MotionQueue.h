/**
 * @file		MotionQueue.h
 * @author		WK
 * @brief		This file is for process motion command with queue.
 * @date		2024/09/24
 * @version		1.00
 *
 */

#ifndef _MotionQueue_h_
#define _MotionQueue_h_

/******************************************************************************/
/*------------------------Includes--------------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Enumerations----------------------------------------*/
/******************************************************************************/
/**
  * @brief Motion Queue Error Type
  */
typedef enum tagQE_TYPE
{
	emQET_NoError			= 0,	/* \brief motion queue has no error */
	emQET_RamRunOut			= 1,	/* \brief ram run out */
	emQET_QueueOverflow		= 2,	/* \brief queue overflow */
	emQET_CmdSourceErr		= 3,	/* \brief command source is different */
} QE_TYPE;

/**
  * @brief Motion Command type
  */
typedef enum tagMC_TYPE
{
	/**
	 * @brief Motion Profile Command
	 */
	emMCT_MoveAbs 		=   0,	/* \brief absolute moving */
	emMCT_MoveRel 		=   1,	/* \brief relative moving  */
	emMCT_DecMotion		=   2,	/* \brief execute deceleration */
} MC_TYPE;

/**
  * @brief Motion Source type
  */
typedef enum tagMS_Type
{
	emMST_InternalReg	=   0,	/* \brief Motion command from internal register(Multi-pos) */
	emMST_ExternalPulse	=   1,	/* \brief Motion command from external pulse input */
	emMST_UART		 	=   2,	/* \brief Motion command from UART */
	emMST_USB		 	=   3,	/* \brief Motion command from USB */
	emMST_EtherNet		=   4,	/* \brief Motion command from EtherNet */
	emMST_EtherCAT		=   5,	/* \brief Motion command from EtherCAT */
	emMST_CAN		 	=   6,	/* \brief Motion command from CAN */
	emMST_PLC 			=   7,	/* \brief Motion command from PLC */
	emMST_ExternalCom	=	8,	/* \brief Motion command from External Communication */
	emMST_MAX			=	9,	/* \brief Maximum value */
	emMST_SystemOp		=  10,  /* \brief Motion command from system operation by itself */
} MS_TYPE;

/* \brief Motion Profile type */
typedef enum tagMP_Type
{
	emMPT_Idle 			= 0,	/* \brief Complete TP module */
	emMPT_Wait 			= 1,	/* \brief Wait the interval time */
	emMPT_DirectProfile = 10,	/* \brief execute direct profile */
	emMPT_RampProfile 	= 11,	/* \brief execute trapezoid profile  */
	emMPT_3PointCurve 	= 13,	/* \brief execute 3-point curve profile */
	emMPT_Deceleration 	= 14,	/* \brief execute deceleration */
	emMPT_QuickStop 	= 15,
} MP_TYPE;

/**
  * @brief 32-bit motion command queue union data type
  */
typedef union
{
	SLONG sl;					/* \brief SLONG */
	ULONG ul;					/* \brief ULONG */
	Float32 fl;					/* \brief FLOAT32 */
} COMMAND_UNION;

/******************************************************************************/
/*------------------------Structures------------------------------------------*/
/******************************************************************************/
/**
  * @brief Motion Target data structure
  */
typedef struct tagMotion_Target
{
	SLONG	slTargetPos;	/* \brief Target position for this segment (unit: pulse)*/
	Float32 flTargetVel;	/* \brief Target velocity for this segment (unit: Hz)*/
	Float32 flTargetAcc;	/* \brief Target acceleration for this segment (unit: sec)*/
	Float32 flTargetDec;	/* \brief Target deceleration for this segment (unit: sec)*/
} tMOTION_TARGET;

/**
  * @brief Queue Command data structure
  */
typedef struct tagQueue_Cmd_Struct
{
	MC_TYPE emMotionCmd;			/* \brief Motion command type */
	MS_TYPE emMotionSource;			/* \brief Motion source type */
	COMMAND_UNION unValue1;			/* \brief Parameter 1 for motion command */
	COMMAND_UNION unValue2;			/* \brief Parameter 2 for motion command */
	COMMAND_UNION unValue3;			/* \brief Parameter 3 for motion command */
	COMMAND_UNION unValue4;			/* \brief Parameter 4 for motion command */
} tQUEUE_CMD_STRUCT;

/******************************************************************************/
/*------------------------Global variables------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Public Functions------------------------------------*/
/******************************************************************************/
extern void MQ_voPowerOnInit(void);
extern Bool MQ_blIsMotionQueueBusy(void);
extern Bool MQ_blPullMotionQueue(tQUEUE_CMD_STRUCT **stQueueDataPtr);
extern Bool MQ_blPushMotionQueue(tQUEUE_CMD_STRUCT *stQueueDataPtr);
extern void MQ_voFlushMotionQueue(void);

#endif /* _MotionQueue_h_ */
