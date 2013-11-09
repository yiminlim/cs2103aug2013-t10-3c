#include "UserInterface.h"

const std::string UserInterface::COMMAND_ADD = "add";
const std::string UserInterface::COMMAND_DELETE = "delete";
const std::string UserInterface::COMMAND_SEARCH = "search";
const std::string UserInterface::COMMAND_EDIT = "edit";
const std::string UserInterface::COMMAND_EDITBLOCK = "editblock";
const std::string UserInterface::COMMAND_EDITALL = "editall";
const std::string UserInterface::COMMAND_ADDBLOCK = "addblock";
const std::string UserInterface::COMMAND_DELETEBLOCK = "deleteblock";
const std::string UserInterface::COMMAND_FINALISE = "finalise";
const std::string UserInterface::COMMAND_FINALIZE = "finalize";
const std::string UserInterface::COMMAND_RETURN = "return";
const std::string UserInterface::COMMAND_MARKDONE = "markdone";
const std::string UserInterface::COMMAND_DONE = "done";
const std::string UserInterface::COMMAND_OVERDUE = "overdue";
const std::string UserInterface::COMMAND_CLEAROVERDUE = "clearoverdue";
const std::string UserInterface::COMMAND_UNDO = "undo";
const std::string UserInterface::COMMAND_CLEAR = "clear";
const std::string UserInterface::COMMAND_HELP = "help";
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
const std::string UserInterface::MESSAGE_AVAILABLE_BLOCKS = "Available Blocks: ";
const std::string UserInterface::MESSAGE_ADDBLOCK = "All blocking of dates are successful";
const std::string UserInterface::MESSAGE_EDITALL = "Tasks' action and location in the all blocked slots have been edited";
const std::string UserInterface::MESSAGE_DELETEBLOCK = "Requested blocked slot has been deleted";
const std::string UserInterface::MESSAGE_FINALISE = "Time and date of the task has been finalised";
const std::string UserInterface::MESSAGE_MARKDONE = "Task has been marked done";
const std::string UserInterface::MESSAGE_UNDO = "Previous command is undone";
const std::string UserInterface::MESSAGE_CLEAROVERDUE = "Overdue list is cleared";
const std::string UserInterface::MESSAGE_EXIT = "Thank you for using Task Buddy!";

const std::string UserInterface::ERROR_NO_TASK_TODAY = "No task due today!";
const std::string UserInterface::ERROR_INVALID_COMMAND = "Invalid command";
const std::string UserInterface::ERROR_SEARCH_BEFORE = "Please search for the task before attempting to delete/ edit/ markdone/ editall";
const std::string UserInterface::ERROR_OUT_OF_VECTOR_RANGE = "Please input a number within the range of the search";
const std::string UserInterface::ERROR_UNDO_INITIALISE = "No existing commands to undo";

const std::string UserInterface::MESSAGE_INVALID_ADD = "Task cannot be added";
const std::string UserInterface::MESSAGE_INVALID_SEARCH = "No task is found";
const std::string UserInterface::MESSAGE_INVALID_DELETE = "Task cannot be deleted";
const std::string UserInterface::MESSAGE_INVALID_EDIT = "Task cannot be edited";
const std::string UserInterface::MESSAGE_INVALID_MARKDONE = "Task cannot be marked done";
const std::string UserInterface::MESSAGE_INVALID_DONE = "No tasks that are marked done is found";
const std::string UserInterface::MESSAGE_INVALID_OVERDUE = "No tasks that are overdue is found";
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
	tbLogic.saveOverdue();
	tbLogic.save();
	displayWelcomeMessage();
	std::cout << std::endl;
	displayTodayTask();	
	return;
}
	
