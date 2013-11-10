#include "Task.h"

//-----CONSTRUCTORS----------------------------------------------------------------------------

//Default constructor
Task::Task(){
}

/* 
	Purpose: Takes task variable values and constructs a task object.
	Pre-conditions: All variables values should be valid. (e.g. strings should not be NULL)
	Post-conditions: Formatted task output string is initialised and task object is constructed. 
*/
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
	_task = formatTaskOutputString();
}

//-----GET METHODS-----------------------------------------------------------------------------

/* 
	Purpose: Retrieves formatted task output string.
	Pre-condition: Task object has initialised output task string value.
	Post-condition: Returns formatted output string. 
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
*/
void Task::setBlock(bool newBlock) {
	_block = newBlock;     
	_task = formatTaskOutputString();
	
	return;
}

//-----FORMATTING METHODS----------------------------------------------------------------------

/* 
	Purpose: Formats task output string to be displayed to user.
	Pre-condition: Task object variables have been initialised.
	Post-condition: Returns formatted task output string.
*/
std::string Task::formatTaskOutputString() {
	std::ostringstream output;
	if (isDeadlineType()) {
		output << "by ";
		if (!isEmptyDate(_deadlineDate)) {
			output << formatDateOutputString(_deadlineDate);
		}
		if (!isEmptyTime(_deadlineTime)) {
			output << " " << formatTimeOutputString(_deadlineTime) << " hrs";
		}
		output << " : " << _action;
		if (_location.size() > 0) {
			output << " at " << _location;
		}
		if (_block) {
			output << " (blockoff)";
		}
	}
	else {
		output << "   ";	//For alignment with deadline tasks during display
		if (!isEmptyDate(_startingDate)) {
			output << formatDateOutputString(_startingDate);
		}
		if (!isEmptyTime(_startingTime)) {
			output << " " << formatTimeOutputString(_startingTime) << " hrs";
		}
		if (!isEmptyDate(_endingDate) || !isEmptyTime(_endingTime)) {
			output << " -";
			if (!isEmptyDate(_endingDate)) {
				output << " " << formatDateOutputString(_endingDate);
			}
			if (!isEmptyTime(_endingTime)) {
				output << " " << formatTimeOutputString(_endingTime) << " hrs";
			}
		}
		output << " : " << _action;
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
	Post-condition: Returns time output string in 24hr format (should be 4 digits) 
*/
std::string Task::formatTimeOutputString(int time){
	std::ostringstream timeString;

	if (time < 1000) {
		timeString << "0";	//Adds zeros for values that are of less 
	}						//than 4 digits
	if (time < 100) {
		timeString << "0";
	}
	if (time < 10) {
		timeString << "0";
	}
	timeString << time;

	return timeString.str();
}

/* 
	Purpose: Formats date output string based on dd/mm/yyyy. 
	Pre-condition: Date is valid and not empty (i.e. 0/0/0).
	Post-condition: Returns date output string (should be in dd/mm/yyyy format).
*/

std::string Task::formatDateOutputString(Date date) {
	std::ostringstream dateString;
	if (date._day < 10) {
		dateString << "0";		//Adds zeros for day and month values that are 
	}							//single digits to ensure proper format
	dateString << date._day;
	dateString << "/";
	if (date._month < 10) {
		dateString << "0";
	}
	dateString << date._month;
	dateString << "/";
	if (date._year < 1000) {
		dateString << "0";		//Adds zeros to year values that are less than
	}							//four digits to ensure proper format
	if (date._year < 100) {
		dateString << "0";
	}
	if (date._year < 10) {
		dateString << "0";
	}
	dateString << date._year;

	return dateString.str();
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
	return !isEmptyDate(_deadlineDate);
}

/* 
	Purpose: Checks if task is an activity type. 
	Pre-condition: Task object date values have been initialised.
	Post-condition: Returns true if startingDate is not empty (i.e. 0/0/0) and false otherwise. 
*/

bool Task::isActivityType() {
	return !isEmptyDate(_startingDate);
}

/* 
	Purpose: Checks if task is an floating type (only contains action and no dates/times). 
	Pre-condition: Task object date values have been initialised.
	Post-condition: Returns true if all types of dates are empty (i.e. 0/0/0) and false otherwise. 
*/

bool Task::isFloatingType() {
	return isEmptyDate(_deadlineDate) && isEmptyDate(_startingDate) && isEmptyDate(_endingDate);
}

/* 
	Purpose: Checks if date value is empty i.e. 0/0/0. 
	Pre-condition: Date value has been initialised.
	Post-condition: Returns true if date is empty (i.e. 0/0/0) and false otherwise.
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
*/
bool Task::isValidMonth(int month) {
	return month >= 1 && month <= 12;
}

/* 
	Purpose: Checks if year value of date is valid. 
	Pre-condition: Year value has been initialised.
	Post-condition: Returns true if year value of date is valid and false otherwise. 
*/
bool Task::isValidYear(int year) {
	return year > 0;
}

/* 
	Purpose: Checks if time value is empty i.e. -1. 
	Pre-condition: Time value has been initialised.
	Post-condition: Returns true if time is empty (i.e. -1) and false otherwise. 
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
*/
bool Task::isValidHour(int hour) {
	return hour >= 1 && hour <= 23;
}

/* 
	Purpose: Checks if minutes value of time is valid. 
	Pre-condition: Minutes value is an integer.
	Post-condition: Returns true if minutes value of time is valid and false otherwise. 
*/
bool Task::isValidMins(int mins) {
	return mins >= 1 && mins <= 59;
}