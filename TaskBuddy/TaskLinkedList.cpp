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
	if (task.getDeadlineDate()._day == 0){
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

//Returns true if the curTask is of an earlier date and time than listTask
bool TaskLinkedList::compareDateAndTime(Task & curTask, Task & listTask){
		Date *curDate = new Date;
		Date *listDate = new Date;
		int *curTime = new int, *listTime = new int;
		bool condition = false;
		obtainDateAndTime(curTask, curDate, curTime);
		obtainDateAndTime(listTask, listDate, listTime);

		if (curDate->_year < listDate->_year){
			condition = true;
		} else if(curDate->_month < listDate->_month){
			condition = true;
		} else if(curDate->_day < listDate->_day){
			condition = true;
		} else if(curTime < listTime){
			condition = true;
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

//Returns the index at which a Task is to be added
int TaskLinkedList::getInsertIndex(Task & curTask){
	ListNode *cur = _head;
	int i = 1;

	if (isEmpty()){
		return i;
	}

	while (cur != NULL){
		if (compareDateAndTime(curTask, cur->item)){
			return i;
		} else{
			cur = cur->next;
			i++;
		}
	} 

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
	
//Returns the index of the task to be removed
//Assume that the index returned have to be within the index range. If there is an error, it will return 0
bool TaskLinkedList::getRemoveIndex(std::string task, int *index){
	ListNode *cur = _head;

	while (cur->item.getTask() != task){
		cur = cur->next;
		(*index)++;
	}
	if (cur != NULL){
		return true;
	}
	return false;
}

//Returns true if task is remove from linked list
bool TaskLinkedList::remove(std::string task){
	int *index = new int;
	*index = 1;
	bool condition = false;
	if (getRemoveIndex(task,index)){
		ListNode *cur;
		--_size;

		if (*index == 1){
			cur = _head;
			_head = _head->next;
		} else{
			ListNode *prev = traverseTo(*index-1);
			cur = prev->next;
			prev->next = cur->next;
		}
		delete cur;
		cur = NULL;
		condition = true;
	}
	delete index;
	index = NULL;
	return condition;
}
	
//Returns the task in the linked list as given by the index
bool TaskLinkedList::retrieve(const std::vector<std::string> keywords, std::vector<std::string> & taskList){
	ListNode *cur = _head;

	while (cur != NULL){
		int count = 0;
		for (unsigned int i=0; i<keywords.size(); i++){
			if ((cur->item.getTask()).find(keywords[i]) != std::string::npos){
				count++;
			}
		}
		if (count == keywords.size()){
			taskList.push_back(cur->item.getTask());
		}
		cur = cur->next;
	}

	if (taskList.empty()){
		return false;
	} else{
		return true;
	}
}
	
//Returns true if task is edited successfully in linked list
std::string TaskLinkedList::edit(std::string taskString,std::string newAction,std::string newLocation,Date newStartingDate,int newStartingTime,Date newEndingDate,int newEndingTime,Date newDeadlineDate,int newDeadlineTime){
	//search for that task, pass everything to that task and the task will change itself and return back the new task string (updated)
	return NULL;
}

