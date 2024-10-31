/**
 * @file		MotionCommandHandler.cpp
 * @author		WK
 * @brief		Unit tests for the MotionCommandHandler module.
 * @date		2024/10/16
 * @version		1.00
 *
 */


/******************************************************************************/
/*------------------------Includes--------------------------------------------*/
/******************************************************************************/
#include <gtest/gtest.h>
#include <string>
#include <map>

extern "C"
{
	#include "MacroDefine.h"
	#include "EXTERN_MACRO_C2000.h"
	#include "TypeDefine.h"
	#include "A/MotionQueue.h"  // dependency
	#include "B/UnitConvert.h"  // dependency
	#include "A/MotionCommandHandler.h"  // The function under test
	#include "fff.h"  // FFF mocking framework

	DEFINE_FFF_GLOBALS
	FAKE_VOID_FUNC(MQ_voFlushMotionQueue);
    FAKE_VALUE_FUNC(Bool, MQ_blPushMotionQueue, tQUEUE_CMD_STRUCT *);
	FAKE_VALUE_FUNC(Float32, UC_flHz2Rdps, Float32);
}

/******************************************************************************/
/*------------------------Macro-----------------------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Structures------------------------------------------*/
/******************************************************************************/
/**
* @brief Test Data Structure for MC_blAbsMove/MC_blRelMove
*/
struct TDS_MC_blAbsRelMove
{
	// 確認(預期結果)
	Bool Expect_blResult;
	UBYTE Expect_ubFlushFunctionCalledCount;
	tQUEUE_CMD_STRUCT Expect_stQueueCommand;

	// 輸入(輸入資料)
	tMOTION_TARGET Fake_Data_stTarget;
	MS_TYPE Fake_Data_emSourceType;
	Bool Fake_Data_blIsImmediate;

	// Mock假資料
	Float32 MockData_flUCHz2Rdps;
	Bool MockData_blPushMQRtn;
};

/**
* @brief Test Data Structure for MC_blDirectProfileMove
*/
struct TDS_MC_blDirectProfileMove
{
	// 確認(預期結果)
	Bool Expect_blResult;
	tQUEUE_CMD_STRUCT Expect_stQueueCommand;

	// 輸入(輸入資料)
	tMOTION_TARGET Fake_Data_stTarget;
	MS_TYPE Fake_Data_emSourceType;

	// Mock假資料
	Float32 MockData_flUCHz2Rdps;
	Bool MockData_blPushMQRtn;
};

/**
* @brief Test Data Structure for MC_blDecMotion
*/
struct TDS_MC_blDecMotion
{
	// 確認(預期結果)
	Bool Expect_blResult;
	UBYTE Expect_ubFlushFunctionCalledCount;
	tQUEUE_CMD_STRUCT Expect_stQueueCommand;

	// 輸入(輸入資料)
	tMOTION_TARGET Fake_Data_stTarget;
	MS_TYPE Fake_Data_emSourceType;
	Bool Fake_Data_blIsImmediate;
	MP_TYPE Fake_Data_emMotionProfile;

	// Mock假資料
	Float32 MockData_flUCHz2Rdps;
	Bool MockData_blPushMQRtn;
};

