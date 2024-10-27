/*
 * MacroDefine.h
 */
#ifndef FALSE
#define FALSE 					        (0)
#endif
#ifndef TRUE
#define TRUE 					        (1)
#endif

#define Q32             (4294967296)    // 0x100000000
#define Q31             (2147483648)
#define Q30             (1073741824)
#define Q16             (65536)         // 0x00010000
#define Q13		        (8192)          // 0x00002000

#define Q16_INV			(0.0000152587890625F)
#define Q30_INV        	(0.000000000931322574615478515625F)
#define Q31_INV        	(0.0000000004656612873077392578125F)
#define Q32_INV        	(0.00000000023283064365386962890625F)

#define Q32_LIMIT       (4294967295)    // 0xFFFFFFFF
#define Q31_LIMIT       (2147483647)
#define Q30_LIMIT       (1073741824)
#define Q16_LIMIT       (65535)         // 0x0000FFFF
#define Q15_LIMIT       (32767)         // 0x00007FFF

#define INV_Q12_LIMIT	(0.0002442002442002442)		/* 1/4095 */

#define VAR_SET_BIT(var, bitIndex)	(var |= (1u << bitIndex))
#define VAR_CLR_BIT(var, bitIndex)	(var &= ~(1u << bitIndex))
#define VAR_TGL_BIT(var, bitIndex)	(var ^= (1u << bitIndex))
#define VAR_GET_BIT(var, bitIndex)	((var >> bitIndex) & 1u)
#define LOC_VAR_BIT_CTL(var, bitIndex, val)  (var |= (val << bitIndex))
#define VAR_BIT_CTL(var, bitIndex, val) ( var = (var & ( ~(1u << bitIndex))) | (val << bitIndex) )
#define VAR_BIT_TGL(var, bitIndex, val) ( (val == FALSE) ? VAR_SET_BIT(var, bitIndex) : VAR_CLR_BIT(var, bitIndex) )

#define BYTE_LENGTH     (8)
#define WORD_LENGTH     (16)

#define INTEGER_ZERO    (0)
#define INTEGER_ONE    (1U)
#define INTEGER_TWO    (2U)
#define INTEGER_THREE  (3U)
#define INTEGER_FOUR   (4U)
#define INTEGER_FIVE   (5U)
#define INTEGER_SIX    (6U)
#define INTEGER_SEVEN  (7U)
#define INTEGER_EIGHT  (8U)

//fixme
#define DebugMFDPAGEMAX 77
#define C20MAX          (0x11+1)                // MAX ITEM C20XX//2000H~200FH
#define C21MAX          (0x60+1)                // MAX ITEM C21XX//2100H~2113H
#define prUnitinfoMAX	    71  // MAX Pr unit
#define GRALL 	(14) /* �ݭn�P�BeKEYPAD_GROUP_Max */
//fixme


#define MAX(A,B)                (((A) > (B)) ? (A) : (B))
#define MIN(A,B)                (((A) < (B)) ? (A) : (B))

//****** For MBD Using ************************************************************
#define MBD_SET ((Bool) 1)
#define MBD_CLR ((Bool) 0)

#define NORMAL        ((UBYTE) 0) /* Description: Normal state, no saturation occurs. */
#define OVER_UP_LIM   ((UBYTE) 1) /* Description: Input is over upper limit. */
#define BELOW_LOW_LIM ((UBYTE) 2) /* Description: Input is below lower limit. */
//*********************************************************************************

#define DLT_INLINE inline

#define FAKE_FREQ_BASE (650000U)
#define FAKE_INV_FREQ_BASE (0.00000153846153846154f)
#define ADC_VALUE_MAX   (4095)
#define CHAR_MAX		(127)

#define CARRIER_FREQ_1kHz	(1000U)
#define CARRIER_FREQ_2kHz	(2000U)
#define CARRIER_FREQ_3kHz	(3000U)
#define CARRIER_FREQ_4kHz	(4000U)
#define CARRIER_FREQ_5kHz	(5000U)
#define CARRIER_FREQ_6kHz	(6000U)
#define CARRIER_FREQ_7kHz	(7000U)
#define CARRIER_FREQ_8kHz	(8000U)
#define CARRIER_FREQ_9kHz	(9000U)
#define CARRIER_FREQ_10kHz	(10000U)
#define CARRIER_FREQ_11kHz	(11000U)
#define CARRIER_FREQ_12kHz	(12000U)
#define CARRIER_FREQ_13kHz	(13000U)
#define CARRIER_FREQ_14kHz	(14000U)
#define CARRIER_FREQ_15kHz	(15000U)
#define CARRIER_FREQ_16kHz	(16000U)
#define CARRIER_FREQ_17kHz	(17000U)
#define CARRIER_FREQ_18kHz	(18000U)
#define CARRIER_FREQ_19kHz	(19000U)
#define CARRIER_FREQ_20kHz	(20000U)

#define KHZ_TO_HZ		(1000U)
#define HZ_TO_KHZ		(0.001F)
#define W_TO_KW			(0.001F)
#define LS66PCT_CARRIER     (0.666666667F)

#define MIN_TO_SEC      (60)
#define SEC_TO_MS       (1000)
#define HR_TO_SEC       (3600)

#define PULL_LOW		(0U)
#define PULL_HIGH		(1U)

#define PIN_HIGH        (1)
#define PIN_LOW         (0)