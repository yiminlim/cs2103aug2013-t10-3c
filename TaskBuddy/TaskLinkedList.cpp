#include "TaskLinkedList.h"

TaskLinkedList::TaskLinkedList(){
	_head = NULL;
	_size = 0;
}
	
//destructor for linked list
TaskLinkedList::~TaskLinkedList(){
	while (!isEmpty()){
		remove("1");
	}
}

//Returns a ListNode pointer that will traverse to the position given by the index
TaskLinkedList::ListNode* TaskLinkedList::traverseTo(int index){
	if ( (index < 1) || (index > getSize()) ){
		return NULL;
	}

	else{
		ListNode *cur = _head;
		for (int skip=1; skip<index; skip++){
			cur = cur->next;
		}
		return cur;
	}
}
	
//Returns true if the linked list is empty
bool TaskLinkedList::isEmpty(){
	return _size==0;
}
	
//Returns number of tasks in linked list
int TaskLinkedList::getSize(){
	return _size;
}

//determine if the task has a starting date and time or deadline date and time and pass back the one with the value
void TaskLinkedList::obtainDateAndTime(Task & task, Date *date, int *time){
	if (task.getDeadlineDate().day == NULL){
		date->day = task.getStartingDate().day;
		date->month = task.getStartingDate().month;
		date->year = task.getStartingDate().year;
		*time = task.getStartingTime();
	}

	else{
		date->day = task.getDeadlineDate().day;
		date->month = task.getDeadlineDate().month;
		date->year = task.getDeadlineDate().year;
		*time = task.getDeadlineTime();
	}
	return;
}

//Returns true if the curTask is of an earlier date and time than listTask
bool TaskLinkedList::compareDateAndTime(Task & curTask, Task & listTask){
		Date *curDate = new Date;
		Date *listDate = new Date;
		int *curTime, *listTime;
		obtainDateAndTime(curTask, curDate, curTime);
		obtainDateAndTime(listTask, listDate, listTime);

		if (curDate->year < listDate->year){
			return true;
		} else if(curDate->month < listDate->month){
			return true;
		} else if(curDate->day < listDate->day){
			return true;
		} else if(curTime < listTime){
			return true;
		} else{
			return false;
		}
}

//Returns the index at which a Task is to be added
int TaskLinkedList::getInsertIndex(Task & curTask){
	ListNode *cur = _head;
	int i = 1;

	if (isEmpty()){
		return i;
	}

	do{
		if (compareDateAndTime(curTask, cur->item)){
			return i;
		} else{
			cur = cur->next;
			i++;
		}
	} while (cur != _head);

	return i;
}

//Returns true if task is added to linked list
bool TaskLinkedList::insert(Task & curTask){
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
		} else{
			ListNode *prev = traverseTo(index-1);
			newTask->next = prev->next;
			prev->next = newTask;
		}
	}
	return true;
}
	
//Returns true if task is remove from linked list
bool TaskLinkedList::remove(std::string){
	return true;
}
	
//Returns the task in the linked list as given by the index
bool TaskLinkedList::retrieve(const std::vector<std::string>, std::vector<std::string> &){
	return true;
}
	
//Returns true if task is edited successfully in linked list
bool TaskLinkedList::edit(int, Task){
	return true;
}

