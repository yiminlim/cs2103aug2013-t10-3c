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

//Returns true if the curTask is of an earlier date and time than listTask
bool TaskLinkedList::compareDateAndTime(const Task & curTask, const Task & listTask){

}

//Returns the index at which a Task is to be added
int TaskLinkedList::getInsertIndex(const Task & curTask){
	ListNode *cur = _head;
	int i = 1;

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
bool TaskLinkedList::insert(const Task & curTask){
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

