//@author A0103481R
#include <gtest\gtest.h>
#include "DoneLinkedListTest.h"

/****************************
 TEST FOR INSERT FUNCTION
****************************/

//Check to see if the function copies the date from one Date class to another Date class correctly.
TEST(DoneLinkedListTest, InsertMinorFunction1) {
	DoneLinkedList doneList;
	Date inputDate(1, 2, 2013);
	Date date;

	doneList.obtainDateSeparately(&inputDate, &date);

	EXPECT_EQ(1, date._day);
	EXPECT_EQ(2, date._month);
	EXPECT_EQ(2013, date._year);
}

//Check to see if the function obtains the right date and time (either starting or deadline) and updates the ending date and time accordingly.
TEST(DoneLinkedListTest, InsertMinorFunction2) {
	DoneLinkedList doneList;

	Date tempDate1(1,2,2013), tempDate2(3,4,2013), tempDate3(5,6,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate1, 1200, tempDate2, 1300, nullDate, -1, false);
	Task task3("lunch with mum", "techno", nullDate, -1, nullDate, -1, tempDate3, 1400, false);
	Date date, endDate;
	int time, endTime = -1;


	doneList.obtainDateAndTime(task1, &date, &time, &endDate, &endTime);
	EXPECT_EQ(1, date._day);
	EXPECT_EQ(1200, time);
	EXPECT_EQ(0, endDate._day);
	EXPECT_EQ(-1, endTime);
	
	doneList.obtainDateAndTime(task3, &date, &time, &endDate, &endTime);
	EXPECT_EQ(5, date._day);
	EXPECT_EQ(1400, time);
	EXPECT_EQ(0, endDate._day);
	EXPECT_EQ(-1, endTime);

	doneList.obtainDateAndTime(task2, &date, &time, &endDate, &endTime);
	EXPECT_EQ(1, date._day);
	EXPECT_EQ(1200, time);
	EXPECT_EQ(3, endDate._day);
	EXPECT_EQ(1300, endTime);
}

//Check to see if the comparing of 2 dates give the correct result (true if cur is earlier than list).
TEST(DoneLinkedListTest, InsertMinorFunction3) {
	DoneLinkedList doneList;
	Date curDate(1,2,2013), listDate(3,4,2013);
	bool check = false;
	
	EXPECT_EQ(true, doneList.compareDates(&curDate, &listDate, &check));
	EXPECT_EQ(false, check);

	EXPECT_EQ(false, doneList.compareDates(&listDate, &curDate, &check));
	EXPECT_EQ(false, check);

	EXPECT_EQ(false, doneList.compareDates(&curDate, &curDate, &check));
	EXPECT_EQ(true, check);
}

//Check to see if the comaring of 2 tasks give the correct result (meaning which task should be sorted in front of which task accordingly to date and time).
TEST(DoneLinkedListTest, InsertMinorFunction4) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), tempDate3(5,6,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate2, 1200, tempDate2, 1300, nullDate, -1, false);
	Task task3("lunch with mum", "techno", nullDate, -1, nullDate, -1, tempDate3, 1400, false);
	Task task4("lunch with mum", "techno", tempDate2, 1200, tempDate2, 1000, nullDate, -1, false);

	EXPECT_EQ(true, doneList.compareDateAndTime(task1, task2));
	EXPECT_EQ(false, doneList.compareDateAndTime(task2, task1));
	EXPECT_EQ(true, doneList.compareDateAndTime(task1, task3));
	EXPECT_EQ(false, doneList.compareDateAndTime(task2, task4));
}

//Check to see if function returns the correct index pointing to the task that is passed over.
TEST(DoneLinkedListTest, InsertMinorFunction5) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);	
	EXPECT_EQ(1, doneList.getInsertIndex(task1));
}

//Check to see if the function inserts a task properly, sorted according to date and time.
TEST(DoneLinkedListTest, InsertFunction) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate2, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 2359, false);
	std::vector<std::string> listOfTasks;

	EXPECT_EQ(true, doneList.insert(task1));
	doneList.insert(task2);
	doneList.insert(task3);

	doneList.updateStorageVector(listOfTasks);
	EXPECT_EQ(task2.getTask(), listOfTasks[0]);
	EXPECT_EQ(task3.getTask(), listOfTasks[1]);
	EXPECT_EQ(task1.getTask(), listOfTasks[2]);
}

/****************************
 TEST FOR REMOVE FUNCTION
****************************/

//Check if the function updates the date and time according to the one that is required from comparing when deciding whether the task is overdued.
TEST(DoneLinkedListTest, RemoveMinorFunction1) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate, date;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate2, 2359, false);
	int time;

	doneList.obtainDateAndTimeForRemoving(task1, &date, &time);
	EXPECT_EQ(tempDate1._day, date._day);
	EXPECT_EQ(1200, time);

	doneList.obtainDateAndTimeForRemoving(task2, &date, &time);
	EXPECT_EQ(tempDate2._day, date._day);
	EXPECT_EQ(1800, time);

	doneList.obtainDateAndTimeForRemoving(task3, &date, &time);
	EXPECT_EQ(tempDate2._day, date._day);
	EXPECT_EQ(2359, time);
}

//Check if the function returns a vector of index pointing to overdued tasks.
TEST(DoneLinkedListTest, RemoveMinorFunction2) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), tempDate2(3,2,2013), nullDate, today(2,2,2013);
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 2359, false);
	std::vector<int> index;

	doneList.insert(task1);
	doneList.insert(task2);
	doneList.insert(task3);
	index = doneList.getIndex(today);
	EXPECT_EQ(2, index.size());
	EXPECT_EQ(1, index[0]);
	EXPECT_EQ(3, index[1]);
}

//Check if the function removes a task properly according to the input index.
TEST(DoneLinkedListTest, RemoveFunctionByIndex) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 1600, false);
	std::vector<std::string> listOfTasks;

	doneList.insert(task1);
	doneList.insert(task2);
	doneList.insert(task3);
	doneList.remove(2);
	doneList.updateStorageVector(listOfTasks);
	EXPECT_EQ(2, listOfTasks.size());
	EXPECT_EQ(task1.getTask(), listOfTasks[0]);
	EXPECT_EQ(task3.getTask(), listOfTasks[1]);
}

//Check if the function removes a task properly according to the input task sting.
TEST(DoneLinkedListTest, RemoveFunctionByTask) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 2359, false);
	std::vector<std::string> listOfTasks;

	doneList.insert(task1);
	doneList.insert(task2);
	doneList.insert(task3);
	doneList.removeTask(task2.getTask());
	doneList.updateStorageVector(listOfTasks);
	EXPECT_EQ(2, listOfTasks.size());
	EXPECT_EQ(task1.getTask(), listOfTasks[0]);
	EXPECT_EQ(task3.getTask(), listOfTasks[1]);
}

/****************************
 TEST FOR UPDATE FUNCTION
****************************/

//Check if the function updates the linked list by removing overdued tasks.
TEST(DoneLinkedListTest, UpdateFunction) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), tempDate2(3,2,2013), nullDate, today(2,2,2013);
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 2359, false);
	std::vector<std::string> listOfTasks;

	doneList.insert(task1);
	doneList.insert(task2);
	doneList.insert(task3);
	doneList.update(today);
	doneList.updateStorageVector(listOfTasks);
	EXPECT_EQ(1, listOfTasks.size());
	EXPECT_EQ(task2.getTask(), listOfTasks[0]);
}