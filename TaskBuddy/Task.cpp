#include "Task.h"

//empty constructor
Task::Task(){
}

//constructor
Task::Task(std::string, std:: string, std::string, std::string, Date, int, Date, int, Date, int){
}

//returns task
std::string Task::getOriginalTask(){
	return _originalTask;
}

std::string Task::getFormattedTask(){
	return _formattedTask;
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