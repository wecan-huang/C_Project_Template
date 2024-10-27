/**
 * @file		Queue.cpp
 * @author		WK
 * @brief		Unit tests for the Queue module.
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
	#include "A/Queue.h"  // The function under test
}

/******************************************************************************/
/*------------------------Macro-----------------------------------------------*/
/******************************************************************************/
typedef UWORD    			ITEM_TYPE;
#define ITEM_SIZE 			sizeof(ITEM_TYPE)
#define ITEM_BUFFER_SIZE	(10U)
#define QUEUE_ITEM_MAX_SIZE	(256U)
#define QUEUE_MAX_SIZE		(256U)

/******************************************************************************/
/*------------------------Structures------------------------------------------*/
/******************************************************************************/
/**
* @brief Test Data Structure for QUE_blCreateQueue
*/
struct TDS_QUE_blCreateQueue
{
	// 確認(預期結果)
	Bool Expect_blResult;
	tQUEUE Expect_stQueue;

	// 輸入(輸入資料)
	tCREATE_Q_ST_IN FakeData_stIn;

	// Mock假資料

};

/**
* @brief Test Data Structure for QUE_stDeQueue
*/
struct TDS_QUE_stDeQueue
{
	// 確認(預期結果)
	Bool Expect_blResult;
	tQUEUE *Expect_stQueue;
	ITEM_TYPE *Expect_ItemDataAdr;

	// 輸入(輸入資料)
	tQUEUE *FakeData_stQueue;

	// Mock假資料
};

/**
* @brief Test Data Structure for QUE_blEnQueue
*/
struct TDS_QUE_blEnQueue
{
	// 確認(預期結果)
	Bool Expect_blResult;
	tQUEUE *Expect_stQueue;
	ITEM_TYPE Expect_ItemData;

	// 輸入(輸入資料)
	ITEM_TYPE FakeData_ItemIdx;
	tEN_Q_ST_IN *FakeData_stIn;

	// Mock假資料
};

/**
* @brief Test Data Structure for QUE_blEmptyQueue
*/
struct TDS_QUE_blEmptyQueue
{
	// 確認(預期結果)
	Bool Expect_blResult;
	tQUEUE *Expect_stQueue;

	// 輸入(輸入資料)
	tQUEUE *FakeData_stQueue;

	// Mock假資料
};

/**
* @brief Test Data Structure for QUE_ubGetQueueCnt
*/
struct TDS_QUE_ubGetQueueCnt
{
	// 確認(預期結果)
	UBYTE Expect_ubResult;

	// 輸入(輸入資料)
	tQUEUE *FakeData_stQueue;

	// Mock假資料
};

/******************************************************************************/
/*------------------------Class-----------------------------------------------*/
/******************************************************************************/
/**
* @brief Test fixture for QUE_blCreateQueue with parameters
*/
class TS_QUE_blCreateQueue : public ::testing::TestWithParam<TDS_QUE_blCreateQueue> {
public:
    // Declaration
	static tQUEUE stFakeQueue;
	static ITEM_TYPE FakeItemBuf[ITEM_BUFFER_SIZE];
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
		TS_QUE_blCreateQueue::stFakeQueue.voItemBufPtr = NULL;
		TS_QUE_blCreateQueue::stFakeQueue.ubItemSize = 0;
		TS_QUE_blCreateQueue::stFakeQueue.ubFront = 0;
		TS_QUE_blCreateQueue::stFakeQueue.ubRear = 0;
		TS_QUE_blCreateQueue::stFakeQueue.ubSize = 0;
		TS_QUE_blCreateQueue::stFakeQueue.ubCapacity = 0;
		memset(TS_QUE_blCreateQueue::FakeItemBuf, 0, ITEM_BUFFER_SIZE);
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for QUE_stDeQueue with parameters
*/
class TS_QUE_stDeQueue : public ::testing::TestWithParam<TDS_QUE_stDeQueue> {
public:
	// Declaration
	static tQUEUE stExpectedQueue[];
	static tQUEUE stFakeQueue[];
	static ITEM_TYPE FakeItemBuf[ITEM_BUFFER_SIZE];
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for QUE_blEnQueue with parameters
*/
class TS_QUE_blEnQueue : public ::testing::TestWithParam<TDS_QUE_blEnQueue> {
public:
	// Declaration
	static ITEM_TYPE InputItem[];
	static tQUEUE stExpectedQueue[];
	static tQUEUE stFakeQueue[];
	static ITEM_TYPE FakeItemBuf[][ITEM_BUFFER_SIZE];
	static tEN_Q_ST_IN FakeData_stIn[];
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for QUE_blEmptyQueue with parameters
*/
class TS_QUE_blEmptyQueue : public ::testing::TestWithParam<TDS_QUE_blEmptyQueue> {
public:
	// Declaration
	static tQUEUE stExpectedQueue[];
	static tQUEUE stFakeQueue[];
	static ITEM_TYPE FakeItemBuf[][ITEM_BUFFER_SIZE];
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};

/**
* @brief Test fixture for QUE_ubGetQueueCnt with parameters
*/
class TS_QUE_ubGetQueueCnt : public ::testing::TestWithParam<TDS_QUE_ubGetQueueCnt> {
public:
	// Declaration
	static ITEM_TYPE FakeItemBuf[ITEM_BUFFER_SIZE];
	static tQUEUE stFakeQueue[];
protected:
	using ::testing::Test::SetUp;

