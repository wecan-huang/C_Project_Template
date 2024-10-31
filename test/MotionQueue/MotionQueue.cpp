/**
 * @file		MotionQueue.cpp
 * @author		WK
 * @brief		Unit tests for the MotionQueue module.
 * @date		2024/10/14
 * @version		1.00
 *
 */


/******************************************************************************/
/*------------------------Includes--------------------------------------------*/
/******************************************************************************/
#include <gtest/gtest.h>

extern "C"
{
	#include "MacroDefine.h"
	#include "TypeDefine.h"
	#include "A/Queue.h"  // dependency
	#include "A/MotionQueue.h"  // The function under test
	#include "fff.h"  // FFF mocking framework

	DEFINE_FFF_GLOBALS
    FAKE_VALUE_FUNC(Bool, QUE_blCreateQueue, tCREATE_Q_ST_IN *);
	FAKE_VALUE_FUNC(tDE_Q_ST_OUT, QUE_stDeQueue, tQUEUE *);
	FAKE_VALUE_FUNC(Bool, QUE_blEnQueue, tEN_Q_ST_IN *);
	FAKE_VALUE_FUNC(Bool, QUE_blEmptyQueue, tQUEUE *);
	FAKE_VALUE_FUNC(UBYTE, QUE_ubGetQueueCnt, tQUEUE *);
}

/******************************************************************************/
/*------------------------Macro-----------------------------------------------*/
/******************************************************************************/
#define MOTION_QUEUE_MAX_SIZE	(10U)

/******************************************************************************/
/*------------------------Structures------------------------------------------*/
/******************************************************************************/
/**
* @brief Test Data Structure for MQ_blIsMotionQueueBusy
*/
struct TDS_MQ_blIsMotionQueueBusy
{
	// 確認(預期結果)		
	Bool Expect_blResult;

	// 輸入(輸入資料)

	// Mock假資料
	UBYTE MockData_Rtn;
};

/**
* @brief Test Data Structure for MQ_blPullMotionQueue
*/
struct TDS_MQ_blPullMotionQueue
{
	// 確認(預期結果)		
	Bool Expect_blResult;
	tQUEUE_CMD_STRUCT* Expect_stOut;

	// 輸入(輸入資料)
	tQUEUE_CMD_STRUCT** FakeData_stIn;

	// Mock假資料
	tDE_Q_ST_OUT MockData_Rtn;
};

/**
* @brief Test Data Structure for MQ_blPushMotionQueue
*/
struct TDS_MQ_blPushMotionQueue
{
	// 確認(預期結果)		
	Bool Expect_blResult;

	// 輸入(輸入資料)
	tQUEUE_CMD_STRUCT* FakeData_stIn;

	// Mock假資料
	Bool MockData_Rtn;
};

/******************************************************************************/
/*------------------------Class-----------------------------------------------*/
/******************************************************************************/
/**
* @brief Test fixture for MQ_blIsMotionQueueBusy with parameters
*/
class TS_MQ_blIsMotionQueueBusy : public ::testing::TestWithParam<TDS_MQ_blIsMotionQueueBusy> {
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
		RESET_FAKE(QUE_ubGetQueueCnt);
		FFF_RESET_HISTORY();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for MQ_blPullMotionQueue with parameters
*/
class TS_MQ_blPullMotionQueue : public ::testing::TestWithParam<TDS_MQ_blPullMotionQueue> {
public:
    // Declaration
	static tQUEUE_CMD_STRUCT *stQueueCmdPtr;
	static tQUEUE_CMD_STRUCT stMockQueueCommand[];
	static tDE_Q_ST_OUT stMockDequeueOut[];
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
		RESET_FAKE(QUE_stDeQueue);
		FFF_RESET_HISTORY();
		stQueueCmdPtr = NULL;
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for MQ_blPushMotionQueue with parameters
*/
class TS_MQ_blPushMotionQueue : public ::testing::TestWithParam<TDS_MQ_blPushMotionQueue> {
public:
	// Declaration
	static tQUEUE_CMD_STRUCT stMockQueueCommand[];
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
		RESET_FAKE(QUE_blEnQueue);
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
* @brief Instantiate the parameterized test suite for MQ_blIsMotionQueueBusy
* @note
* @anchor MQ_blIsMotionQueueBusy_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	MQ_blIsMotionQueueBusy_TestData,
	TS_MQ_blIsMotionQueueBusy,
	::testing::Values(
		// 測試資料 1
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			1
		},
		// 測試資料 2
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			2
		},
		// 測試資料 3
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			3
		},
		// 測試資料 4
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			4
		},
		// 測試資料 5
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			5
		},
		// 測試資料 6
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			6
		},
		// 測試資料 7
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			7
		},
		// 測試資料 8
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE,
			// Mock假資料
			8
		},
		// 測試資料 9
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			9
		},
		// 測試資料 10
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			TRUE, 
			// Mock假資料
			MOTION_QUEUE_MAX_SIZE
		},
		// 測試資料 11
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			TRUE, 
			// Mock假資料
			MOTION_QUEUE_MAX_SIZE+1
		}
	)
);
* @endcode
*/
INSTANTIATE_TEST_SUITE_P(
	MQ_blIsMotionQueueBusy_TestData,
	TS_MQ_blIsMotionQueueBusy,
	::testing::Values(
		// 測試資料 1
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			1
		},
		// 測試資料 2
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			2
		},
		// 測試資料 3
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			3
		},
		// 測試資料 4
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			4
		},
		// 測試資料 5
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			5
		},
		// 測試資料 6
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			6
		},
		// 測試資料 7
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			7
		},
		// 測試資料 8
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE,
			// Mock假資料
			8
		},
		// 測試資料 9
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			FALSE, 
			// Mock假資料
			9
		},
		// 測試資料 10
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			TRUE, 
			// Mock假資料
			MOTION_QUEUE_MAX_SIZE
		},
		// 測試資料 11
		TDS_MQ_blIsMotionQueueBusy{
			// 確認(預期結果)
			TRUE, 
			// Mock假資料
			MOTION_QUEUE_MAX_SIZE+1
		}
	)
);

