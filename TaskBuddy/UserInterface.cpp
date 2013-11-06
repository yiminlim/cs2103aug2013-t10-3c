#include "UserInterface.h"

const std::string UserInterface::COMMAND_ADD = "add";
const std::string UserInterface::COMMAND_DELETE = "delete";
const std::string UserInterface::COMMAND_SEARCH = "search";
const std::string UserInterface::COMMAND_EDIT = "edit";
const std::string UserInterface::COMMAND_MARKDONE = "markdone";
const std::string UserInterface::COMMAND_DONE = "done";
const std::string UserInterface::COMMAND_OVERDUE = "overdue";
const std::string UserInterface::COMMAND_CLEAROVERDUE = "clearoverdue";
const std::string UserInterface::COMMAND_EDITBLOCK = "editblock";
const std::string UserInterface::COMMAND_ADDBLOCK = "addblock";
const std::string UserInterface::COMMAND_EDITALL = "editall";
const std::string UserInterface::COMMAND_DELETEBLOCK = "deleteblock";
const std::string UserInterface::COMMAND_FINALISE = "finalise";
const std::string UserInterface::COMMAND_FINALIZE = "finalize";
const std::string UserInterface::COMMAND_UNDO = "undo";
const std::string UserInterface::COMMAND_CLEAR = "clear";
const std::string UserInterface::COMMAND_EXIT = "exit";

const std::string UserInterface::KEYWORD_TODAY = "today";
const std::string UserInterface::KEYWORD_BLOCKOFF = "blockoff";
const std::string UserInterface::KEYWORD_EMPTY_STRING = "";
const std::string UserInterface::KEYWORD_SPACE = " ";
const std::string UserInterface::KEYWORD_BULLETING = ". ";
const std::string UserInterface::KEYWORD_END = "end";

const std::string UserInterface::MESSAGE_TODAY_TASK = "Task(s) due by TODAY!";
const std::string UserInterface::MESSAGE_COMMAND = "command: ";
const std::string UserInterface::MESSAGE_ADD = "Task has been added";
const std::string UserInterface::MESSAGE_CLASH = "Task added clashes with the following task: ";
const std::string UserInterface::MESSAGE_DELETE = "Task has been deleted";
const std::string UserInterface::MESSAGE_EDIT = "Task has been edited";
const std::string UserInterface::MESSAGE_MARKDONE = "Task has been marked done";
const std::string UserInterface::MESSAGE_UNDO = "Previous command is undone";
const std::string UserInterface::MESSAGE_AVAILABLE_BLOCKS = "Available Blocks: ";
const std::string UserInterface::MESSAGE_ADDBLOCK = "All blocking of dates are successful";
const std::string UserInterface::MESSAGE_EDITALL = "Tasks' action and location in the all blocked slots have been edited";
const std::string UserInterface::MESSAGE_DELETEBLOCK = "Requested blocked slot has been deleted";
const std::string UserInterface::MESSAGE_FINALISE = "Time and date of the task has been finalised";
const std::string UserInterface::MESSAGE_EXIT = "Thank you for using Task Buddy!";

const std::string UserInterface::ERROR_NO_TASK_TODAY = "No task due today!";
const std::string UserInterface::ERROR_INVALID_COMMAND = "Invalid command";
const std::string UserInterface::ERROR_SEARCH_BEFORE = "Please search for the task before attempting to delete/ edit/ markdone/ editall";

const std::string UserInterface::MESSAGE_INVALID_ADD = "Task cannot be added";
const std::string UserInterface::MESSAGE_INVALID_SEARCH = "No task is found";
const std::string UserInterface::MESSAGE_INVALID_DELETE = "Task cannot be deleted";
const std::string UserInterface::MESSAGE_INVALID_EDIT = "Task cannot be edited";
const std::string UserInterface::MESSAGE_INVALID_MARKDONE = "Task cannot be marked done";
const std::string UserInterface::MESSAGE_INVALID_DONELIST = "No tasks that are marked done is found";
const std::string UserInterface::MESSAGE_INVALID_UNDO = "Previous command cannot be undone";
const std::string UserInterface::MESSAGE_INVALID_ADDBLOCK = "Blocking of dates has failed";
const std::string UserInterface::MESSAGE_INVALID_EDITALL = "Editing of tasks in all blocked slots has failed";
const std::string UserInterface::MESSAGE_INVALID_DELETEBLOCK = "Deleting of requested blocked slots has failed";
const std::string UserInterface::MESSAGE_INVALID_FINALISE = "Finalising of the time and date of the task has failed"; 



