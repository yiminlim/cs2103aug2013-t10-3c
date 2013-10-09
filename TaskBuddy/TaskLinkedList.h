#ifndef _TASKLINKEDLIST_H_
#define _TASKLINKEDLIST_H_

#include "Task.h"

class TaskLinkedList{
private:
	struct ListNode {
		Task item;
		ListNode *next;
		ListNode *prev;
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

	//Convert the date from a string to int
	void convertDate(const std::string, int*, int*, int*);

	//Check whether the task has a starting date and time or due date and time and return the respective one
	void getTimeAndDate(Task &, int*, int*, int*, int*);

	//Returns the index at which a Task is to be added
	int getAddingIndex(Task &);
	
	//Returns true if task is added to linked list
	bool insert(const Task &);
	
	//Returns true if task is remove from linked list
	bool remove(std::string);
	
	//Pass over a vector of keywords and an empty vector of string for me to return those strings with the words in it
	bool retrieve(const std::vector<std::string>, std::vector<std::string> &);
	
	//Returns true if task is edited successfully in linked list
	bool edit(int, Task);
};
#endif;