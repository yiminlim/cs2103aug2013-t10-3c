#pragma once

#include <iostream>
#include <sstream>
#include <Windows.h>
#include <tchar.h>
#include <exception>
#include "TaskLogic.h"

class UserInterface{
private:
	TaskLogic tbLogic;
	HANDLE hConsole;

	static const std::string COMMAND_ADD;
	static const std::string COMMAND_DELETE;
	static const std::string COMMAND_SEARCH;
	static const std::string COMMAND_EDIT;
	static const std::string COMMAND_EDITBLOCK;
	static const std::string COMMAND_ADDBLOCK;	
	static const std::string COMMAND_EDITALL;
	static const std::string COMMAND_DELETEBLOCK;
	static const std::string COMMAND_FINALISE;
	static const std::string COMMAND_FINALIZE;	
	static const std::string COMMAND_RETURN;
	static const std::string COMMAND_MARKDONE;
	static const std::string COMMAND_DONE;
	static const std::string COMMAND_OVERDUE;
	static const std::string COMMAND_CLEAROVERDUE;	
	static const std::string COMMAND_UNDO;
	static const std::string COMMAND_CLEAR;
	static const std::string COMMAND_HELP;
	static const std::string COMMAND_EXIT;	

	static const std::string KEYWORD_TODAY;
	static const std::string KEYWORD_BLOCKOFF;
	static const std::string KEYWORD_EMPTY_STRING;
	static const std::string KEYWORD_SPACE;
	static const std::string KEYWORD_BULLETING;
	static const std::string KEYWORD_END;

	static const std::string MESSAGE_TODAY_TASK;
	static const std::string MESSAGE_COMMAND;
	static const std::string MESSAGE_ADD;
	static const std::string MESSAGE_CLASH;
	static const std::string MESSAGE_DELETE;
	static const std::string MESSAGE_EDIT;
	static const std::string MESSAGE_AVAILABLE_BLOCKS;
	static const std::string MESSAGE_ADDBLOCK;
	static const std::string MESSAGE_EDITALL;
	static const std::string MESSAGE_DELETEBLOCK;
	static const std::string MESSAGE_FINALISE;
	static const std::string MESSAGE_MARKDONE;
	static const std::string MESSAGE_UNDO;
	static const std::string MESSAGE_CLEAROVERDUE;
	static const std::string MESSAGE_EXIT;

	static const std::string ERROR_INVALID_COMMAND;	
	static const std::string ERROR_SEARCH_BEFORE;
	static const std::string ERROR_OUT_OF_VECTOR_RANGE;
	static const std::string ERROR_UNDO_INITIALISE;

	static const std::string MESSAGE_INVALID_EDIT;
	static const std::string MESSAGE_INVALID_MARKDONE;
	static const std::string MESSAGE_INVALID_DONE;
	static const std::string MESSAGE_INVALID_OVERDUE;
	static const std::string MESSAGE_INVALID_UNDO;
	static const std::string MESSAGE_INVALID_EDITALL;
	static const std::string MESSAGE_INVALID_DELETEBLOCK;
	static const std::string MESSAGE_INVALID_FINALISE;

public:
		
	//User interface constructor
	//Precondition: Nil, Post-conditions: Nil
	UserInterface();

	//To initialise the program
	//Precondition: program just started with no task in linked list
	//Post-condition: program initialise and all task from textfile stored in linked list
	void initUI();
	
	//To read in different commands by user and handles them accordingly 
	//Precondition: program is initialised
	//Post-condition: Nil
	void commandUI();
	
	//To read in the details of task (excluding command)
	//Precondition: user has input a task to the pogram
	//Post-condition: task without command word in a string format will be return
	//Equivalence Partition: any command keyword
	//Boundary:	empty String, any other words
	std::string readTask(const std::string, const std::string);

	//To display the sub-menu for editing of block off dates
	//Precondition: 
	//Post-condition:
	void editBlockUI(const std::string);

	//To display welcome message
	//Precondition: display only after program is initialised
	//Post-condition: welcome message is displayed
	void displayWelcomeMessage();

	//To display the tasks to be done for that day
	//Precondition: 
	//Post-condition: 
	void displayTodayTask();

	//To display all information stored in a vector
	//Precondition:
	//Post-condition:
	void displayInformationInVector(std::vector<std::string>);

	//To display messages when commands are executed successfully
	//Precondition: function successfully call
	//Post-condition: success message with respect to command will be displayed
	void displayMessage(const std::string);

	//To display messages when commands fail to executed successfully
	//Precondition: function call fail
	//Post-condition: fail message with be displayed
	void displayFailMessage(const std::string);

	//To display the help message for commandUI
	void displayHelpCommandUI();

	//To display the help message for editBlockUI
	void displayHelpEditBlockUI();
};