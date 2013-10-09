#include "Task.h"

//empty constructor
Task::Task(){
}

//constructor
Task::Task(std::string task, std::string action, std::string location, Date startingDate, int startingTime, Date endingDate, int endingTime, Date deadlineDate, int deadlineTime){
	_task = task;
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
Task::Date Task::getStartingDate(){
	return _startingDate;
}

//returns task starting time
int Task::getStartingTime(){
	return _startingTime;
}

//returns tsak ending date
Task::Date Task::getEndingDate(){
	return _endingDate;
}

//returns task ending time
int Task::getEndingTime(){
	return _endingTime;
}

//returns task deadline date
Task::Date Task::getDeadlineDate(){
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