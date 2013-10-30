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
	
	//Returns a ListNode pointer that will traverse to the position given by the index
	ListNode* traverseTo(int index);
	
public:
	//empty constructor
	TaskLinkedList();
	
	//destructor for linked list
	~TaskLinkedList();
	
	//Returns true if the linked list is empty
	bool isEmpty();
	
	//Returns number of tasks in linked list
	int getSize();

	//determine if the task has a starting date and time or deadline date and time and pass back the one with the value
	void obtainDateAndTime(Task &, Date*, int*, int*);

	//Returns true if the curTask is of an earlier date and time than listTask
	bool compareDateAndTime(Task &, Task &, bool &);

	//Returns the index at which a Task is to be added
	int getInsertIndex(Task &, bool &);
	
	//Returns true if task is added to linked list. Check if there are any clashes.
	bool insert(Task &, bool &);

	//Returns the index of the task to be removed
	bool getRemoveIndex(std::string, int*);

	//Split a string into a vector of keywords
	void splitIntoKeywords(std::string, std::vector<std::string> &);
	
	//check if the task is a blocked item and if it is the last task left. IF true, unblock the task
	void checkIfRemainingBlockTask(std::string); 
	
	//Returns true if task is remove from linked list, at the same time, if the deleted item is a blocked item, check if there is only one task left in that specific block. If true, unblock the last task
	bool remove(std::string, std::string);

	//Convert string into lowercase
	std::string toLowerCase(std::string);

	//convert int to string for date
	std::string getStringDate(int, int, int);

	//compare the range of dates and add the range into the task output format
	std::string compareAndIncludeRange(std::string, int*, int*, int*, int*, int*, int*);

	//convert string to int for date
	void getIntDate(std::string, int*, int*, int*);

	//"main functoin" to call the other functions to assist in including range in dates into temptask for searching
	std::string includeRangeOfDates(std::string);

	//Pass over a vector of keywords and an empty vector of string for me to return those strings with the words in it
	bool retrieve(const std::vector<std::string>, std::vector<std::string> &);

	//Remove blockings that are unwanted which are stored in the vector
	//bool removeBlockings(const std::vector<std::string>);

	//Return true if blockings are finalised
	//bool finaliseBlocking(const std::vector<std::string>);

	//Copy the entire list of output format of the tasks in the linked list into the empty vector that is passed over
	void updateStorageVector(std::vector<std::string> &);

	//Set the bool block component of the string as true
	void setBlock(std::string);
};