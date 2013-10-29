#include "Task.h"

//-----CONSTRUCTORS----------------------------------------------------------------------------

//Default constructor
Task::Task(){
}

/* 
	Purpose: Takes task variable values and constructs a task object.
	Pre-conditions: All variables should have values. (strings should not be NULL)
	Post-conditions: Given that all variable values are found to be valid and necessary variables are included, formatted task output string is generated and task object is constructed. 
*/
//Use isValid/isEmpty methods to check & throw exceptions if necessary
//Note: isEmpty will be accepted also because they are not included under isValid
Task::Task(std::string action, std::string location, Date startingDate, int startingTime, Date endingDate, int endingTime, Date deadlineDate, int deadlineTime, bool block){
	_action = action;
	_location = location;
	_startingDate = startingDate;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_endingTime = endingTime;
	_deadlineDate = deadlineDate;
	_deadlineTime = deadlineTime;
	_block = block;
	_task = formatTask();
}

//-----GET METHODS-----------------------------------------------------------------------------

/* 
	Purpose: Retrieves task string.
	Pre-condition: Task object has initialised output task string value.
	Post-condition: Returns formatted task output string. 
*/
std::string Task::getTask(){
	return _task;
}

/* 
	Purpose: Retrieves task action string.
	Pre-condition: Task object has initialised action string value.
	Post-condition: Returns action string.
*/
std::string Task::getAction(){
	return _action;
}

/* 
	Purpose: Retrieves task location string.
	Pre-condition: Task object has initialised location string value.
	Post-condition: Returns location string.
*/
std::string Task::getLocation(){
	return _location;
}

/* 
	Purpose: Retrieves task starting date.
	Pre-condition: Task object has initialised starting date value. (Either valid date or empty date i.e. 0/0/0)
	Post-condition: Returns starting date. 
*/
Date Task::getStartingDate(){
	return _startingDate;
}

/* 
	Purpose: Retrieves task starting time.
	Pre-condition: Task object has initialised starting time value. (Either valid time or empty time i.e. -1)
	Post-condition: Returns starting time. 
*/
int Task::getStartingTime(){
	return _startingTime;
}

/* 
	Purpose: Retrieves task ending date.
	Pre-condition: Task object has initialised ending date value. (Either valid date or empty date i.e. 0/0/0)
	Post-condition: Returns ending date. 
*/
Date Task::getEndingDate(){
	return _endingDate;
}

/* 
	Purpose: Retrieves task ending time.
	Pre-condition: Task object has initialised ending time value. (Either valid time or empty time i.e. -1)
	Post-condition: Returns ending time. 
*/
int Task::getEndingTime(){
	return _endingTime;
}

/* 
	Purpose: Retrieves task deadline date.
	Pre-condition: Task object has initialised deadline date value. (Either valid date or empty date i.e. 0/0/0)
	Post-condition: Returns deadline date. 
*/
Date Task::getDeadlineDate(){
	return _deadlineDate;
}

/* 
	Purpose: Retrieves task deadline time.
	Pre-condition: Task object has initialised deadline time value. (Either valid time or empty time i.e. -1)
	Post-condition: Returns deadline time. 
*/
int Task::getDeadlineTime(){
	return _deadlineTime;
}

/* 
	Purpose: Retrieves task status.
	Pre-condition: Task object has initialised status value.
	Post-condition: Returns status. 
*/
/*char Task::getStatus(){
	char temp = ' ';
	return temp;
}
*/

/* 
	Purpose: Checks if task is part of a block.
	Pre-condition: Task object has initialised block value.
	Post-condition: Returns true if task is part of a block and false if otherwise.
*/
bool Task::getBlock(){
	return _block;
}

//-----SET METHODS-----------------------------------------------------------------------------

/* 
	Purpose: Set whether task is part of a block or not.
	Pre-condition: Task object has been initialised.
	Post-condition: Task block variable and formatted task output string are updated. 
	Equivalence Partitions: true, false 
*/
void Task::setBlock(bool newBlock) {
	_block = newBlock;
	_task = formatTask();
	
	return;
}

//-----FORMATTING METHODS----------------------------------------------------------------------

/* 
	Purpose: Formats task output string to be displayed to user.
	Pre-condition: Task object variables have been initialised.
	Post-condition: Returns formatted task output string.
*/
//refactor to make keywords constant strings? 'at', 'by', 'blockoff'
std::string Task::formatTask() {
	std::ostringstream output;
	if (isDeadlineType()) {
		output << "by ";
		if (!isEmptyDate(_deadlineDate)) {
			output << _deadlineDate._day << "/" << _deadlineDate._month << "/" << _deadlineDate._year;
		}
		if (!isEmptyTime(_deadlineTime)) {
			output << " " << formatTimeOutputString(_deadlineTime) << " hrs";
		}
		output << ": " << _action;
		if (_location.size() > 0) {
			output << " at " << _location;
		}
		if (_block) {
			output << " (blockoff)";
		}
	}
	else {
		if (!isEmptyDate(_startingDate)) {
			output << _startingDate._day << "/" << _startingDate._month << "/" << _startingDate._year;
		}
		if (!isEmptyTime(_startingTime)) {
			output << " " << formatTimeOutputString(_startingTime) << " hrs";
		}
		if (!isEmptyDate(_endingDate) || !isEmptyTime(_endingTime)) {
			output << " - ";
			if (!isEmptyDate(_endingDate)) {
				output << _endingDate._day << "/" << _endingDate._month << "/" << _endingDate._year;
			}
			if (!isEmptyTime(_endingTime)) {
				output << " " << formatTimeOutputString(_endingTime) << " hrs";
			}
		}
		output << ": " << _action;
		if (_location.size() > 0) {
			output << " at " << _location;
		}
		if (_block) {
			output << " (blockoff)";
		}
	}

	return output.str();
}

