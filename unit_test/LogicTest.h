#include <gtest\gtest.h>
#include <TaskLogic.h>
#include <Task.h>
#include <Parse.h>
#include <TaskLinkedList.h>
#include <Date.h>
 
class LogicTest : public ::testing::Test {

protected:
	/*
	static const std::string FILENAME_TB_STORAGE;
	static const std::string FILENAME_TB_DONE_STORAGE;
	static const std::string FILENAME_TB_OVERDUE_STORAGE;
	static const std::string UI_FORMAT;
	static const std::string PROCESSED_FORMAT;
	static const std::string BLOCK_OFF;
	*/
	LogicTest() {
	
	}
 
	virtual ~LogicTest() {
	
	}
 
	virtual void SetUp() {
		std::string action = "", location ="";
		std::vector<Date> startingDateVector, endingDateVector, deadlineDateVector; 
		std::vector<int> startingTimeVector, endingTimeVector, deadlineTimeVector; 
		bool isBlock = false;
	}

	virtual void TearDown(){
	
	}

	TaskLogic taskLogic;


};