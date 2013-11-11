#include <gtest\gtest.h>
#include "ParseTest.h"

TEST_F(ParseTest, DateStringToDateConversion){
	Date checkDate(1,1,2013);

	// d/m/yyyy format
	std::string dateString1 = "1/1/2013";
	Date date1 = taskParse.convertToDate(dateString1);
	EXPECT_EQ(checkDate._day, date1._day);
	EXPECT_EQ(checkDate._month, date1._month);
	EXPECT_EQ(checkDate._year, date1._year);

	// dd/m/yy format
	std::string dateString2 = "01/1/13";
	Date date2 = taskParse.convertToDate(dateString2);
	EXPECT_EQ(checkDate._day, date2._day);
	EXPECT_EQ(checkDate._month, date2._month);
	EXPECT_EQ(checkDate._year, date2._year);

	// d/mm/yyyy format
	std::string dateString3 = "1/01/2013";
	Date date3 = taskParse.convertToDate(dateString3);
	EXPECT_EQ(checkDate._day, date3._day);
	EXPECT_EQ(checkDate._month, date3._month);
	EXPECT_EQ(checkDate._year, date3._year);

	// dd/mm/yy format
	std::string dateString4 = "01/01/13";
	Date date4 = taskParse.convertToDate(dateString4);
	EXPECT_EQ(checkDate._day, date4._day);
	EXPECT_EQ(checkDate._month, date4._month);
	EXPECT_EQ(checkDate._year, date4._year);
}

TEST_F(ParseTest, TimeStringToIntTimeConversion){
	//Single digit
	std::string timeString1 = "0001";
	int timeValue1 = 1;
	EXPECT_EQ(timeValue1, taskParse.convertToTime(timeString1));
	
	//Double digit
	std::string timeString2 = "0010";
	int timeValue2 = 10;
	EXPECT_EQ(timeValue2, taskParse.convertToTime(timeString2));
	
	//Triple digit
	std::string timeString3 = "0100";
	int timeValue3 = 100;
	EXPECT_EQ(timeValue3, taskParse.convertToTime(timeString3));
	
	//Four digits
	std::string timeString4 = "1000";
	int timeValue4 = 1000;
	EXPECT_EQ(timeValue4, taskParse.convertToTime(timeString4));
}

TEST_F(ParseTest, DayKeywordToDateStringConversion){
	//Initialise dateStrings vector given that today is 11/11/2013
	std::vector<std::string> dateStrings;
	dateStrings.push_back("11/11/2013");
	for (unsigned int i = 0; i < 7; i++){
		std::ostringstream dateString;
		int dateValue = 11 + i;
		dateString << dateValue;
		dateStrings.push_back(dateString.str()+"/11/2013");
	}
	dateStrings.push_back("12/11/2013");

	EXPECT_EQ("11/11/2013", taskParse.changeDayToDate("today", dateStrings));
	EXPECT_EQ("11/11/2013", taskParse.changeDayToDate("Mon", dateStrings));
	EXPECT_EQ("11/11/2013", taskParse.changeDayToDate("monday", dateStrings));
	EXPECT_EQ("12/11/2013", taskParse.changeDayToDate("tues", dateStrings));
	EXPECT_EQ("12/11/2013", taskParse.changeDayToDate("Tue", dateStrings));
	EXPECT_EQ("12/11/2013", taskParse.changeDayToDate("tuesday", dateStrings));
	EXPECT_EQ("13/11/2013", taskParse.changeDayToDate("wed", dateStrings));
	EXPECT_EQ("13/11/2013", taskParse.changeDayToDate("WEDNESDAY", dateStrings));
	EXPECT_EQ("14/11/2013", taskParse.changeDayToDate("Thursday", dateStrings));
	EXPECT_EQ("14/11/2013", taskParse.changeDayToDate("thu", dateStrings));
	EXPECT_EQ("14/11/2013", taskParse.changeDayToDate("thurs", dateStrings));
	EXPECT_EQ("14/11/2013", taskParse.changeDayToDate("Thur", dateStrings));
	EXPECT_EQ("15/11/2013", taskParse.changeDayToDate("friday", dateStrings));
	EXPECT_EQ("15/11/2013", taskParse.changeDayToDate("fri", dateStrings));
	EXPECT_EQ("16/11/2013", taskParse.changeDayToDate("Sat", dateStrings));
	EXPECT_EQ("16/11/2013", taskParse.changeDayToDate("saturday", dateStrings));
	EXPECT_EQ("17/11/2013", taskParse.changeDayToDate("SUN", dateStrings));
	EXPECT_EQ("17/11/2013", taskParse.changeDayToDate("sunday", dateStrings));
	EXPECT_EQ("12/11/2013", taskParse.changeDayToDate("tmr", dateStrings));
	EXPECT_EQ("12/11/2013", taskParse.changeDayToDate("tomorrow", dateStrings));
}

