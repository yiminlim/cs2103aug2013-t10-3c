//@ author A0103481R
#include "OverdueLinkedList.h"
#include <assert.h>

const std::string OverdueLinkedList::KEYWORD_EMPTY_STRING = "";

OverdueLinkedList::OverdueLinkedList(){
	_head = NULL;
	_size = 0;
}
	
//Destructor for linked list
OverdueLinkedList::~OverdueLinkedList(){
}

//Pre-condition: Input an index between the range of 1 and the size of the linked list (including).
//Post-condition: Return a ListNode pointer that will traverse to the position given by the index.
OverdueLinkedList::ListNode* OverdueLinkedList::traverseTo(int index){
	if ( (index < 1) || (index > getSize()) ){
		return NULL;
	}else{
		ListNode *cur = _head;
		for (int skip = 1; skip < index; skip++){
			cur = cur->next;
		}
		return cur;
	}
}

//Pre-condition: Check if linked list is empty.
//Post-condition: Return true if the linked list is empty.
bool OverdueLinkedList::isEmpty(){
	return _size == 0;
}
	
//Pre-condition: Check for the size of the linked list.
//Post-condition: Return the number of tasks in the linked list.
int OverdueLinkedList::getSize(){
	return _size;
}

//Pre-condition: Input a Date input and an empty Date date and copy the input into the date.
//Post-condition: The date now contains the same values as the input.
void OverdueLinkedList::obtainDateSeparately(Date *inputDate, Date *date){
	date->_day = inputDate->_day;
	date->_month = inputDate->_month;
	date->_year = inputDate->_year;
}

//Pre-condition: Input in a Task reference and fours pointers indicating date and time and ending date and time.
//				 For empty time, it is declared with a value -1.
//				 For empty Date, it is declared as 0.
//Post-condition: The pointer indicating date and time will be updated to store either the startingDate and startingTime or the deadlineDate and deadlineTime of the respective Task. 
//				  The pointer indicating endDate and endTime will be updated to store the endingDate and endingDate if it has one. Else, store them as 0 and -1.
void OverdueLinkedList::obtainDateAndTime(Task & task, Date *date, int *time, Date *endDate, int *endTime){
	if (task.getDeadlineDate()._day == 0){
		obtainDateSeparately(&task.getStartingDate(), date);
		*time = task.getStartingTime();
		obtainDateSeparately(&task.getEndingDate(), endDate);
		*endTime = task.getEndingTime();
	}else{
		obtainDateSeparately(&task.getDeadlineDate(), date);
		*time = task.getDeadlineTime();
		*endTime = -1;
	}
	return;
}

//Pre-condition: Input 2 dates and a bool check to compare the 2 dates. If both dates are the same, return check as true.
//Post-condition: Return true if the curDate is earlier than the listDate. If there is no difference, the bool check is updated as true and it returns false.
bool OverdueLinkedList::compareDates(Date *curDate, Date *listDate, bool *check){
		if (curDate->_year < listDate->_year){
			return true;
		} else if (curDate->_year > listDate->_year){
			return false;
		} else if (curDate->_month < listDate->_month){
			return true;
		} else if (curDate->_month > listDate->_month){
			return false;
		} else if (curDate->_day < listDate->_day){
			return true;
		} else if (curDate->_day > listDate->_day){
			return false;
		}else{
			*check = true;
			return false;
		}
}

//Pre-condition: Input the Task reference to be added and a specific Task reference from the linked list and sort them accordingly.
//Post-condition: Return true if the Task reference to be added is of an earlier date and time than the specific Task reference from the linked list.
bool OverdueLinkedList::compareDateAndTime(Task & curTask, Task & listTask){
		Date *curDate = new Date;
		Date *listDate = new Date;
		Date *endListDate = new Date;
		Date *endCurDate = new Date;
		int *curTime = new int, *listTime = new int, *endCurTime = new int, *endListTime = new int;
		bool condition = false, check=false;
		obtainDateAndTime(curTask, curDate, curTime, endCurDate, endCurTime);
		obtainDateAndTime(listTask, listDate, listTime, endListDate, endListTime);

		condition = compareDates(curDate, listDate, &check);
		if (check){
			if (*curTime < *listTime){
				condition = true;
			}else if (*curTime == *listTime){
				if (*curTime == -1){
					condition = true;
				}else{
					check = false;
					condition = compareDates(endCurDate, endListDate, &check);
					if (check){
						if (*endCurTime < *endListTime){
							condition = true;
						}else{
							condition = false;
						}
					}
				}
			}else if(*curTime > *listTime){
				condition = false;
				}
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

//Pre-condition: Input a Task reference to check for the index which it should be inserted into the linked list, in a sorted manner.
//Post-condition: Return the index where the Task is supposed to be added at.
int OverdueLinkedList::getInsertIndex(Task & curTask){
	ListNode *cur = _head;
	int i = 1;

	if (isEmpty()){
		return i;
	}

	while (cur != NULL){
		if (compareDateAndTime(curTask, cur->item)){
			return i;
		}else{
			cur = cur->next;
			i++;
		}
	} 

	return i;
}

//Pre-condition: Input a Task reference to be added into the linked list. 
//Post-condition: Return true if the task is added into the linked list in an sorted manner.
bool OverdueLinkedList::insert(Task & curTask){
	assert (curTask.getTask() != KEYWORD_EMPTY_STRING);
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
		}else{
			ListNode *prev = traverseTo(index-1);
			newTask->next = prev->next;
			prev->next = newTask;
		}
	}
	return true;
}

//Pre-condition: Call this function to remove the first item in the linked list.
//Post-condition: Head of the linked list is removed.
void OverdueLinkedList::remove(){
	ListNode *cur;
	--_size;

	cur = _head;
	_head = _head->next;
 
	delete cur;
	cur = NULL;
}

//Pre-condition: Call this function to clear the entire linked list.
//Post-condition: Entire linked list is removed.
void OverdueLinkedList::clear(){
	while (!isEmpty()){
		remove();
	}
}

//Pre-condition: Input an empty vector to retrieve alll the items in the linked list.
//Post-condition: Return a vector containing all the items in the linked list.
void OverdueLinkedList::updateStorageVector(std::vector<std::string> & tbOverdueVector){
	assert (tbOverdueVector.empty());
	ListNode *cur = _head;

	while (cur != NULL){
		tbOverdueVector.push_back(cur->item.getTask());
		cur = cur->next;
	}
}