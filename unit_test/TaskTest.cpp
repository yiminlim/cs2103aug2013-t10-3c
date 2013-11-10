#include "TaskTest.h"


TEST_F(TaskTest, FormatFloatingTaskStringWithLocation) {
	std::string action = "action";
	std::string location = "location";
	Date startingDate;
	int startingTime = -1;
	Date endingDate;
	int endingTime = -1;
	Date deadlineDate;
	int deadlineTime = -1;
	bool block = true;
	
	Task task(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, block);
	std::string expectedTaskString = "   : action at location";

	EXPECT_EQ(expectedTaskString, task.formatTaskOutputString());
}

