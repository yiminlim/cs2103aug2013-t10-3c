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
void TaskLinkedList::convertDate(std::string date, int *day, int *month, int *year){

}

//Returns the index at which a Task is to be added
int TaskLinkedList::getAddingIndex(const Task & curTask){
	ListNode *cur = _head;
	int i=1;

	if (curTask.getStartingDate != NULL){
		std::string date = curTask.getStartingDate;
		int time = curTask.getStartingTime;
	}
	else{
		std::string date = curTask.getDeadlineDate;
		int time = curTask.getDeadlineTime;
	}

	do{

	
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