/******************************************************************************/
/*------------------------Class-----------------------------------------------*/
/******************************************************************************/
/**
* @brief Test fixture for MC_blAbsMove/MC_blRelMove with parameters
*/
class TS_MC_blAbsRelMove : public ::testing::TestWithParam<TDS_MC_blAbsRelMove> {
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
		RESET_FAKE(MQ_voFlushMotionQueue);
		RESET_FAKE(MQ_blPushMotionQueue);
		RESET_FAKE(UC_flHz2Rdps);
		FFF_RESET_HISTORY();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for MC_blDirectProfileMove with parameters
*/
class TS_MC_blDirectProfileMove : public ::testing::TestWithParam<TDS_MC_blDirectProfileMove> {
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
		RESET_FAKE(MQ_blPushMotionQueue);
		RESET_FAKE(UC_flHz2Rdps);
		FFF_RESET_HISTORY();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for MC_blDecMotion with parameters
*/
class TS_MC_blDecMotion : public ::testing::TestWithParam<TDS_MC_blDecMotion> {
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
		RESET_FAKE(MQ_voFlushMotionQueue);
		RESET_FAKE(MQ_blPushMotionQueue);
		RESET_FAKE(UC_flHz2Rdps);
		FFF_RESET_HISTORY();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/******************************************************************************/
/*------------------------Global variables------------------------------------*/
/******************************************************************************/
/**
* @brief Instantiate the parameterized test suite for MC_blAbsMove/MC_blRelMove
* @note
* @anchor MC_blAbsRelMove_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
    MC_blAbsRelMove_TestData,
    TS_MC_blAbsRelMove,
    ::testing::Values(
		// 測試資料 1
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_InternalReg, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_InternalReg, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 2
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 3
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 2000}, {.fl = 5000}},
            // 輸入(輸入資料)
            {100000, 100, 0.005, 0.002}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 4
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 10000}, {.fl = 5000}},
            // 輸入(輸入資料)
            {100000, 100, 0.0005, 0.002}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 5
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 2000}, {.fl = 10000}},
            // 輸入(輸入資料)
            {100000, 100, 0.005, 0.0002}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 6
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 1, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 7
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            FALSE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, FALSE
        },
		// 測試資料 8
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            FALSE, 1, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE,
            // Mock假資料
            10, FALSE
        }
    )
);
* @endcode
*/
INSTANTIATE_TEST_SUITE_P(
    MC_blAbsRelMove_TestData,
    TS_MC_blAbsRelMove,
    ::testing::Values(
		// 測試資料 1
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_InternalReg, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_InternalReg, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 2
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 3
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 2000}, {.fl = 5000}},
            // 輸入(輸入資料)
            {100000, 100, 0.005, 0.002}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 4
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 10000}, {.fl = 5000}},
            // 輸入(輸入資料)
            {100000, 100, 0.0005, 0.002}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 5
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 2000}, {.fl = 10000}},
            // 輸入(輸入資料)
            {100000, 100, 0.005, 0.0002}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 6
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            TRUE, 1, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE,
            // Mock假資料
            10, TRUE
        },
		// 測試資料 6
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            FALSE, 0, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE,
            // Mock假資料
            10, FALSE
        },
		// 測試資料 7     
        TDS_MC_blAbsRelMove{
            // 確認(預期結果)
            FALSE, 1, {emMCT_MoveAbs, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.fl = 5000}, {.fl = 2500}},
            // 輸入(輸入資料)
            {100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE,
            // Mock假資料
            10, FALSE
        }
    )
);