	void SetUp() override {
		// 測試前執行行為
		Test::SetUp();
	}

	void TearDown() override {
		// 測試後執行行為
	}
};


/******************************************************************************/
/*------------------------Global variables------------------------------------*/
/******************************************************************************/
/**
* @brief Instantiate the parameterized test suite for QUE_blCreateQueue
* @note
* @anchor QUE_blCreateQueue_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	QUE_blCreateQueue_TestData,
	TS_QUE_blCreateQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			TRUE, {TS_QUE_blCreateQueue::FakeItemBuf, sizeof(ITEM_TYPE), 0, 0, 0, ITEM_BUFFER_SIZE},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, TS_QUE_blCreateQueue::FakeItemBuf, ITEM_SIZE, ITEM_BUFFER_SIZE}
		},
		// 測試資料 2
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{NULL, TS_QUE_blCreateQueue::FakeItemBuf, ITEM_SIZE, ITEM_BUFFER_SIZE}
		},
		// 測試資料 3
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, NULL, ITEM_SIZE, ITEM_BUFFER_SIZE}
		},
		// 測試資料 4
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, TS_QUE_blCreateQueue::FakeItemBuf, QUEUE_ITEM_MAX_SIZE+1, ITEM_BUFFER_SIZE}
		},
		// 測試資料 5
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, TS_QUE_blCreateQueue::FakeItemBuf, ITEM_SIZE, QUEUE_MAX_SIZE+1}
		}							
	)
);
* @endcode
*/
// Definition
tQUEUE TS_QUE_blCreateQueue::stFakeQueue;
ITEM_TYPE TS_QUE_blCreateQueue::FakeItemBuf[ITEM_BUFFER_SIZE];

INSTANTIATE_TEST_SUITE_P(
	QUE_blCreateQueue_TestData,
	TS_QUE_blCreateQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			TRUE, {TS_QUE_blCreateQueue::FakeItemBuf, sizeof(ITEM_TYPE), 0, 0, 0, ITEM_BUFFER_SIZE},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, TS_QUE_blCreateQueue::FakeItemBuf, ITEM_SIZE, ITEM_BUFFER_SIZE}
		},
		// 測試資料 2
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{NULL, TS_QUE_blCreateQueue::FakeItemBuf, ITEM_SIZE, ITEM_BUFFER_SIZE}
		},
		// 測試資料 3
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, NULL, ITEM_SIZE, ITEM_BUFFER_SIZE}
		},
		// 測試資料 4
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, TS_QUE_blCreateQueue::FakeItemBuf, QUEUE_ITEM_MAX_SIZE+1, ITEM_BUFFER_SIZE}
		},
		// 測試資料 5
		TDS_QUE_blCreateQueue{
			// 確認(預期結果)
			FALSE, {NULL, 0, 0, 0, 0, 0},
			// 輸入(輸入資料)
			{&TS_QUE_blCreateQueue::stFakeQueue, TS_QUE_blCreateQueue::FakeItemBuf, ITEM_SIZE, QUEUE_MAX_SIZE+1}
		}							
	)
);