/**
* @brief Instantiate the parameterized test suite for MQ_blPullMotionQueue
* @note
* @anchor MQ_blPullMotionQueue_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	MQ_blPullMotionQueue_TestData,
	TS_MQ_blPullMotionQueue,
	::testing::Values(
		// 測試資料 1
		TDS_MQ_blPullMotionQueue{
			// 確認(預期結果)
			TRUE, &TS_MQ_blPullMotionQueue::stMockQueueCommand[0],
			// 輸入(輸入資料)
			&TS_MQ_blPullMotionQueue::stQueueCmdPtr,
			// Mock假資料
			TS_MQ_blPullMotionQueue::stMockDequeueOut[0]
		},
		// 測試資料 2
		TDS_MQ_blPullMotionQueue{
			// 確認(預期結果)
			FALSE, NULL,
			// 輸入(輸入資料)
			&TS_MQ_blPullMotionQueue::stQueueCmdPtr,
			// Mock假資料
			TS_MQ_blPullMotionQueue::stMockDequeueOut[1]
		},
		// 測試資料 3
		TDS_MQ_blPullMotionQueue{
			// 確認(預期結果)
			FALSE, NULL,
			// 輸入(輸入資料)
			NULL,
			// Mock假資料
			TS_MQ_blPullMotionQueue::stMockDequeueOut[1]
		}
	)
);
* @endcode
*/
// Definition
tQUEUE_CMD_STRUCT TS_MQ_blPullMotionQueue::stMockQueueCommand[] = {
	{emMCT_MoveRel, emMST_ExternalPulse, 1, 2, 3, 4},
    {emMCT_DecMotion, emMST_UART, 1, 2, 3, 4}
}; 
tDE_Q_ST_OUT TS_MQ_blPullMotionQueue::stMockDequeueOut[] = {
	{&TS_MQ_blPullMotionQueue::stMockQueueCommand[0], TRUE},
	{&TS_MQ_blPullMotionQueue::stMockQueueCommand[1], FALSE}
};
tQUEUE_CMD_STRUCT* TS_MQ_blPullMotionQueue::stQueueCmdPtr = NULL;

INSTANTIATE_TEST_SUITE_P(
	MQ_blPullMotionQueue_TestData,
	TS_MQ_blPullMotionQueue,
	::testing::Values(
		// 測試資料 1
		TDS_MQ_blPullMotionQueue{
			// 確認(預期結果)
			TRUE, &TS_MQ_blPullMotionQueue::stMockQueueCommand[0],
			// 輸入(輸入資料)
			&TS_MQ_blPullMotionQueue::stQueueCmdPtr,
			// Mock假資料
			TS_MQ_blPullMotionQueue::stMockDequeueOut[0]
		},
		// 測試資料 2
		TDS_MQ_blPullMotionQueue{
			// 確認(預期結果)
			FALSE, NULL,
			// 輸入(輸入資料)
			&TS_MQ_blPullMotionQueue::stQueueCmdPtr,
			// Mock假資料
			TS_MQ_blPullMotionQueue::stMockDequeueOut[1]
		},
		// 測試資料 3
		TDS_MQ_blPullMotionQueue{
			// 確認(預期結果)
			FALSE, NULL,
			// 輸入(輸入資料)
			NULL,
			// Mock假資料
			TS_MQ_blPullMotionQueue::stMockDequeueOut[1]
		}
	)
);