//User interface constructor
UserInterface::UserInterface(){

}

//To initialise the program by calling for TaskLogic initialisation function
void UserInterface::initUI(){
	COORD screenBufferSize = {110, 300};
	SMALL_RECT consoleWindowSize = {0, 0, 109, 50};

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hConsole, screenBufferSize);
	SetConsoleWindowInfo(hConsole, TRUE, &consoleWindowSize);
	TCHAR programTitle[20] = TEXT("Task Buddy");
	SetConsoleTitle(programTitle);

	tbLogic.initLogic();
	displayWelcomeMessage();
	displayTodayTask();
	tbLogic.saveOverdue();
	return;
}
	
//To read in different commands by user and call for the respective TaskLogic function
void UserInterface::commandUI(){
	int option;
	char space;
	bool contProgram = true;
	bool isClash;
	std::string currentCommand, previousCommand = KEYWORD_EMPTY_STRING;
	std::vector<std::string> display;
	std::vector<std::string> doneList;
	std::vector<std::string> overdueList;
	std::vector<std::string> clashVector;
	
	do{
		try{
			std::cout << MESSAGE_COMMAND;
			std::cin >> currentCommand;
			space = getchar();
			isClash = false;

			if ((currentCommand == COMMAND_DELETE || currentCommand == COMMAND_EDIT || currentCommand == COMMAND_MARKDONE || currentCommand == COMMAND_EDITBLOCK) &&
				(previousCommand != COMMAND_SEARCH)){
					throw std::runtime_error(ERROR_SEARCH_BEFORE);
			}

			if (currentCommand == COMMAND_ADD){		
				if (tbLogic.add(readTask(currentCommand, KEYWORD_EMPTY_STRING), isClash, clashVector)){
					displayMessage(currentCommand);
					if (isClash){
						std::cout << MESSAGE_CLASH << std::endl;
						displayInformationInVector(clashVector);
					}
					tbLogic.save();
				}
				else{
					displayFailMessage(currentCommand);
				}
				display.clear();
				clashVector.clear();
			}
			else if (currentCommand == COMMAND_SEARCH){
				display.clear();
				if (tbLogic.generalSearch(readTask(currentCommand, KEYWORD_EMPTY_STRING), display)){
					displayInformationInVector(display);
				}
				else{
					displayFailMessage(currentCommand);
				}
			}
			else if (currentCommand == COMMAND_DELETE){
				std::stringstream ss(readTask(currentCommand, KEYWORD_EMPTY_STRING));
				while (!ss.eof() && ss >> option){
					if (tbLogic.del(display[option-1], false)){
						tbLogic.save();
						displayMessage(currentCommand);			
					}
					else{
						displayFailMessage(currentCommand);
					}
				}
				display.clear();
			}
			else if (currentCommand == COMMAND_EDIT){
				std::cin >> option;
				if (tbLogic.edit(display[option-1], readTask(COMMAND_EDIT, KEYWORD_EMPTY_STRING), isClash, clashVector)){
					displayMessage(currentCommand);
					if (isClash){
						std::cout << MESSAGE_CLASH << std::endl;
						displayInformationInVector(clashVector);
					}
					tbLogic.save();
				}
				else{
					displayFailMessage(currentCommand);
				}
				display.clear();
				clashVector.clear();
			}
			else if (currentCommand == COMMAND_MARKDONE){
				std::stringstream ss(readTask(currentCommand, KEYWORD_EMPTY_STRING));
				while (!ss.eof() && ss >> option){
					if (tbLogic.markDone(display[option-1])){
						tbLogic.save();
						tbLogic.saveDone();
						displayMessage(currentCommand);
					}
					else{
						displayFailMessage(currentCommand);
					}
				}
				display.clear();
			}
			else if (currentCommand == COMMAND_DONE){
				if (tbLogic.retrieveDoneList(doneList)){
					displayInformationInVector(doneList);
				}
				else{
					displayFailMessage(currentCommand);
				}
				doneList.clear();
			}
			else if (currentCommand == COMMAND_OVERDUE){
				if (tbLogic.retrieveOverdueList(overdueList)){
					displayInformationInVector(overdueList);
				}
				overdueList.clear();
			}
			else if (currentCommand == COMMAND_CLEAROVERDUE){
				tbLogic.clearOverdueList();
				tbLogic.saveOverdue();
			}
			else if (currentCommand == COMMAND_EDITBLOCK){
				std::cin >> option;
				system("CLS");
				editBlockUI(display[option-1]);
				display.clear();
				displayWelcomeMessage();
			}
			else if (currentCommand == COMMAND_UNDO){
				if (tbLogic.undo()){
					tbLogic.save();
					tbLogic.saveDone();
					displayMessage(currentCommand);
				}
				else{
					displayFailMessage(currentCommand);
				}
				display.clear();
			}
			else if (currentCommand == COMMAND_CLEAR){
				system("CLS");
				display.clear();
			}
			else if (currentCommand == COMMAND_EXIT){
				displayMessage(currentCommand);
				contProgram = false;
			}
			else{
				throw std::runtime_error(ERROR_INVALID_COMMAND);
			}
		}
		catch (std::runtime_error &error){
			std::cout << error.what() << std::endl;
		}

		previousCommand = currentCommand;

		if (currentCommand != COMMAND_CLEAR){
			std::cout << std::endl;
		}

	} while (contProgram);
}
	
