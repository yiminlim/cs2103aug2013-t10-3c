#include "UserInterface.h"

const std::string COMMAND_ADD = "add";
const std::string COMMAND_DELETE = "delete";
const std::string COMMAND_SEARCH = "search";
//const std::string COMMAND_DISPLAY = "display";
const std::string COMMAND_EXIT = "exit";
const std::string COMMAND_FAIL = "fail";
const std::string COMMAND_SAVE = "save";

const std::string MESSAGE_WELCOME = "Welcome to Task Buddy!";
const std::string MESSAGE_ADD = "Task is added";
const std::string MESSAGE_DELETE = "Task is deleted";
//const std::string MESSAGE_READY = " is ready for use";
const std::string MESSAGE_COMMAND = "command: ";
const std::string MESSAGE_INVALID_COMMAND = "Invalid command";
const std::string MESSAGE_EXIT = "Thank you for using Task Buddy!";

UserInterface::UserInterface(){
}

//Starts the UserInterface from main.
//To initialise the taskLinkedList inside tbLogic by sending an initialising command to tbLogic.
void UserInterface::initUI(){
	tbLogic.initLogic();
	std::cout << MESSAGE_WELCOME << std::endl;
	return;
}
	
//To read in different commands and the details of task if given, using readTask and readDate. 
//Given different commands, it calls out the corresponding function in tbLogic.
void UserInterface::commandUI(){
	std::string command;
	std::string task;
	char space;
	bool contProgram = true;
	std::vector<std::string> display;

	do{
		std::cout << MESSAGE_COMMAND;
		std::cin >> command;
		space = getchar();

		if (command == COMMAND_ADD){		
			if (tbLogic.add(readTask(command))){
				displayMessage(COMMAND_ADD);
			}
			else{
				displayMessage(COMMAND_FAIL);
			}
		}
		else if (command == COMMAND_SEARCH){
			display.clear();
			if (tbLogic.generalSearch(readTask(command), display)){
				for (unsigned int i=0; i<display.size(); i++){
					std::cout << i+1 << ". " << display[i] << std::endl;
				}
			}
			else{
				displayMessage(COMMAND_FAIL);
			}
		}
		else if (command == COMMAND_DELETE){
			int option;
			std::cin >> option;
			if (tbLogic.del(display[option-1])){
				displayMessage(COMMAND_DELETE);			
			}
			else{
				displayMessage(COMMAND_FAIL);
			}
		}
		else if (command == COMMAND_SAVE){
			tbLogic.save();
		}
		else if(command == COMMAND_EXIT){
			exitUI();
			contProgram = false;
		}
		else{
			displayMessage(COMMAND_FAIL);
		}		
	} while(contProgram);
}
	
//To read in the task details
std::string UserInterface::readTask(std::string command){
	std::string task;
	std::getline(std::cin, task);
	if (command == COMMAND_ADD){
		return command + " " + task;
	}
	return task;
}
	
/*To read in date of task, for a search for relevant task
std::string UserInterface::readDate(){

	return "test";
}*/
	
//To display main menu
void UserInterface::displayMainMenu(){

}
	
//To display common messages to User
void UserInterface::displayMessage(std::string message){
	if (message == COMMAND_ADD){
		std::cout << MESSAGE_ADD;
	}
	else if (message == COMMAND_DELETE){
		std::cout << MESSAGE_DELETE;
	}
	else if (message == COMMAND_FAIL){
		std::cout << MESSAGE_INVALID_COMMAND;
	}
	std::cout << std::endl;

}
	
//To send a command to tbLogic to write the taskLinkedList to a text file
void UserInterface::exitUI(){
	tbLogic.exitLogic();
	std::cout << MESSAGE_EXIT;
}