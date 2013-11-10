#include <gtest\gtest.h>
#include "TaskLinkedListTest.h"

/****************************
 TEST FOR INSERT FUNCTION
****************************/

TEST(TaskLinkedListTest, InsertMinorFunction1){
	TaskLinkedList taskList;
	Date inputDate(1, 2, 2013);
	Date date;

	taskList.obtainDateSeparately(&inputDate, &date);

	EXPECT_EQ(1, date._day);
	EXPECT_EQ(2, date._month);
	EXPECT_EQ(2013, date._year);
}

TEST(TaskLinkedListTest, InsertMinorFunction2){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), tempDate3(5,6,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate1, 1200, tempDate2, 1300, nullDate, -1, false);
	Task task3("lunch with mum", "techno", nullDate, -1, nullDate, -1, tempDate3, 1400, false);
	Date date, endDate;
	int time, endTime;


	taskList.obtainDateAndTime(task1, &date, &time, &endDate, &endTime);
	EXPECT_EQ(1, date._day);
	EXPECT_EQ(1200, time);
	EXPECT_EQ(0, endDate._day);
	EXPECT_EQ(-1, endTime);
	
	taskList.obtainDateAndTime(task3, &date, &time, &endDate, &endTime);
	EXPECT_EQ(5, date._day);
	EXPECT_EQ(1400, time);
	EXPECT_EQ(0, endDate._day);
	EXPECT_EQ(-1, endTime);

	taskList.obtainDateAndTime(task2, &date, &time, &endDate, &endTime);
	EXPECT_EQ(1, date._day);
	EXPECT_EQ(1200, time);
	EXPECT_EQ(3, endDate._day);
	EXPECT_EQ(1300, endTime);
}	

TEST(TaskLinkedListTest, InsertMinorFunction3){
	TaskLinkedList taskList;
	Date curDate(1,2,2013), listDate(3,4,2013);
	bool check = false;
	
	EXPECT_EQ(true, taskList.compareDates(&curDate, &listDate, &check));
	EXPECT_EQ(false, check);

	EXPECT_EQ(false, taskList.compareDates(&listDate, &curDate, &check));
	EXPECT_EQ(false, check);

	EXPECT_EQ(false, taskList.compareDates(&curDate, &curDate, &check));
	EXPECT_EQ(true, check);
}

TEST(TaskLinkedListTest, InsertMinorFunction4){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), tempDate3(5,6,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate2, 1200, tempDate2, 1300, nullDate, -1, false);
	Task task3("lunch with mum", "techno", nullDate, -1, nullDate, -1, tempDate3, 1400, false);
	Task task4("lunch with mum", "techno", tempDate2, 1200, tempDate2, 1000, nullDate, -1, false);
	bool isClash = false;
	std::vector<std::string> clashTasks;

	EXPECT_EQ(true, taskList.compareDateAndTime(task1, task2, isClash, clashTasks));
	EXPECT_EQ(false, taskList.compareDateAndTime(task2, task1, isClash, clashTasks));
	EXPECT_EQ(true, taskList.compareDateAndTime(task1, task3, isClash, clashTasks));
	EXPECT_EQ(false, taskList.compareDateAndTime(task2, task4, isClash, clashTasks));
}

TEST(TaskLinkedListTest, InsertMinorFunction5){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);	
	bool isClash = false;
	std::vector<std::string> clashTasks;

	EXPECT_EQ(1, taskList.getInsertIndex(task1, isClash, clashTasks));
}

TEST(TaskLinkedListTest, InsertFunction){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), tempDate2(3,4,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate2, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1500, tempDate1, 1800, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate2, 2359, false);
	bool isClash = false;
	std::vector<std::string> clashTasks, listOfTasks;

	EXPECT_EQ(true, taskList.insert(task1, isClash, clashTasks));
	taskList.insert(task2, isClash, clashTasks);
	isClash = false;
	taskList.insert(task3, isClash, clashTasks);

	taskList.updateStorageVector(listOfTasks);
	EXPECT_EQ(task2.getTask(), listOfTasks[0]);
	EXPECT_EQ(task1.getTask(), listOfTasks[1]);
	EXPECT_EQ(task3.getTask(), listOfTasks[2]);
}

TEST(TaskLinkedListTest, CheckForClashesInInsert){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1000, tempDate1, 1400, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 1200, false);
	Task task4("meeting friends", "marina square", tempDate1, 1700, nullDate, -1, nullDate, -1, false);
	bool isClash = false;
	std::vector<std::string> clashTasks;

	taskList.insert(task1, isClash, clashTasks);
	EXPECT_EQ(false, isClash);
	EXPECT_EQ(0, clashTasks.size());
	
	isClash = false;
	clashTasks.clear();
	taskList.insert(task2, isClash, clashTasks);
	EXPECT_EQ(true, isClash);
	EXPECT_EQ(task1.getTask(), clashTasks[0]);
	EXPECT_EQ(1, clashTasks.size());

	isClash = false;
	clashTasks.clear();
	taskList.insert(task4, isClash, clashTasks);
	EXPECT_EQ(false, isClash);
	EXPECT_EQ(0, clashTasks.size());

	isClash = false;
	clashTasks.clear();
	taskList.insert(task3, isClash, clashTasks);
	EXPECT_EQ(true, isClash);
	EXPECT_EQ(task2.getTask(), clashTasks[0]);
	EXPECT_EQ(task1.getTask(), clashTasks[1]);
	EXPECT_EQ(2, clashTasks.size());
}

