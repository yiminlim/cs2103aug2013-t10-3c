#include <gtest\gtest.h>
#include "DoneLinkedListTest.h"

/****************************
 TEST FOR INSERT FUNCTION
****************************/

TEST(DoneLinkedListTest, InsertMinorFunction1) {
	DoneLinkedList doneList;
	Date inputDate(1, 2, 2013);
	Date date;

	doneList.obtainDateSeparately(&inputDate, &date);

	EXPECT_EQ(1, date._day);
	EXPECT_EQ(2, date._month);
	EXPECT_EQ(2013, date._year);
}

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

TEST(DoneLinkedListTest, InsertMinorFunction5) {
	DoneLinkedList doneList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);	
	EXPECT_EQ(1, doneList.getInsertIndex(task1));
}

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