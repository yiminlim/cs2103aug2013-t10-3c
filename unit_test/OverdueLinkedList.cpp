#include <gtest\gtest.h>
#include "OverdueLinkedListTest.h"

/****************************
 TEST FOR INSERT FUNCTION
****************************/

TEST(OverdueLinkedListTest, InsertMinorFunction1) {
	OverdueLinkedList overdueList;
	Date inputDate(1, 2, 2013);
	Date date;

	overdueList.obtainDateSeparately(&inputDate, &date);

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