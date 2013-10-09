#include "TaskLogic.h"
#include <sstream>

TaskLogic::TaskLogic(){
}

TaskLogic::~TaskLogic(){
}

//Takes in filename and takes all existing tasks inside file into tbLinkedList
void TaskLogic::initLogic(){
	tbStorage.getExistingTasks(tbVector);
	Task task;
	for(unsigned int i=0; i < tbVector.size() ; i++){
		task = createTask(tbVector[i], 2); // retrieveTask method, only used at the start
		add(task); 
	}
	return;
}

//initialisation by adding new task from text file to list
//void TaskLogic::initialAdd(const Task &){
//}
	
Task TaskLogic::createTask(std::string taskString, int method){
	Task task;
	if(method == 1)
		task = taskParse.generateTaskFromUserInput(taskString);
	else if(method == 2)
		task = taskParse.retrieveTask(taskString);
	//add exceptions for error:
	return task;
}

//sort all tasks in program
//void TaskLogic::initialSort(){
//}
	
//add a new task to the list (search for correct index first)
bool TaskLogic::add(const std::string taskString){
	Task task;
	task = createTask(taskString, 1); //generating task from user input.
	return tbLinkedList.insert(task);
}

void TaskLogic::add(Task task){
	tbLinkedList.insert(task);
	return;
}
	
//delete a task from the list at the index given
bool TaskLogic::del(const std::string taskString){
	return tbLinkedList.remove(taskString);
}
	
//return all tasks in the list that contains keyword and copy these tasks into vector parameter
bool TaskLogic::generalSearch(std::string userInput, std::vector<std::string>& vectorOutput){
	std::vector<std::string> keywordVector;
	std::istringstream iss;
	std:: string keyword;
	while(iss >> keyword)
		keywordVector.push_back(keyword);

	return tbLinkedList.retrieve(keywordVector,vectorOutput);
}
	
	
//returns all tasks in the list that has the same date and copy these tasks into vector parameter
bool TaskLogic::daySearch(std::string, std::vector<std::string> &){
	return true;
}
	
//edit a task from the list at the index given
//bool TaskLogic::edit(int, std::string, std::vector<Task> &){
//	return true;
//}
	
//returns number of tasks in the list
//int TaskLogic::getNumTasks(){
//	return 0;
//}
	
//returns a task at the index given
//Task TaskLogic::getTasks(int){
//	Task temp;
//	return temp;
//}
	
void TaskLogic::save(){
	tbStorage.saveTasksIntoFile(tbVector);
}

//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
void TaskLogic::exitLogic(){
	save();
	tbVector.clear();
}