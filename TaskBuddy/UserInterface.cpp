#include "UserInterface.h"

const std::string UserInterface::COMMAND_ADD = "add";
const std::string UserInterface::COMMAND_DELETE = "delete";
const std::string UserInterface::COMMAND_SEARCH = "search";
const std::string UserInterface::COMMAND_EDIT = "edit";
const std::string UserInterface::COMMAND_UNDO = "undo";
const std::string UserInterface::COMMAND_CLEAR = "clear";
const std::string UserInterface::COMMAND_EXIT = "exit";

const std::string UserInterface::KEYWORD_TODAY = "today";

const std::string UserInterface::MESSAGE_TODAY_TASK = "Task(s) due by TODAY!";
const std::string UserInterface::MESSAGE_NO_TASK_TODAY = "No task due today!";
const std::string UserInterface::MESSAGE_COMMAND = "command: ";
const std::string UserInterface::MESSAGE_ADD = "Task is added";
const std::string UserInterface::MESSAGE_DELETE = "Task is deleted";
const std::string UserInterface::MESSAGE_EDIT = "Task is edited";
const std::string UserInterface::MESSAGE_UNDO = "Previous command is undone";
const std::string UserInterface::MESSAGE_INVALID_ADD = "Task cannot be added";
const std::string UserInterface::MESSAGE_INVALID_SEARCH = "No task is found";
const std::string UserInterface::MESSAGE_INVALID_DELETE = "Task cannot be deleted";
const std::string UserInterface::MESSAGE_INVALID_EDIT = "Task cannot be edited";
const std::string UserInterface::MESSAGE_INVALID_UNDO = "Previous command cannot be undone";
const std::string UserInterface::MESSAGE_INVALID_COMMAND = "Invalid command";
const std::string UserInterface::MESSAGE_EXIT = "Thank you for using Task Buddy!";

//User interface constructor
UserInterface::UserInterface(){

}

//To initialise the program by calling for TaskLogic initialisation function
void UserInterface::initUI(){
	tbLogic.initLogic();
	displayWelcomeMessage();
	displayTodayTask();
	return;
}
	
//To read in different commands by user and call for the respective TaskLogic function
void UserInterface::commandUI(){
	std::string command;
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
				displaySuccessfulMessage(command);				
			}
			else{
				displayFailMessage(command);
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
				displayFailMessage(command);
			}
		}
		else if (command == COMMAND_DELETE){
			int option;
			std::cin >> option;
			if (tbLogic.del(display[option-1])){
				tbLogic.save();
				displaySuccessfulMessage(command);			
			}
			else{
				displayFailMessage(command);
			}
		}
		else if (command == COMMAND_EDIT){
			int option;
			std::string editString;
			std::cin >> option;
			editString = "add " + readTask(COMMAND_EDIT); //adding 'add ' to the start 
			if (tbLogic.edit(display[option-1], editString)){
				tbLogic.save();
				displaySuccessfulMessage(command);
			}
			else{
				displayFailMessage(command);
			}
		}
		else if (command == COMMAND_EXIT){
			tbLogic.exitLogic();
			displaySuccessfulMessage(command);
			contProgram = false;
		}
		/*
		else if (command == COMMAND_UNDO){
			if (tbLogic.undo()){
				displaySuccessfulMessage(command);
			}
			else{
				displayFailMessage(command);
			}
		}
		*/
		else if (command == COMMAND_CLEAR){
			system("CLS");
		}
		else{
			displayFailMessage("");
		}

		if (command != COMMAND_CLEAR){
			std::cout << std::endl;
		}

	} while(contProgram);
}
	
//To read in the details of task (excluding command)
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
					task = task + " " + block; 
				}
			} while(block != "end");
		}	
	}
	return task;
}

//To display welcome message after the program is initialised
void UserInterface::displayWelcomeMessage(){
	std::cout << "===========================================================================" << std::endl
			  << "=                                                                         =" << std::endl
		      << "=           ==========       ==         =======    ==    ==               =" << std::endl
			  << "=               ==         ==  ==       ==         ==  ==                 =" << std::endl
			  << "=               ==        ========      =======    ====                   =" << std::endl
			  << "=               ==       ==      ==          ==    ==  ==                 =" << std::endl
			  << "=               ==      ==        ==    =======    ==    ==               =" << std::endl
			  << "=                                                                         =" << std::endl
			  << "=        ======     ==     ==     =====       =====      ==    ==         =" << std::endl
			  << "=        ==   ==    ==     ==     ==   ==     ==   ==     ==  ==          =" << std::endl
			  << "=        ======     ==     ==     ==    ==    ==    ==     ====           =" << std::endl
			  << "=        ==   ==    ==     ==     ==   ==     ==   ==       ==            =" << std::endl
			  << "=        ======       =====       =====       =====         ==            =" << std::endl
			  << "=                                                                         =" << std::endl
			  << "===========================================================================" << std::endl;
}

//To display the tasks to be done for that day
void UserInterface::displayTodayTask(){
	std::vector<std::string> todayTask;

	if (tbLogic.generalSearch(KEYWORD_TODAY, todayTask)){
		std::cout << MESSAGE_TODAY_TASK << std::endl;
		for (unsigned int i = 0; i < todayTask.size(); i++){
			std::cout << i+1 << ". " << todayTask[i] << std::endl;
		}
	}
	else{
		displayFailMessage(KEYWORD_TODAY);
	}
	std::cout << std::endl;
}
	
//To display messages when commands are executed successfully
void UserInterface::displaySuccessfulMessage(const std::string command){
	if (command == COMMAND_ADD){
		std::cout << MESSAGE_ADD;
	}
	else if (command == COMMAND_DELETE){
		std::cout << MESSAGE_DELETE;
	}
	else if (command == COMMAND_EDIT){
		std::cout << MESSAGE_EDIT;
	}
	else if (command == COMMAND_UNDO){
		std::cout << MESSAGE_UNDO;
	}
	else if (command == COMMAND_EXIT){
		std::cout << MESSAGE_EXIT;
	}
	std::cout << std::endl;
}

//To display messages when commands fail to execute successfully
void UserInterface::displayFailMessage(const std::string command){
	if (command == KEYWORD_TODAY){
		std::cout << MESSAGE_NO_TASK_TODAY << std::endl;
	}
	else if (command == COMMAND_ADD){
		std::cout << MESSAGE_INVALID_ADD << std::endl;
	}
	else if (command == COMMAND_SEARCH){
		std::cout << MESSAGE_INVALID_SEARCH << std::endl;
	}
	else if (command == COMMAND_DELETE){
		std::cout << MESSAGE_INVALID_DELETE << std::endl;
	}
	else if (command == COMMAND_EDIT){
		std::cout << MESSAGE_INVALID_EDIT << std::endl;
	}
	else if (command == COMMAND_UNDO){
		std::cout << MESSAGE_INVALID_UNDO << std::endl;
	}
	else{
		std::cout << MESSAGE_INVALID_COMMAND << std::endl;
	}
}