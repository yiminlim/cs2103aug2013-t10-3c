#include <gtest\gtest.h>
#include "OverdueLinkedListTest.h"

/****************************
 TEST FOR INSERT FUNCTION
****************************/

//Check to see if the function copies the date from one Date class to another Date class correctly.
TEST(OverdueLinkedListTest, InsertMinorFunction1){
	OverdueLinkedList overdueList;
	Date inputDate(1, 2, 2013);
	Date date;

	overdueList.obtainDateSeparately(&inputDate, &date);

	EXPECT_EQ(1, date._day);
	EXPECT_EQ(2, date._month);
	EXPECT_EQ(2013, date._year);
}

//Check to see if the function obtains the right date and time (either starting or deadline) and updates the ending date and time accordingly.
TEST(OverdueLinkedListTest, InsertMinorFunction2){
	OverdueLinkedList overdueList;

	Date tempDate1(1,2,2013), tempDate2(3,4,2013), tempDate3(5,6,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate1, 1200, tempDate2, 1300, nullDate, -1, false);
	Task task3("lunch with mum", "techno", nullDate, -1, nullDate, -1, tempDate3, 1400, false);
	Date date, endDate;
	int time, endTime = -1;


	overdueList.obtainDateAndTime(task1, &date, &time, &endDate, &endTime);
	EXPECT_EQ(1, date._day);
	EXPECT_EQ(1200, time);
	EXPECT_EQ(0, endDate._day);
	EXPECT_EQ(-1, endTime);
	
	overdueList.obtainDateAndTime(task3, &date, &time, &endDate, &endTime);
	EXPECT_EQ(5, date._day);
	EXPECT_EQ(1400, time);
	EXPECT_EQ(0, endDate._day);
	EXPECT_EQ(-1, endTime);

	overdueList.obtainDateAndTime(task2, &date, &time, &endDate, &endTime);
	EXPECT_EQ(1, date._day);
	EXPECT_EQ(1200, time);
	EXPECT_EQ(3, endDate._day);
	EXPECT_EQ(1300, endTime);
}

//Check to see if the comparing of 2 dates give the correct result (true if cur is earlier than list).
TEST(OverdueLinkedListTest, InsertMinorFunction3){
	OverdueLinkedList overdueList;
	Date curDate(1,2,2013), listDate(3,4,2013);
	bool check = false;
	
	EXPECT_EQ(true, overdueList.compareDates(&curDate, &listDate, &check));
	EXPECT_EQ(false, check);

	EXPECT_EQ(false, overdueList.compareDates(&listDate, &curDate, &check));
	EXPECT_EQ(false, check);

	EXPECT_EQ(false, overdueList.compareDates(&curDate, &curDate, &check));
	EXPECT_EQ(true, check);
}

//Check to see if the comaring of 2 tasks give the correct result (meaning which task should be sorted in front of which task accordingly to date and time).
TEST(OverdueLinkedListTest, InsertMinorFunction4){
	OverdueLinkedList overdueList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), tempDate3(5,6,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate2, 1200, tempDate2, 1300, nullDate, -1, false);
	Task task3("lunch with mum", "techno", nullDate, -1, nullDate, -1, tempDate3, 1400, false);
	Task task4("lunch with mum", "techno", tempDate2, 1200, tempDate2, 1000, nullDate, -1, false);

	EXPECT_EQ(true, overdueList.compareDateAndTime(task1, task2));
	EXPECT_EQ(false, overdueList.compareDateAndTime(task2, task1));
	EXPECT_EQ(true, overdueList.compareDateAndTime(task1, task3));
	EXPECT_EQ(false, overdueList.compareDateAndTime(task2, task4));
}

//Check to see if function returns the correct index pointing to the task that is passed over.
TEST(OverdueLinkedListTest, InsertMinorFunction5){
	OverdueLinkedList overdueList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);	
	EXPECT_EQ(1, overdueList.getInsertIndex(task1));
}

//Check to see if the function inserts a task properly, sorted according to date and time.
TEST(OverdueLinkedListTest, InsertFunction){
	OverdueLinkedList overdueList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate2, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 2359, false);
	std::vector<std::string> listOfTasks;

	EXPECT_EQ(true, overdueList.insert(task1));
	overdueList.insert(task2);
	overdueList.insert(task3);

	overdueList.updateStorageVector(listOfTasks);
	EXPECT_EQ(task2.getTask(), listOfTasks[0]);
	EXPECT_EQ(task3.getTask(), listOfTasks[1]);
	EXPECT_EQ(task1.getTask(), listOfTasks[2]);
}

/****************************
 TEST FOR CLEAR FUNCTION
****************************/

//Check if the function removes the head of the linked list properly
TEST(OverdueLinkedListTest, ClearMinorFunction1){
	OverdueLinkedList overdueList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 1600, false);
	std::vector<std::string> listOfTasks;

	overdueList.insert(task1);
	overdueList.insert(task2);
	overdueList.insert(task3);

	overdueList.remove();
	overdueList.updateStorageVector(listOfTasks);
	EXPECT_EQ(2, listOfTasks.size());
	EXPECT_EQ(task2.getTask(), listOfTasks[0]);
	EXPECT_EQ(task3.getTask(), listOfTasks[1]);
}

//Check if the function clears the entire linked list.
TEST(OverdueLinkedListTest, ClearFunction){
	OverdueLinkedList overdueList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate2, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 1600, false);
	std::vector<std::string> listOfTasks;

	overdueList.insert(task1);
	overdueList.insert(task2);
	overdueList.insert(task3);
	overdueList.clear();
	overdueList.updateStorageVector(listOfTasks);
	EXPECT_EQ(0, listOfTasks.size());
}