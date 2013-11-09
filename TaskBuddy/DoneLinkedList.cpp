#include "DoneLinkedList.h"
#include <assert.h>

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
//				 for empty Date, it is declared with 0
//				 for empty time, it is declared with a value -1
//Post-condition: the pointer indicating date and time will be updated to store either the startingDate and startingTime or the deadlineDate and deadlineTime of the respective Task. 
void DoneLinkedList::obtainDateAndTime(Task & task, Date *date, int *time, Date *endDate, int *endTime){
	if (task.getDeadlineDate()._day == 0){
		date->_day = task.getStartingDate()._day;
		date->_month = task.getStartingDate()._month;
		date->_year = task.getStartingDate()._year;
		*time = task.getStartingTime();
		if (task.getEndingDate()._day != 0){
			endDate->_day = task.getEndingDate()._day;
			endDate->_month = task.getEndingDate()._month;
			endDate->_year = task.getEndingDate()._year;
			*endTime = task.getEndingTime();
		}
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
		Date *endListDate = new Date;
		Date *endCurDate = new Date;
		int *curTime = new int, *listTime = new int, *endCurTime = new int, *endListTime = new int;
		bool condition = false;
		obtainDateAndTime(curTask, curDate, curTime, endCurDate, endCurTime);
		obtainDateAndTime(listTask, listDate, listTime, endListDate, endListTime);

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
		else if (*curTime = *listTime){
			if (endCurDate-> _year < endListDate->_year){
				condition = true;
			}else if(endCurDate->_year > endListDate->_year){
				condition = false;
			}else if(endCurDate->_month < endListDate->_month){
				condition = true;
			}else if(endCurDate->_month > endListDate->_month){
				condition = false;
			}else if(endCurDate->_day < endListDate->_day){
				condition = true;
			}else if(endCurDate->_day > endListDate->_day){
				condition = false;
			}else if(*endCurTime < *endListTime){
				condition = true;
			}else{
				condition = false;
			}
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
		delete endCurDate;
		endCurDate = NULL;
		delete endListDate;
		endListDate = NULL;
		delete endCurTime;
		endCurTime = NULL;
		delete endListTime;
		endListTime = NULL;

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
	assert (curTask.getTask() != "");
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

void DoneLinkedList::obtainDateAndTimeForRemoving(Task & task, Date *date, int *time){
	if(task.getDeadlineDate()._day != 0){
		date->_day = task.getDeadlineDate()._day;
		date->_month = task.getDeadlineDate()._month;
		date->_year = task.getDeadlineDate()._year;
		*time = task.getDeadlineTime();
	} else if(task.getStartingDate()._day != 0 && task.getEndingDate()._day==0){
		date->_day = task.getStartingDate()._day;
		date->_month = task.getStartingDate()._month;
		date->_year = task.getStartingDate()._year;
		*time = task.getStartingTime();
	} else if(task.getStartingDate()._day != 0 && task.getEndingDate()._day!=0){
		date->_day = task.getEndingDate()._day;
		date->_month = task.getEndingDate()._month;
		date->_year = task.getEndingDate()._year;
		*time = task.getEndingTime();
	}
	return;
}

//Pre-condition: input a date today and compare to get the index pointing to the first task that is not overdued
//				 does not take into consideration to
//Post-condition: return an index pointing to the first task that is not overdued
std::vector<int> DoneLinkedList::getIndex(Date today){
	ListNode *cur = _head;
	std::vector <int> index; 
	int i = 1;
	Date *date = new Date;
	int *time = new int;
	
	while(cur != NULL){
		obtainDateAndTimeForRemoving(cur->item, date, time);
		if(today._year > date->_year){
			index.push_back(i);
		}else if(today._year < date->_year){
		}else if(today._month > date->_month){
			index.push_back(i);
		}else if(today._month < date->_month){
		}else if(today._day > date->_day){
			index.push_back(i);
		}else if(today._day < date->_day){
		}else{
		}
		cur = cur->next;
		i++;
	}

	delete cur;
	cur = NULL;
	delete date;
	date = NULL;
	delete time;
	time = NULL;

	return index;
}

//pre-condition: input an index and remove the task from the linked list which the index points to
//post-condition: task pointed by the index is deleted
void DoneLinkedList::remove(int index){
	assert (index > 0 && index < getSize()+1);
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

bool DoneLinkedList::removeTask(std::string task){
	ListNode *cur = _head;
	int index = 1;
	
	while (cur != NULL){
		if (task == cur->item.getTask()){
			remove(index);
			return true;
		}
		else{
			cur = cur->next;
			index++;
		}
	}
	return false;
}

//pre-condition: input a Date today that stores day, month and year individully as integers and update the linked list such that tasks before this date are all removed
//post-condition: linked list do not contain any overdued done items in terms of date wise (not timewise)
void DoneLinkedList::update(Date today){
	assert (today._day != 0 && today._month != 0 && today._year != 0);
	std::vector <int> index = getIndex(today);

	for(int i=index.size(); i>0; i--){
		remove(index[i-1]);
	}
}

//pre-condition: input an empty vector and copy all the output format of the tasks in the linked list into this vector
//post-condition: the entire output format of the tasks in the linked list is copied over into the vector
void DoneLinkedList::updateStorageVector(std::vector<std::string> & tbDoneVector){
	assert (tbDoneVector.empty());
	ListNode *cur = _head;

	while (cur != NULL){
		tbDoneVector.push_back(cur->item.getTask());
		cur = cur->next;
	}
}