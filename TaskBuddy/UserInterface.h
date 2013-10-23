#pragma once

#include <iostream>
#include "TaskLogic.h"

class UserInterface{
private:
	TaskLogic tbLogic; // all the commands will be going through tbLogic to change the TaskLinkedList


public:
	/*
	const std::string COMMAND_ADD;
	const std::string COMMAND_DELETE;
	const std::string COMMAND_SEARCH;
	const std::string COMMAND_EDIT;
	const std::string COMMAND_SAVE;
	const std::string COMMAND_EXIT;	

	const std::string MESSAGE_WELCOME;
	const std::string MESSAGE_ADD;
	const std::string MESSAGE_DELETE;
	const std::string MESSAGE_EDIT;
	const std::string MESSAGE_COMMAND;
	const std::string MESSAGE_INVALID_COMMAND;
	const std::string MESSAGE_EXIT;
	*/
	
	//Starts the UserInterface from main.
	//To initialise the taskLinkedList inside tbLogic by sending an initialising command to tbLogic.
	UserInterface();

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
	//void displayMainMenu();
};