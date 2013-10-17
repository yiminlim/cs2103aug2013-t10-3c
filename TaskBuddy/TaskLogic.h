#pragma once

#include <fstream>
#include "TaskLinkedList.h"
#include "Storage.h"
#include "Parse.h"

class TaskLogic{
private:
	TaskLinkedList tbLinkedList; // all the commands will be going through tbLogic to change the TaskLinkedList
    Storage tbStorage;
	std::vector<std::string> tbVector;
	Parse taskParse;

public:

	TaskLogic();

	~TaskLogic();

	//Takes in filename and takes all existing tasks inside file into tbLinkedList
	void initLogic();

	//initialisation by adding new task from text file to list
	//void initialAdd(const Task &);
		
	Task createTask(std::string, int);
	
	//sort all tasks in program
	//void initialSort();
	
	//add a new task to the list (search for correct index first)
	bool add(const std::string);
	
	void add(Task); //for initLogic use only

	//delete a task from the list at the index given
	bool del(const std::string);
	
	//return all tasks in the list that contains keyword and copy these tasks into vector parameter
	bool generalSearch(std::string, std::vector<std::string> &);
	
	//returns all tasks in the list that has the same date and copy these tasks into vector parameter
	bool daySearch(std::string, std::vector<std::string> &);
	
	//edit a task from the list at the index given
	//bool edit(int, std::string, std::vector<Task> &);
	
	//returns number of tasks in the list
	//int getNumTasks();
	
	//returns a task at the index given
	//Task getTasks(int);
	
	//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
	void save();
	
	void exitLogic();


};