/* 
	Purpose: Formats time output string based on time integer value. 
	Pre-condition: Time is valid and not empty (i.e. -1)
	Post-condition: Returns time output string (should be 4 digits) 
*/
std::string Task::formatTimeOutputString(int time){
	std::ostringstream timeString;

	if (time < 1000) {
		timeString << "0";
	}
	if (time < 100) {
		timeString << "0";
	}
	if (time < 10) {
		timeString << "0";
	}
	timeString << time;

	return timeString.str();
}

//-----CHECK METHODS---------------------------------------------------------------------------

/* 
	Purpose: Checks if task is a deadline type. 
	Pre-condition: Task object deadline date values have been initialised.
	Post-condition: Returns true if deadlineDate is not empty (i.e. 0/0/0) and false otherwise. 
	Equivalence Partitions: day/month/year = 0, valid integer values.
	Boundary values: 0, 1
*/
bool Task::isDeadlineType() {
	return (_deadlineDate._day && _deadlineDate._month && _deadlineDate._year);
}

/* 
	Purpose: Checks if date value is empty i.e. 0/0/0. 
	Pre-condition: Date value has been initialised.
	Post-condition: Returns true if date is empty (i.e. 0/0/0) and false otherwise.
	Equivalence Partitions: day/month/year = 0, valid integer values.
	Boundary values: 0, 1
*/
bool Task::isEmptyDate(Date date) {
	return (date._day == 0 && date._month == 0 && date._year == 0);
}

/* 
	Purpose: Checks if date value is valid. 
	Pre-condition: Date value has been initialised.
	Post-condition: Returns true if date is valid and false otherwise. 
*/
bool Task::isValidDate(Date date) {
	return isValidDay(date._day) && isValidMonth(date._month) && isValidYear(date._year);
}

/* 
	Purpose: Checks if day value of year is valid. 
	Pre-condition: Day value has been initialised.
	Post-condition: Returns true if day value of date is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-31, > 31
	Boundary values: 0, 1, 2, 30, 31, 32
*/
bool Task::isValidDay(int day) {
	return day >= 1 && day <= 31;
}

/* 
	Purpose: Checks if month value of date is valid. 
	Pre-condition: Month value has been initialised.
	Post-condition: Returns true if month value of date is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-12, > 12
	Boundary values: 0, 1, 2, 11, 12, 13
*/
bool Task::isValidMonth(int month) {
	return month >= 1 && month <= 12;
}

/* 
	Purpose: Checks if year value of date is valid. 
	Pre-condition: Year value has been initialised.
	Post-condition: Returns true if year value of date is valid and false otherwise. 
	Equivalence Partitions: < 1, >= 1
	Boundary values:  0, 1, 2
*/
bool Task::isValidYear(int year) {
	return year > 0;
}

/* 
	Purpose: Checks if time value is empty i.e. -1. 
	Pre-condition: Time value has been initialised.
	Post-condition: Returns true if time is empty (i.e. -1) and false otherwise. 
	Equivalence Partitions: -1, any positive integer
	Boundary values: -1, 1
*/
bool Task::isEmptyTime(int time) {
	return time == -1;
}

/* 
	Purpose: Checks if time value is valid. 
	Pre-condition: Time value has been initialised.
	Post-condition: Returns true if time is valid and false otherwise. 
*/
bool Task::isValidTime(int time) {
	int hour = time/100;
	int mins = time - (hour*100);

	return isValidHour(hour) && isValidMins(mins);
}

/* 
	Purpose: Checks if hour value of time is valid. 
	Pre-condition: Hour value is an integer.
	Post-condition: Returns true if hour value of time is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-23, > 23 
	Boundary values: 0, 1, 2, 22, 23, 24
*/
bool Task::isValidHour(int hour) {
	return hour >= 1 && hour <= 23;
}

/* 
	Purpose: Checks if minutes value of time is valid. 
	Pre-condition: Minutes value is an integer.
	Post-condition: Returns true if minutes value of time is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-59, > 59
	Boundary values: 0, 1, 2, 58, 59, 60
*/
bool Task::isValidMins(int mins) {
	return mins >= 1 && mins <= 59;
}