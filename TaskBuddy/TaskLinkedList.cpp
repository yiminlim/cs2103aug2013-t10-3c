#include "TaskLinkedList.h"

TaskLinkedList::TaskLinkedList(){
	_head = NULL;
	_size = 0;
}
	
//destructor for linked list
TaskLinkedList::~TaskLinkedList(){
}

//Pre-condition: input an index between the range of 1 and the size of the linked list (including)
//Post-condition: returns a ListNode pointer that will traverse to the position given by the index
TaskLinkedList::ListNode* TaskLinkedList::traverseTo(int index){
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
bool TaskLinkedList::isEmpty(){
	return _size==0;
}
	
//Pre-condition: check for the size of the linked list
//Post-condition: return the number of tasks in the linked list
int TaskLinkedList::getSize(){
	return _size;
}

//Pre-condition: input in a Task reference and two pointers indicating date and time 
//				 the task have to have either a startingDate and startingTime or a deadlineDate and deadlineTime
//				 for empty time, it is declared with a value -1
//Post-condition: the pointer indicating date and time will be updated to store either the startingDate and startingTime or the deadlineDate and deadlineTime of the respective Task. 
void TaskLinkedList::obtainDateAndTime(Task & task, Date *date, int *time, int *endTime){
	if (task.getDeadlineTime() == -1){
		date->_day = task.getStartingDate()._day;
		date->_month = task.getStartingDate()._month;
		date->_year = task.getStartingDate()._year;
		*time = task.getStartingTime();
		*endTime = task.getEndingTime();
	}
	else{
		date->_day = task.getDeadlineDate()._day;
		date->_month = task.getDeadlineDate()._month;
		date->_year = task.getDeadlineDate()._year;
		*time = task.getDeadlineTime();
		*endTime = -1;
	}
	return;
}

//Pre-condition: input the Task reference to be added and a specific Task reference from the linked list and sort them accordingly. Check along the way if there are any clashes
//Post-condition: returns true if the Task reference to be added is of an earlier date and time than the specific Task reference from the linked list. Update isClash accordingly
bool TaskLinkedList::compareDateAndTime(Task & curTask, Task & listTask, bool & isClash){
		Date *curDate = new Date;
		Date *listDate = new Date;
		int *curTime = new int, *listTime = new int, *endCurTime = new int, *endListTime = new int;
		bool condition = false;
		obtainDateAndTime(curTask, curDate, curTime, endCurTime);
		obtainDateAndTime(listTask, listDate, listTime, endListTime);

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
			if (*endListTime == -1 || (*endListTime != -1 && *endCurTime != -1)){ //both from to
				if (*endCurTime > *listTime){
					isClash = true; //cur is from to, list is from
				}
			}
		}
		else if (*curTime == *listTime){
			isClash = true; //both froms
			condition = false;
		}
		else if (*curTime > *listTime){
			condition = false; 
			if (*endCurTime == -1 ){
				if (*endListTime > *curTime || (*endListTime != -1 && *endCurTime != -1)){ //both from to
					isClash = true; //cur is from, list is from to
				}
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
		delete endCurTime;
		endCurTime = NULL;
		delete endListTime;
		endListTime = NULL;

		return condition;		
}

//Pre-condition: input a Task reference to check for the index which it should be inserted into the linked list, in a sorted manner
//Post-condition: return the index where the Task is supposed to be added at
int TaskLinkedList::getInsertIndex(Task & curTask, bool & isClash){
	ListNode *cur = _head;
	int i = 1;

	if (isEmpty()){
		return i;
	}

	while (cur != NULL){
		if (compareDateAndTime(curTask, cur->item, isClash)){
			return i;
		} 
		else{
			cur = cur->next;
			i++;
		}
	} 

	return i;
}

//Pre-condition: input a Task reference to be added into the linked list, check if any task clashes and update isClash to be true if it does 
//				 isClash has to be false when it is passed over
//Post-condition: return true if the task is added into the linked list in an sorted manner. isClash is updated accordingly
bool TaskLinkedList::insert(Task & curTask, bool & isClash){
	int newSize = getSize() + 1;
	int index = getInsertIndex(curTask, isClash);

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

//Pre-condition: input a string containing the output format of the task to be deleted from the linked list and a pointer indicating the index, search for the task in the linked list and obtain the index of the task
//Post-condition: return true if task is found in the linked list and the index pointer will be updated accordingly
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

//pre-condition: input a line and an empty vector to contain keywords
//post-condition: rsplit the line into individual words and store them in the keywords vector
void TaskLinkedList::splitIntoKeywords(std::string line, std::vector<std::string> & keywords){
	std::stringstream iss;
	std::string keyword;
	iss << line;

	while (iss >> keyword){
		keywords.push_back(keyword);
	}
}

//pre-condition: input a string containing a line of action and location and check if there is only one block off task having this action and location left. If yes, the last block off task will be unblocked
//			     the last task must contain the word "blockoff" in the output format
//post-condition: checks if there is only one task left in that specific block and unblock it if it is true
void TaskLinkedList::checkIfRemainingBlockTask(std::string line){
	std::vector<std::string> keywords;
	std::vector<std::string> taskList;
	int *index = new int;
	*index = 1;
	ListNode *cur = _head;
	splitIntoKeywords(line, keywords);
	keywords.push_back("blockoff");

	if(retrieve(keywords, taskList)){
		if(taskList.size() == 1){
			if(getRemoveIndex(taskList[0], index)){
				cur = traverseTo(*index);
				cur->item.setBlock(false);
			}
		}
	}

	delete index;
//	delete cur;
//	cur = NULL;
	index = NULL;
}

//Pre-condition: input a string containing the output format of the task to be deleted from the linked list and a line containing the action and location to cater in the fact that if there's only one task block remaining, it will be unblocked
//Post-condition: return true if the task is found and deleted from the linked list, if task comes from a block, the last block will be unblocked.
bool TaskLinkedList::remove(std::string task, std::string line){
	int *index = new int;
	*index = 1;
	bool condition = false;
	if (getRemoveIndex(task,index)){
		ListNode *cur;
		--_size;

		if (*index == 1){
			cur = _head;
			_head = _head->next;
		} 
		else{
			ListNode *prev = traverseTo(*index-1);
			cur = prev->next;
			prev->next = cur->next;
		}
		delete cur;
		cur = NULL;
		condition = true;
	}

	checkIfRemainingBlockTask(line);
	
	delete index;
	index = NULL;
	return condition;
}

//Pre-condition: input a string of words/word and convert it to lower case
//Post-condition: return the same string but converted to lower case
std::string TaskLinkedList::toLowerCase(std::string line){
	for (unsigned int i = 0; line[i] != '\0'; i++){
		line[i] = tolower(line[i]);
	}
	return line;
}

//pre-condition:input day, month and year in int and convert them into a string in this format dd/mm/yy
//				assume that the day and month are greater than 0. While year are at least 4 digits (the first digit is not 0)
//post-condtion: return a string date form from individual int day, month, year
std::string TaskLinkedList::getStringDate(int day, int month, int year){
	std::ostringstream output;
	output << day << "/" << month << "/" << year; 
	return output.str();
}

//pre-condition: input a tempTask and the starting and ending dates and push in the dates that are within the range of the starting and ending dates
//				 consider the maximum number of days to be 31 for all cases
//post-condition: return a tempTask with the range of dates added at the back
std::string TaskLinkedList::compareAndIncludeRange(std::string tempTask, int *startDay, int *startMonth, int *startYear, int *endDay, int *endMonth, int *endYear){
	int i, j, k;

	if (*startYear != *endYear){
		for(i=*startYear; i<*endYear; i++){
			for(j=1; j<=12; j++){
				if(i == *startYear && j==1){
					j=*startMonth;
				}
				for(k=1; k<=31; k++){
					if(j == *startMonth && k==1){
						k=*startDay;
					}
					tempTask = tempTask + getStringDate(k,j,i);
				}
			}
		}
		if (i == *endYear){
			for (j=1; j<=*endMonth; j++){
				for(k=1; k<=*endDay; k++){
					tempTask = tempTask + getStringDate(k,j,i);
				}
			}
		}
	}

	else if (*startMonth != *endMonth){
		i = *startYear;
		for(j=*startMonth; j<*endMonth; j++){
			for(k=1; k<=31; k++){
				if(j == *startMonth && k==1){
					k = *startDay;
				}
				tempTask = tempTask + getStringDate(k, j, i);
			}
		}
		if (j == *endMonth){
			for(k=1; k<=*endDay; k++){
				tempTask = tempTask + getStringDate(k,j,i);
			}
		}
	}

	else if (*startDay != *endDay){
		i = *startYear;
		j = *startMonth;
		for(k=*startDay; k<=*endDay; k++){
			tempTask = tempTask + getStringDate(k,j,i);
		}
	}

	return tempTask;
}

//precondition: input a string date and convert into individual day, month and year as integers
//				string must be in the format dd/mm/yyyy
//postcondition: pointers are updated (day, month, year as int)
void TaskLinkedList::getIntDate(std::string date, int *day, int *month, int *year){
	size_t posFirstDateSeparator = date.find("/");
	size_t posSecondDateSeparator = date.find("/", posFirstDateSeparator+1);
	
	std::string sDay = date.substr(0,posFirstDateSeparator-0);
	std::string sMonth = date.substr(posFirstDateSeparator+1, posSecondDateSeparator-posFirstDateSeparator-1);
	std::string sYear = date.substr(posSecondDateSeparator+1);

	std::istringstream ss1(sDay);
	ss1 >> *day;
	std::istringstream ss2(sMonth);
	ss2 >> *month;
	std::istringstream ss3(sYear);
	ss3 >> *year;
}

//only check for range of dates entered in proper date format dd/mm/yyyy (note that the first digit day and month entered cannot have 0) 
std::string TaskLinkedList::includeRangeOfDates(std::string tempTask){
	if((tempTask).find("-") != std::string::npos){
		std::vector<std::string> words;
		splitIntoKeywords(tempTask, words);
		int i = 0;

		int *startDay = new int, *startMonth = new int, *startYear = new int, *endDay = new int, *endMonth = new int, *endYear = new int;
		getIntDate(words[i], startDay, startMonth, startYear);

		while (words[i] != "-"){
			i++;
		}
		getIntDate(words[i+1], endDay, endMonth, endYear);

		tempTask = compareAndIncludeRange(tempTask, startDay, startMonth, startYear, endDay, endMonth, endYear);
	
		delete startDay;
		startDay = NULL;
		delete startMonth;
		startMonth = NULL;	
		delete startYear;
		startYear = NULL;
		delete endDay;
		endDay = NULL;
		delete endMonth;
		endMonth = NULL;
		delete endYear;
		endYear = NULL;
	}

	return tempTask;
}
	
//Pre-condition: input a vector of individual keywords and an empty vector of taskList to store the task that are found from the linked list which contains all of the keywords 
//				 check for the range in dates for from to as well
//				 will only take into consideration range in dates if the user inputs the date in the right format or uses words like today, tmr,.. (dd/mm/yyyy)
//Post-condition: return true if at least 1 task is found to contain all of the keywords from the vector and updates the taskList vector accordingly
bool TaskLinkedList::retrieve(const std::vector<std::string> keywords, std::vector<std::string> & taskList){
	ListNode *cur = _head;

	while (cur != NULL){
		int count = 0;
		for (unsigned int i = 0; i < keywords.size(); i++){
			std::string tempTask = toLowerCase(cur->item.getTask());
			tempTask = includeRangeOfDates(tempTask);
			std::string tempKeyword = toLowerCase(keywords[i]);
			if ((tempTask).find(tempKeyword) != std::string::npos){
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
	} 
	else{
		return true;
	}
}


//Pre-condition: input a vector of strings to be deleted from the linked list and deltes them from the linked list using the remove function
//Post-condition: returns true when all the strings to be deleted are deleted from the linked list
/*bool TaskLinkedList::removeBlockings(const std::vector<std::string> taskToBeDeleted){
	bool isRemoved = true;

	for(unsigned int i=0; i<taskToBeDeleted.size(); i++){
		if (!remove(taskToBeDeleted[i])){
			isRemoved = false;
		}
	}

	return isRemoved;
}

//Pre-condition: input a vector of tasks to be finalised in the blocking. The function will search through the linked list and remove the other blockings that are unwanted
//Post-condition: return true if the blockings are successfully finalised. Meaning that the other unwanted blockings are removed. 
bool TaskLinkedList::finaliseBlocking(const std::vector<std::string> tasks){
	ListNode *cur = _head;
	std::vector<std::string> taskToBeDeleted;

	while (cur != NULL){
		bool finBlocks = false;

		if (cur->item.getBlock()){
			for(unsigned int i=0; i<tasks.size(); i++){
				if (cur->item.getTask() == tasks[i]){
					finBlocks = true;
				}
			}
		}

		if (finBlocks == false){
			taskToBeDeleted.push_back(cur->item.getTask());
		}
		
		cur = cur->next;
	}

	if(removeBlockings(taskToBeDeleted)){
		return true;
	} else{
		return false;
	}
}	
*/

//pre-condition: input an empty vector and copy all the output format of the tasks in the linked list into this vector
//post-condition: the entire output format of the tasks in the linked list is copied over into the vector
void TaskLinkedList::updateStorageVector(std::vector<std::string> & tbVector){
	ListNode *cur = _head;

	while (cur != NULL){
		tbVector.push_back(cur->item.getTask());
		cur = cur->next;
	}
}

//Pre-condition: input a string task to be located and change it's bool block as true
//				 the task must be found in the linked list to successfully change the block to true
//Post-condition: the task passed in is set as true for it's bool block
void TaskLinkedList::setBlock(std::string task){
	ListNode *cur = _head;

	while(cur != NULL){
		if (cur->item.getTask() == task){ 
			cur->item.setBlock(true);
			return;
		}
		else{
			cur = cur->next;
		}
	}
}