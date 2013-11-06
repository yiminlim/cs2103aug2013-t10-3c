#include "OverdueLinkedList.h"

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

void OverdueLinkedList::insert(Task & curTask){
	_size = getSize() + 1;
	int index = getSize();

	ListNode *newTask = new ListNode;
	newTask->item = curTask;
	newTask->next = NULL;

	ListNode *prev = traverseTo(index-1);
	newTask->next = prev->next;
	prev->next = newTask;
}

void OverdueLinkedList::remove(){
	ListNode *cur;
	--_size;

	cur = _head;
	_head = _head->next;
 
	delete cur;
	cur = NULL;
}

void OverdueLinkedList::clear(){
	while (!isEmpty()){
		remove();
	}
}
	
void OverdueLinkedList::updateStorageVector(std::vector<std::string> & tbOverdueVector){
	ListNode *cur = _head;

	while (cur != NULL){
		tbOverdueVector.push_back(cur->item.getTask());
		cur = cur->next;
	}
}