#include "DoneLinkedList.h"

DoneLinkedList::DoneLinkedList(){
	_head = NULL;
	_size = 0;
}
	
//destructor for linked list
DoneLinkedList::~DoneLinkedList(){
}

//Pre-condition: input an index between the range of 1 and the size of the linked list (including)
//Post-condition: returns a ListNode pointer that will traverse to the position given by the index
DoneLinkedList::ListNode* DoneLinkedList::traverseTo(int index){
	if ( (index < 1) || (index > getSize()) ){
		return NULL;
	}

	else{
		ListNode *cur = _head;
		for (int skip = 1; skip < index; skip++){
			cur = cur->next;
		}
		return cur;
	}
}
	
//Pre-condition: check if linked list is empty
//Post-condition: return true if the linked list is empty
bool DoneLinkedList::isEmpty(){
	return _size==0;
}
	
//Pre-condition: check for the size of the linked list
//Post-condition: return the number of tasks in the linked list
int DoneLinkedList::getSize(){
	return _size;
}

//Pre-condition: input in a Task reference and two pointers indicating date and time 
//				 the task have to have either a startingDate and startingTime or a deadlineDate and deadlineTime
//				 for empty time, it is declared with a value -1
//Post-condition: the pointer indicating date and time will be updated to store either the startingDate and startingTime or the deadlineDate and deadlineTime of the respective Task. 
void DoneLinkedList::obtainDateAndTime(Task & task, Date *date, int *time){
	if (task.getDeadlineTime() == -1){
		date->_day = task.getStartingDate()._day;
		date->_month = task.getStartingDate()._month;
		date->_year = task.getStartingDate()._year;
		*time = task.getStartingTime();
	}
	else{
		date->_day = task.getDeadlineDate()._day;
		date->_month = task.getDeadlineDate()._month;
		date->_year = task.getDeadlineDate()._year;
		*time = task.getDeadlineTime();
	}
	return;
}

//Pre-condition: input the Task reference to be added and a specific Task reference from the linked list and sort them accordingly 
//Post-condition: returns true if the Task reference to be added is of an earlier date and time than the specific Task reference from the linked list
bool DoneLinkedList::compareDateAndTime(Task & curTask, Task & listTask){
		Date *curDate = new Date;
		Date *listDate = new Date;
		int *curTime = new int, *listTime = new int;
		bool condition = false;
		obtainDateAndTime(curTask, curDate, curTime);
		obtainDateAndTime(listTask, listDate, listTime);

		if (curDate->_year < listDate->_year){
			condition = true;
		} 
		else if (curDate->_year > listDate->_year){
			condition = false;
		} 
		else if (curDate->_month < listDate->_month){
			condition = true;
		}
		else if (curDate->_month > listDate->_month){
			condition = false;
		}
		else if (curDate->_day < listDate->_day){
			condition = true;
		}
		else if (curDate->_day > listDate->_day){
			condition = false;
		}
		else if (*curTime < *listTime){
			condition = true;
		}
		else{
			condition = false;
		}
			
		delete curDate;
		curDate = NULL;
		delete listDate;
		listDate = NULL;
		delete curTime;
		curTime = NULL;
		delete listTime;
		listTime = NULL;

		return condition;		
}

//Pre-condition: input a Task reference to check for the index which it should be inserted into the linked list, in a sorted manner
//Post-condition: return the index where the Task is supposed to be added at
int DoneLinkedList::getInsertIndex(Task & curTask){
	ListNode *cur = _head;
	int i = 1;

	if (isEmpty()){
		return i;
	}

	while (cur != NULL){
		if (compareDateAndTime(curTask, cur->item)){
			return i;
		} 
		else{
			cur = cur->next;
			i++;
		}
	} 

	return i;
}

//Pre-condition: input a Task reference to be added into the linked list 
//Post-condition: return true if the task is added into the linked list in an sorted manner
bool DoneLinkedList::insert(Task & curTask){
	int newSize = getSize() + 1;
	int index = getInsertIndex(curTask);

	if ( (index < 1) || (index > newSize) ){
		return false;
	}
	else{
		ListNode *newTask = new ListNode;
		newTask->item = curTask;
		newTask->next = NULL;
		_size = newSize;

		if (index == 1){
			newTask->next = _head;
			_head = newTask;
		} 
		else{
			ListNode *prev = traverseTo(index-1);
			newTask->next = prev->next;
			prev->next = newTask;
		}
	}
	return true;
}

//Pre-condition: input a string containing the output format of the task to be deleted from the linked list and a pointer indicating the index, search for the task in the linked list and obtain the index of the task
//Post-condition: return true if task is found in the linked list and the index pointer will be updated accordingly
int DoneLinkedList::getIndex(Date today){
	ListNode *cur = _head;
	int index=1; 
	Date *date = new Date;
	int *time = new int;
	
	while(cur != NULL){
		obtainDateAndTime(cur->item, date, time);
		if(today._year > date->_year){
			index++;
		}else if(today._year < date->_year){
			return index;
		}else if(today._month > date->_month){
			index++;
		}else if(today._month < date->_month){
			return index;
		}else if(today._day > date->_day){
			index++;
		}else if(today._day < date->_day){
			return index;
		}else{
			return index;
		}
		cur = cur->next;
	}

	delete cur;
	cur = NULL;
	delete date;
	date = NULL;
	delete time;
	time = NULL;

	return index;
}

void DoneLinkedList::remove(int index){
	ListNode *cur;
	--_size;

	if (index == 1){
		cur = _head;
		_head = _head->next;
	} 
	else{
		ListNode *prev = traverseTo(index-1);
		cur = prev->next;
		prev->next = cur->next;
	}
	delete cur;
	cur = NULL;
}

//pre-condition: input a Date today that stores day, month and year individully as integers and update the linked list such that tasks before this date are all removed
//post-condition: linked list do not contain any overdued done items
void DoneLinkedList::update(Date today){
	int index = getIndex(today);

	for(int i=1; i<index; i++){
		remove(i);
	}
}