//To read in different commands by user and call for the respective TaskLogic function
void UserInterface::commandUI(){
	unsigned int option;
	char space;
	bool contProgram = true;
	bool isClash;
	std::string command;
	std::vector<std::string> searchTaskVector;
	std::vector<std::string> searchOtherTaskVector;
	std::vector<std::string> clashVector;
	
	do{
		try{
			std::cout << MESSAGE_COMMAND;
			std::cin >> command;
			isClash = false;
			space = getchar();

			// throw exception if user did not search before delete/ edit/ mark done/ edit block
			if ((command == COMMAND_DELETE || command == COMMAND_EDIT || command == COMMAND_MARKDONE || command == COMMAND_EDITBLOCK) &&
				(searchTaskVector.size() == 0)){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					throw std::runtime_error(ERROR_SEARCH_BEFORE);
			}
			// throw exception if user try to undo when undo stack is empty
			else if ((command == COMMAND_UNDO) && (tbLogic.checkUndoStackEmpty())){
				throw std::runtime_error(ERROR_UNDO_INITIALISE);
			}

			if (command == COMMAND_ADD){		
				if (tbLogic.add(readTask(command, KEYWORD_EMPTY_STRING), isClash, clashVector)){
					displayMessage(command);
					if (isClash){
						std::cout << MESSAGE_CLASH << std::endl;
						displayInformationInVector(clashVector);
					}
					tbLogic.save();
				}
				else{
					displayFailMessage(command);
				}
				searchTaskVector.clear();
				clashVector.clear();
			}
			else if (command == COMMAND_SEARCH){
				searchTaskVector.clear();
				if (tbLogic.generalSearch(readTask(command, KEYWORD_EMPTY_STRING), searchTaskVector)){
					displayInformationInVector(searchTaskVector);
				}
				else{
					displayFailMessage(command);
				}
			}
			else if (command == COMMAND_DELETE){
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				while (!ss.eof() && ss >> option){
					if (option > searchTaskVector.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
					else if (tbLogic.del(searchTaskVector[option-1], false)){
						tbLogic.save();
						displayMessage(command);			
					}
					else{
						displayFailMessage(command);
					}
				}
				searchTaskVector.clear();
			}
			else if (command == COMMAND_EDIT){
				std::cin >> option;
				if (option > searchTaskVector.size()){
					throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
				}
				else if (tbLogic.edit(searchTaskVector[option-1], readTask(COMMAND_EDIT, KEYWORD_EMPTY_STRING), isClash, clashVector)){
					displayMessage(command);
					if (isClash){
						std::cout << MESSAGE_CLASH << std::endl;
						displayInformationInVector(clashVector);
					}
					tbLogic.save();
				}
				else{
					displayFailMessage(command);
				}
				searchTaskVector.clear();
				clashVector.clear();
			}
			else if (command == COMMAND_EDITBLOCK){
				std::cin >> option;

				if (option > searchTaskVector.size()){
					throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
				}
				
				system("CLS");
				editBlockUI(searchTaskVector[option-1]);
				searchTaskVector.clear();
				displayWelcomeMessage();
			}
			else if (command == COMMAND_MARKDONE){
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				while (!ss.eof() && ss >> option){
					if (option > searchTaskVector.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
					else if (tbLogic.markDone(searchTaskVector[option-1])){
						tbLogic.save();
						tbLogic.saveDone();
						displayMessage(command);
					}
					else{
						displayFailMessage(command);
					}
				}
				searchTaskVector.clear();
			}
			else if (command == COMMAND_DONE){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}

				if (tbLogic.retrieveDoneList(searchOtherTaskVector)){
					displayInformationInVector(searchOtherTaskVector);
				}
				else{
					displayFailMessage(command);
				}
				searchOtherTaskVector.clear();
			}
			else if (command == COMMAND_OVERDUE){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}

				if (tbLogic.retrieveOverdueList(searchOtherTaskVector)){
					displayInformationInVector(searchOtherTaskVector);
				}
				else{
					displayFailMessage(command);
				}
				searchOtherTaskVector.clear();
			}
			else if (command == COMMAND_CLEAROVERDUE){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				tbLogic.clearOverdueList();
				tbLogic.saveOverdue();
				displayMessage(command);
			}
			else if (command == COMMAND_UNDO){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}

				if (tbLogic.undo()){
					tbLogic.save();
					tbLogic.saveDone();
					displayMessage(command);
				}
				else{
					displayFailMessage(command);
				}
				searchTaskVector.clear();
			}
			else if (command == COMMAND_CLEAR){
				system("CLS");
				searchTaskVector.clear();
			}
			else if (command == COMMAND_HELP){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				displayHelpCommandUI();
			}
			else if (command == COMMAND_EXIT){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				displayMessage(command);
				contProgram = false;
			}
			else{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				throw std::runtime_error(ERROR_INVALID_COMMAND);
			}
		}
		catch (std::runtime_error &error){
			std::cout << error.what() << std::endl;
		}

		if (command != COMMAND_CLEAR){
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

//To display sub-menu for editing of block off dates of a certain task
void UserInterface::editBlockUI(const std::string stringToEditBlock){
	char space;
	unsigned int option;
	bool isClash = false;
	bool contEditBlock = true;
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

	do{
		try{
			std::cout << MESSAGE_COMMAND;
			std::cin >> command;
			space = getchar();

			if (command == COMMAND_ADD){
				command = COMMAND_ADDBLOCK;
				if (tbLogic.addBlock(readTask(command, taskActionLocation), originalTaskString, isClash, clashVector)){
					tbLogic.save();
					displayMessage(command);
					if (isClash){
						std::cout << MESSAGE_CLASH << std::endl;
						displayInformationInVector(clashVector);
					}					
					clashVector.clear();
					contEditBlock = false;
				}
				else{
					displayFailMessage(command);
				}
			}
			else if (command == COMMAND_EDITALL){
				if (tbLogic.editBlock(readTask(command, KEYWORD_EMPTY_STRING), blockTaskVector)){
					tbLogic.save();
					displayMessage(command);
					contEditBlock = false;
				}		
				else{
					displayFailMessage(command);
				}
			}
			else if (command == COMMAND_DELETE){
				command = COMMAND_DELETEBLOCK;
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				while (!ss.eof() && ss >> option){
					if (option > blockTaskVector.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
					else if (tbLogic.del(blockTaskVector[option-1], false)){
						tbLogic.save();
						displayMessage(command);
						contEditBlock = false;
					}
					else{
						displayFailMessage(command);
					}
				}
			}
			else if (command == COMMAND_FINALISE || command == COMMAND_FINALIZE){
				std::cin >> option;
				if (option > blockTaskVector.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
				}
				else if (tbLogic.finaliseBlock(option, blockTaskVector)){
					tbLogic.save();
					displayMessage(command);
					contEditBlock = false;
				}
				else{
					displayFailMessage(command);
				}
			}
			else if (command == COMMAND_HELP){
				displayHelpEditBlockUI();
			}
			else if (command == COMMAND_RETURN){
				contEditBlock = false;
			}
			else{
				throw std::runtime_error(ERROR_INVALID_COMMAND);
			}
		}
		catch (std::runtime_error &error){
			std::cout << error.what() << std::endl;
		}
		std::cout << std::endl;
	} while (contEditBlock);
	
	system("PAUSE");
	system("CLS");
}

//To display welcome message after the program is initialised
void UserInterface::displayWelcomeMessage(){
	std::cout << "@===========================================================================================================@" << std::endl
			  << "(                                                                                                           )" << std::endl
		      << " )                           **********       **         *******    **    **                               ( " << std::endl
			  << "(                                **         **  **       **         **  **                                  )" << std::endl
			  << " )                               **        ********      *******    ****                                   ( " << std::endl
			  << "(                                **       **      **          **    **  **                                  )" << std::endl
			  << " )                               **      **        **    *******    **    **                               ( " << std::endl
			  << "(                                                                                                           )" << std::endl
			  << " )                        ******     **     **     *****       *****      **    **                         ( " << std::endl
			  << "(                         **   **    **     **     **   **     **   **     **  **                           )" << std::endl
			  << " )                        ******     **     **     **    **    **    **     ****                           ( " << std::endl
			  << "(                         **   **    **     **     **   **     **   **       **                             )" << std::endl
			  << " )                        ******       *****       *****       *****         **                            ( " << std::endl
			  << "(                                                                                                           )" << std::endl
			  << "@===========================================================================================================@" << std::endl;
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
	else if(command == COMMAND_CLEAROVERDUE){
		std::cout << MESSAGE_CLEAROVERDUE;
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
		std::cout << MESSAGE_INVALID_DONE << std::endl;
	}
	else if (command == COMMAND_OVERDUE){
		std::cout << MESSAGE_INVALID_OVERDUE << std::endl;
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

//To display the help message for commandUI
void UserInterface::displayHelpCommandUI(){
	std::cout << "@-----------------------------------------------------------------------------------------------------------@" << std::endl
       		  << "|To add(timed tasks): add \"action\" at \"location\" from dd/mm/yyyy hhmm to dd/mm/yyyy hhmm                      |" << std::endl
			  << "|Example: add swimming at school from 20/11/2013 0900 to 20/11/2013 1000                                     " <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To add(deadline tasks): add \"action\" at \"location\" by dd/mm/yyyy hhmm                                      |" << std::endl
			  << "|Example: add do homework at home by 20/11/2013 2000                                                        |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To add(floating tasks): add \"action\" at \"location\"                                                         |" << std::endl
			  << "|Example: add play computer game at home                                                                    |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To add(block off time slots): add \"action\" at \"location\" blockoff [press ENTER]                            |" << std::endl
			  << "|                            : from dd/mm/yyyy hhmm to dd/mm/yyyy hhmm [press ENTER]                        |" << std::endl
			  << "|                            : by dd/mm/yyyy hhmm [press ENTER]                                             |" << std::endl
			  << "|                            : end                                                                          |" << std::endl
			  << "|Example: add swimming at school blockoff                                                                   |" << std::endl
			  << "|       : from 20/11/2013 1100 to 20/11/2013 1200                                                           |" << std::endl
			  << "|       : by 21/11/2013 1000                                                                                |" << std::endl
			  << "|       : end                                                                                               |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To search for task: search \"keyword\"                                                                       |" << std::endl
			  << "|Example: search home                                                                                       |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To delete a task: delete \"option\"                                                                          |" << std::endl
			  << "|Example: delete 1                                                                                          |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To edit a task: edit \"option\" \"changes in task\"                                                            |" << std::endl
			  << "|Example: edit 1 running at school                                                                          |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To edit tasks with block off timings: editblock \"option\"                                                   |" <<std::endl
			  << "|Example: editblock 1                                                                                       |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To mark done a task: markdone \"option\"                                                                     |" << std::endl
			  << "|Example: markdone 1                                                                                        |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To see completed tasks: done                                                                               |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To see overdue tasks: overdue                                                                              |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To clear overdue tasks list: clearoverdue                                                                  |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To undo previous command: undo                                                                             |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To clear display screen: clear                                                                             |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To exit program: exit                                                                                      |" << std::endl
			  << "@-----------------------------------------------------------------------------------------------------------@" << std::endl;
}

//To display the help message for editBlockUI
void UserInterface::displayHelpEditBlockUI(){
	std::cout << "@-----------------------------------------------------------------------------------------------------------@" << std::endl
			  << "|To add: add blockoff [press ENTER]                                                                         |" << std::endl
			  << "|      : from dd/mm/yyyy hhmm to dd/mm/yyyy hhmm [press ENTER]                                              |" << std::endl
			  << "|      : by dd/mm/yyyy hhmm                                                                                 |" << std::endl
			  << "|      : end                                                                                                |" << std::endl
		   	  << "|Example: add blockoff                                                                                      |" << std::endl
			  << "|       : from 20/11/2013 1100 to 20/11/2013 1200                                                           |" << std::endl
			  << "|       : by 21/11/2013 1000                                                                                |" << std::endl
			  << "|       : end                                                                                               |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To edit action and location of all block off: editall \"action\" at \"location\"                             |" << std::endl
			  << "|Example: editall running at school                                                                         |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To delete: delete \"option\"                                                                                 |" << std::endl
			  << "|Example: delete 1                                                                                          |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To finalise time slot for task: finalise \"option\"                                                          |" << std::endl
			  << "|Example: finalise 1 (option 1 is the time slot that user wants)                                            |" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|To return to main menu: return                                                                             |" << std::endl
			  << "@-----------------------------------------------------------------------------------------------------------@" << std::endl;
}