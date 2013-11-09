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
	
	//Returns a ListNode pointer that will traverse to the position given by the index.
	ListNode* traverseTo(int index);
	
public:
	//Empty constructor
	DoneLinkedList();
	
	//Destructor for linked list
	~DoneLinkedList();
	
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

	//Determine which date to look at for updating (starting, ending or deadline) and pass the selected one over.
	void obtainDateAndTimeForRemoving(Task &, Date*, int*);

	//Return a vector of index which indicates the tasks to be deleted.
	std::vector <int> getIndex(Date);

	//Remove the task pointed to by the index.
	void remove(int);

	//Return true if the task passed over is found and removed from the linked list.
	bool removeTask(std::string);

	//Update the linked list such that it does not contain overdued due items.
	void update(Date);

	//Return everything in the linked list.
	void updateStorageVector(std::vector<std::string> &);
};