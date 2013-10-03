#ifndef _TASKLOGIC_H_
#define _TASKLOGIC_H_

#include <fstream>
#include "TaskLinkedList.h"

class TaskLogic{
private:
	TaskLinkedList tbLinkedList; // all the commands will be going through tbLogic to change the TaskLinkedList

public:

	TaskLogic();

	~TaskLogic();

	//Takes in filename and takes all existing tasks inside file into tbLinkedList
	void initLogic(std::string);

	//initialisation by adding new task from text file to list
	void initialAdd(const Task &);
	
	//sort all tasks in program
	void initialSort();
	
	//add a new task to the list (search for correct index first)
	bool add(const Task &, std::vector<Task> &);
	
	//delete a task from the list at the index given
	bool del(int, std::vector<Task> &);
	
	//return all tasks in the list that contains keyword and copy these tasks into vector parameter
	bool generalSearch(std::string, std::vector<Task> &);
	
	//returns all tasks in the list that has the same date and copy these tasks into vector parameter
	bool dateSearch(std::string, std::vector<Task> &);
	
	//edit a task from the list at the index given
	bool edit(int, std::string, std::vector<Task> &);
	
	//returns number of tasks in the list
	int getNumTasks();
	
	//returns a task at the index given
	Task getTasks(int);
	
	//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
	void exitLogic(std::string);


};
#endif;