/**
* @brief Instantiate the parameterized test suite for QUE_stDeQueue
* @note
* @anchor QUE_stDeQueue_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	QUE_stDeQueue_TestData,
	TS_QUE_stDeQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_stDeQueue::stExpectedQueue[0], &TS_QUE_stDeQueue::FakeItemBuf[0],
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[0]
		},
		// 測試資料 2
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_stDeQueue::stExpectedQueue[1], &TS_QUE_stDeQueue::FakeItemBuf[1],
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[1]
		},
		// 測試資料 3
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_stDeQueue::stExpectedQueue[2], NULL,
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[2]
		},
		// 測試資料 4
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			FALSE, NULL, NULL,
			// 輸入(輸入資料)
			NULL
		},
		// 測試資料 5
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_stDeQueue::stExpectedQueue[3], NULL,
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[3]
		}									
	)
);
* @endcode
*/
// Definition
tQUEUE TS_QUE_stDeQueue::stExpectedQueue[] = {
	{TS_QUE_stDeQueue::FakeItemBuf, ITEM_SIZE, 1, 1, 0, ITEM_BUFFER_SIZE},
	{TS_QUE_stDeQueue::FakeItemBuf, ITEM_SIZE, 2, 3, 0, ITEM_BUFFER_SIZE},
	{TS_QUE_stDeQueue::FakeItemBuf, ITEM_SIZE, 2, 2, 0, ITEM_BUFFER_SIZE},
	{NULL, ITEM_SIZE, 2, 2, 0, ITEM_BUFFER_SIZE}
};
tQUEUE TS_QUE_stDeQueue::stFakeQueue[] = {
	{TS_QUE_stDeQueue::FakeItemBuf, ITEM_SIZE, 0, 1, 1, ITEM_BUFFER_SIZE},
	{TS_QUE_stDeQueue::FakeItemBuf, ITEM_SIZE, 1, 3, 1, ITEM_BUFFER_SIZE},
	{TS_QUE_stDeQueue::FakeItemBuf, ITEM_SIZE, 2, 2, 0, ITEM_BUFFER_SIZE},
	{NULL, ITEM_SIZE, 2, 2, 0, ITEM_BUFFER_SIZE}
};
ITEM_TYPE TS_QUE_stDeQueue::FakeItemBuf[ITEM_BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

INSTANTIATE_TEST_SUITE_P(
	QUE_stDeQueue_TestData,
	TS_QUE_stDeQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_stDeQueue::stExpectedQueue[0], &TS_QUE_stDeQueue::FakeItemBuf[0],
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[0]
		},
		// 測試資料 2
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_stDeQueue::stExpectedQueue[1], &TS_QUE_stDeQueue::FakeItemBuf[1],
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[1]
		},
		// 測試資料 3
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_stDeQueue::stExpectedQueue[2], NULL,
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[2]
		},
		// 測試資料 4
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			FALSE, NULL, NULL,
			// 輸入(輸入資料)
			NULL
		},
		// 測試資料 5
		TDS_QUE_stDeQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_stDeQueue::stExpectedQueue[3], NULL,
			// 輸入(輸入資料)
			&TS_QUE_stDeQueue::stFakeQueue[3]
		}									
	)
);