TEST_F(ParseTest, LowercaseConversion){
	std::string checkWord = "word";

	std::string word1 = "Word";
	EXPECT_EQ(checkWord, taskParse.convertToLowercase(word1)); 
	
	std::string word2 = "wORd";
	EXPECT_EQ(checkWord, taskParse.convertToLowercase(word2));
	
	std::string word3 = "worD";
	EXPECT_EQ(checkWord, taskParse.convertToLowercase(word3));
	
	std::string word4 = "WORD";
	EXPECT_EQ(checkWord, taskParse.convertToLowercase(word4));
}

TEST_F(ParseTest, ProcessTaskStringFromUI){
	std::string action;
	std::string location;
	std::vector<Date> startingDate;
	std::vector<int> startingTime;
	std::vector<Date> endingDate;
	std::vector<int> endingTime;
	std::vector<Date> deadlineDate;
	std::vector<int> deadlineTime;
	bool block;
	//Initialise dateStrings vector given that today is 11/11/2013
	std::vector<std::string> dateStrings;
	dateStrings.push_back("11/11/2013");
	for (unsigned int i = 0; i < 7; i++){
		std::ostringstream dateString;
		int dateValue = 11 + i;
		dateString << dateValue;
		dateStrings.push_back(dateString.str()+"/11/2013");
	}
	dateStrings.push_back("12/11/2013");

	//Floating task with location
	std::string userInput1 = "have lunch with parents at macs";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromUI(userInput1, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block, dateStrings);

	EXPECT_EQ("have lunch with parents", action);
	EXPECT_EQ("macs", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(0, startingDate[0]._day);
	EXPECT_EQ(0, startingDate[0]._month);
	EXPECT_EQ(0, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(0, endingDate[0]._day);
	EXPECT_EQ(0, endingDate[0]._month);
	EXPECT_EQ(0, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(0, deadlineDate[0]._day);
	EXPECT_EQ(0, deadlineDate[0]._month);
	EXPECT_EQ(0, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(-1, deadlineTime[0]);
	EXPECT_EQ(false, block);

	//Activity task with date date strings with different day formats
	std::string userInput2 = "sleepover with jc friends from 3/12/2013 to 04/12/2013";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromUI(userInput2, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block, dateStrings);

	EXPECT_EQ("sleepover with jc friends", action);
	EXPECT_EQ("", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(3, startingDate[0]._day);
	EXPECT_EQ(12, startingDate[0]._month);
	EXPECT_EQ(2013, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(4, endingDate[0]._day);
	EXPECT_EQ(12, endingDate[0]._month);
	EXPECT_EQ(2013, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(0, deadlineDate[0]._day);
	EXPECT_EQ(0, deadlineDate[0]._month);
	EXPECT_EQ(0, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(-1, deadlineTime[0]);
	EXPECT_EQ(false, block);

	//Deadline task with day keyword and time
	std::string userInput3 = "submit cs2103 taskbuddy program v0.5 by TODAY 2359";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromUI(userInput3, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block, dateStrings);

	EXPECT_EQ("submit cs2103 taskbuddy program v0.5", action);
	EXPECT_EQ("", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(0, startingDate[0]._day);
	EXPECT_EQ(0, startingDate[0]._month);
	EXPECT_EQ(0, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(0, endingDate[0]._day);
	EXPECT_EQ(0, endingDate[0]._month);
	EXPECT_EQ(0, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(11, deadlineDate[0]._day);
	EXPECT_EQ(11, deadlineDate[0]._month);
	EXPECT_EQ(2013, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(2359, deadlineTime[0]);
	EXPECT_EQ(false, block);

	//Blocked task with location and mixture of task types (with and without time)
	std::string userInput4 = "study for cs2103 finals at mac commons blockoff from 11/11/13 1300 to today 1900 by today 2100 from mon to 13/11/2013 from Tues 0800";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromUI(userInput4, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block, dateStrings);

	EXPECT_EQ("study for cs2103 finals", action);
	EXPECT_EQ("mac commons", location);
	EXPECT_EQ(3, startingDate.size());
	EXPECT_EQ(11, startingDate[0]._day);
	EXPECT_EQ(11, startingDate[0]._month);
	EXPECT_EQ(2013, startingDate[0]._year);
	EXPECT_EQ(11, startingDate[1]._day);
	EXPECT_EQ(11, startingDate[1]._month);
	EXPECT_EQ(2013, startingDate[1]._year);
	EXPECT_EQ(12, startingDate[2]._day);
	EXPECT_EQ(11, startingDate[2]._month);
	EXPECT_EQ(2013, startingDate[2]._year);
	EXPECT_EQ(3, startingTime.size());
	EXPECT_EQ(1300, startingTime[0]);
	EXPECT_EQ(-1, startingTime[1]);
	EXPECT_EQ(800, startingTime[2]);
	EXPECT_EQ(3, endingDate.size());
	EXPECT_EQ(11, endingDate[0]._day);
	EXPECT_EQ(11, endingDate[0]._month);
	EXPECT_EQ(2013, endingDate[0]._year);
	EXPECT_EQ(13, endingDate[1]._day);
	EXPECT_EQ(11, endingDate[1]._month);
	EXPECT_EQ(2013, endingDate[1]._year);
	EXPECT_EQ(0, endingDate[2]._day);
	EXPECT_EQ(0, endingDate[2]._month);
	EXPECT_EQ(0, endingDate[2]._year);
	EXPECT_EQ(3, endingTime.size());
	EXPECT_EQ(1900, endingTime[0]);
	EXPECT_EQ(-1, endingTime[1]);
	EXPECT_EQ(-1, endingTime[2]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(11, deadlineDate[0]._day);
	EXPECT_EQ(11, deadlineDate[0]._month);
	EXPECT_EQ(2013, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(2100, deadlineTime[0]);
	EXPECT_EQ(true, block);

	//Activity task with start and end date with single digit day/month input format
	std::string userInput5 = "family overseas holiday from 22/12/2013 to 6/1/2014";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromUI(userInput5, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block, dateStrings);

	EXPECT_EQ("family overseas holiday", action);
	EXPECT_EQ("", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(22, startingDate[0]._day);
	EXPECT_EQ(12, startingDate[0]._month);
	EXPECT_EQ(2013, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(6, endingDate[0]._day);
	EXPECT_EQ(1, endingDate[0]._month);
	EXPECT_EQ(2014, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(0, deadlineDate[0]._day);
	EXPECT_EQ(0, deadlineDate[0]._month);
	EXPECT_EQ(0, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(-1, deadlineTime[0]);
	EXPECT_EQ(false, block);
}

TEST_F(ParseTest, ProcessTaskFromFile){
	std::string action;
	std::string location;
	std::vector<Date> startingDate;
	std::vector<int> startingTime;
	std::vector<Date> endingDate;
	std::vector<int> endingTime;
	std::vector<Date> deadlineDate;
	std::vector<int> deadlineTime;
	bool block;

	//Floating task with location
	std::string fileTask1 = "   have lunch with parents at macs";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromFile(fileTask1, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	
	EXPECT_EQ("have lunch with parents", action);
	EXPECT_EQ("macs", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(0, startingDate[0]._day);
	EXPECT_EQ(0, startingDate[0]._month);
	EXPECT_EQ(0, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(0, endingDate[0]._day);
	EXPECT_EQ(0, endingDate[0]._month);
	EXPECT_EQ(0, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(0, deadlineDate[0]._day);
	EXPECT_EQ(0, deadlineDate[0]._month);
	EXPECT_EQ(0, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(-1, deadlineTime[0]);
	EXPECT_EQ(false, block);

	//Activity task with start and end date with single digit day and double digit month
	std::string fileTask2 = "   03/12/2013 - 04/12/2013 : sleepover with jc friends";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromFile(fileTask2, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);

	EXPECT_EQ("sleepover with jc friends", action);
	EXPECT_EQ("", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(3, startingDate[0]._day);
	EXPECT_EQ(12, startingDate[0]._month);
	EXPECT_EQ(2013, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(4, endingDate[0]._day);
	EXPECT_EQ(12, endingDate[0]._month);
	EXPECT_EQ(2013, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(0, deadlineDate[0]._day);
	EXPECT_EQ(0, deadlineDate[0]._month);
	EXPECT_EQ(0, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(-1, deadlineTime[0]);
	EXPECT_EQ(false, block);

	//Deadline task with time
	std::string fileTask3 = "by 11/11/2013 2359 hrs : submit cs2103 taskbuddy program v0.5";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromFile(fileTask3, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);

	EXPECT_EQ("submit cs2103 taskbuddy program v0.5", action);
	EXPECT_EQ("", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(0, startingDate[0]._day);
	EXPECT_EQ(0, startingDate[0]._month);
	EXPECT_EQ(0, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(0, endingDate[0]._day);
	EXPECT_EQ(0, endingDate[0]._month);
	EXPECT_EQ(0, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(11, deadlineDate[0]._day);
	EXPECT_EQ(11, deadlineDate[0]._month);
	EXPECT_EQ(2013, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(2359, deadlineTime[0]);
	EXPECT_EQ(false, block);

	//Blocked activity task with start date and time
	std::string fileTask4 = "   12/11/2013 0800 hrs : study for cs2103 finals at mac commons (blockoff)";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromFile(fileTask4, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);

	EXPECT_EQ("study for cs2103 finals", action);
	EXPECT_EQ("mac commons", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(12, startingDate[0]._day);
	EXPECT_EQ(11, startingDate[0]._month);
	EXPECT_EQ(2013, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(800, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(0, endingDate[0]._day);
	EXPECT_EQ(0, endingDate[0]._month);
	EXPECT_EQ(0, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(0, deadlineDate[0]._day);
	EXPECT_EQ(0, deadlineDate[0]._month);
	EXPECT_EQ(0, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(-1, deadlineTime[0]);
	EXPECT_EQ(true, block);

	//Activity task with start and end date with single digit day/month 
	std::string fileTask5 = "   22/12/2013 - 06/01/2014 : family overseas holiday";
	action = "";
	location = "";
	startingDate.clear();
	startingTime.clear();
	endingDate.clear();
	endingTime.clear();
	deadlineDate.clear();
	deadlineTime.clear();
	block = false;
	taskParse.processTaskStringFromFile(fileTask5, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);

	EXPECT_EQ("family overseas holiday", action);
	EXPECT_EQ("", location);
	EXPECT_EQ(1, startingDate.size());
	EXPECT_EQ(22, startingDate[0]._day);
	EXPECT_EQ(12, startingDate[0]._month);
	EXPECT_EQ(2013, startingDate[0]._year);
	EXPECT_EQ(1, startingTime.size());
	EXPECT_EQ(-1, startingTime[0]);
	EXPECT_EQ(1, endingDate.size());
	EXPECT_EQ(6, endingDate[0]._day);
	EXPECT_EQ(1, endingDate[0]._month);
	EXPECT_EQ(2014, endingDate[0]._year);
	EXPECT_EQ(1, endingTime.size());
	EXPECT_EQ(-1, endingTime[0]);
	EXPECT_EQ(1, deadlineDate.size());
	EXPECT_EQ(0, deadlineDate[0]._day);
	EXPECT_EQ(0, deadlineDate[0]._month);
	EXPECT_EQ(0, deadlineDate[0]._year);
	EXPECT_EQ(1, deadlineTime.size());
	EXPECT_EQ(-1, deadlineTime[0]);
	EXPECT_EQ(false, block);
}

TEST_F(ParseTest, CheckForKeyword){
	//Check that not affected by case
	std::string fromUppercase = "FROM";
	std::string byCapitalised = "By";
	std::string atLower = "at";
	std::string toUppercase = "TO";
	std::string blockBothcase = "bLOckOff";
	EXPECT_EQ(true, taskParse.isKeyword(fromUppercase));
	EXPECT_EQ(true, taskParse.isKeyword(byCapitalised));
	EXPECT_EQ(true, taskParse.isKeyword(atLower));
	EXPECT_EQ(true, taskParse.isKeyword(toUppercase));
	EXPECT_EQ(true, taskParse.isKeyword(blockBothcase));
}

TEST_F(ParseTest, CheckForDayKeyword){
	//Check that not affected by case 
	std::string todayLowercase = "today";
	std::string mondayUppercase = "MONDAY";
	std::string monLowercase = "mon";
	std::string tuesdayLowercase = "tuesday";
	std::string tueCapitalised = "Tue";
	std::string tuesUppercase = "TUES";
	std::string wednesdayLowercase = "wednesday";
	std::string wedBothcase = "wEd";
	std::string thursdayBothcase = "thuRsDAy";
	std::string thursUppercase = "THURS";
	std::string thurCapitalised = "Thur";
	std::string thuLowercase = "thu";
	std::string fridayCapitalised = "Friday";
	std::string friUppercase = "FRI";
	std::string saturdayBothcase = "SAturDaY";
	std::string satLowercase = "sat";
	std::string sundayCapitalised = "Sunday";
	std::string sunUppercase = "SUN";
	std::string tomorrowBothcase = "TOMorrOw";
	std::string tmrLowercase = "tmr";
	EXPECT_EQ(true, taskParse.isDayKeyword(todayLowercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(mondayUppercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(monLowercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(tuesdayLowercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(tuesUppercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(tueCapitalised));
	EXPECT_EQ(true, taskParse.isDayKeyword(wednesdayLowercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(wedBothcase));
	EXPECT_EQ(true, taskParse.isDayKeyword(thursdayBothcase));
	EXPECT_EQ(true, taskParse.isDayKeyword(thursUppercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(thurCapitalised));
	EXPECT_EQ(true, taskParse.isDayKeyword(thuLowercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(fridayCapitalised));
	EXPECT_EQ(true, taskParse.isDayKeyword(friUppercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(saturdayBothcase));
	EXPECT_EQ(true, taskParse.isDayKeyword(satLowercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(sundayCapitalised));
	EXPECT_EQ(true, taskParse.isDayKeyword(sunUppercase));
	EXPECT_EQ(true, taskParse.isDayKeyword(tomorrowBothcase));
	EXPECT_EQ(true, taskParse.isDayKeyword(tmrLowercase));
}

TEST_F(ParseTest, CheckForValidFormat){
	 //Check date input format
	std::string dayInput1 = "1";
	std::string dayInput2 = "01";
	std::string dayInput3 = "001";
	EXPECT_EQ(true, taskParse.isValidDayFormat(dayInput1));
	EXPECT_EQ(true, taskParse.isValidDayFormat(dayInput2));
	EXPECT_EQ(false, taskParse.isValidDayFormat(dayInput3));
	
	//Check month input format
	std::string monthInput1 = "1";
	std::string monthInput2 = "01";
	std::string monthInput3 = "001";
	EXPECT_EQ(true, taskParse.isValidMonthFormat(monthInput1));
	EXPECT_EQ(true, taskParse.isValidMonthFormat(monthInput2));
	EXPECT_EQ(false, taskParse.isValidMonthFormat(monthInput3));
	
	//Check year input format
	std::string yearInput1 = "1";
	std::string yearInput2 = "01";
	std::string yearInput3 = "150";
	std::string yearInput4 = "2013";
	std::string yearInput5 = "20133";
	EXPECT_EQ(false, taskParse.isValidYearFormat(yearInput1));
	EXPECT_EQ(true, taskParse.isValidYearFormat(yearInput2));
	EXPECT_EQ(false, taskParse.isValidYearFormat(yearInput3));
	EXPECT_EQ(true, taskParse.isValidYearFormat(yearInput4));
	EXPECT_EQ(false, taskParse.isValidYearFormat(yearInput5));
	
	//Check time input format
	std::string timeInput1 = "800";
	std::string timeInput2 = "1200";
	std::string timeInput3 = "12300";
	EXPECT_EQ(false, taskParse.isValidTimeFormat(timeInput1));
	EXPECT_EQ(true, taskParse.isValidTimeFormat(timeInput2));
	EXPECT_EQ(false, taskParse.isValidTimeFormat(timeInput3));
}

TEST_F(ParseTest, CheckForValidTime){
	//Check valid hour value
	int hour1 = 0;
	int hour2 = 1;
	int hour3 = 22; 
	int hour4 = 23;
	int hour5 = 24;
	EXPECT_EQ(true, taskParse.isValidHour(hour1));
	EXPECT_EQ(true, taskParse.isValidHour(hour2));
	EXPECT_EQ(true, taskParse.isValidHour(hour3));
	EXPECT_EQ(true, taskParse.isValidHour(hour4));
	EXPECT_EQ(false, taskParse.isValidHour(hour5));
	
	//Check valid mins value
	int mins1 = 0;
	int mins2 = 1;
	int mins3 = 58;
	int mins4 = 59;
	int mins5 = 60;
	EXPECT_EQ(true, taskParse.isValidMins(mins1));
	EXPECT_EQ(true, taskParse.isValidMins(mins2));
	EXPECT_EQ(true, taskParse.isValidMins(mins3));
	EXPECT_EQ(true, taskParse.isValidMins(mins4));
	EXPECT_EQ(false, taskParse.isValidMins(mins5));
	
	//Check valid time value
	int time1 = 0;
	int time2 = 2459;
	int time3 = 2360;
	int time4 = 59;
	int time5 = 2301;
	EXPECT_EQ(true, taskParse.isValidTime(time1));
	EXPECT_EQ(false, taskParse.isValidTime(time2));
	EXPECT_EQ(false, taskParse.isValidTime(time3));
	EXPECT_EQ(true, taskParse.isValidTime(time4));
	EXPECT_EQ(true, taskParse.isValidTime(time5));

}
