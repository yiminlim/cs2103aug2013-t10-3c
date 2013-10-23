#pragma once

#include <fstream>
#include <assert.h>
#include "Date.h"
#include "Task.h"
#include "TaskLinkedList.h"
#include "Storage.h"
#include "Parse.h"

class TaskLogic{
private:
	TaskLinkedList tbLinkedList; // all the commands will be going through tbLogic to change the TaskLinkedList
    Storage tbStorage; 
	Parse taskParse;
	std::vector<std::string> tbVector;
	std::vector<std::string> dateVector; //dateVector[0] : today, dateVector[1] : coming Monday, ....dateVector[7] : coming Sunday, dateVector[8] : tomorrow (all in the form : dd/mm/yy)

public:

	TaskLogic();

	~TaskLogic();

	//Takes in filename and takes all existing tasks inside file into tbLinkedList
	void initLogic();

	void initDate();

	void stringParse(const std::string, const int, std::string &, std::string &, std::vector<Date> &, int &, std::vector<Date> &, int &, std::vector<Date> &, int &);
	//converts userInput String into various components from existing
		
	std::vector<Task> createTask(std::string, int);

	//add a new task to the list (search for correct index first)
	void addExistingTask(const std::string); //for initLogic use only
	
	bool add(const std::string);

	bool checkIsValidInput(std::string);
	
	//delete a task from the list at the index given
	bool del(const std::string);

	bool delFromVector(const std::string);
	
	//return all tasks in the list that contains keyword and copy these tasks into vector parameter
	bool generalSearch(std::string, std::vector<std::string> &);

	bool isDay(std::string &);
	
	
	//edit a task from the list at the index given
	bool edit(std::string, std::string);
	
	//returns number of tasks in the list
	//int getNumTasks();
	
	//returns a task at the index given
	//Task getTasks(int);
	
	//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
	void save();
	
	void exitLogic();

	std::string extractDate(std::string);
};