/**
* @brief Instantiate the parameterized test suite for MQ_blPushMotionQueue
* @note
* @anchor MQ_blPushMotionQueue_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	MQ_blPushMotionQueue_TestData,
	TS_MQ_blPushMotionQueue,
	::testing::Values(
		// 測試資料 1
		TDS_MQ_blPushMotionQueue{
			// 確認(預期結果)
			TRUE,
			// 輸入(輸入資料)
			&TS_MQ_blPushMotionQueue::stMockQueueCommand[0],
			// Mock假資料
			TRUE
		},
		// 測試資料 2
        TDS_MQ_blPushMotionQueue{
			// 確認(預期結果)
			FALSE,
			// 輸入(輸入資料)
			&TS_MQ_blPushMotionQueue::stMockQueueCommand[0],
			// Mock假資料
			FALSE
		},
		// 測試資料 3
		TDS_MQ_blPushMotionQueue{
			// 確認(預期結果)
			FALSE,
			// 輸入(輸入資料)
			NULL,
			// Mock假資料
			FALSE
		}
	)
);
* @endcode
*/
// Definition
tQUEUE_CMD_STRUCT TS_MQ_blPushMotionQueue::stMockQueueCommand[] = {
	{emMCT_MoveRel, emMST_ExternalPulse, 1, 2, 3, 4},
    {emMCT_DecMotion, emMST_UART, 1, 2, 3, 4}
};
INSTANTIATE_TEST_SUITE_P(
	MQ_blPushMotionQueue_TestData,
	TS_MQ_blPushMotionQueue,
	::testing::Values(
		// 測試資料 1
		TDS_MQ_blPushMotionQueue{
			// 確認(預期結果)
			TRUE,
			// 輸入(輸入資料)
			&TS_MQ_blPushMotionQueue::stMockQueueCommand[0],
			// Mock假資料
			TRUE
		},
		// 測試資料 2
        TDS_MQ_blPushMotionQueue{
			// 確認(預期結果)
			FALSE,
			// 輸入(輸入資料)
			&TS_MQ_blPushMotionQueue::stMockQueueCommand[0],
			// Mock假資料
			FALSE
		},
		// 測試資料 3
		TDS_MQ_blPushMotionQueue{
			// 確認(預期結果)
			FALSE,
			// 輸入(輸入資料)
			NULL,
			// Mock假資料
			FALSE
		}
	)
);


/******************************************************************************/
/*------------------------Test Functions--------------------------------------*/
/******************************************************************************/
/**
* @test This test verifies the MQ_blIsMotionQueueBusy
* @note
* ### 測試場景 1
* - **目的**: Queue未滿，回傳FALSE
* - **輸入**: NA
* - **動作**: 
*   - 模擬queue count為1~9【MockData_Rtn】
* - **確認**: 
*   1. Motion queue不是busy狀態【Expect_blResult】
* - **測試資料編號**: @ref MQ_blIsMotionQueueBusy_TestData "1~9"
* ### 測試場景 2
* - **目的**: Queue已滿，回傳TRUE
* - **輸入**: NA
* - **動作**: 
*   - 模擬queue count為10~11【MockData_Rtn】
* - **確認**: 
*   1. Motion queue busy狀態【Expect_blResult】
* - **測試資料編號**: @ref MQ_blIsMotionQueueBusy_TestData "10、11"
*/
TEST_P(TS_MQ_blIsMotionQueueBusy, CheckMotionQueueBusyStatus) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_MQ_blIsMotionQueueBusy stTD = GetParam();
	QUE_ubGetQueueCnt_fake.return_val = stTD.MockData_Rtn;

	/* Call the process function and check the result
	 note:
	*/
	EXPECT_EQ(MQ_blIsMotionQueueBusy(), stTD.Expect_blResult);
}