/**
* @brief Instantiate the parameterized test suite for QUE_blEnQueue
* @note
* @anchor QUE_blEnQueue_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	QUE_blEnQueue_TestData,
	TS_QUE_blEnQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEnQueue::stExpectedQueue[0], 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[0]
		},
		// 測試資料 2
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEnQueue::stExpectedQueue[1], 10,
			// 輸入(輸入資料)
			9, &TS_QUE_blEnQueue::FakeData_stIn[1]
		},
		// 測試資料 3
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEnQueue::stExpectedQueue[2], 10,
			// 輸入(輸入資料)
			7, &TS_QUE_blEnQueue::FakeData_stIn[2]
		},
		// 測試資料 4
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_blEnQueue::stExpectedQueue[3], 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[3]
		},
		// 測試資料 5
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_blEnQueue::stExpectedQueue[0], 0,
			// 輸入(輸入資料)
			0, NULL
		},
		// 測試資料 6
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, NULL, 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[4]
		},
		// 測試資料 7
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_blEnQueue::stExpectedQueue[4], 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[5]
		}
	)
);
* @endcode
*/
// Definition
ITEM_TYPE TS_QUE_blEnQueue::InputItem[] = {
	1, 10, 11
};
ITEM_TYPE TS_QUE_blEnQueue::FakeItemBuf[][ITEM_BUFFER_SIZE] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
	{3, 4, 5, 6, 7, 8, 9, 0, 1, 2},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
};
tQUEUE TS_QUE_blEnQueue::stExpectedQueue[] = {
	{TS_QUE_blEnQueue::FakeItemBuf[0], ITEM_SIZE, 0, 1, 1, ITEM_BUFFER_SIZE},
	{TS_QUE_blEnQueue::FakeItemBuf[1], ITEM_SIZE, 0, 0, 10, ITEM_BUFFER_SIZE},
	{TS_QUE_blEnQueue::FakeItemBuf[2], ITEM_SIZE, 8, 8, 10, ITEM_BUFFER_SIZE},
	{TS_QUE_blEnQueue::FakeItemBuf[3], ITEM_SIZE, 0, 0, 10, ITEM_BUFFER_SIZE},
	{TS_QUE_blEnQueue::FakeItemBuf[0], ITEM_SIZE, 0, 0, 0, ITEM_BUFFER_SIZE},
};
tQUEUE TS_QUE_blEnQueue::stFakeQueue[] = {
	{TS_QUE_blEnQueue::FakeItemBuf[0], ITEM_SIZE, 0, 0, 0, ITEM_BUFFER_SIZE},
	{TS_QUE_blEnQueue::FakeItemBuf[1], ITEM_SIZE, 0, 9, 9, ITEM_BUFFER_SIZE},
	{TS_QUE_blEnQueue::FakeItemBuf[2], ITEM_SIZE, 8, 7, 9, ITEM_BUFFER_SIZE},
	{TS_QUE_blEnQueue::FakeItemBuf[3], ITEM_SIZE, 0, 0, 10, ITEM_BUFFER_SIZE},
	{NULL, ITEM_SIZE, 0, 0, 10, ITEM_BUFFER_SIZE},
};
tEN_Q_ST_IN TS_QUE_blEnQueue::FakeData_stIn[] = {
	{&TS_QUE_blEnQueue::stFakeQueue[0], &TS_QUE_blEnQueue::InputItem[0]},
	{&TS_QUE_blEnQueue::stFakeQueue[1], &TS_QUE_blEnQueue::InputItem[1]},
	{&TS_QUE_blEnQueue::stFakeQueue[2], &TS_QUE_blEnQueue::InputItem[1]},
	{&TS_QUE_blEnQueue::stFakeQueue[3], &TS_QUE_blEnQueue::InputItem[2]},
	{NULL, &TS_QUE_blEnQueue::InputItem[0]},
	{&TS_QUE_blEnQueue::stFakeQueue[4], &TS_QUE_blEnQueue::InputItem[0]},
};
INSTANTIATE_TEST_SUITE_P(
	QUE_blEnQueue_TestData,
	TS_QUE_blEnQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEnQueue::stExpectedQueue[0], 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[0]
		},
		// 測試資料 2
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEnQueue::stExpectedQueue[1], 10,
			// 輸入(輸入資料)
			9, &TS_QUE_blEnQueue::FakeData_stIn[1]
		},
		// 測試資料 3
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEnQueue::stExpectedQueue[2], 10,
			// 輸入(輸入資料)
			7, &TS_QUE_blEnQueue::FakeData_stIn[2]
		},
		// 測試資料 4
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_blEnQueue::stExpectedQueue[3], 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[3]
		},
		// 測試資料 5
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_blEnQueue::stExpectedQueue[0], 0,
			// 輸入(輸入資料)
			0, NULL
		},
		// 測試資料 6
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, NULL, 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[4]
		},
		// 測試資料 7
		TDS_QUE_blEnQueue{
			// 確認(預期結果)
			FALSE, &TS_QUE_blEnQueue::stExpectedQueue[4], 1,
			// 輸入(輸入資料)
			0, &TS_QUE_blEnQueue::FakeData_stIn[5]
		}
	)
);

/**
* @brief Instantiate the parameterized test suite for QUE_blEmptyQueue
* @note
* @anchor QUE_blEmptyQueue_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	QUE_blEmptyQueue_TestData,
	TS_QUE_blEmptyQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_blEmptyQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEmptyQueue::stExpectedQueue[0],
			// 輸入(輸入資料)
			&TS_QUE_blEmptyQueue::stFakeQueue[0]
		},
		// 測試資料 2
		TDS_QUE_blEmptyQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEmptyQueue::stExpectedQueue[1],
			// 輸入(輸入資料)
			&TS_QUE_blEmptyQueue::stFakeQueue[1]
		},
		// 測試資料 3
		TDS_QUE_blEmptyQueue{
			// 確認(預期結果)
			FALSE, NULL,
			// 輸入(輸入資料)
			NULL
		}				
	)
);
* @endcode
*/
// Definition
ITEM_TYPE TS_QUE_blEmptyQueue::FakeItemBuf[][ITEM_BUFFER_SIZE] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};
tQUEUE TS_QUE_blEmptyQueue::stExpectedQueue[] = {
	{TS_QUE_blEmptyQueue::FakeItemBuf[0], ITEM_SIZE, 0, 0, 0, ITEM_BUFFER_SIZE},
	{TS_QUE_blEmptyQueue::FakeItemBuf[1], ITEM_SIZE, 0, 0, 0, ITEM_BUFFER_SIZE},
};
tQUEUE TS_QUE_blEmptyQueue::stFakeQueue[] = {
	{TS_QUE_blEmptyQueue::FakeItemBuf[0], ITEM_SIZE, 0, 0, 0, ITEM_BUFFER_SIZE},
	{TS_QUE_blEmptyQueue::FakeItemBuf[1], ITEM_SIZE, 0, 0, 10, ITEM_BUFFER_SIZE},
};

