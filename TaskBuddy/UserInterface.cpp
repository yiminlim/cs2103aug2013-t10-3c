#include "UserInterface.h"

const std::string UserInterface::COMMAND_ADD = "add";
const std::string UserInterface::COMMAND_DELETE = "delete";
const std::string UserInterface::COMMAND_SEARCH = "search";
const std::string UserInterface::COMMAND_EDIT = "edit";
const std::string UserInterface::COMMAND_SAVE = "save";
const std::string UserInterface::COMMAND_EXIT = "exit";
//const std::string COMMAND_DISPLAY = "display";

const std::string UserInterface::MESSAGE_WELCOME = "Welcome to Task Buddy!";
const std::string UserInterface::MESSAGE_ADD = "Task is added";
const std::string UserInterface::MESSAGE_DELETE = "Task is deleted";
const std::string UserInterface::MESSAGE_EDIT = "Task is edited";
const std::string UserInterface::MESSAGE_COMMAND = "command: ";
const std::string UserInterface::MESSAGE_INVALID_COMMAND = "Invalid command";
const std::string UserInterface::MESSAGE_EXIT = "Thank you for using Task Buddy!";

UserInterface::UserInterface(){

}

//Starts the UserInterface from main.
//To initialise the taskLinkedList inside tbLogic by sending an initialising command to tbLogic.
void UserInterface::initUI(){
	tbLogic.initLogic();
	std::cout << MESSAGE_WELCOME << std::endl;
	return;
}
	
//To read in different commands and the details of task if given using readTask.
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
		space = getchar();						//Is it possible for space to obtain a char other than space?

		if (command == COMMAND_ADD){		
			if (tbLogic.add(readTask(command))){
				tbLogic.save();
				displaySuccessfulMessage(COMMAND_ADD);				
			}
			else{
				displayFailMessage();
			}
		}
		else if (command == COMMAND_SEARCH){
			display.clear();
			if (tbLogic.generalSearch(readTask(command), display)){
				for (unsigned int i = 0; i < display.size(); i++){
					std::cout << i+1 << ". " << display[i] << std::endl;
				}
			}
			else{
				displayFailMessage();
			}
		}
		else if (command == COMMAND_DELETE){
			int option;
			std::cin >> option;
			if (tbLogic.del(display[option-1])){
				tbLogic.save();
				displaySuccessfulMessage(COMMAND_DELETE);			
			}
			else{
				displayFailMessage();
			}
		}
		else if (command == COMMAND_EDIT){
			int option;
			std::string editString;
			std::cin >> option;
			std::getline(std::cin, editString);
			editString = "add " + editString; //adding 'add ' to the start 
			if (tbLogic.edit(display[option-1], editString)){
				tbLogic.save();
				displaySuccessfulMessage(COMMAND_EDIT);
			}
			else{
				displayFailMessage();
			}
		}
		else if(command == COMMAND_EXIT){
			tbLogic.exitLogic();
			displaySuccessfulMessage(COMMAND_EXIT);
			contProgram = false;
		}
		else{
			displayFailMessage();
		}		
	} while(contProgram);
}
	
//To read in the task details
std::string UserInterface::readTask(const std::string command){
	std::string task;
	std::getline(std::cin, task);

	if (command == COMMAND_ADD){
		task = command + " " + task;
		if (task.find("blockoff") != std::string::npos){
			std::string block;
			do{
				std::getline(std::cin, block);
				if (block != "end"){
					task = task + " " + block; //add space
				}
			} while(block != "end");
		}	
	}
	return task;
}
	
//To display only successful messages to User
void UserInterface::displaySuccessfulMessage(std::string command){
	if (command == COMMAND_ADD){
		std::cout << MESSAGE_ADD;
	}
	else if (command == COMMAND_DELETE){
		std::cout << MESSAGE_DELETE;
	}
	else if (command == COMMAND_EDIT){
		std::cout << MESSAGE_EDIT;
	}
	else if (command == COMMAND_EXIT){
		std::cout << MESSAGE_EXIT;
	}
	std::cout << std::endl;
}

//To display only fail messages to User
void UserInterface::displayFailMessage(){
	std::cout << MESSAGE_INVALID_COMMAND << std::endl;
}

//To display main menu
//void UserInterface::displayMainMenu(){

//}