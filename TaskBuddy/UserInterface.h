#pragma once

#include <iostream>
#include "TaskLogic.h"

class UserInterface{
private:
	TaskLogic tbLogic; 

	static const std::string COMMAND_ADD;
	static const std::string COMMAND_DELETE;
	static const std::string COMMAND_SEARCH;
	static const std::string COMMAND_EDIT;
	static const std::string COMMAND_UNDO;
	static const std::string COMMAND_CLEAR;
	static const std::string COMMAND_EXIT;	

	static const std::string KEYWORD_TODAY;

	static const std::string MESSAGE_TODAY_TASK;
	static const std::string MESSAGE_NO_TASK_TODAY;
	static const std::string MESSAGE_COMMAND;
	static const std::string MESSAGE_ADD;
	static const std::string MESSAGE_DELETE;
	static const std::string MESSAGE_EDIT;
	static const std::string MESSAGE_UNDO;	
	static const std::string MESSAGE_INVALID_ADD;
	static const std::string MESSAGE_INVALID_SEARCH;
	static const std::string MESSAGE_INVALID_DELETE;
	static const std::string MESSAGE_INVALID_EDIT;
	static const std::string MESSAGE_INVALID_UNDO;
	static const std::string MESSAGE_INVALID_COMMAND;
	static const std::string MESSAGE_EXIT;

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
	std::string readTask(const std::string);

	//To display welcome message
	//Precondition: display only after program is initialised
	//Post-condition: welcome message is displayed
	void displayWelcomeMessage();

	//To display the tasks to be done for that day
	//Precondition: 
	//Post-condition: 
	void displayTodayTask();

	//To display messages when commands are executed successfully
	//Precondition: function successfully call
	//Post-condition: success message with respect to command will be displayed
	void displaySuccessfulMessage(const std::string);

	//To display messages when commands fail to executed successfully
	//Precondition: function call fail
	//Post-condition: fail message with be displayed
	void displayFailMessage(const std::string);
};