INSTANTIATE_TEST_SUITE_P(
	QUE_blEmptyQueue_TestData,
	TS_QUE_blEmptyQueue,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_blEmptyQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEmptyQueue::stExpectedQueue[0],
			// 輸入(輸入資料)
			&TS_QUE_blEmptyQueue::stFakeQueue[0]
		},
		// 測試資料 2
		TDS_QUE_blEmptyQueue{
			// 確認(預期結果)
			TRUE, &TS_QUE_blEmptyQueue::stExpectedQueue[1],
			// 輸入(輸入資料)
			&TS_QUE_blEmptyQueue::stFakeQueue[1]
		},
		// 測試資料 3
		TDS_QUE_blEmptyQueue{
			// 確認(預期結果)
			FALSE, NULL,
			// 輸入(輸入資料)
			NULL
		}				
	)
);

/**
* @brief Instantiate the parameterized test suite for QQUE_ubGetQueueCnt
* @note
* @anchor QUE_ubGetQueueCnt_TestData
* 測試資料(Copy from code)：
* @code
INSTANTIATE_TEST_SUITE_P(
	QUE_ubGetQueueCnt_TestData,
	TS_QUE_ubGetQueueCnt,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			0,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[0]
		},
		// 測試資料 2
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			1,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[1]
		},
		// 測試資料 3
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			1,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[2]
		},
		// 測試資料 4
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			10,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[3]
		},
		// 測試資料 5
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			10,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[4]
		},
		// 測試資料 6
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			0,
			// 輸入(輸入資料)
			NULL
		}	
	)
);
* @endcode
*/
// Definition
ITEM_TYPE TS_QUE_ubGetQueueCnt::FakeItemBuf[ITEM_BUFFER_SIZE] = {0};
tQUEUE TS_QUE_ubGetQueueCnt::stFakeQueue[] = {
	{TS_QUE_ubGetQueueCnt::FakeItemBuf, ITEM_SIZE, 0, 0, 0, ITEM_BUFFER_SIZE},
	{TS_QUE_ubGetQueueCnt::FakeItemBuf, ITEM_SIZE, 0, 1, 1, ITEM_BUFFER_SIZE},
	{TS_QUE_ubGetQueueCnt::FakeItemBuf, ITEM_SIZE, 7, 8, 1, ITEM_BUFFER_SIZE},
	{TS_QUE_ubGetQueueCnt::FakeItemBuf, ITEM_SIZE, 0, 0, 10, ITEM_BUFFER_SIZE},
	{TS_QUE_ubGetQueueCnt::FakeItemBuf, ITEM_SIZE, 7, 7, 10, ITEM_BUFFER_SIZE},
};

INSTANTIATE_TEST_SUITE_P(
	QUE_ubGetQueueCnt_TestData,
	TS_QUE_ubGetQueueCnt,
	::testing::Values(
		// 測試資料 1
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			0,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[0]
		},
		// 測試資料 2
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			1,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[1]
		},
		// 測試資料 3
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			1,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[2]
		},
		// 測試資料 4
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			10,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[3]
		},
		// 測試資料 5
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			10,
			// 輸入(輸入資料)
			&TS_QUE_ubGetQueueCnt::stFakeQueue[4]
		},
		// 測試資料 6
		TDS_QUE_ubGetQueueCnt{
			// 確認(預期結果)
			0,
			// 輸入(輸入資料)
			NULL
		}	
	)
);

