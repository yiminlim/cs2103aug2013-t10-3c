#include "TaskLinkedList.h"

TaskLinkedList::TaskLinkedList(){
	_head = NULL;
	_size = 0;
}
	
//destructor for linked list
TaskLinkedList::~TaskLinkedList(){
	while (!isEmpty()){
		remove(1);
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

//Convert the date from a string to int
void TaskLinkedList::convertDate(const std::string date, int *day, int *month, int *year){
	*day = (date[0]-'0')*10 + (date[1]-'0');
	*month = (date[3]-'0')*10 + (date[4]-'0');
	*year = (date[6]-'0')*10 + (date[7]-'0');
	return;
}

//Check whether the task has a starting date and time or due date and time and return the respective one
void TaskLinkedList::getTimeAndDate(Task & task, int *day, int *month, int *year, int *time){
	if (task.getStartingDate() != "NULL"){
		convertDate(task.getStartingDate(), day, month, year);
		*time = task.getStartingTime();
	}
	else{
		convertDate(task.getDeadlineDate(), day, month, year);
		*time = task.getDeadlineTime();
	}
	return;
}

//Returns the index at which a Task is to be added
int TaskLinkedList::getAddingIndex(Task & curTask){
	ListNode *cur = _head;
	int i=1, *day, *month, *year, *time;
	int *listDay, *listMonth, *listYear, *listTime;
	getTimeAndDate(curTask, day, month, year, time);

	do{
		getTimeAndDate(cur->item, listDay, listMonth, listYear, listTime);
		if (*year < *listYear){
			return i;
		} else if (*month < *listMonth){
			return i;
		} else if (*day < *listDay){
			return i;
		} else if (*time < *listTime){
			return i;
		} else {
			cur = cur->next;
		}
		i++;
	} while (cur != _head);

	return i;
}

//initialisation by inserting all task into program at the start
void TaskLinkedList::initialInsert(const Task &){
	
}
	
//sort tasks in list according to date and time
void TaskLinkedList::mergeSort(int, int){
}
	
//Returns true if task is added to linked list
bool TaskLinkedList::insert(const Task &){
	return true;
}
	
//Returns true if task is remove from linked list
bool TaskLinkedList::remove(int){
	return true;
}
	
//Returns the task in the linked list as given by the index
Task TaskLinkedList::retrieve(int){
	Task temp;
	return temp;
}
	
//Returns true if task is edited successfully in linked list
bool TaskLinkedList::edit(int, Task){
	return true;
}

