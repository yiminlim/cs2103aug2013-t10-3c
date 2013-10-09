#include "UserInterface.h"

const std::string COMMAND_ADD = "add";
const std::string COMMAND_DELETE = "delete";
const std::string COMMAND_SEARCH = "search";
const std::string COMMAND_DISPLAY = "display";
const std::string COMMAND_EXIT = "exit";


const std::string MESSAGE_WELCOME = "Welcome to Task Buddy. ";
const std::string MESSAGE_READY = " is ready for use";
const std::string MESSAGE_COMMAND = "command: ";
const std::string MESSAGE_INVALID_COMMAND = "Invalid command";

UserInterface::UserInterface(){
}

//Starts the UserInterface from main.
//To initialise the taskLinkedList inside tbLogic by sending an initialising command to tbLogic.
void UserInterface::initUI(){
	// display welcome message using displayMessage function
	fileName = "taskBuddyFile.txt";
	//tbLogic.initLogic(fileName);
}
	
//To read in different commands and the details of task if given, using readTask and readDate. 
//Given different commands, it calls out the corresponding function in tbLogic.
void UserInterface::commandUI(){

}
	
//To read in all details of task, creates a task and passes it to TaskList to be added
std::string UserInterface::readTask(){

	return "test";
}
	
//To read in date of task, for a search for relevant task
std::string UserInterface::readDate(){

	return "test";
}
	
//To display main menu
void UserInterface::displayMainMenu(){

}
	
//To display common messages to User
void UserInterface::displayMessage(std::string){

};
	
//To send a command to tbLogic to write the taskLinkedList to a text file
void UserInterface::exitUI(){
	//tbLogic.exitLogic(fileName);
}


