#pragma once

#include <iostream>
#include "TaskLogic.h"

class UserInterface{
private:
	TaskLogic tbLogic; // all the commands will be going through tbLogic to change the TaskLinkedList

	static const std::string COMMAND_ADD;
	static const std::string COMMAND_DELETE;
	static const std::string COMMAND_SEARCH;
	static const std::string COMMAND_EXIT;	
	static const std::string COMMAND_FAIL;
	static const std::string COMMAND_SAVE;

	static const std::string MESSAGE_WELCOME;
	static const std::string MESSAGE_ADD;
	static const std::string MESSAGE_DELETE;
	static const std::string MESSAGE_COMMAND;
	static const std::string MESSAGE_INVALID_COMMAND;
	static const std::string MESSAGE_EXIT;

public:

	//Starts the UserInterface from main.
	//To initialise the taskLinkedList inside tbLogic by sending an initialising command to tbLogic.
	void initUI();
	
	//To read in different commands and the details of task if given, using readTask and readDate. 
	//Given different commands, it calls out the corresponding function in tbLogic.
	void commandUI();
	
	//To read in the task details
	std::string readTask(std::string);

	//To display only successful messages to User
	void displaySuccessfulMessage(std::string);

	//To display only fail messages to User
	void displayFailMessage();
	
	//To display main menu
	void displayMainMenu();
};