//To read in the details of task (excluding command)
std::string UserInterface::readTask(const std::string command, const std::string stringToBeAdded){
	std::string task;
	std::string block;

	std::getline(std::cin, task);

	if ((command == COMMAND_ADD || command == COMMAND_ADDBLOCK) && (task.find(KEYWORD_BLOCKOFF) != std::string::npos)){
			if (command == COMMAND_ADDBLOCK){
				task = stringToBeAdded + KEYWORD_SPACE + task;
			}

			do{
				std::getline(std::cin, block);
				if (block != KEYWORD_END){
					task = task + KEYWORD_SPACE + block; 
				}
			} while(block != KEYWORD_END);
	}
	return task;
}

//To display welcome message after the program is initialised
void UserInterface::displayWelcomeMessage(){
	std::cout << "=============================================================================================================" << std::endl
			  << "=                                                                                                           =" << std::endl
		      << "=                            ==========       ==         =======    ==    ==                                =" << std::endl
			  << "=                                ==         ==  ==       ==         ==  ==                                  =" << std::endl
			  << "=                                ==        ========      =======    ====                                    =" << std::endl
			  << "=                                ==       ==      ==          ==    ==  ==                                  =" << std::endl
			  << "=                                ==      ==        ==    =======    ==    ==                                =" << std::endl
			  << "=                                                                                                           =" << std::endl
			  << "=                         ======     ==     ==     =====       =====      ==    ==                          =" << std::endl
			  << "=                         ==   ==    ==     ==     ==   ==     ==   ==     ==  ==                           =" << std::endl
			  << "=                         ======     ==     ==     ==    ==    ==    ==     ====                            =" << std::endl
			  << "=                         ==   ==    ==     ==     ==   ==     ==   ==       ==                             =" << std::endl
			  << "=                         ======       =====       =====       =====         ==                             =" << std::endl
			  << "=                                                                                                           =" << std::endl
			  << "=============================================================================================================" << std::endl;
}

//To display the tasks to be done for that day
void UserInterface::displayTodayTask(){
	std::vector<std::string> todayTask;
	try{
		if (tbLogic.generalSearch(KEYWORD_TODAY, todayTask)){
			std::cout << MESSAGE_TODAY_TASK << std::endl;
			for (unsigned int i = 0; i < todayTask.size(); i++){
				if (i < 9){ 
					std::cout << KEYWORD_SPACE;
				}
				std::cout << i+1 << KEYWORD_BULLETING << todayTask[i] << std::endl;
			}
		}
		else{
			throw std::runtime_error(ERROR_NO_TASK_TODAY);
		}
	}
	catch (std::runtime_error &error){
		std::cout << error.what() << std::endl;
	}
	std::cout << std::endl;
}

