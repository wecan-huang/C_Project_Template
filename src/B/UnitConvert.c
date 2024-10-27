/**
 * @file		UnitConvert.c
 * @author		Lingyuan, Hsu
 * @brief		This file is for convert the physical unit to the other one.
 * @date		2018/11/23
 * @version		1.00
 *
 */

#ifndef _UnitConvert_c_
#define _UnitConvert_c_

/******************************************************************************/
/*------------------------Included Dependency---------------------------------*/
/******************************************************************************/
#include <stdio.h>
#include <math.h>
#include "MacroDefine.h"
#include "Extern_Macro_C2000.h"
#include "TypeDefine.h"
#include "B/UnitConvert.h"

/******************************************************************************/
/*------------------------Macros----------------------------------------------*/
/******************************************************************************/
//TODO: Un-done interface.
#define COF_ubMPolePair                 4
#define PG1_ulGetPgPulsePerRev()		4096
#define PG1_flGetPgPulsePerRevInv()		1024

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

Float32 UC_flHz2Rdps( Float32 flVelHz )
{
	/* Formula: 2*PI*(MaxHz)/PolePair */
	return TWO_PI * flVelHz / (float)COF_ubMPolePair;
}

Float32 UC_flHz2Rpm (Float32 flVelHz)
{
	return flVelHz*MIN_TO_SEC/(float)COF_ubMPolePair;
}


Float32 UC_flRdps2Hz( Float32 flVelRdps )
{
	/* Formula: (MaxRdps)*PolePair/(2*PI) */
	return flVelRdps * INV_TWO_PI * (float)COF_ubMPolePair;
}

Float32 UC_flPulse2Rad( SQWORD sqPosPulse )
{
	/* Formula: 2*PI*Position/ppr */
	/* Note: if sqPosPulse is big, conversion from SQWORD to Float32 will lose accuracy! */

	return TWO_PI * (Float32)sqPosPulse * PG1_flGetPgPulsePerRevInv();
}

Float32 UC_flRad2Pulse( Float32 flPosRad )
{
	/* Formula: Position*ppr/(2*PI) */
	/* Note1: if conversion result is claimed as SLONG, conversion error from Float32 to SLONG will be truncated! 
	 *        Then, the trajectory will loose accuracy.
	 * Note2: if flPosRad is big, conversion from radian to pulse will lose accuracy! */

	return flPosRad * PG1_ulGetPgPulsePerRev() * INV_TWO_PI;
}

#endif /* _UnitConvert_c_ */
