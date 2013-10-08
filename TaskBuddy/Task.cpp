#include "Task.h"

//empty constructor
Task::Task(){
}

//constructor
Task::Task(std::string, std::string, std::string, Date, int, Date, int, Date, int){
}

//returns task
std::string Task::getTask(){
	return "";
}

//returns task action
std::string Task::getAction(){
	return "";
}

//returns task location
std::string Task::getLocation(){
	return "";
}

//returns task starting date
Task::Date Task::getStartingDate(){
	Date date;
	return date;
}

//returns task starting time
int Task::getStartingTime(){
	return 0;
}

//returns tsak ending date
Task::Date Task::getEndingDate(){
	Date date;
	return date;
}

//returns task ending time
int Task::getEndingTime(){
	return 0;
}

//returns task deadline date
Task::Date Task::getDeadlineDate(){
	Date date;
	return date;
}

//returns task deadline time
int Task::getDeadlineTime(){
	return 0;
}

//returns task status
char Task::getStatus(){
	char temp = ' ';
	return temp;
}