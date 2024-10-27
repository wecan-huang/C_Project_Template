/******************************************************************************************************
 * Copyright (c) 2021 Delta Electronics, Inc. All rights reserved

 * Filename        : TypeDefine.h
 * Description     :
 * Revision History:
 *
******************************************************************************************************/
#ifndef TYPES_DEFINE_H
#define TYPES_DEFINE_H

//#define SPI_TEST/*Fixme*/

/* Include File *********************************************************************/
#include <stdbool.h>
#include <stdint.h>


/* Data Type Definition *************************************************************/
typedef uint16_t    Bool;
typedef int16_t     SBYTE;      //In C28x system, byte is 16bit
typedef uint16_t    UBYTE;      //In C28x system, byte is 16bit
typedef int16_t     SWORD;
typedef uint16_t    UWORD;
typedef int32_t     SLONG;
typedef uint32_t    ULONG;
typedef float       FLOAT;
typedef float       Float32;	//For MBD
typedef int64_t     SQWORD;
typedef uint64_t    UQWORD;


/* Enumerations Definition *******************************************************/

/* Data Structures Definition *******************************************************/
typedef union{
    struct{
        UWORD b0:1;
        UWORD b1:1;
        UWORD b2:1;
        UWORD b3:1;
        UWORD b4:1;
        UWORD b5:1;
        UWORD b6:1;
        UWORD b7:1;
        UWORD b8:1;
        UWORD b9:1;
        UWORD b10:1;
        UWORD b11:1;
        UWORD b12:1;
        UWORD b13:1;
        UWORD b14:1;
        UWORD b15:1;
    }bit;
    struct{
        UBYTE low:8;
        UBYTE hi:8;
    }ub;
    UWORD uw;
}UWORD_UNION;

typedef union {

	struct {
		ULONG BYTE0 :8;
		ULONG BYTE1 :8;
		ULONG BYTE2 :8;
		ULONG BYTE3 :8;
	} ub;

	struct {
		UWORD low;
		UWORD hi;
	} uw;

	ULONG ul;

} ULONG_UNION;

typedef union {

	struct {
		UQWORD BYTE0 :8;
		UQWORD BYTE1 :8;
		UQWORD BYTE2 :8;
		UQWORD BYTE3 :8;
		UQWORD BYTE4 :8;
		UQWORD BYTE5 :8;
		UQWORD BYTE6 :8;
		UQWORD BYTE7 :8;
	} ub;

	struct {
		UWORD WORD0;
		UWORD WORD1;
		UWORD WORD2;
		UWORD WORD3;
	} uw;

	struct {
		ULONG low;
		ULONG hi;
	} ul;

	UQWORD uq;

} UQWORD_UNION;

typedef union
{
    float flvalue;
    struct
    {
        UBYTE LWLbyte :8;
        UBYTE LWHbyte :8;
        UBYTE HWLbyte :8;
        UBYTE HWHbyte :8;
    }byte;
    struct
    {
        UWORD LWord;
        UWORD HWord;
    }word;
    struct
    {
        ULONG DWord;
    }dword;


}FLOAT_UNION;

typedef union
{
    double dvalue;
	struct {
		UQWORD BYTE0 :8;
		UQWORD BYTE1 :8;
		UQWORD BYTE2 :8;
		UQWORD BYTE3 :8;
		UQWORD BYTE4 :8;
		UQWORD BYTE5 :8;
		UQWORD BYTE6 :8;
		UQWORD BYTE7 :8;
	} ub;

	struct {
		UWORD WORD0;
		UWORD WORD1;
		UWORD WORD2;
		UWORD WORD3;
	} uw;

	struct {
		ULONG low;
		ULONG hi;
	} ul;

}DOUBLE_UNION;

typedef struct{
	UBYTE x[33];
}string32;

typedef struct{
	UBYTE x[25];
}string24;

typedef struct{
	UBYTE x[21];
}string20;

typedef struct{
	char x[21];
}string20_CPU1; /* Fixme:����s�զr�겾��CM��A���ŧi�H������ */

typedef struct{
	UBYTE x[17];
}string16;

typedef struct{
	UBYTE x[9];
}string8;

typedef struct{
	UBYTE x[5];
}string4;

typedef struct{
	char x[5];
}string4_CPU1;	/* Fixme:����s�զr�겾��CM��A���ŧi�H������ */


typedef struct fl_abc {    /* three phase in a,b,c axis (Float Type)*/
	FLOAT  a;
	FLOAT  b;
	FLOAT  c;
} FLOAT_ABC_ST;

typedef struct uw_abc {    /* three phase in a,b,c axis (Fixed-Point Type)*/
	UWORD  a;
	UWORD  b;
	UWORD  c;
} UWORD_ABC_ST;

typedef struct fl_dqs {     /* two phase in stationary d,q axis (Float Type)*/
	FLOAT  ds;
	FLOAT  qs;
} FLOAT_DQS_ST;

typedef struct fl_dqe {     /* two phase in rotation d,q axis (Float Type)*/
	FLOAT  de;
	FLOAT  qe;
} FLOAT_DQE_ST;

typedef struct tagPWM_COMPARE_VALUE_ST
{
	UWORD uwU;
	UWORD uwV;
	UWORD uwW;
	UWORD uwX;
	UWORD uwY;
	UWORD uwZ;

}PWM_COMPARE_VALUE_ST;




#endif
/*--------------------------------------------------------------------------------------------------------------------------------------------------*\
  END OF FILE
\*--------------------------------------------------------------------------------------------------------------------------------------------------*/
