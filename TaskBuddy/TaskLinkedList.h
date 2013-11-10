#pragma once

#include "Task.h"
#include "Date.h"

class TaskLinkedList{
private:
	struct ListNode {
		Task item;
		ListNode *next;
	};
	
	ListNode* _head;
	int _size;
	
	//Return a ListNode pointer that will traverse to the position given by the index.
	ListNode* traverseTo(int index);

	static const std::string KEYWORD_EMPTY_STRING;
	static const std::string KEYWORD_BLOCKOFF;
	static const std::string KEYWORD_ZERO;
	static const std::string KEYWORD_SLASH;
	static const std::string KEYWORD_DASH;
	
	static const char KEYWORD_NULL;
	
	static const int KEYNUMBER_DAY;
	static const int KEYNUMBER_MONTH;
	
public:
	//Empty constructor
	TaskLinkedList();
	
	//Destructor for linked list
	~TaskLinkedList();
	
	//Return true if the linked list is empty.
	bool isEmpty();
	
	//Return number of tasks in linked list.
	int getSize();

	//Copy the Date from one Date to another.
	void obtainDateSeparately(Date*, Date*);

	//Determine if the task has a starting date and time or deadline date and time and pass back the one with the value and update the ending date and time accordingly.
	void obtainDateAndTime(Task &, Date*, int*, Date*, int*);

	//Compare the 2 dates and return true is one of the date is earlier than the other one. If they are the same, updated the bool value passed into the function.
	bool compareDates(Date*, Date*, bool*);

	//Return true if the one task is of an earlier date and time than the other task and check for clashes in the meantime.
	bool compareDateAndTime(Task &, Task &, bool &, std::vector<std::string>&);

	//Return the index at which a Task is to be added.
	int getInsertIndex(Task &, bool &, std::vector<std::string>&);
	
	//Return true if task is added to linked list. Check if there are any clashes.
	bool insert(Task &, bool &, std::vector<std::string>&);

	//Return the index of the task to be removed.
	bool getRemoveIndex(std::string, int*);

	//Split a string into a vector of keywords.
	void splitIntoKeywords(std::string, std::vector<std::string> &);
	
	//Check if the task is a blocked item and if it is the last task left. If true, unblock the task.
	void checkIfRemainingBlockTask(std::string); 
	
	//Return true if task is remove from linked list, at the same time, if the deleted item is a blocked item, check if there is only one task left in that specific block. If true, unblock the last task.
	bool remove(std::string, std::string);

	//Convert string into lowercase.
	std::string toLowerCase(std::string);

	//Convert int to string for date.
	std::string getStringDate(int, int, int);

	//Compare the range of dates and add the range into the task output format.
	std::string compareAndIncludeRange(std::string, int*, int*, int*, int*, int*, int*);

	//Convert string to int for date.
	void getIntDate(std::string, int*, int*, int*);

	//"Main function" to call the other functions to assist in including range in dates into temptask for searching.
	std::string includeRangeOfDates(std::string);

	//Pass over a vector of keywords and search for task which contains all keywords and return them in the empty vector of string that is passed over.
	bool retrieve(const std::vector<std::string>, std::vector<std::string> &);

	//Copy the entire list of output format of the tasks in the linked list into the empty vector that is passed over.
	void updateStorageVector(std::vector<std::string> &);

	//Set the bool block component of the string as true.
	void setBlock(std::string);

	//Compare the date with today's date and push the task into the vector passed over if it is earlier than today's date.
	void compareWithToday(Date, Date, std::string, std::vector<std::string> &);

	//Return list of overdued items.
	void getOverdueList(Date, std::vector<std::string> &);
	
	//Return whether the task indicated by the index is blocked or not (For g-test).
	bool getBlockStatus(int index);

	//Return true if it is the last remaining task.
	bool checkIfRemainingTask(std::string);
};