//To display sub-menu for editing of block off dates of a certain task
void UserInterface::editBlockUI(const std::string stringToEditBlock){
	char space;
	int option;
	bool isClash = false;
	std::string command;
	std::string taskString;
	std::string taskActionLocation;
	std::string originalTaskString = stringToEditBlock;
	std::vector<std::string> blockTaskVector;
	std::vector<std::string> clashVector;

	if (tbLogic.getBlock(originalTaskString, taskActionLocation, blockTaskVector)){
		std::cout << MESSAGE_AVAILABLE_BLOCKS << std::endl;
		displayInformationInVector(blockTaskVector);
		std::cout << std::endl;
	}

	std::cout << MESSAGE_COMMAND;
	std::cin >> command;
	space = getchar();
	
	try{
		if (command == COMMAND_ADD){
			command = COMMAND_ADDBLOCK;
			if (tbLogic.addBlock(readTask(command, taskActionLocation), originalTaskString, isClash, clashVector)){
				displayMessage(command);
				if (isClash){
					std::cout << MESSAGE_CLASH << std::endl;
					displayInformationInVector(clashVector);
				}
				tbLogic.save();
				clashVector.clear();
			}
			else{
				displayFailMessage(command);
			}
		}
		else if (command == COMMAND_EDITALL){
			if (tbLogic.editBlock(readTask(command, KEYWORD_EMPTY_STRING), blockTaskVector)){
				tbLogic.save();
				displayMessage(command);
			}		
			else{
				displayFailMessage(command);
			}
		}
		else if (command == COMMAND_DELETE){
			command = COMMAND_DELETEBLOCK;
			std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
			while (!ss.eof() && ss >> option){
				if (tbLogic.del(blockTaskVector[option-1], false)){
					tbLogic.save();
					displayMessage(command);			
				}
				else{
					displayFailMessage(command);
				}
			}
		}
		else if (command == COMMAND_FINALISE || command == COMMAND_FINALIZE){
			std::cin >> option;
			if (tbLogic.finaliseBlock(option, blockTaskVector)){
				tbLogic.save();
				displayMessage(command);
			}
			else{
				displayFailMessage(command);
			}
		}
		else{
			throw std::runtime_error(ERROR_INVALID_COMMAND);
		}
	}
	catch (std::runtime_error &error){
		std::cout << error.what() << std::endl;
	}
	system("PAUSE");
	system("CLS");
}

//To display all information in a vector
void UserInterface::displayInformationInVector(std::vector<std::string> vec){
	for (unsigned int i = 0; i < vec.size(); i++){
		if (i < 9){
			std::cout << KEYWORD_SPACE;
		}
		std::cout << i+1 << KEYWORD_BULLETING << vec[i] << std::endl;
	}
}

//To display messages when commands are executed successfully
void UserInterface::displayMessage(const std::string command){
	if (command == COMMAND_ADD){
		std::cout << MESSAGE_ADD;
	}
	else if (command == COMMAND_DELETE){
		std::cout << MESSAGE_DELETE;
	}
	else if (command == COMMAND_EDIT){
		std::cout << MESSAGE_EDIT;
	}
	else if (command == COMMAND_MARKDONE){
		std::cout << MESSAGE_MARKDONE;
	}
	else if (command == COMMAND_UNDO){
		std::cout << MESSAGE_UNDO;
	}
	else if (command == COMMAND_ADDBLOCK){
		std::cout << MESSAGE_ADDBLOCK;
	}
	else if (command == COMMAND_EDITALL){
		std::cout << MESSAGE_EDITALL;
	}
	else if (command == COMMAND_DELETEBLOCK){
		std::cout << MESSAGE_DELETEBLOCK;
	}
	else if (command == COMMAND_FINALISE || command == COMMAND_FINALIZE){
		std::cout << MESSAGE_FINALISE;
	}
	else if (command == COMMAND_EXIT){
		std::cout << MESSAGE_EXIT;
	}
	std::cout << std::endl;
}

//To display messages when commands fail to execute successfully
void UserInterface::displayFailMessage(const std::string command){
	if (command == COMMAND_ADD){
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
	else if (command == COMMAND_MARKDONE){
		std::cout << MESSAGE_INVALID_MARKDONE << std::endl;
	}
	else if (command == COMMAND_DONE){
		std::cout << MESSAGE_INVALID_DONELIST << std::endl;
	}
	else if (command == COMMAND_UNDO){
		std::cout << MESSAGE_INVALID_UNDO << std::endl;
	}
	else if (command == COMMAND_ADDBLOCK){
		std::cout << MESSAGE_INVALID_ADDBLOCK << std::endl;
	}
	else if (command == COMMAND_EDITALL){
		std::cout << MESSAGE_INVALID_EDITALL << std::endl;
	}
	else if (command == COMMAND_DELETEBLOCK){
		std::cout << MESSAGE_INVALID_DELETEBLOCK << std::endl;
	}
	else if (command == COMMAND_FINALISE || command == COMMAND_FINALIZE){
		std::cout << MESSAGE_INVALID_FINALISE << std::endl;
	}
}