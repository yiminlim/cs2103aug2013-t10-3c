#include "TaskTest.h"

TEST(TaskTest, FormatDateWithSingleDigitDay){
	Task task;
	Date date(1,10,2013);
	std::string expectedDateString = "01/10/2013";
	EXPECT_EQ(expectedDateString, task.formatDateOutputString(date));
}
TEST(TaskTest, FormatDateWithSingleDigitMonth){
	Task task;
	Date date(12,1,2013);
	std::string expectedDateString = "12/01/2013";
	EXPECT_EQ(expectedDateString, task.formatDateOutputString(date));
}

TEST(TaskTest, FormatDateWithSingleDigitDayAndMonth){
	Task task;
	Date date(1,1,2013);
	std::string expectedDateString = "01/01/2013";
	EXPECT_EQ(expectedDateString, task.formatDateOutputString(date));
}

TEST(TaskTest, FormatTimeWithSingleDigitValue){
	Task task;
	int time = 5;
	std::string expectedTimeString = "0005";
	EXPECT_EQ(expectedTimeString, task.formatTimeOutputString(time));
}

TEST(TaskTest, FormatTimeWithDoubleDigitValue){
	Task task;
	int time = 30;
	std::string expectedTimeString = "0030";
	EXPECT_EQ(expectedTimeString, task.formatTimeOutputString(time));
}

TEST(TaskTest, FormatTimeWithTripleDigitValue){
	Task task;
	int time = 845;
	std::string expectedTimeString = "0845";
	EXPECT_EQ(expectedTimeString, task.formatTimeOutputString(time));
}

TEST(TaskTest, FormatTimeWithFourDigitValue){
	Task task;
	int time = 1230;
	std::string expectedTimeString = "1230";
	EXPECT_EQ(expectedTimeString, task.formatTimeOutputString(time));
}

TEST(TaskTest, FormatFloatingTaskStringWithLocation){
	std::string action = "action";
	std::string location = "location";
	Date startingDate;
	int startingTime = -1;
	Date endingDate;
	int endingTime = -1;
	Date deadlineDate;
	int deadlineTime = -1;
	bool block = false;
	
	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	std::string expectedTaskString = "   action at location";
	EXPECT_EQ(expectedTaskString, task.formatTaskOutputString());
}

TEST(TaskTest, FormatActivityTaskWithEndWithTime){
	std::string action = "action";
	std::string location = "";
	Date startingDate(11,11,2013);
	int startingTime = 800;
	Date endingDate(11,11,2013);
	int endingTime = 900;
	Date deadlineDate;
	int deadlineTime = -1;
	bool block = false; 

	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	std::string expectedTaskString = "   11/11/2013 0800 hrs - 11/11/2013 0900 hrs : action";
	EXPECT_EQ(expectedTaskString, task.formatTaskOutputString());
}

TEST(TaskTest, FormatBlockedActivityTaskWithLocation){
	std::string action = "action";
	std::string location = "location";
	Date startingDate(11,11,2013);
	int startingTime = -1;
	Date endingDate;
	int endingTime = -1;
	Date deadlineDate;
	int deadlineTime = -1;
	bool block = true; 

	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	std::string expectedTaskString = "   11/11/2013 : action at location (blockoff)";
	EXPECT_EQ(expectedTaskString, task.formatTaskOutputString());
}

TEST(TaskTest, FormatDeadlineTaskWithTime){
	std::string action = "action";
	std::string location = "";
	Date startingDate;
	int startingTime = -1;
	Date endingDate;
	int endingTime = -1;
	Date deadlineDate(11,11,2013);
	int deadlineTime = 2359;
	bool block = false; 

	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	std::string expectedTaskString = "by 11/11/2013 2359 hrs : action";
	EXPECT_EQ(expectedTaskString, task.formatTaskOutputString());
}

TEST(TaskTest, CheckingDeadlineTaskType){
	std::string action = "action";
	std::string location = "";
	Date startingDate;
	int startingTime = -1;
	Date endingDate;
	int endingTime = -1;
	Date deadlineDate(11,11,2013);
	int deadlineTime = 2359;
	bool block = false; 

	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	EXPECT_EQ(true, task.isDeadlineType());
	EXPECT_EQ(false, task.isActivityType());
	EXPECT_EQ(false, task.isFloatingType());
}

TEST(TaskTest, CheckingActivityTaskType){
	std::string action = "action";
	std::string location = "";
	Date startingDate(11,11,2013);
	int startingTime = -1;
	Date endingDate(14,11,2013);
	int endingTime = -1;
	Date deadlineDate;
	int deadlineTime = -1;
	bool block = false; 

	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	EXPECT_EQ(false, task.isDeadlineType());
	EXPECT_EQ(true, task.isActivityType());
	EXPECT_EQ(false, task.isFloatingType());
}

TEST(TaskTest, CheckingFloatingTaskType){
	std::string action = "action";
	std::string location = "location";
	Date startingDate;
	int startingTime = -1;
	Date endingDate;
	int endingTime = -1;
	Date deadlineDate;
	int deadlineTime = -1;
	bool block = false; 

	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	EXPECT_EQ(false, task.isDeadlineType());
	EXPECT_EQ(false, task.isActivityType());
	EXPECT_EQ(true, task.isFloatingType());
}

TEST(TaskTest, EditingBlock){
	std::string action = "action";
	std::string location = "";
	Date startingDate;
	int startingTime = -1;
	Date endingDate;
	int endingTime = -1;
	Date deadlineDate(11,11,2013);
	int deadlineTime = 2359;
	bool block = false; 

	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	task.setBlock(true);
	EXPECT_EQ(true, task.getBlock());
	std::string newExpectedOutputString = "by 11/11/2013 2359 hrs : action (blockoff)";
	EXPECT_EQ(newExpectedOutputString, task.formatTaskOutputString());
}