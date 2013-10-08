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

//Check whether the task has a starting date and time or due date and time and return the respective one
void TaskLinkedList::getTimeAndDate(Task & task, int *day, int *month, int *year, int *time){
	/*if (task.getStartingDate() != NULL){
		convertDate(task.getStartingDate(), day, month, year);
		*time = task.getStartingTime();
	}
	else{
		convertDate(task.getDeadlineDate(), day, month, year);
		*time = task.getDeadlineTime();
	}
	return;*/
	return;
}

//Returns the index at which a Task is to be added
int TaskLinkedList::getAddingIndex(const Task & curTask){
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

//Returns true if task is added to linked list
bool TaskLinkedList::insert(const Task & curTask){
	int newSize = getSize() + 1;
	int index = getAddingIndex(curTask);

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

