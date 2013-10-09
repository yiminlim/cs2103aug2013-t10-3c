#ifndef _TASKLINKEDLIST_H_
#define _TASKLINKEDLIST_H_

#include "Task.h"

struct Date{
		int day;
		int month;
		int year;
	};

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
	void obtainDateAndTime(Task &, Date*, int*);

	//Returns true if the curTask is of an earlier date and time than listTask
	bool compareDateAndTime(Task &, Task &);

	//Returns the index at which a Task is to be added
	int getInsertIndex(Task &);
	
	//Returns true if task is added to linked list
	bool insert(Task &);

	//Returns the index of the task to be removed
	int getRemoveIndex(std::string);
	
	//Returns true if task is remove from linked list
	bool remove(std::string);
	
	//Pass over a vector of keywords and an empty vector of string for me to return those strings with the words in it
	bool retrieve(const std::vector<std::string>, std::vector<std::string> &);
	
	//Returns true if task is edited successfully in linked list
	bool edit(int, Task);
};
#endif;