/**
* @brief Instantiate the parameterized test suite for MC_blDirectProfileMove
* @note
* @anchor MC_blDirectProfileMove_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	MC_blDirectProfileMove_TestData,
	TS_MC_blDirectProfileMove,
	::testing::Values(
		// 測試資料 1
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			TRUE, {emMCT_MoveRel, emMST_InternalReg, {.sl = 100000}, {.fl = 10}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_InternalReg,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 2	
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			TRUE, {emMCT_MoveRel, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 3
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			TRUE, {emMCT_MoveRel, emMST_SystemOp, {.sl = 100000}, {.fl = 100}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp,
			// Mock假資料
			100, TRUE
		},
		// 測試資料 4		
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			FALSE, {emMCT_MoveRel, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp,
			// Mock假資料
			10, FALSE
		}
	)
);
* @endcode
*/
INSTANTIATE_TEST_SUITE_P(
	MC_blDirectProfileMove_TestData,
	TS_MC_blDirectProfileMove,
	::testing::Values(
		// 測試資料 1
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			TRUE, {emMCT_MoveRel, emMST_InternalReg, {.sl = 100000}, {.fl = 10}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_InternalReg,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 2	
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			TRUE, {emMCT_MoveRel, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 3
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			TRUE, {emMCT_MoveRel, emMST_SystemOp, {.sl = 100000}, {.fl = 100}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp,
			// Mock假資料
			100, TRUE
		},
		// 測試資料 4		
		TDS_MC_blDirectProfileMove{
			// 確認(預期結果)
			FALSE, {emMCT_MoveRel, emMST_SystemOp, {.sl = 100000}, {.fl = 10}, {.sl = 0}, {.sl = 0}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp,
			// Mock假資料
			10, FALSE
		}
	)
);

/**
* @brief Instantiate the parameterized test suite for MC_blDecMotion
* @note
* @anchor MC_blDecMotion_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	MC_blDecMotion_TestData,
	TS_MC_blDecMotion,
	::testing::Values(
		// 測試資料 1
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_InternalReg, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_InternalReg, FALSE, emMPT_Idle,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 2
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_Idle,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 3
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_Deceleration,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 4
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 2000}, {.fl = 5000}},
			// 輸入(輸入資料)
			{100000, 100, 0.005, 0.002}, emMST_SystemOp, FALSE, emMPT_Deceleration,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 5				
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 6
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 2000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.005, 0.002}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 7
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 10000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.0005, 0.002}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 8
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 2000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.005, 0.0002}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 9
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_Deceleration,
			// Mock假資料
			10, TRUE
		},	
		// 測試資料 10	
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 11
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_Deceleration,
			// Mock假資料
			10, FALSE
		},	
		// 測試資料 12	
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, FALSE
		},
		// 測試資料 13
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_Deceleration,
			// Mock假資料
			10, FALSE
		},	
		// 測試資料 14			
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_QuickStop,
			// Mock假資料
			10, FALSE
		}
	)
);
* @endcode
*/
INSTANTIATE_TEST_SUITE_P(
	MC_blDecMotion_TestData,
	TS_MC_blDecMotion,
	::testing::Values(
		// 測試資料 1
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_InternalReg, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_InternalReg, FALSE, emMPT_Idle,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 2
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_Idle,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 3
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_Deceleration,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 4
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 2000}, {.fl = 5000}},
			// 輸入(輸入資料)
			{100000, 100, 0.005, 0.002}, emMST_SystemOp, FALSE, emMPT_Deceleration,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 5				
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 6
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 2000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.005, 0.002}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 7
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 10000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.0005, 0.002}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 8
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 2000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.005, 0.0002}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 9
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_Deceleration,
			// Mock假資料
			10, TRUE
		},	
		// 測試資料 10	
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			TRUE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_QuickStop,
			// Mock假資料
			10, TRUE
		},
		// 測試資料 11
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_Deceleration,
			// Mock假資料
			10, FALSE
		},	
		// 測試資料 12	
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 0, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, FALSE, emMPT_QuickStop,
			// Mock假資料
			10, FALSE
		},
		// 測試資料 13
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 2500}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_Deceleration,
			// Mock假資料
			10, FALSE
		},	
		// 測試資料 14			
		TDS_MC_blDecMotion{
			// 確認(預期結果)
			FALSE, 1, {emMCT_DecMotion, emMST_SystemOp, {.fl = 0}, {.fl = 0}, {.fl = 5000}, {.fl = 10}},
			// 輸入(輸入資料)
			{100000, 100, 0.002, 0.004}, emMST_SystemOp, TRUE, emMPT_QuickStop,
			// Mock假資料
			10, FALSE
		}
	)
);

