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
	void convertDate(std::string, int*, int*, int*);

	//Returns the index at which a Task is to be added
	int getAddingIndex(const Task &);
	
	//initialisation by inserting all task into program at the start
	void initialInsert(const Task &);
	
	//sort tasks in list according to date and time
	void mergeSort(int, int); 
	
	//Returns true if task is added to linked list
	bool insert(const Task &);
	
	//Returns true if task is remove from linked list
	bool remove(int);
	
	//Returns the task in the linked list as given by the index
	Task retrieve(int);
	
	//Returns true if task is edited successfully in linked list
	bool edit(int, Task);
};
#endif;