/******************************************************************************/
/*------------------------Test Functions--------------------------------------*/
/******************************************************************************/
/**
* @test This test verifies the QUE_blCreateQueue
* @note
* ### 測試場景 1
* - **目的**: 可正常Create queue
* - **輸入**: 
*   1. Queue指向stFakeQueue，ItemBuf指向uwFakeItemBuf，ItemSize為sizeof(UWORD)，QCapacity為10【FakeData_stIn】
* - **動作**: 
*   - Create queue 1次
* - **確認**: 
*   1. item內容如預期【Expect_stOut】
*   2. Create queue狀態成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_blCreateQueue_TestData "1"
* ### 測試場景 2
* - **目的**: Queue指標為NULL，Create queue失敗
* - **輸入**: 
*   1. Queue指向NULL，其餘正常給定【FakeData_stIn】
* - **動作**: 
*   - Create queue 1次
* - **確認**: 
*   1. 無item內容【Expect_stOut】
*   2. Create queue狀態失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blCreateQueue_TestData "2"
* ### 測試場景 3
* - **目的**: Item指標為NULL，Create queue失敗
* - **輸入**: 
*   1. ItemBuf指向NULL，其餘正常給定【FakeData_stIn】
* - **動作**: 
*   - Create queue 1次
* - **確認**: 
*   1. 無item內容【Expect_stOut】
*   2. Create queue狀態失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blCreateQueue_TestData "3"
* ### 測試場景 4
* - **目的**: Item size大於Queue item最大值，Create queue失敗
* - **輸入**: 
*   1. ItemSize大於Queue item最大值(257)，其餘正常給定【FakeData_stIn】
* - **動作**: 
*   - Create queue 1次
* - **確認**: 
*   1. 無item內容【Expect_stOut】
*   2. Create queue狀態失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blCreateQueue_TestData "4"
* ### 測試場景 5
* - **目的**: Queue capacity大於Queue最大深度，Create queue失敗
* - **輸入**: 
*   1. QCapacity大於Queue最大深度(257)，其餘正常給定【FakeData_stIn】
* - **動作**: 
*   - Create queue 1次
* - **確認**: 
*   1. 無item內容【Expect_stOut】
*   2. Create queue狀態失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blCreateQueue_TestData "5"
*/
TEST_P(TS_QUE_blCreateQueue, CreateQueue) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_QUE_blCreateQueue stTD = GetParam();

	/* Call the process function and check the result
	 note:
	*/
	EXPECT_EQ(QUE_blCreateQueue(&stTD.FakeData_stIn), stTD.Expect_blResult);
	if (stTD.FakeData_stIn.stQPtr!=NULL)
	{
		EXPECT_EQ(stTD.FakeData_stIn.stQPtr->voItemBufPtr, stTD.Expect_stQueue.voItemBufPtr);
		EXPECT_EQ(stTD.FakeData_stIn.stQPtr->ubItemSize, stTD.Expect_stQueue.ubItemSize);
		EXPECT_EQ(stTD.FakeData_stIn.stQPtr->ubFront, stTD.Expect_stQueue.ubFront);
		EXPECT_EQ(stTD.FakeData_stIn.stQPtr->ubRear, stTD.Expect_stQueue.ubRear);
		EXPECT_EQ(stTD.FakeData_stIn.stQPtr->ubSize, stTD.Expect_stQueue.ubSize);
		EXPECT_EQ(stTD.FakeData_stIn.stQPtr->ubCapacity, stTD.Expect_stQueue.ubCapacity);
	}
}

/**
* @test This test verifies the QUE_stDeQueue
* @note
* ### 測試場景 1
* - **目的**: 可正常Dequeue
* - **輸入**: 
*   1. 含有1個item資料的Queue【FakeData_stIn】
* - **動作**: 
*   - Dequeue 1次
* - **確認**: 
*   1. item內容如預期，queue狀態如預期【Expect_stOut】
*   2. Dequeue成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_stDeQueue_TestData "1"
* ### 測試場景 2
* - **目的**: 可正常Dequeue
* - **輸入**: 
*   1. 含有2個item資料的Queue【FakeData_stIn】
* - **動作**: 
*   - Dequeue 1次
* - **確認**: 
*   1. item內容如預期，queue狀態如預期【Expect_stOut】
*   2. Dequeue成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_stDeQueue_TestData "2"
* ### 測試場景 3
* - **目的**: Queue為空，Dequeue失敗
* - **輸入**: 
*   1. 含有0個item資料的Queue【FakeData_stIn】
* - **動作**: 
*   - Dequeue 1次
* - **確認**: 
*   1. 無item內容，queue狀態沒有改變【Expect_stOut】
*   2. Dequeue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_stDeQueue_TestData "3"
* ### 測試場景 4
* - **目的**: Queue指標為NULL，Dequeue失敗
* - **輸入**: 
*   1. NULL Queue【FakeData_stIn】
* - **動作**: 
*   - Dequeue 1次
* - **確認**: 
*   1. Queue為NULL【Expect_stOut】
*   2. Dequeue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_stDeQueue_TestData "4"
* ### 測試場景 5
* - **目的**: Queue item指標為NULL，Dequeue失敗
* - **輸入**: 
*   1. NULL Queue item【FakeData_stIn】
* - **動作**: 
*   - Dequeue 1次
* - **確認**: 
*   1. Queue item為NULL，queue狀態沒有改變【Expect_stOut】
*   2. Dequeue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_stDeQueue_TestData "5"
*/
TEST_P(TS_QUE_stDeQueue, DeQueue) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_QUE_stDeQueue stTD = GetParam();

	/* Call the process function and check the result
	 note:
	*/
	tDE_Q_ST_OUT stRtn = QUE_stDeQueue(stTD.FakeData_stQueue);
	EXPECT_EQ(stRtn.blSuccess, stTD.Expect_blResult);
	EXPECT_EQ(stRtn.voItemPtr, stTD.Expect_ItemDataAdr);
	if (stTD.FakeData_stQueue!=NULL)
	{
		EXPECT_EQ(stTD.FakeData_stQueue->voItemBufPtr, stTD.Expect_stQueue->voItemBufPtr);
		EXPECT_EQ(stTD.FakeData_stQueue->ubItemSize, stTD.Expect_stQueue->ubItemSize);
		EXPECT_EQ(stTD.FakeData_stQueue->ubFront, stTD.Expect_stQueue->ubFront);
		EXPECT_EQ(stTD.FakeData_stQueue->ubRear, stTD.Expect_stQueue->ubRear);
		EXPECT_EQ(stTD.FakeData_stQueue->ubSize, stTD.Expect_stQueue->ubSize);
		EXPECT_EQ(stTD.FakeData_stQueue->ubCapacity, stTD.Expect_stQueue->ubCapacity);
	}
}

