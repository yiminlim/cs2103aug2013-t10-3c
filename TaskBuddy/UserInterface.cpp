#include "UserInterface.h"

const std::string UserInterface::COMMAND_ADD = "add";
const std::string UserInterface::COMMAND_DELETE = "delete";
const std::string UserInterface::COMMAND_SEARCH = "search";
const std::string UserInterface::COMMAND_EDIT = "edit";
const std::string UserInterface::COMMAND_ADDBLOCK = "addblock";
const std::string UserInterface::COMMAND_EDITBLOCK = "editblock";
const std::string UserInterface::COMMAND_EDITALL = "editall";
const std::string UserInterface::COMMAND_FINALISE = "finalise";
const std::string UserInterface::COMMAND_FINALIZE = "finalize";
const std::string UserInterface::COMMAND_UNDO = "undo";
const std::string UserInterface::COMMAND_CLEAR = "clear";
const std::string UserInterface::COMMAND_EXIT = "exit";

const std::string UserInterface::KEYWORD_TODAY = "today";
const std::string UserInterface::KEYWORD_BLOCKOFF = "blockoff";
const std::string UserInterface::KEYWORD_END = "end";

const std::string UserInterface::MESSAGE_TODAY_TASK = "Task(s) due by TODAY!";
const std::string UserInterface::MESSAGE_NO_TASK_TODAY = "No task due today!";
const std::string UserInterface::MESSAGE_COMMAND = "command: ";
const std::string UserInterface::MESSAGE_ADD = "Task is added";
const std::string UserInterface::MESSAGE_DELETE = "Task is deleted";
const std::string UserInterface::MESSAGE_EDIT = "Task is edited";
const std::string UserInterface::MESSAGE_UNDO = "Previous command is undone";
const std::string UserInterface::MESSAGE_AVAILABLE_BLOCKS = "Available Blocks: ";
const std::string UserInterface::MESSAGE_ADDBLOCK = "All blocking of dates are successful";
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
	int option;
	char space;
	bool contProgram = true;
	bool isClash = false;
	std::string command;
	std::vector<std::string> display;

	do{
		std::cout << MESSAGE_COMMAND;
		std::cin >> command;
		space = getchar();						//Is it possible for space to obtain a char other than space?

		if (command == COMMAND_ADD){		
			if (tbLogic.add(readTask(command, ""), isClash)){
				tbLogic.save();
				displaySuccessfulMessage(command);				
			}
			else{
				displayFailMessage(command);
			}
			display.clear();
		}
		else if (command == COMMAND_SEARCH){
			display.clear();
			if (tbLogic.generalSearch(readTask(command, ""), display)){
				displayInformationInVector(display);
			}
			else{
				displayFailMessage(command);
			}
		}
		else if (command == COMMAND_DELETE){
			std::stringstream ss(readTask(command, ""));
			while (!ss.eof() && ss >> option){
				if (tbLogic.del(display[option-1])){
					tbLogic.save();
					displaySuccessfulMessage(command);			
				}
				else{
					displayFailMessage(command);
				}
			}
			display.clear();
		}
		else if (command == COMMAND_EDIT){
			std::cin >> option;
			if (tbLogic.edit(display[option-1], readTask(COMMAND_EDIT, ""))){
				tbLogic.save();
				displaySuccessfulMessage(command);
			}
			else{
				displayFailMessage(command);
			}
			display.clear();
		}
		else if (command == COMMAND_EDITBLOCK){
			std::cin >> option;
			editBlockUI(display[option-1]);
			display.clear();
			system("CLS");
			displayWelcomeMessage();
		}
		else if (command == COMMAND_UNDO){
			if (tbLogic.undo()){
				displaySuccessfulMessage(command);
			}
			else{
				displayFailMessage(command);
			}
			display.clear();
		}
		else if (command == COMMAND_CLEAR){
			system("CLS");
			display.clear();
		}
		else if (command == COMMAND_EXIT){
			tbLogic.exitLogic();
			displaySuccessfulMessage(command);
			contProgram = false;
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
std::string UserInterface::readTask(const std::string command, const std::string stringToBeAdded){
	std::string task;
	std::string block;

	std::getline(std::cin, task);

	if ((command == COMMAND_ADD || command == COMMAND_ADDBLOCK) && (task.find(KEYWORD_BLOCKOFF) != std::string::npos){
			if (command == COMMAND_ADDBLOCK){
				task = stringToBeAdded + " " + task;
			}

			do{
				std::getline(std::cin, block);
				if (block != COMMAND_END){
					task = task + " " + block; 
				}
			} while(block != COMMAND_END);
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

//To display sub-menu for editing of block off dates of a certain task
void UserInterface::editBlockUI(const std::string stringToEditBlock){
	char space;
	std::string command;
	std::string taskString;
	std::string taskActionLocation;
	std::string originalTaskString = stringToEditBlock;
	std::vector<std::string> blockTaskVector;

	if (tbLogic.getBlock(originalTaskString, taskActionLocation, blockTaskVector)){
		std::cout << MESSAGE_AVAILABLE_BLOCKS << std::endl;
		displayInformationInVector(blockTaskVector);
	}

	std::cout << MESSAGE_COMMAND;
	std::cin >> command;
	space = getchar();

	if (command == COMMAND_ADD){
		std::getline(std::cin, taskString);
		if (taskString.find(COMMAND_BLOCKOFF) != std::string::npos){
			taskString = taskActionLocation + " " + taskString;
			std::string block;
			do{
				std::getline(std::cin, block);
				if (block != COMMAND_END){
					taskString = taskString + " " + block; 
				}
			} while(block != COMMAND_END);
		}	

		if(tbLogic.addBlock(readTask(COMMAND_ADDBLOCK, taskActionLocation), originalTaskString)){
			displaySuccessfulMessage(COMMAND_ADDBLOCK);
		}
		else{
			displayFailMessage("");
		}
	}
	else if (command == COMMAND_EDITALL){
		
	}
	else if (command == COMMAND_DELETE){

	}
	else if (command == COMMAND_FINALISE || command == COMMAND_FINALIZE){

	}
	else{
		displayFailMessage("");
	}
}

//To display all information in a vector
void UserInterface::displayInformationInVector(std::vector<std::string> vec){
	for (unsigned int i = 0; i < vec.size(); i++){
		std::cout << i+1 << ". " << vec[i] << std::endl;
	}
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
	else if (command == COMMAND_ADDBLOCK){
		std::cout << MESSAGE_ADDBLOCK;
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