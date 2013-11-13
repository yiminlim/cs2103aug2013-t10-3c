//@author A0103481R
#pragma once

#include "Task.h"
#include "Date.h"
#include <assert.h>

class OverdueLinkedList{
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
	
public:
	//Empty constructor
	OverdueLinkedList();
	
	//Destructor for linked list
	~OverdueLinkedList();
	
	//Return true if the linked list is empty.
	bool isEmpty();
	
	//Return number of tasks in linked list.
	int getSize();

	//Copy the Date from one Date to another.
	void obtainDateSeparately(Date*, Date*);

	//Determine if the task has a starting date and time or deadline date and time and pass back the one with the value. Also, update the ending date and time accordingly.
	void obtainDateAndTime(Task &, Date*, int*, Date*, int*);

	//Compare the 2 dates and return true is one of the date is earlier than the other one. If they are the same, updated the bool value passed into the function.
	bool compareDates(Date*, Date*, bool*);

	//Return true if the one task is of an earlier date and time than the other task.
	bool compareDateAndTime(Task &, Task &);

	//Return the index at which a Task is to be added.
	int getInsertIndex(Task &);
	
	//Return true if task is added to linked list.
	bool insert(Task &);

	//Remove the item at the head of the linked list.
	void remove();

	//Remove all the items in the linked list.
	void clear();
	
	//Retrieve all the items in the linked list.
	void updateStorageVector(std::vector<std::string> &);
};