#include "LogicTest.h"
 /*
const std::string TaskLogic::FILENAME_TB_STORAGE = "taskBuddyStorage.txt";
const std::string TaskLogic::FILENAME_TB_DONE_STORAGE = "taskBuddyDoneStorage.txt";
const std::string TaskLogic::FILENAME_TB_OVERDUE_STORAGE = "taskBuddyOverdueStorage.txt";
const std::string TaskLogic::UI_FORMAT = "ui_format";
const std::string TaskLogic::PROCESSED_FORMAT = "processed_format";
const std::string TaskLogic::BLOCK_OFF = "(blockoff)";
*/

void LogicTest::clearParse(std::string &action, std::string &location, std::vector<Date> &startingDateVector, std::vector<int> &startingTimeVector, std::vector<Date> &endingDateVector, std::vector<int> &endingTimeVector, std::vector<Date> &deadlineDateVector, std::vector<int> &deadlineTimeVector, bool &isBlock){
	action = "";
	location = "";
	startingDateVector.clear(); 
	endingDateVector.clear(); 
	deadlineDateVector.clear(); 
	startingTimeVector.clear(); 
	endingTimeVector.clear(); 
	deadlineTimeVector.clear(); 
	isBlock = false;
}

//----HELPER FUNCTIONS-----------------------------------------------------------------------------

TEST_F(LogicTest, IsDayIsWorking){
	std::string day;
	day = "Monday";
	EXPECT_EQ(taskLogic.isDay(day),true);
	day = "tue";
	EXPECT_EQ(taskLogic.isDay(day),true);
	day = "SuNDaY";
	EXPECT_EQ(taskLogic.isDay(day),true);
	day = "TMR";
	EXPECT_EQ(taskLogic.isDay(day),true);
	day = "today";
	EXPECT_EQ(taskLogic.isDay(day),true);
	day = "mday";
	EXPECT_EQ(taskLogic.isDay(day),false);	
	day = "tommrow";
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

	clearParse(action, location, startingDateVector, startingTimeVector, endingDateVector, endingTimeVector, deadlineDateVector, deadlineTimeVector, isBlock);

	taskLogic.stringParse("Have Dinner with Mum at Orchard from 15/11/2013 0900 to 15/11/2013 1000", "ui_format", action, location, startingDateVector, startingTimeVector, endingDateVector, endingTimeVector, deadlineDateVector, deadlineTimeVector, isBlock); 

	EXPECT_EQ(action,"Have Dinner with Mum");
	EXPECT_EQ(location,"Orchard");
	EXPECT_EQ(startingDateVector[0]._day, 15);
	EXPECT_EQ(startingDateVector[0]._month, 11);
	EXPECT_EQ(startingDateVector[0]._year, 2013);
	EXPECT_EQ(startingTimeVector[0], 900);
	EXPECT_EQ(endingDateVector[0]._day, 15);
	EXPECT_EQ(endingDateVector[0]._month, 11);
	EXPECT_EQ(endingDateVector[0]._year, 2013);
	EXPECT_EQ(endingTimeVector[0], 1000);

	clearParse(action, location, startingDateVector, startingTimeVector, endingDateVector, endingTimeVector, deadlineDateVector, deadlineTimeVector, isBlock);

	taskLogic.stringParse("Complete HW Assignment by 16/11/2013 2359", "ui_format", action, location, startingDateVector, startingTimeVector, endingDateVector, endingTimeVector, deadlineDateVector, deadlineTimeVector, isBlock); 

	EXPECT_EQ(action,"Complete HW Assignment");
	EXPECT_EQ(location,"");
	EXPECT_EQ(deadlineDateVector[0]._day, 16);
	EXPECT_EQ(deadlineDateVector[0]._month, 11);
	EXPECT_EQ(deadlineDateVector[0]._year, 2013);
	EXPECT_EQ(deadlineTimeVector[0], 2359);

	clearParse(action, location, startingDateVector, startingTimeVector, endingDateVector, endingTimeVector, deadlineDateVector, deadlineTimeVector, isBlock);

	taskLogic.stringParse("by 16/11/2013 : testAction at testLocation", "processed_format", action, location, startingDateVector, startingTimeVector, endingDateVector, endingTimeVector, deadlineDateVector, deadlineTimeVector, isBlock); 

	EXPECT_EQ(action,"testAction");
	EXPECT_EQ(location,"testLocation");
	EXPECT_EQ(deadlineDateVector[0]._day, 16);
	EXPECT_EQ(deadlineDateVector[0]._month, 11);
	EXPECT_EQ(deadlineDateVector[0]._year, 2013);
	EXPECT_EQ(deadlineTimeVector[0], -1);

}

TEST_F(LogicTest, isOnlyActionLocationIsWorking){
	EXPECT_EQ(taskLogic.isOnlyActionLocation("from 15/11/2013 1000 to 15/11/2013 1200 taskAction at taskLocation"), false);
	EXPECT_EQ(taskLogic.isOnlyActionLocation("taskAction at taskLocation from 15/11/2013 1000 to 15/11/2013 1200"), false);
	EXPECT_EQ(taskLogic.isOnlyActionLocation("taskAction at taskLocation from 15/11/2013"), false);
	EXPECT_EQ(taskLogic.isOnlyActionLocation("taskAction at taskLocation by 15/11/2013"), false);
	EXPECT_EQ(taskLogic.isOnlyActionLocation("taskAction at taskLocation"), true);
	EXPECT_EQ(taskLogic.isOnlyActionLocation("Dinner with Mum"), true);
}

TEST_F(LogicTest, convertToDateStringIsWorking){
	Date date(15,11,2013);
	EXPECT_EQ(taskLogic.convertToDateString(date),"15/11/2013");
	Date date1(01,01,2001);
	EXPECT_EQ(taskLogic.convertToDateString(date1),"1/1/2001");
	Date date2(30,12,2999);
	EXPECT_EQ(taskLogic.convertToDateString(date2),"30/12/2999");
}

TEST_F(LogicTest, getActionLocationIsWorking){
	EXPECT_EQ(taskLogic.getActionLocation("15/11/2013 1000 hrs - 15/11/2013 1200 hrs : taskAction"), "taskAction");
	EXPECT_EQ(taskLogic.getActionLocation("15/11/2013 1000 hrs - 15/11/2013 1200 : taskAction at taskLocation"), "taskAction at taskLocation");
	EXPECT_EQ(taskLogic.getActionLocation("15/11/2013 1000 hrs : Lunch with Mum"), "Lunch with Mum");
	EXPECT_EQ(taskLogic.getActionLocation("by 15/11/2013 1000 hrs : Lunch with Mum at Techno"), "Lunch with Mum at Techno");
}


TEST_F(LogicTest, checkSameDateIsWorking){
	Date date1(15,11,2013);
	Date date2(15,11,2013);
	EXPECT_EQ(taskLogic.checkSameDate(date1,date2),true);
	Date date3(01,11,2013);
	Date date4(30,11,2013);
	EXPECT_EQ(taskLogic.checkSameDate(date3,date4),false);
	Date date5(15,01,2013);
	Date date6(15,12,2013);
	EXPECT_EQ(taskLogic.checkSameDate(date5,date6),false);
}
