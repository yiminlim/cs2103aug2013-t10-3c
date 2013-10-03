#include "TaskLogic.h"

TaskLogic::TaskLogic(){
}

TaskLogic::~TaskLogic(){
}

//Takes in filename and takes all existing tasks inside file into tbLinkedList
void TaskLogic::initLogic(std::string){
}

//initialisation by adding new task from text file to list
void TaskLogic::initialAdd(const Task &){
}
	
//sort all tasks in program
void TaskLogic::initialSort(){
}
	
//add a new task to the list (search for correct index first)
bool TaskLogic::add(const Task &, std::vector<Task> &){
	return true;
}
	
//delete a task from the list at the index given
bool TaskLogic::del(int, std::vector<Task> &){
	return true;
}
	
//return all tasks in the list that contains keyword and copy these tasks into vector parameter
bool TaskLogic::generalSearch(std::string, std::vector<Task> &){
	return true;
}
	
//returns all tasks in the list that has the same date and copy these tasks into vector parameter
bool TaskLogic::dateSearch(std::string, std::vector<Task> &){
	return true;
}
	
//edit a task from the list at the index given
bool TaskLogic::edit(int, std::string, std::vector<Task> &){
	return true;
}
	
//returns number of tasks in the list
int TaskLogic::getNumTasks(){
	return 0;
}
	
//returns a task at the index given
Task TaskLogic::getTasks(int){
	Task temp;
	return temp;
}
	
//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
void TaskLogic::exitLogic(std::string){
}