/******************************************************************************/
/*------------------------Test Functions--------------------------------------*/
/******************************************************************************/
/**
* @test This test verifies the MC_blAbsMove
* @note
* ### 測試場景 1
* - **目的**: 給定命令(不插斷命令)，並且Push motion queue成功，確認結果符合預期
* - **輸入**: 
*   1. 不插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**: 
*   - 創建Absolute move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**: 
*   1. 沒有執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "1~5"
* ### 測試場景 2
* - **目的**: 給定命令(插斷命令)，並且Push motion queue成功，確認結果符合預期
* - **輸入**: 
*   1. 插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**: 
*   - 創建Absolute move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**: 
*   1. 執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "6"
* ### 測試場景 3
* - **目的**: 給定命令(不插斷命令)，但Push motion queue失敗，確認結果符合預期
* - **輸入**: 
*   1. 不插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Absolute move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**: 
*   1. 沒有執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "7"
* ### 測試場景 4
* - **目的**: 給定命令(插斷命令)，但Push motion queue失敗，確認結果符合預期
* - **輸入**: 
*   1. 插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Absolute move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. 執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "8"
*/
TEST_P(TS_MC_blAbsRelMove, AbsMove) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_MC_blAbsRelMove stTD = GetParam();
	MQ_blPushMotionQueue_fake.return_val = stTD.MockData_blPushMQRtn;
	UC_flHz2Rdps_fake.return_val= stTD.MockData_flUCHz2Rdps;
	stTD.Expect_stQueueCommand.emMotionCmd = emMCT_MoveAbs;

	/* Call the process function and check the result
	 note:
	*/
	tQUEUE_CMD_STRUCT stCapturedData;
	Bool blResult = MC_blAbsMove(stTD.Fake_Data_stTarget, stTD.Fake_Data_emSourceType, stTD.Fake_Data_blIsImmediate);
	memcpy(&stCapturedData, MQ_blPushMotionQueue_fake.arg0_val, sizeof(tQUEUE_CMD_STRUCT));
	EXPECT_EQ(blResult, stTD.Expect_blResult);
	EXPECT_EQ(MQ_voFlushMotionQueue_fake.call_count, stTD.Expect_ubFlushFunctionCalledCount);
	EXPECT_EQ(stCapturedData.emMotionCmd, stTD.Expect_stQueueCommand.emMotionCmd);
	EXPECT_EQ(stCapturedData.emMotionSource, stTD.Expect_stQueueCommand.emMotionSource);
	EXPECT_EQ(stCapturedData.unValue1.sl, stTD.Expect_stQueueCommand.unValue1.sl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue2.fl, stTD.Expect_stQueueCommand.unValue2.fl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue3.fl, stTD.Expect_stQueueCommand.unValue3.fl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue4.fl, stTD.Expect_stQueueCommand.unValue4.fl);
}

/**
* @test This test verifies the MC_blRelMove
* @note
* ### 測試場景 1:
* - **目的**: 給定命令(不插斷命令)，並且Push motion queue成功，確認結果符合預期
* - **輸入**:
*   1. 不插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Relative move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. 沒有執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "1~5"	
* ### 測試場景 2:
* - **目的**: 給定命令(插斷命令)，並且Push motion queue成功，確認結果符合預期
* - **輸入**: 
*   1. 插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Relative move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. 執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "6"
* ### 測試場景 3:
* - **目的**: 給定命令(不插斷命令)，但Push motion queue失敗，確認結果符合預期
* - **輸入**: 
*   1. 不插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Relative move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. 沒有執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "7"
* ### 測試場景 4:
* - **目的**: 給定命令(插斷命令)，但Push motion queue失敗，確認結果符合預期
* - **輸入**:
*   1. 插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【Fake_Data_emSourceType】
*   3. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Relative move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. 執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blAbsRelMove_TestData "8"
*/
TEST_P(TS_MC_blAbsRelMove, RelMove) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_MC_blAbsRelMove stTD = GetParam();
	MQ_blPushMotionQueue_fake.return_val = stTD.MockData_blPushMQRtn;
	UC_flHz2Rdps_fake.return_val= stTD.MockData_flUCHz2Rdps;
	stTD.Expect_stQueueCommand.emMotionCmd = emMCT_MoveRel;

	/* Call the process function and check the result
	 note:
	*/
	tQUEUE_CMD_STRUCT stCapturedData;
	Bool blResult = MC_blRelMove(stTD.Fake_Data_stTarget, stTD.Fake_Data_emSourceType, stTD.Fake_Data_blIsImmediate);
	memcpy(&stCapturedData, MQ_blPushMotionQueue_fake.arg0_val, sizeof(tQUEUE_CMD_STRUCT));
	EXPECT_EQ(blResult, stTD.Expect_blResult);
	EXPECT_EQ(MQ_voFlushMotionQueue_fake.call_count, stTD.Expect_ubFlushFunctionCalledCount);
	EXPECT_EQ(stCapturedData.emMotionCmd, stTD.Expect_stQueueCommand.emMotionCmd);
	EXPECT_EQ(stCapturedData.emMotionSource, stTD.Expect_stQueueCommand.emMotionSource);
	EXPECT_EQ(stCapturedData.unValue1.sl, stTD.Expect_stQueueCommand.unValue1.sl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue2.fl, stTD.Expect_stQueueCommand.unValue2.fl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue3.fl, stTD.Expect_stQueueCommand.unValue3.fl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue4.fl, stTD.Expect_stQueueCommand.unValue4.fl);
}

