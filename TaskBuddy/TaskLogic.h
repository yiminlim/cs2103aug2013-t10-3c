#pragma once

#include <fstream>
#include <assert.h>
#include <stack>
#include "Date.h"
#include "Task.h"
#include "TaskLinkedList.h"
#include "DoneLinkedList.h"
#include "Storage.h"
#include "Parse.h"

class TaskLogic{
private:
	TaskLinkedList tbLinkedList; // all the commands will be going through tbLogic to change the TaskLinkedList
	DoneLinkedList tbDoneLinkedList;
	Storage tbStorage; 
	Storage tbDoneStorage;
	Parse taskParse;

	std::vector<std::string> dateVector; //dateVector[0] : today, dateVector[1] : coming Monday, ....dateVector[7] : coming Sunday, dateVector[8] : tomorrow (all in the form : dd/mm/yy)
	std::stack<std::string> commandStackHistory;
	std::stack<std::string> taskStackHistory;

	static const std::string COMMAND_ADD;
	static const std::string COMMAND_DELETE;
	static const std::string COMMAND_EDIT;
	static const std::string COMMAND_MARKDONE;
	static const std::string FILENAME_TB_STORAGE;
	static const std::string FILENAME_TB_DONE_STORAGE;
	static const std::string FILENAME_TB_OVERDUE_STORAGE;

public:

	TaskLogic();

	~TaskLogic();

//-----INITIALISATION, SAVING & EXIT------------------------------------------------------------------------
	//Takes in filename and takes all existing tasks inside file into tbLinkedList
	void initLogic();

	void initDate();

	//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
	void save();
	
	void saveDone();

//-----ADD TASK----------------------------------------------------------------------------------------------

	bool add(const std::string, bool&, std::vector<std::string>&);

	//add a new task to the list (search for correct index first)
	bool addExistingTask(const std::string); //for initLogic use only

	bool addExistingDoneTask(const std::string); //for initLogic use only

//-----DELETE TASK-------------------------------------------------------------------------------------------

	//delete a task from the list at the index given
	bool del(const std::string, bool);

//-----SEARCH TASK-------------------------------------------------------------------------------------------

	//return all tasks in the list that contains keyword and copy these tasks into vector parameter
	bool generalSearch(std::string, std::vector<std::string> &);
	
//-----EDIT TASK---------------------------------------------------------------------------------------------

	//edit a task from the list at the index given
	bool edit(std::string, std::string);

//-----EDIT BLOCK--------------------------------------------------------------------------------------------

	//gives back entire block of taskStrings and also a string that contains the task (action + " at " location )
	bool getBlock(std::string &, std::string &, std::vector<std::string> &);
	
	//for editing location, action of all blocked item.
	bool editBlock(const std::string, std::vector<std::string> &);

	//for adding in new blocks, const string contains action + location while vector string contains timings and dates
	bool addBlock(const std::string, const std::string);
	// first string is the action and location of original taskString, 2nd string is the original taskString

	//delete all the blocks of the string given
	//finaliseBlock is the same as deleteBlock. Just give in all those that is meant to be deleted. If only one left, send in isBloack = false
	bool finaliseBlock(int, std::vector<std::string> &);

//-----UNDO---------------------------------------------------------------------------------------------------

	//To update taskVector with new command and task by user
	void update(std::string, std::string, std::string);

	//To undo the most recent command made by user
	bool undo();
	
//-----HELPER FUNCTIONS---------------------------------------------------------------------------------------
	
	void stringParse(const std::string, const int, std::string &, std::string &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, bool &);
	//converts userInput String into various components from existing
		
	std::vector<Task> createTask(std::string, int);

	bool isDay(std::string &);

	std::string extractDate(std::string);

	std::string getActionLocation(std::string);

//-----MARK DONE------------------------------------------------------------------------------------------------
	bool markDone(std::string taskString); 

	bool retrieveDoneList(std::vector<std::string> &);

};