/**
* @test This test verifies the QUE_blEnQueue
* @note
* ### 測試場景 1
* - **目的**: 可正常Enqueue，Enqueue成功
* - **輸入**: 
*   1. 無任何資料的queue【FakeData_stIn】
* - **動作**: 
*   - Enqueue 1次
* - **確認**: 
*   1. item buffer內資料如預期，queue狀態如預期【Expect_stOut】
*   2. Enqueue成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEnQueue_TestData "1"
* ### 測試場景 2
* - **目的**: 可正常Enqueue，Enqueue成功
* - **輸入**: 
*   1. front為0且差1個滿的queue【FakeData_stIn】
* - **動作**: 
*   - Enqueue 1次
* - **確認**: 
*   1. item buffer內資料如預期，queue狀態如預期【Expect_stOut】
*   2. Enqueue成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEnQueue_TestData "2"
* ### 測試場景 3
* - **目的**: 可正常Enqueue，Enqueue成功
* - **輸入**: 
*   1. front不在0且差1個滿的queue【FakeData_stIn】
* - **動作**: 
*   - Enqueue 1次
* - **確認**: 
*   1. item buffer內資料如預期，queue狀態如預期【Expect_stOut】
*   2. Enqueue成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEnQueue_TestData "3"
* ### 測試場景 4
* - **目的**: Queue已滿，Enqueue失敗
* - **輸入**: 
*   1. 已滿的queue【FakeData_stIn】
* - **動作**: 
*   - Enqueue 1次
* - **確認**: 
*   1. item buffer內資料如預期，queue狀態如預期【Expect_stOut】
*   2. Enqueue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEnQueue_TestData "4"
* ### 測試場景 5
* - **目的**: input指標為NULL，Enqueue失敗
* - **輸入**: 
*   1. NULL input【FakeData_stIn】
* - **動作**: 
*   - Enqueue 1次
* - **確認**: 
*   1. Enqueue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEnQueue_TestData "5"
* ### 測試場景 6
* - **目的**: Queue指標為NULL，Enqueue失敗
* - **輸入**: 
*   1. NULL Queue【FakeData_stIn】
* - **動作**: 
*   - Enqueue 1次
* - **確認**: 
*   1. Queue為NULL指標【Expect_stOut】
*   2. Enqueue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEnQueue_TestData "6"
* ### 測試場景 7
* - **目的**: Queue item指標為NULL，Enqueue失敗
* - **輸入**: 
*   1. NULL Queue item【FakeData_stIn】
* - **動作**: 
*   - Enqueue 1次
* - **確認**: 
*   1. Queue狀態沒有改變【Expect_stOut】
*   2. Enqueue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEnQueue_TestData "7"
*/
TEST_P(TS_QUE_blEnQueue, EnQueue) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_QUE_blEnQueue stTD = GetParam();

	/* Call the process function and check the result
	 note:
	*/
	EXPECT_EQ(QUE_blEnQueue(stTD.FakeData_stIn), stTD.Expect_blResult);
	if (stTD.FakeData_stIn!=NULL)
	{
		if (stTD.FakeData_stIn->stQPtr!=NULL)
		{
			if (stTD.FakeData_stIn->stQPtr->voItemBufPtr!=NULL)
			{
				EXPECT_EQ(stTD.FakeData_stIn->stQPtr->ubItemSize, stTD.Expect_stQueue->ubItemSize);
				EXPECT_EQ(stTD.FakeData_stIn->stQPtr->ubFront, stTD.Expect_stQueue->ubFront);
				EXPECT_EQ(stTD.FakeData_stIn->stQPtr->ubRear, stTD.Expect_stQueue->ubRear);
				EXPECT_EQ(stTD.FakeData_stIn->stQPtr->ubSize, stTD.Expect_stQueue->ubSize);
				EXPECT_EQ(stTD.FakeData_stIn->stQPtr->ubCapacity, stTD.Expect_stQueue->ubCapacity);
				ITEM_TYPE * DataPtr = (ITEM_TYPE *)stTD.FakeData_stIn->stQPtr->voItemBufPtr;
				EXPECT_EQ(*(DataPtr + stTD.FakeData_ItemIdx), stTD.Expect_ItemData);
			}
		}
	}
}

