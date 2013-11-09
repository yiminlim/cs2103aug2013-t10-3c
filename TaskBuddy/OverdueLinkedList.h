#pragma once

#include "Task.h"
#include "Date.h"

class OverdueLinkedList{
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
	OverdueLinkedList();
	
	//destructor for linked list
	~OverdueLinkedList();
	
	//Returns true if the linked list is empty
	bool isEmpty();
	
	//Returns number of tasks in linked list
	int getSize();

	void obtainDateSeparately(Date*, Date*);

	//determine if the task has a starting date and time or deadline date and time and pass back the one with the value
	void obtainDateAndTime(Task &, Date*, int*, Date*, int*);

	bool compareDates(Date*, Date*, bool*);

	//Returns true if the curTask is of an earlier date and time than listTask
	bool compareDateAndTime(Task &, Task &);

	//Returns the index at which a Task is to be added
	int getInsertIndex(Task &);
	
	//Returns true if task is added to linked list
	bool insert(Task &);

	//Remove the item at the head of the linked list
	void remove();

	//Remove all the items in the linked list
	void clear();
	
	//Retrieve all the items in the linked list
	void updateStorageVector(std::vector<std::string> &);
};