/**
* @test This test verifies the MC_blDirectProfileMove
* @note
* ### 測試場景 1:
* - **目的**: 給定命令，並且Push motion queue成功，確認結果符合預期
* - **輸入**:
*   1. Motion Target【Fake_Data_stTarget】
*   2. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Direct profile move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   -  Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   2. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blDirectProfileMove_TestData "1~2"
* ### 測試場景 2:
* - **目的**: 給定命令，並且Push motion queue成功，確認結果符合預期
* - **輸入**:
*   1. Motion Target【Fake_Data_stTarget】
*   2. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Direct profile move命令
*   - Mock UC_flHz2Rdps()為100【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   2. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blDirectProfileMove_TestData "3"	
* ### 測試場景 3:
* - **目的**: 給定命令，但Push motion queue失敗，確認結果符合預期
* - **輸入**:
*   1. Motion Target【Fake_Data_stTarget】
*   2. Source Type【Fake_Data_emSourceType】
* - **動作**:
*   - 創建Direct profile move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   2. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blDirectProfileMove_TestData "4"
*/
TEST_P(TS_MC_blDirectProfileMove, DirectProfileMove) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_MC_blDirectProfileMove stTD = GetParam();
	MQ_blPushMotionQueue_fake.return_val = stTD.MockData_blPushMQRtn;
	UC_flHz2Rdps_fake.return_val= stTD.MockData_flUCHz2Rdps;

	/* Call the process function and check the result
	 note:
	*/
	tQUEUE_CMD_STRUCT stCapturedData;
	Bool blResult = MC_blDirectProfileMove(stTD.Fake_Data_stTarget, stTD.Fake_Data_emSourceType);
	memcpy(&stCapturedData, MQ_blPushMotionQueue_fake.arg0_val, sizeof(tQUEUE_CMD_STRUCT));
	EXPECT_EQ(blResult, stTD.Expect_blResult);
	EXPECT_EQ(stCapturedData.emMotionCmd, stTD.Expect_stQueueCommand.emMotionCmd);
	EXPECT_EQ(stCapturedData.emMotionSource, stTD.Expect_stQueueCommand.emMotionSource);
	EXPECT_EQ(stCapturedData.unValue1.sl, stTD.Expect_stQueueCommand.unValue1.sl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue2.fl, stTD.Expect_stQueueCommand.unValue2.fl);
	EXPECT_EQ(stCapturedData.unValue3.sl, stTD.Expect_stQueueCommand.unValue3.sl);
	EXPECT_EQ(stCapturedData.unValue4.sl, stTD.Expect_stQueueCommand.unValue4.sl);
}

