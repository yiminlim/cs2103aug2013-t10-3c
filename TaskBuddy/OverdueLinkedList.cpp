#include "OverdueLinkedList.h"
#include <assert.h>

OverdueLinkedList::OverdueLinkedList(){
	_head = NULL;
	_size = 0;
}
	
//destructor for linked list
OverdueLinkedList::~OverdueLinkedList(){
}

//Pre-condition: input an index between the range of 1 and the size of the linked list (including)
//Post-condition: returns a ListNode pointer that will traverse to the position given by the index
OverdueLinkedList::ListNode* OverdueLinkedList::traverseTo(int index){
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
bool OverdueLinkedList::isEmpty(){
	return _size==0;
}
	
//Pre-condition: check for the size of the linked list
//Post-condition: return the number of tasks in the linked list
int OverdueLinkedList::getSize(){
	return _size;
}

//Pre-condition: read in a task and insert it to the back of the linked list
//Post-condition: insert the new task to the back of the linked list
void OverdueLinkedList::insert(Task & curTask){
	assert (curTask.getTask() != "");
	_size = getSize() + 1;
	int index = getSize();

	ListNode *newTask = new ListNode;
	newTask->item = curTask;
	newTask->next = NULL;

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

//Pre-condition: call this function to remove the first item in the linked list
//Post-condition: head of the linked list is removed
void OverdueLinkedList::remove(){
	ListNode *cur;
	--_size;

	cur = _head;
	_head = _head->next;
 
	delete cur;
	cur = NULL;
}

//Pre-condition: call this function to clear the entire linked list
//Post-condition: entire linked list is removed
void OverdueLinkedList::clear(){
	while (!isEmpty()){
		remove();
	}
}

//Pre-condition: input an empty vector to retrieve alll the items in the linked list
//Post-condition: returns a vector containing all the items in the linked list
void OverdueLinkedList::updateStorageVector(std::vector<std::string> & tbOverdueVector){
	assert (tbOverdueVector.empty());
	ListNode *cur = _head;

	while (cur != NULL){
		tbOverdueVector.push_back(cur->item.getTask());
		cur = cur->next;
	}
}