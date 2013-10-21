#include "Task.h"

//empty constructor
Task::Task(){
}

//constructor
Task::Task(std::string action, std::string location, Date startingDate, int startingTime, Date endingDate, int endingTime, Date deadlineDate, int deadlineTime){
	_task = formatTask(action,location,startingDate,startingTime,endingDate,endingTime,deadlineDate,deadlineTime);
	_action = action;
	_location = location;
	_startingDate = startingDate;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_endingTime = endingTime;
	_deadlineDate = deadlineDate;
	_deadlineTime = deadlineTime;
}

//returns task
std::string Task::getTask(){
	return _task;
}

//returns task action
std::string Task::getAction(){
	return _action;
}

//returns task location
std::string Task::getLocation(){
	return _location;
}

//returns task starting date
Date Task::getStartingDate(){
	return _startingDate;
}

//returns task starting time
int Task::getStartingTime(){
	return _startingTime;
}

//returns tsak ending date
Date Task::getEndingDate(){
	return _endingDate;
}

//returns task ending time
int Task::getEndingTime(){
	return _endingTime;
}

//returns task deadline date
Date Task::getDeadlineDate(){
	return _deadlineDate;
}

//returns task deadline time
int Task::getDeadlineTime(){
	return _deadlineTime;
}

//returns task status
/*char Task::getStatus(){
	char temp = ' ';
	return temp;
}
*/

std::string Task::formatTask(std::string action, std::string location, Date startingDate, int startingTime, Date endingDate, int endingTime, Date deadlineDate, int deadlineTime, bool isDeadLineType) {
	std::ostringstream output;
	if (isDeadLineType) {
		assert (deadlineTime >= 0 && deadlineTime <= 2359);
		output << "by " << deadlineDate._day << "/" << deadlineDate._month << "/" << deadlineDate._year;
		output << " " << formatTimeOutputString(deadlineTime) << " hrs";
		output << ": " << action;
		if (location.size() > 0) {
			output << " at " << location;
		}
	}
	else {
		output << startingDate._day << "/" << startingDate._month << "/" << startingDate._year;
		output << " " << formatTimeOutputString(startingTime) << " hrs";
		if (endingDate._day && endingDate._month && endingDate._year) {
			output << " - " << endingDate._day << "/" << endingDate._month << "/" << endingDate._year;
			output << " " << formatTimeOutputString(endingTime) << " hrs";
		}
		output << ": " << action;
		if (location.size() > 0) {
		output << " at " << location;
		}
	}

	return output.str();
}

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