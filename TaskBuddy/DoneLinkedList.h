#pragma once

#include "Task.h"
#include "Date.h"

class DoneLinkedList{
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
	DoneLinkedList();
	
	//destructor for linked list
	~DoneLinkedList();
	
	//Returns true if the linked list is empty
	bool isEmpty();
	
	//Returns number of tasks in linked list
	int getSize();

	//determine if the task has a starting date and time or deadline date and time and pass back the one with the value
	void obtainDateAndTime(Task &, Date*, int*);

	//Returns true if the curTask is of an earlier date and time than listTask
	bool compareDateAndTime(Task &, Task &);

	//Returns the index at which a Task is to be added
	int getInsertIndex(Task &);
	
	//Returns true if task is added to linked list
	bool insert(Task &);

	//Return the nidex of the first task that is not overdued
	int getIndex(Date);

	//remove the task pointed to by the index
	void remove(int);

	//Update the linked list such that it does not contain overdued due items
	void update(Date);

	//Retrieves all task from DoneLinkedList
	void retrieveAll(std::vector<std::string> &);
};