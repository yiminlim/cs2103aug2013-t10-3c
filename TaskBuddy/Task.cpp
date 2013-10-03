#include "Task.h"

//empty constructor
Task::Task(){
}

//constructor
Task::Task(std::string, std::string, std::string, std::string, int, std::string, int, std::string, char, std::vector<std::string>){
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
std::string Task::getStartingDate(){
	return "";
}

//returns task starting time
int Task::getStartingTime(){
	return 0;
}

//returns tsak ending date
std::string Task::getEndingDate(){
	return "";
}

//returns task ending time
int Task::getEndingTime(){
	return 0;
}

//returns task deadline date
std::string Task::getDeadlineDate(){
	return "";
}

//returns task deadline time
std::string Task::getDeadlineTime(){
	return "";
}

//returns task status
char Task::getStatus(){
	char temp = ' ';
	return temp;
}