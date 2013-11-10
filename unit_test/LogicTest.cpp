#include "LogicTest.h"
 /*
const std::string TaskLogic::FILENAME_TB_STORAGE = "taskBuddyStorage.txt";
const std::string TaskLogic::FILENAME_TB_DONE_STORAGE = "taskBuddyDoneStorage.txt";
const std::string TaskLogic::FILENAME_TB_OVERDUE_STORAGE = "taskBuddyOverdueStorage.txt";
const std::string TaskLogic::UI_FORMAT = "ui_format";
const std::string TaskLogic::PROCESSED_FORMAT = "processed_format";
const std::string TaskLogic::BLOCK_OFF = "(blockoff)";
*/
TEST_F(LogicTest, IsDayIsWorking){
	//EXPECT_EQ("abc", textBuddy.getTextNumbered(1));
	//EXPECT_EQ("123", textBuddy.getTextNumbered(2));
	EXPECT_EQ("efg","efg");
	EXPECT_EQ("abc","abc");
	std::string day;
	day = "Monday";
	EXPECT_EQ(taskLogic.isDay(day),true);
	day = "blah";
	EXPECT_EQ(taskLogic.isDay(day),false);
}

TEST_F(LogicTest, StringParseIsWorking){
	std::string action = "";
	std::string location = "";
	std::vector<Date> startingDateVector, endingDateVector, deadlineDateVector; 
	std::vector<int> startingTimeVector, endingTimeVector, deadlineTimeVector; 
	bool isBlock = false;
	
	taskLogic.stringParse("testAction at testLocation from 15/11/2013 0900 to 15/11/2013 1000", "ui_format", action, location, startingDateVector, startingTimeVector, endingDateVector, endingTimeVector, deadlineDateVector, deadlineTimeVector, isBlock); 

	EXPECT_EQ(action,"testAction");
	EXPECT_EQ(location,"testLocation");
	EXPECT_EQ(startingDateVector[0].isEmptyDate(), false);
	EXPECT_EQ(endingDateVector[0].isEmptyDate(), false);
	EXPECT_EQ(deadlineDateVector[0].isEmptyDate(), true);
}