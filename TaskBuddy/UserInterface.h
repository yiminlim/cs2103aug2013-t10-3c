#ifndef _USERINTERFACE_H_
#define _USERINTERFACE_H_

#include <iostream>
#include "TaskLogic.h"

class UserInterface{
private:
	std::string fileName; // "taskBuddyFile.txt"
	TaskLogic tbLogic; // all the commands will be going through tbLogic to change the TaskLinkedList

public:

	UserInterface();

	//~UserInterface();

	//Starts the UserInterface from main.
	//To initialise the taskLinkedList inside tbLogic by sending an initialising command to tbLogic.
	void initUI();
	
	//To read in different commands and the details of task if given, using readTask and readDate. 
	//Given different commands, it calls out the corresponding function in tbLogic.
	void commandUI();
	
	//To read in all details of task, creates a task and passes it to TaskList to be added
	std::string readTask();
	
	//To read in date of task, for a search for relevant task
	std::string readDate();
	
	//To display main menu
	void displayMainMenu();
	
	//To display common messages to User
	void displayMessage(std::string);
	
	//To send a command to tbLogic to write the taskLinkedList to a text file
	void exitUI();
};
#endif;