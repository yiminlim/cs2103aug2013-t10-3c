#include "TaskLinkedList.h"
#include <assert.h>

const std::string OverdueLinkedList::KEYWORD_EMPTY_STRING = "";
const std::string OverdueLinkedList::KEYWORD_BLOCKOFF = "blockoff";
const std::string OverdueLinkedList::KEYWORD_NULL = "/0";
const std::string OverdueLinkedList::KEYWORD_ZERO = "0";
const std::string OverdueLinkedList::KEYWORD_SLASH = "/";
const std::string OverdueLinkedList::KEYWORD_DASH = "-";

const int OverdueLinkedList::KEYNUMBER_DAY = 31;
const int OverdueLinkedList::KEYNUMBER_MONTH = 12;

TaskLinkedList::TaskLinkedList(){
	_head = NULL;
	_size = 0;
}
	
//Destructor for linked list
TaskLinkedList::~TaskLinkedList(){
}

//Pre-condition: Input an index between the range of 1 and the size of the linked list (including).
//Post-condition: Return a ListNode pointer that will traverse to the position given by the index.
TaskLinkedList::ListNode* TaskLinkedList::traverseTo(int index){
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
bool TaskLinkedList::isEmpty(){
	return _size == 0;
}
	
//Pre-condition: Check for the size of the linked list.
//Post-condition: Return the number of tasks in the linked list.
int TaskLinkedList::getSize(){
	return _size;
}

//Pre-condition: Input a Date input and an empty Date date and copy the input into the date.
//Post-condition: The date now contains the same values as the input.
void TaskLinkedList::obtainDateSeparately(Date *inputDate, Date *date){
	date->_day = inputDate->_day;
	date->_month = inputDate->_month;
	date->_year = inputDate->_year;
}

//Pre-condition: Input in a Task reference and fours pointers indicating date and time and ending date and time.
//				 For empty time, it is declared with a value -1.
//				 For empty Date, it is declared as 0.
//Post-condition: The pointer indicating date and time will be updated to store either the startingDate and startingTime or the deadlineDate and deadlineTime of the respective Task. 
//				  The pointer indicating endDate and endTime will be updated to store the endingDate and endingDate if it has one. Else, store them as 0 and -1.
void TaskLinkedList::obtainDateAndTime(Task & task, Date *date, int *time, Date *endDate, int *endTime){
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
bool TaskLinkedList::compareDates(Date *curDate, Date *listDate, bool *check){
		if (curDate->_year < listDate->_year){
			return true;
		}else if (curDate->_year > listDate->_year){
			return false;
		}else if (curDate->_month < listDate->_month){
			return true;
		}else if (curDate->_month > listDate->_month){
			return false;
		}else if (curDate->_day < listDate->_day){
			return true;
		}else if (curDate->_day > listDate->_day){
			return false;
		}else{
			*check = true;
			return false;
		}
}

//Pre-condition: Input the Task reference to be added and a specific Task reference from the linked list and sort them accordingly. Check along the way if there are any clashes.
//Post-condition: Return true if the Task reference to be added is of an earlier date and time than the specific Task reference from the linked list. Update isClash accordingly and return a vector of task that clashes.
bool TaskLinkedList::compareDateAndTime(Task & curTask, Task & listTask, bool & isClash, std::vector<std::string>& clashTasks){
		Date *curDate = new Date;
		Date *listDate = new Date;
		Date *endListDate = new Date;
		Date *endCurDate = new Date;
		int *curTime = new int, *listTime = new int, *endCurTime = new int, *endListTime = new int;
		bool condition = false, check = false;
		obtainDateAndTime(curTask, curDate, curTime, endCurDate, endCurTime);
		obtainDateAndTime(listTask, listDate, listTime, endListDate, endListTime);

		condition = compareDates(curDate, listDate, &check);
		if (check){
			if (*curTime < *listTime){
				condition = true;
				if ( (*endListTime == -1 && *endCurTime != -1 && curDate->_day != 0 && listDate->_day != 0) || (*endListTime != -1 && *endCurTime != -1 && curDate->_day != 0 && listDate->_day != 0) ){ //both from to
					if (*endCurTime > *listTime){
						isClash = true; //cur is from to, list is from
						clashTasks.push_back(listTask.getTask());
					}
				}
			}else if (*curTime == *listTime && *curTime != -1){
				isClash = true; //both froms
				clashTasks.push_back(listTask.getTask());
				
				check = false;
				condition = compareDates(endCurDate, endListDate, &check);
				if (check){
					if (*endCurTime < *endListTime){
						condition = true;
					}else{
						condition = false;
					}
				}
			}else if (*curTime > *listTime){
				condition = false; 
				if ( (*endCurTime == -1 && *endListTime != -1 && curDate->_day != 0 && listDate->_day != 0) || (*endListTime != -1 && *endCurTime != -1 && curDate->_day != 0 && listDate->_day != 0) ){ //both from to
					if (*endListTime > *curTime){
						isClash = true; //cur is from, list is from to
						clashTasks.push_back(listTask.getTask());
					}	
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
		delete endCurDate;
		endCurDate = NULL;
		delete endListDate;
		endListDate = NULL;

		return condition;		
}

//Pre-condition: Input a Task reference to check for the index which it should be inserted into the linked list, in a sorted manner. Also, check for clashes throughout the linked list.
//Post-condition: Return the index where the Task is supposed to be added at. Update isClash accordingly and return a vector of task that clashes.
int TaskLinkedList::getInsertIndex(Task & curTask, bool & isClash, std::vector<std::string>& clashTasks){
	ListNode *cur = _head;
	int i = 1;
	bool dummy;

	if (isEmpty()){
		return i;
	}

	while (cur != NULL){
		if (compareDateAndTime(curTask, cur->item, isClash, clashTasks)){
			if (isClash){
				cur = cur->next;
				while (cur != NULL){
					dummy = compareDateAndTime(curTask, cur->item, isClash, clashTasks);
					cur = cur->next;
				}
				return i;
			}else{
				return i;
			}
		}else{
			cur = cur->next;
			i++;
		}
	} 
	return i;
}

//Pre-condition: Input a Task reference to be added into the linked list, check if any task clashes and update isClash to be true if it does and return the vector of tasks that clash.
//				 isClash has to be false when it is passed over.
//				 clashTasks must be empty.
//Post-condition: Return true if the task is added into the linked list in a sorted manner. isClash and clashTasks are updated accordingly.
bool TaskLinkedList::insert(Task & curTask, bool & isClash, std::vector<std::string>& clashTasks){
	assert(curTask.getTask() != KEYWORD_EMPTY_STRING);
	assert(!isClash);
	int newSize = getSize() + 1;
	int index = getInsertIndex(curTask, isClash, clashTasks);

	if ( (index < 1) || (index > newSize) ){
		return false;
	}else{
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

//Pre-condition: Input a string containing the output format of the task to be deleted from the linked list and a pointer indicating the index, search for the task in the linked list and obtain the index of the task.
//Post-condition: Return true if task is found in the linked list and the index pointer will be updated accordingly.
bool TaskLinkedList::getRemoveIndex(std::string task, int *index){
	ListNode *cur = _head;

	while (cur->item.getTask() != task && cur != NULL){
		cur = cur->next;
		(*index)++;
	}

	if (cur != NULL){
		return true; 
	}

	return false;
}

//Pre-condition: Input a line and an empty vector to contain keywords.
//Post-condition: Split the line into individual words and store them in the keywords vector.
void TaskLinkedList::splitIntoKeywords(std::string line, std::vector<std::string> & keywords){
	assert(keywords.empty());
	std::stringstream iss;
	std::string keyword;
	iss << line;

	while (iss >> keyword){
		keywords.push_back(keyword);
	}
}

//Pre-condition: Input a string containing a line of action and location and check if there is only one block off task having this action and location left. If yes, the last block off task will be unblocked.
//			     The last task must contain the word "blockoff" in the output format.
//Post-condition: If there is only one task left in a specific block, unblock the task accordingly.
void TaskLinkedList::checkIfRemainingBlockTask(std::string line){
	std::vector<std::string> keywords;
	std::vector<std::string> taskList;
	int *index = new int;
	*index = 1;
	ListNode *cur = _head;
	splitIntoKeywords(line, keywords);
	keywords.push_back(KEYWORD_BLOCKOFF);

	if (retrieve(keywords, taskList)){
		if (taskList.size() == 1){
			if (getRemoveIndex(taskList[0], index)){
				cur = traverseTo(*index);
				cur->item.setBlock(false);
			}
		}
	}

	delete index;
	index = NULL;
}

//Pre-condition: Input a string containing the output format of the task to be deleted from the linked list and a line containing the action and location to cater in the fact that if there's only one task block remaining, it will be unblocked.
//Post-condition: Return true if the task is found and deleted from the linked list, if task comes from a block, the last block will be unblocked.
bool TaskLinkedList::remove(std::string task, std::string line){
	assert(task != KEYWORD_EMPTY_STRING);
	int *index = new int;
	*index = 1;
	bool condition = false;
	if (getRemoveIndex(task, index)){
		ListNode *cur;
		--_size;

		if (*index == 1){
			cur = _head;
			_head = _head->next;
		}else{
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

//Pre-condition: Input a string of words/word and convert it to lower case.
//Post-condition: Return the same string but converted to lower case.
std::string TaskLinkedList::toLowerCase(std::string line){
	for (unsigned int i = 0; line[i] != KEYWORD_NULL; i++){
		line[i] = tolower(line[i]);
	}
	return line;
}

//Pre-condition:Input day, month and year in int and convert them into a string in this format dd/mm/yy.
//			    Day and month have to be greater than 0. While year is at least 4 digits (the first digit is not 0).
//Post-condtion: Return a string date form from individual int day, month, year.
std::string TaskLinkedList::getStringDate(int day, int month, int year){
	assert(day > 0 && month > 0);
	std::ostringstream output;
	
	if (day < 10){
		output << KEYWORD_ZERO << day << KEYWORD_SLASH;
	}else{
		output << day << KEYWORD_SLASH;
	}

	if (month < 10){
		output << KEYWORD_ZERO << month << KEYWORD_SLASH << year;
	}else{
		output << month << KEYWORD_SLASH << year;
	}

	return output.str();
}

//Pre-condition: Input a tempTask and the starting and ending dates and push in the dates that are within the range of the starting and ending dates.
//				 Consider the maximum number of days to be 31 for all cases.
//Post-condition: Return a tempTask with the range of dates added at the back.
std::string TaskLinkedList::compareAndIncludeRange(std::string tempTask, int *startDay, int *startMonth, int *startYear, int *endDay, int *endMonth, int *endYear){
	int i, j, k;

	if (*startYear != *endYear){
		for (i = *startYear; i < *endYear; i++){
			for (j = 1; j <= KEYNUMBER_MONTH; j++){
				if (i == *startYear && j == 1){
					j = *startMonth;
				}
				for (k = 1; k <= KEYNUMBER_DAY; k++){
					if (j == *startMonth && k == 1){
						k = *startDay;
					}
					tempTask = tempTask + getStringDate(k,j,i);
				}
			}
		}
		if (i == *endYear){
			for (j = 1; j <= *endMonth; j++){
				for (k = 1; k <= *endDay; k++){
					tempTask = tempTask + getStringDate(k,j,i);
				}
			}
		}
	}else if (*startMonth != *endMonth){
		i = *startYear;
		for (j = *startMonth; j < *endMonth; j++){
			for (k = 1; k <= KEYNUMBER_DAY; k++){
				if (j == *startMonth && k == 1){
					k = *startDay;
				}
				tempTask = tempTask + getStringDate(k, j, i);
			}
		}
		if (j == *endMonth){
			for (k = 1; k <= *endDay; k++){
				tempTask = tempTask + getStringDate(k,j,i);
			}
		}
	}else if (*startDay != *endDay){
		i = *startYear;
		j = *startMonth;
		for (k = *startDay; k <= *endDay; k++){
			tempTask = tempTask + getStringDate(k,j,i);
		}
	}

	return tempTask;
}

//Pre-condition: Input a string date and convert into individual day, month and year as integers.
//				 String must be in the format dd/mm/yyyy.
//Post-condition: Pointers are updated (day, month, year as int).
void TaskLinkedList::getIntDate(std::string date, int *day, int *month, int *year){
	size_t posFirstDateSeparator = date.find(KEYWORD_SLASH);
	size_t posSecondDateSeparator = date.find(KEYWORD_SLASH, posFirstDateSeparator+1);
	
	std::string sDay = date.substr(0, posFirstDateSeparator-0);
	std::string sMonth = date.substr(posFirstDateSeparator+1, posSecondDateSeparator-posFirstDateSeparator-1);
	std::string sYear = date.substr(posSecondDateSeparator+1);

	std::istringstream ss1(sDay);
	ss1 >> *day;
	std::istringstream ss2(sMonth);
	ss2 >> *month;
	std::istringstream ss3(sYear);
	ss3 >> *year;
}

//Pre-condition: Input a task in the output format and include the range of dates to the back of this string if it is a period type of task (range of dates or time).
//				 Only check for range of dates entered in proper date format dd/mm/yyyy (note that the first digit day and month must have 0 if they are single digits).
//Post-condition: Return a task in the output format and an extension of dates if it is a period type of task.
std::string TaskLinkedList::includeRangeOfDates(std::string tempTask){
	if ((tempTask).find(KEYWORD_DASH) != std::string::npos){
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
	
//Pre-condition: Input a vector of individual keywords and an empty vector of taskList to store the task that are found from the linked list which contains all of the keywords. 
//				 Check for the range in dates for period type of task as well.
//				 Will only take into consideration range in dates if the user inputs the date in the right format or uses words like today, tmr,.. (dd/mm/yyyy).
//Post-condition: Return true if at least 1 task is found to contain all of the keywords from the vector and updates the taskList vector accordingly.
bool TaskLinkedList::retrieve(const std::vector<std::string> keywords, std::vector<std::string> & taskList){
	assert(taskList.empty());
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
	}else{
		return true;
	}
}

//Pre-condition: Input an empty vector and copy all the output format of the tasks in the linked list into this vector.
//Post-condition: The entire output format of the tasks in the linked list is copied over into the vector.
void TaskLinkedList::updateStorageVector(std::vector<std::string> & tbVector){
	assert(tbVector.empty());
	ListNode *cur = _head;

	while (cur != NULL){
		tbVector.push_back(cur->item.getTask());
		cur = cur->next;
	}
}

//Pre-condition: Input a string task to be located and change it's bool block as true.
//				 The task must be found in the linked list to successfully change the block to true.
//Post-condition: The task passed in is set as true for it's bool block.
void TaskLinkedList::setBlock(std::string task){
	assert(task != KEYWORD_EMPTY_STRING);
	ListNode *cur = _head;

	while (cur != NULL){
		if (cur->item.getTask() == task){ 
			cur->item.setBlock(true);
			return;
		}else{
			cur = cur->next;
		}
	}
}

//Pre-condition: Input 2 dates and compare them to check which is earlier. For dates that are passed today's date, the task in the output format is pushed into the overdueList vector.
//Post-condition: If the date is found to be over today's date, the overdueList vector is updated accordingly. 
void TaskLinkedList::compareWithToday(Date today, Date date, std::string task, std::vector<std::string> & overdueList){
	if (date._year < today._year){
		if (date._year != 0){
			overdueList.push_back(task);
		}
	}else if(date._year == today._year){
		if(date._month < today._month){
			if (date._month != 0){
				overdueList.push_back(task);
			}
		}else if(date._month == today._month){
			if(date._day < today._day){
				if (date._day != 0){
					overdueList.push_back(task);
				}
			}
		}
	}
}

//Pre-condition: Input a today date and a vector of overduelist to compare the dates and store overdue task in taskLinkedList into overduelinkedlist instead.
//Post-condition: Overdue items from taskLinkedList are stored in the vector and returned.
void TaskLinkedList::getOverdueList(Date today, std::vector<std::string> & overdueList){
	ListNode *cur = _head;

	while (cur != NULL){
		if (cur->item.getDeadlineDate()._day == 0 && cur->item.getEndingDate()._day == 0){
			compareWithToday(today, cur->item.getStartingDate(), cur->item.getTask(), overdueList);
		}else if (cur->item.getDeadlineDate()._day == 0 && cur->item.getEndingDate()._day != 0){
			compareWithToday(today, cur->item.getEndingDate(), cur->item.getTask(), overdueList);
		}else if (cur->item.getStartingDate()._day == 0){
			compareWithToday(today, cur->item.getDeadlineDate(), cur->item.getTask(), overdueList);
		}

		cur = cur->next;
	}
}