/**
* @test This test verifies the MQ_blPullMotionQueue
* @note
* ### 測試場景 1
* - **目的**: Dequeue成功，motion command成功被讀出，數據被更新
* - **輸入**: 
*   1. MQ_blPullMotionQueue()的傳參【FakeData_stIn】
* - **動作**: 
*   - 模擬Dequeue正確資料【MockData_Rtn】
* - **確認**: 
*   1. item內容如預期資料【Expect_stOut】
*   2. Dequeue狀態成功【Expect_blResult】
* - **測試資料編號**: @ref MQ_blPullMotionQueue_TestData "1"
* ### 測試場景 2
* - **目的**: Dequeue失敗，數據不更新
* - **輸入**: 
*   1. MQ_blPullMotionQueue()的傳參【FakeData_stIn】
* - **動作**: 
*   - 模擬Dequeue失敗【MockData_Rtn】
* - **確認**: 
*   1. item內容為NULL【Expect_stOut】
*   2. Dequeue狀態失敗【Expect_blResult】
* - **測試資料編號**: @ref MQ_blPullMotionQueue_TestData "2"
* ### 測試場景 3
* - **目的**: 給定命令(不插斷命令)，並且Push motion queue成功，確認結果符合預期
* - **輸入**: 
*   1. NULL【FakeData_stIn】
* - **動作**: 
*   - 模擬Dequeue失敗【MockData_Rtn】
* - **確認**: 
*   1. item內容為NULL【Expect_stOut】
*   2. Dequeue狀態失敗【Expect_blResult】
* - **測試資料編號**: @ref MQ_blPullMotionQueue_TestData "3"
*/
TEST_P(TS_MQ_blPullMotionQueue, PullMotionQueue) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_MQ_blPullMotionQueue stTD = GetParam();
	QUE_stDeQueue_fake.return_val = stTD.MockData_Rtn;

	/* Call the process function and check the result
	 note:
	*/
	EXPECT_EQ(MQ_blPullMotionQueue(stTD.FakeData_stIn), stTD.Expect_blResult);
	if(stTD.FakeData_stIn!=NULL)
	{
		EXPECT_EQ(*stTD.FakeData_stIn, stTD.Expect_stOut);
		if(*stTD.FakeData_stIn!=NULL)
		{
			EXPECT_EQ((*stTD.FakeData_stIn)->emMotionCmd, stTD.Expect_stOut->emMotionCmd);
			EXPECT_EQ((*stTD.FakeData_stIn)->emMotionSource, stTD.Expect_stOut->emMotionSource);
			EXPECT_EQ((*stTD.FakeData_stIn)->unValue1.ul, stTD.Expect_stOut->unValue1.ul);
			EXPECT_EQ((*stTD.FakeData_stIn)->unValue2.ul, stTD.Expect_stOut->unValue2.ul);
			EXPECT_EQ((*stTD.FakeData_stIn)->unValue3.ul, stTD.Expect_stOut->unValue3.ul);
			EXPECT_EQ((*stTD.FakeData_stIn)->unValue4.ul, stTD.Expect_stOut->unValue4.ul);
		}
	}

}

/**
* @test This test verifies the MQ_blPushMotionQueue
* @note
* ### 測試場景 1
* - **目的**: Enqueue成功，回傳成功
* - **輸入**: 
*   1. MQ_blPushMotionQueue()的傳參【FakeData_stIn】
* - **動作**: 
*   - 模擬Enqueue成功【MockData_Rtn】
* - **確認**: 
*   1. Push motion queue狀態成功【Expect_blResult】
* - **測試資料編號**: @ref MQ_blPushMotionQueue_TestData "1"
* ### 測試場景 2
* - **目的**: Enqueue失敗，回傳失敗
* - **輸入**: 
*   1. MQ_blPushMotionQueue()的傳參【FakeData_stIn】
* - **動作**: 
*   - 模擬Enqueue失敗【MockData_Rtn】
* - **確認**: 
*   1. Push motion queue狀態失敗【Expect_blResult】	
* - **測試資料編號**: @ref MQ_blPushMotionQueue_TestData "2"
* ### 測試場景 3
* - **目的**: Queue command指標是NULL，回傳失敗
* - **輸入**: 
*   1. MQ_blPushMotionQueue()的傳參【FakeData_stIn】
* - **動作**: 
*   - 模擬Enqueue失敗【MockData_Rtn】
* - **確認**: 
*   1. Push motion queue狀態失敗【Expect_blResult】	
* - **測試資料編號**: @ref MQ_blPushMotionQueue_TestData "3"
*/
TEST_P(TS_MQ_blPushMotionQueue, PushMotionQueue) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_MQ_blPushMotionQueue stTD = GetParam();
	QUE_blEnQueue_fake.return_val = stTD.MockData_Rtn;

	/* Call the process function and check the result
	 note:
	*/
	EXPECT_EQ(MQ_blPushMotionQueue(stTD.FakeData_stIn), stTD.Expect_blResult);
}