/**
* @test This test verifies the MC_blDecMotion
* @note
* ### 測試場景 1:
* - **目的**: 給定命令(不插斷命令+非Quick Stop Motion profile type)，並且Push motion queue成功，確認結果符合預期
* - **輸入**:
*   1. 不插斷命令【Fake_Data_blIsImmediate】
*   2. Motion Target【Fake_Data_stTarget】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【Fake_Data_emMotionProfile】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. 沒有執行MQ_voFlushMotionQueue()【Expect_ubFlushFunctionCalledCount】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "1~4"
* ### 測試場景 2:
* - **目的**: 給定命令(不插斷命令+Quick Stop Motion profile type)，並且Push motion queue成功，確認結果符合預期
* - **輸入**:
*   1. 不插斷命令【Fake_Data_blIsImmediate】
*   2. Motion Target【Fake_Data_stTarget】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【Fake_Data_emMotionProfile】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. 確認沒有執行MQ_voFlushMotionQueue()【Expect_ubFlushFunctionCalledCount】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "5~8"
* ### 測試場景 3:
* - **目的**: 給定命令(插斷命令+非Quick Stop Motion profile type)，並且Push motion queue成功，確認結果符合預期
* - **輸入**:
*   1. 插斷命令【Fake_Data_blIsImmediate】
*   2. Motion Target【Fake_Data_stTarget】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【Fake_Data_emMotionProfile】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. 執行MQ_voFlushMotionQueue()【Expect_ubFlushFunctionCalledCount】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "9"
* ### 測試場景 4:
* - **目的**: 給定命令(插斷命令+Quick Stop Motion profile type)，並且Push motion queue成功，確認結果符合預期
* - **輸入**: 
*   1. 插斷命令【Fake_Data_blIsImmediate】
*   2. Motion Target【Fake_Data_stTarget】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【Fake_Data_emMotionProfile】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue成功【MockData_blPushMQRtn】
* - **確認**:
*   1. 執行MQ_voFlushMotionQueue()【Expect_ubFlushFunctionCalledCount】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果成功【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "10"
* ### 測試場景 5:
* - **目的**: 給定命令(不插斷命令+非Quick Stop Motion profile type)，但Push motion queue失敗，確認結果符合預期
* - **輸入**:
*   1. 不插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【MockData_blPushMQRtn】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【MockData_blPushMQRtn】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. 沒有執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "11"
* ### 測試場景 6:
* - **目的**: 給定命令(不插斷命令+Quick Stop Motion profile type)，但Push motion queue失敗，確認結果符合預期
* - **輸入**:
*   1. 插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【MockData_blPushMQRtn】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【MockData_blPushMQRtn】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. 沒有執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "12"
* ### 測試場景 7:
* - **目的**: 給定命令(插斷命令+非Quick Stop Motion profile type)，但Push motion queue失敗，確認結果符合預期
* - **輸入**:
*   1. 不插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【MockData_blPushMQRtn】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【MockData_blPushMQRtn】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. 執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "13"
* ### 測試場景 8:
* - **目的**: 給定命令(插斷命令+Quick Stop Motion profile type)，但Push motion queue失敗，確認結果符合預期
* - **輸入**:
*   1. 插斷命令【MockData_blPushMQRtn】
*   2. Motion Target【MockData_blPushMQRtn】
*   3. Source Type【Fake_Data_emSourceType】
*   4. Motion Profile Type【MockData_blPushMQRtn】
* - **動作**:
*   - 創建Decelerate move命令
*   - Mock UC_flHz2Rdps()為10【MockData_flUCHz2Rdps】
*   - Mock Push motion queue失敗【MockData_blPushMQRtn】
* - **確認**:
*   1. 執行MQ_voFlushMotionQueue()【MockData_flUCHz2Rdps】
*   2. MQ_blPushMotionQueue()的傳參符合預期【Expect_stQueueCommand】
*   3. 執行結果失敗【Expect_blResult】
* - **測試資料編號**: @ref MC_blDecMotion_TestData "14"
*/
TEST_P(TS_MC_blDecMotion, DecMotion) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_MC_blDecMotion stTD = GetParam();
	MQ_blPushMotionQueue_fake.return_val = stTD.MockData_blPushMQRtn;
	UC_flHz2Rdps_fake.return_val= stTD.MockData_flUCHz2Rdps;

	/* Call the process function and check the result
	 note:
	*/
	tQUEUE_CMD_STRUCT stCapturedData;
	Bool blResult = MC_blDecMotion(stTD.Fake_Data_stTarget, stTD.Fake_Data_emSourceType, stTD.Fake_Data_blIsImmediate, stTD.Fake_Data_emMotionProfile);
	memcpy(&stCapturedData, MQ_blPushMotionQueue_fake.arg0_val, sizeof(tQUEUE_CMD_STRUCT));
	EXPECT_EQ(blResult, stTD.Expect_blResult);
	EXPECT_EQ(MQ_voFlushMotionQueue_fake.call_count, stTD.Expect_ubFlushFunctionCalledCount);
	EXPECT_EQ(stCapturedData.emMotionCmd, stTD.Expect_stQueueCommand.emMotionCmd);
	EXPECT_EQ(stCapturedData.emMotionSource, stTD.Expect_stQueueCommand.emMotionSource);
	EXPECT_FLOAT_EQ(stCapturedData.unValue1.fl, stTD.Expect_stQueueCommand.unValue1.fl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue2.fl, stTD.Expect_stQueueCommand.unValue2.fl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue3.fl, stTD.Expect_stQueueCommand.unValue3.fl);
	EXPECT_FLOAT_EQ(stCapturedData.unValue4.fl, stTD.Expect_stQueueCommand.unValue4.fl);
}