/****************************
 TEST FOR REMOVE FUNCTION
****************************/

TEST(TaskLinkedListTest, RemoveMinorFunction1){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("dance lessons", "dance studio", tempDate1, 1000, tempDate1, 1400, nullDate, -1, false);
	Task task3("homework assignment 2", "", nullDate, -1, nullDate, -1, tempDate1, 1200, false);
	bool isClash = false;
	std::vector<std::string> clashTasks;
	int index = 1;

	taskList.insert(task1, isClash, clashTasks);
	taskList.insert(task2, isClash, clashTasks);
	isClash = false;
	taskList.insert(task3, isClash, clashTasks);
	EXPECT_EQ(true, taskList.getRemoveIndex(task3.getTask(), &index));
	EXPECT_EQ(3, index);
}

TEST(TaskLinkedListTest, RemoveMinorFunction2){
	TaskLinkedList taskList;
	std::vector<std::string> keywords;
	
	taskList.splitIntoKeywords("lunch with mum", keywords);
	EXPECT_EQ("lunch", keywords[0]);
	EXPECT_EQ("with", keywords[1]);
	EXPECT_EQ("mum", keywords[2]);
	EXPECT_EQ(3, keywords.size());
}

TEST(TaskLinkedListTest, CheckLastBlockOffInRemove){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, true);
	Task task2("lunch with mum", "techno", tempDate1, 1400, nullDate, -1, nullDate, -1, true);
	Task task3("dance lessons", "dance studio", tempDate1, 1700, nullDate, -1, nullDate, -1, true);
	bool isClash = false;
	std::vector<std::string> clashTasks;

	taskList.insert(task1, isClash, clashTasks);
	taskList.insert(task2, isClash, clashTasks);
	taskList.insert(task3, isClash, clashTasks);

	taskList.checkIfRemainingBlockTask("dance lesson at dance studio");
	EXPECT_EQ(false, taskList.getBlockStatus(3));

	taskList.checkIfRemainingBlockTask("lunch with mum at techno");
	EXPECT_EQ(true, taskList.getBlockStatus(1));
	EXPECT_EQ(true, taskList.getBlockStatus(2));
}
	
TEST(TaskLinkedListTest, RemoveFunction){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate1, 1400, nullDate, -1, nullDate, -1, false);
	Task task3("dance lessons", "dance studio", tempDate1, 1700, nullDate, -1, nullDate, -1, false);
	bool isClash = false;
	std::vector<std::string> clashTasks, listOfTasks;

	taskList.insert(task1, isClash, clashTasks);
	taskList.insert(task2, isClash, clashTasks);
	taskList.insert(task3, isClash, clashTasks);

	EXPECT_EQ(true, taskList.remove(task1.getTask(), "lunch with mum at techno"));
	taskList.updateStorageVector(listOfTasks);
	EXPECT_EQ(task2.getTask(), listOfTasks[0]);
	EXPECT_EQ(task3.getTask(), listOfTasks[1]);
	EXPECT_EQ(2, listOfTasks.size());
}

/****************************
 TEST FOR RETRIEVE FUNCTION
****************************/

TEST(TaskLinkedListTest, RetrieveMinorFunction1){
	TaskLinkedList taskList;
	EXPECT_EQ("abcdef", taskList.toLowerCase("AbCDeF"));
}

TEST(TaskLinkedListTest, RetrieveMinorFunction2){
	TaskLinkedList taskList;
	EXPECT_EQ("01/02/2013", taskList.getStringDate(1,2,2013));
	EXPECT_EQ("10/12/2013", taskList.getStringDate(10,12,2013));
}

TEST(TaskLinkedListTest, RetrieveMinorFunction3){
	TaskLinkedList taskList;
	Date tempDate1(31,12,2013), tempDate2(1,2,2014), nullDate;
	Task task1("lunch with mum", "techno", tempDate1, 1200, tempDate2, 1500, nullDate, -1, false);
	EXPECT_EQ(task1.getTask() + "31/12/201301/01/201401/02/2014", taskList.compareAndIncludeRange(task1.getTask(), &tempDate1._day, &tempDate1._month, &tempDate1._year, &tempDate2._day, &tempDate2._month, &tempDate2._year));
}

/*TEST(TaskLinkedListTest, RetrieveMinorFunction3){
	TaskLinkedList taskList;
	Date tempDate1(1,2,2013), tempDate2(3,2,2013), nullDate;
	Task task1("lunch with mum", "deck", tempDate1, 1200, nullDate, -1, nullDate, -1, false);
	Task task2("lunch with mum", "techno", tempDate1, 1400, tempDate2, 1000, nullDate, -1, false);
	Task task3("lunch with dad", "YIH", nullDate, -1, nullDate, -1, tempDate2, 1800, false);
	bool isClash = false;
	std::vector<std::string> clashTasks, keywords,taskList;

	taskList.insert(task1, isClash, clashTasks);
	taskList.insert(task2, isClash, clashTasks);
	taskList.insert(task3, isClash, clashTasks);

	keywords.push_back("lunch");
	keywords.push_back("with");
	keywords.push_back("mum");

	bool TaskLinkedList::retrieve(const std::vector<std::string> keywords, std::vector<std::string> & taskList){
}*/