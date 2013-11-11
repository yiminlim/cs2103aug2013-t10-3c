#pragma once

#include <fstream>
#include <assert.h>
#include <stack>
#include <exception>
#include "Date.h"
#include "Task.h"
#include "TaskLinkedList.h"
#include "DoneLinkedList.h"
#include "OverdueLinkedList.h"
#include "Storage.h"
#include "Parse.h"

class TaskLogic{
private:
	TaskLinkedList tbLinkedList; // all the commands will be going through tbLogic to change the TaskLinkedList
	DoneLinkedList tbDoneLinkedList;
	OverdueLinkedList tbOverdueLinkedList;
	Storage tbStorage; 
	Storage tbDoneStorage;
	Storage tbOverdueStorage;
	Parse taskParse;

	std::vector<std::string> dateVector; //dateVector[0] : today, dateVector[1] : coming Monday, ....dateVector[7] : coming Sunday, dateVector[8] : tomorrow (all in the form : dd/mm/yy)
	std::stack<std::string> commandStackHistory;
	std::stack<std::string> taskStackHistory;
	std::stack<int> countStackHistory;

	static const std::string COMMAND_ADD;
	static const std::string COMMAND_DELETE;
	static const std::string COMMAND_EDIT;
	static const std::string COMMAND_MARKDONE;
	static const std::string KEYWORD_FROM;
	static const std::string KEYWORD_TO;
	static const std::string KEYWORD_BY;
	static const std::string FILENAME_TB_STORAGE;
	static const std::string FILENAME_TB_DONE_STORAGE;
	static const std::string FILENAME_TB_OVERDUE_STORAGE;
	static const std::string UI_FORMAT;
	static const std::string PROCESSED_FORMAT;
	static const std::string BLOCK_OFF;
	static const std::string FLOATING_TASK;
	static const std::string THROW_MESSAGE_MISSING_INPUT;
	static const std::string THROW_MESSAGE_MISSING_ACTION;
	static const std::string THROW_MESSAGE_TASK;
	static const std::string THROW_MESSAGE_ADD_FAILURE;
	static const std::string THROW_MESSAGE_NO_TASK_FOR;
	static const std::string THROW_MESSAGE_NO_TASK_WITH;
	static const std::string THROW_MESSAGE_FOUND;
	static const std::string THROW_MESSAGE_ONLY_ACTION_LOCATION;
	static const std::string THROW_MESSAGE_DATE_PASSED;


public:

	TaskLogic();

	~TaskLogic();

//-----INITIALISATION & SAVING------------------------------------------------------------------------
	
	//Initialise all main components inside Logic class required at start of program  
	void initLogic();

	//Initialise the dates within the next week into dateVector
	void initDate();

	//Initialise tbOverdueLinkedList
	void initOverdue();
	
	//Save all task inside task tbLinkedList into external file
	void save();
	
	//Save all task inside task tbDoneLinkedList into external file
	void saveDone();

	//Save all task inside task tbOverdueLinkedList into external file
	void saveOverdue();

//-----ADD TASK----------------------------------------------------------------------------------------------

	//Add UI format taskString into tbLinkedList
	void add(const std::string, bool&, std::vector<std::string>&, std::vector<std::string>&);

	//Add Processed format taskString into tbLinkedList
	void addExistingTask(const std::string);

	//Add Processed format taskString into tbDoneLinkedList
	void addExistingDoneTask(const std::string);

	//Add Processed format taskString into tbOverdueLinkedList
	void addOverdueTask(const std::string);

	//Creates a task from a string in UI format or processed format	
	std::vector<Task> createTask(std::string, std::string);

//-----DELETE TASK-------------------------------------------------------------------------------------------

	//Delete a task from the tbLinkedList
	void del(const std::string, bool);

//-----SEARCH TASK-------------------------------------------------------------------------------------------

	//Search all tasks in the list that contains keyword
	void generalSearch(std::string, std::vector<std::string> &, std::vector<std::string> &);

	//Edits search output vector by adding in spaces between tasks with different dates
	std::vector<std::string> processSearchOutputVector(std::vector<std::string>, std::vector<std::string> & );

	//Returns dates of all search output in a vector
	std::vector<Date> getSearchOutputDateVector(std::vector<std::string> );
	
//-----EDIT TASK---------------------------------------------------------------------------------------------

	//Edit a task from the tbLinkedList at the index given
	void edit(std::string, std::string, bool, std::vector<std::string>&, std::string&);

	//Edit all new date to take the value of the old date
	void editDateCurrentIntoNew(Date&, Date, Date&, Date, Date&, Date);
	
	//Edit all new timeto take the value of the old time
	void editTimeCurrentIntoNew(int&, int, int&, int, int&, int);

//-----EDIT BLOCK--------------------------------------------------------------------------------------------

	//Updates the block of taskStrings and string that contains the action and location of the task
	void getBlock(std::string &, std::string &, std::vector<std::string> &, std::vector<std::string> &);
	
	//Edit location, action of all blocked item.
	void editBlock(const std::string, std::vector<std::string> &);

	//Add additional blocks for an existing tasks.
	void addBlock(const std::string, const std::string, bool, std::vector<std::string>&, std::vector<std::string>&);

	//Finalise a partiular timing for blocked tasks.
	void finaliseBlock(int, std::vector<std::string>&);

	//Remove the word "(blockoff)" if present in the word
	std::string removeBlockoff(std::string);

//-----UNDO---------------------------------------------------------------------------------------------------
		
	//Check if any of the stack histories are empty 
	bool checkUndoStackEmpty();

	//Update commandStackHistory and taskStackHisory with new command and task respectively
	void update(std::string, std::string, std::string);

	//Update counter for number of actions performed in a command
	void updateCount(int);

	//Undo previous edit
	void undoEdit(std::vector<std::string>&, std::vector<std::string>&);
	
	//Undo previous add
	void undoAdd(std::vector<std::string>&);
	
	//Undo previous delete
	void undoDelete(std::vector<std::string>&);

	//Undo previous mark done
	void undoMarkDone(std::vector<std::string>&);

	//To undo the most recent command from by user
	void undo(std::string&, std::vector<std::string>&, std::vector<std::string>&);

//-----MARK DONE------------------------------------------------------------------------------------------------
	
	//Remove a task from tbLinkedList and Adds it to tbDoneLinkedList
	void markDone(std::string taskString); 

	//Retrieve tasks from tbDoneLinkedList
	bool retrieveDoneList(std::vector<std::string> &);

//-----OVERDUE--------------------------------------------------------------------------------------------------

	//Clear all task in tbOverdueLinkedList
	void clearOverdueList();

	//Retrieve tasks from tbOverdueLinkedList
	bool retrieveOverdueList(std::vector<std::string> &);
	
//-----HELPER FUNCTIONS---------------------------------------------------------------------------------------
	
	//Converts Userinput string into various components in a task 
	void stringParse(const std::string, const std::string, std::string &, std::string &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, bool &);

	//Check if number is a single digit
	bool isSingleDigit(int);

	//Check if string is a day 
	bool isDay(std::string &);

	//Checks if 2 dates are equal
	bool checkSameDate(Date, Date);

	//Converts date into numerical form
	std::string extractDate(std::string);

	//Covert a Date object to date string
	std::string convertToDateString(Date);

	//Retrieve action & location in a task string
	std::string getActionLocation(std::string);

	//Checks if the string only contains action and location
	bool isOnlyActionLocation(std::string);

	//Perform test for valid task 
	void checkValidTask(Task);
};
