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

	void insert(Task &);

	void remove();

	void clear();
	
	void updateStorageVector(std::vector<std::string> &);
};