/**
* @test This test verifies the QUE_blEmptyQueue
* @note
* ### 測試場景 1
* - **目的**: 可清除Queue front和rear index和size，EmptyQueue成功
* - **輸入**: 
*   1. 有1個item在內的Queue【FakeData_stQueue】
* - **動作**: 
*   - EmptyQueue
* - **確認**: 
*   1. Queue狀態符合預期【Expect_stQueue】
*   2. EmptyQueue成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEmptyQueue_TestData "1"
* ### 測試場景 2
* - **目的**: 可清除Queue front和rear index和size，EmptyQueue成功
* - **輸入**: 
*   1. 已滿的Queue【FakeData_stQueue】
* - **動作**: 
*   - EmptyQueue
* - **確認**: 
*   1. Queue狀態符合預期【Expect_stQueue】
*   2. EmptyQueue成功【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEmptyQueue_TestData "2"
* ### 測試場景 3
* - **目的**: Queue為NULL指標，認為EmptyQueue失敗
* - **輸入**: 
*   1. NULL input【FakeData_stQueue】
* - **動作**: 
*   - EmptyQueue
* - **確認**: 
*   1. EmptyQueue失敗【Expect_blResult】
* - **測試資料編號**: @ref QUE_blEmptyQueue_TestData "3"
*/
TEST_P(TS_QUE_blEmptyQueue, EmptyQueue) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_QUE_blEmptyQueue stTD = GetParam();

	/* Call the process function and check the result
	 note:
	*/
	EXPECT_EQ(QUE_blEmptyQueue(stTD.FakeData_stQueue), stTD.Expect_blResult);
	if(stTD.FakeData_stQueue!=NULL)
	{
		EXPECT_EQ(stTD.FakeData_stQueue->ubFront, stTD.Expect_stQueue->ubFront);
		EXPECT_EQ(stTD.FakeData_stQueue->ubRear, stTD.Expect_stQueue->ubRear);
		EXPECT_EQ(stTD.FakeData_stQueue->ubSize, stTD.Expect_stQueue->ubSize);
	}

}

/**
* @test This test verifies the QUE_ubGetQueueCnt
* @note
* ### 測試場景 1
* - **目的**: 可取得當前Queue count
* - **輸入**: 
*   1. 空的Queue【FakeData_stQueue】
* - **動作**: 
*   - GetQueueCnt
* - **確認**: 
*   1. GetQueueCnt=0【Expect_ubResult】
* - **測試資料編號**: @ref QUE_ubGetQueueCnt_TestData "1"
* ### 測試場景 2
* - **目的**: 可取得當前Queue count
* - **輸入**: 
*   1. front在0且1個的queue【FakeData_stQueue】
* - **動作**: 
*   - GetQueueCnt
* - **確認**: 
*   1. GetQueueCnt=1【Expect_ubResult】
* - **測試資料編號**: @ref QUE_ubGetQueueCnt_TestData "2"
* ### 測試場景 3
* - **目的**: 可取得當前Queue count
* - **輸入**: 
*   1. front不在0且1個的queue【FakeData_stQueue】
* - **動作**: 
*   - GetQueueCnt
* - **確認**: 
*   1. GetQueueCnt=1【Expect_ubResult】
* - **測試資料編號**: @ref QUE_ubGetQueueCnt_TestData "3"
* ### 測試場景 4
* - **目的**: 可取得當前Queue count
* - **輸入**: 
*   1. front在0且滿個的queue【FakeData_stQueue】
* - **動作**: 
*   - GetQueueCnt
* - **確認**: 
*   1. GetQueueCnt=10【Expect_ubResult】
* - **測試資料編號**: @ref QUE_ubGetQueueCnt_TestData "4"
* ### 測試場景 5
* - **目的**: 可取得當前Queue count
* - **輸入**: 
*   1. front不在0且滿的queue【FakeData_stQueue】
* - **動作**: 
*   - GetQueueCnt
* - **確認**: 
*   1. GetQueueCnt=10【Expect_ubResult】
* - **測試資料編號**: @ref QUE_ubGetQueueCnt_TestData "5"
* ### 測試場景 6
* - **目的**: Queue為NULL指標，認為GetQueueCnt失敗
* - **輸入**: 
*   1. NULL input【FakeData_stQueue】
* - **動作**: 
*   - GetQueueCnt
* - **確認**: 
*   1. GetQueueCnt=0【Expect_ubResult】
* - **測試資料編號**: @ref QUE_ubGetQueueCnt_TestData "6"
*/
TEST_P(TS_QUE_ubGetQueueCnt, GetQueueCnt) {
	/* Setup the mock behavior
	 note:
	*/
	TDS_QUE_ubGetQueueCnt stTD = GetParam();

	/* Call the process function and check the result
	 note:
	*/
	EXPECT_EQ(QUE_ubGetQueueCnt(stTD.FakeData_stQueue), stTD.Expect_ubResult);
}