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
const std::string UserInterface::KEYWORD_QUOTE = "\"";
const std::string UserInterface::KEYWORD_END = "end";
const std::string UserInterface::KEYWORD_EQUAL_LEFT = "===[ ";
const std::string UserInterface::KEYWORD_EQUAL_RIGHT = " ]===";

const std::string UserInterface::MESSAGE_TODAY_TASK = "Task(s) due by TODAY!";
const std::string UserInterface::MESSAGE_COMMAND = "command: ";
const std::string UserInterface::MESSAGE_ADD = " has been added";
const std::string UserInterface::MESSAGE_CLASH = "Task added clashes with the following task: ";
const std::string UserInterface::MESSAGE_DELETE = " has been deleted";
const std::string UserInterface::MESSAGE_EDIT = "has been edited to";
const std::string UserInterface::MESSAGE_AVAILABLE_BLOCKS = "Available Blocks: ";
const std::string UserInterface::MESSAGE_EDITALL = "Task's action and location of all blocked slots have been edited to ";
const std::string UserInterface::MESSAGE_FINALISE = " has been finalised";
const std::string UserInterface::MESSAGE_MARKDONE = " has been marked done";
const std::string UserInterface::MESSAGE_UNDONE = " has been marked undone";
const std::string UserInterface::MESSAGE_CLEAROVERDUE = "Overdue list is cleared";
const std::string UserInterface::MESSAGE_CLEAR = "Display screen is cleared";
const std::string UserInterface::MESSAGE_EXIT = "Thank you for using Task Buddy!";

const std::string UserInterface::ERROR_INVALID_COMMAND = "Invalid command";
const std::string UserInterface::ERROR_SEARCH_BEFORE = "Please search for the task before attempting to delete/ edit/ markdone/ editall";
const std::string UserInterface::ERROR_OUT_OF_VECTOR_RANGE = "Please input a number within the range of the search";
const std::string UserInterface::ERROR_UNDO_INITIALISE = "No existing commands to undo";
const std::string UserInterface::ERROR_INVALID_OPTION = "Please enter a valid number";
const std::string UserInterface::ERROR_REPEATED_OPTION = "Repeated option is found";

const std::string UserInterface::MESSAGE_INVALID_DONE = "No tasks that are marked done is found";
const std::string UserInterface::MESSAGE_INVALID_OVERDUE = "No tasks that are overdue is found";

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
	bool flag;
	std::string command;
	std::string undoCommand;
	std::string feedback;
	std::vector<std::string> searchTaskVector;
	std::vector<std::string> searchOtherTaskVector;
	std::vector<std::string> searchDateVector;
	std::vector<std::string> clashVector;
	std::vector<std::string> feedbackOldVector;
	std::vector<std::string> feedbackNewVector;
	std::vector<std::string> displayUser;
	
	do{
		try{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			std::cout << MESSAGE_COMMAND;
			std::cin >> command;
			isClash = false;
			space = getchar();
			flag = true;
			
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
				tbLogic.add(readTask(command, KEYWORD_EMPTY_STRING), isClash, clashVector, feedbackOldVector);
				displayFeedback(command, KEYWORD_EMPTY_STRING, KEYWORD_EMPTY_STRING, feedbackOldVector);				
				if (isClash){
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);	
					std::cout << std::endl << MESSAGE_CLASH << std::endl;
					displayInformationInVector(clashVector, displayUser, searchDateVector);
				}
				tbLogic.save();
				searchTaskVector.clear();
				searchDateVector.clear();
				clashVector.clear();
				displayUser.clear();
				feedbackOldVector.clear();
			}
			else if (command == COMMAND_SEARCH){
				searchTaskVector.clear();
				searchDateVector.clear();
				displayUser.clear();
				tbLogic.generalSearch(readTask(command, KEYWORD_EMPTY_STRING), searchTaskVector, searchDateVector);
				displayInformationInVector(searchTaskVector, displayUser, searchDateVector);
			}
			else if (command == COMMAND_DELETE){
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				std::vector<int> compareOption;

				while (!ss.eof() && ss >> option){
					flag = false;
					if (option > displayUser.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
					for (unsigned int i = 0; i < compareOption.size(); i++){
						if (option == compareOption[i]){
							throw std::runtime_error(ERROR_REPEATED_OPTION);
						}
					}
					compareOption.push_back(option);
					tbLogic.del(displayUser[option-1], false);
					tbLogic.save();
					displayFeedback(command, displayUser[option-1], KEYWORD_EMPTY_STRING, feedbackOldVector);
				}
				if (flag){
					throw std::runtime_error(ERROR_INVALID_OPTION);
				}
				searchTaskVector.clear();
				searchDateVector.clear();
				feedbackOldVector.clear();
				displayUser.clear();
			}
			else if (command == COMMAND_EDIT){
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				std::string task;
				std::string word;
				if (!ss.eof() && ss >> option){
					flag = false;
					if (option > displayUser.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
				}
				if (flag){
					throw std::runtime_error(ERROR_INVALID_OPTION);
				}
				while (ss >> word){
					task = task + word + KEYWORD_SPACE;
				}
				if (task != KEYWORD_EMPTY_STRING){
					task = task.substr(0, task.length()-1);
				}
				tbLogic.edit(displayUser[option-1], task, isClash, clashVector, feedback);
				displayFeedback(command, displayUser[option-1], feedback, feedbackOldVector);
				if (isClash){
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);	
					std::cout << std::endl << MESSAGE_CLASH << std::endl;
					displayInformationInVector(clashVector, displayUser, searchDateVector);
				}				
				tbLogic.save();
				searchTaskVector.clear();
				searchDateVector.clear();
				feedbackOldVector.clear();
				displayUser.clear();
				clashVector.clear();
			}
			else if (command == COMMAND_EDITBLOCK){
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				while (!ss.eof() && ss >> option){
					flag = false;
					if (option > displayUser.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
				}
				if (flag){
					throw std::runtime_error(ERROR_INVALID_OPTION);
				}

				system("CLS");
				editBlockUI(displayUser[option-1]);
				searchTaskVector.clear();
				searchDateVector.clear();
				displayUser.clear();
				displayWelcomeMessage();
			}
			else if (command == COMMAND_MARKDONE){
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				while (!ss.eof() && ss >> option){
					flag = false;
					if (option > displayUser.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
					tbLogic.markDone(displayUser[option-1]);
					tbLogic.save();
					tbLogic.saveDone();
					displayFeedback(command, displayUser[option-1], KEYWORD_EMPTY_STRING, feedbackOldVector);
				}
				if (flag){
					throw std::runtime_error(ERROR_INVALID_OPTION);
				}
				searchTaskVector.clear();
				feedbackOldVector.clear();
				displayUser.clear();
				searchDateVector.clear();
			}
			else if (command == COMMAND_DONE){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}

				if (tbLogic.retrieveDoneList(searchOtherTaskVector)){
					displayInformationInVector(searchOtherTaskVector, displayUser, searchDateVector);
				}
				else{
					displayFailMessage(command);
				}
				searchOtherTaskVector.clear();
				searchDateVector.clear();
				displayUser.clear();
				searchTaskVector.clear();
				searchDateVector.clear();
			}
			else if (command == COMMAND_OVERDUE){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}

				if (tbLogic.retrieveOverdueList(searchOtherTaskVector)){
					displayInformationInVector(searchOtherTaskVector, displayUser, searchDateVector);
				}
				else{
					displayFailMessage(command);
				}
				searchOtherTaskVector.clear();
				searchDateVector.clear();
				displayUser.clear();
				searchTaskVector.clear();
				searchDateVector.clear();
			}
			else if (command == COMMAND_CLEAROVERDUE){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				tbLogic.clearOverdueList();
				tbLogic.saveOverdue();
				displaySuccessfulMessage(command);
				feedbackOldVector.clear();
				searchTaskVector.clear();
				searchDateVector.clear();
			}
			else if (command == COMMAND_UNDO){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				tbLogic.undo(undoCommand, feedbackOldVector, feedbackNewVector);
				tbLogic.save();
				tbLogic.saveDone();
				displayUndoFeedback(undoCommand, feedbackOldVector, feedbackNewVector);
				feedbackOldVector.clear();
				feedbackNewVector.clear();
				searchTaskVector.clear();
				searchDateVector.clear();
				displayUser.clear();
			}
			else if (command == COMMAND_CLEAR){
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				system("CLS");
				displaySuccessfulMessage(command);
				searchTaskVector.clear();
				searchDateVector.clear();
				displayUser.clear();
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
				displaySuccessfulMessage(command);
				contProgram = false;
			}
			else{
				if (space == ' '){
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				throw std::runtime_error(ERROR_INVALID_COMMAND);
			}
		}
		catch (std::runtime_error &error){
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
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
	bool flag = true;
	std::string command;
	std::string taskString; 
	std::string taskActionLocation;
	std::string originalTaskString = stringToEditBlock;
	std::vector<std::string> blockTaskVector;
	std::vector<std::string> clashVector;
	std::vector<std::string> feedbackVector;
	std::vector<std::string> displayUser;
	std::vector<std::string> searchDateVector;

	tbLogic.getBlock(originalTaskString, taskActionLocation, blockTaskVector, searchDateVector);
	std::cout << MESSAGE_AVAILABLE_BLOCKS << std::endl;
	displayInformationInVector(blockTaskVector, displayUser, searchDateVector);
	std::cout << std::endl;

	do{
		try{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			std::cout << MESSAGE_COMMAND;
			std::cin >> command;
			space = getchar();

			if (command == COMMAND_ADD){
				command = COMMAND_ADDBLOCK;
				tbLogic.addBlock(readTask(command, taskActionLocation), originalTaskString, isClash, clashVector, feedbackVector);
				tbLogic.save();
				displayFeedback(command, KEYWORD_EMPTY_STRING, KEYWORD_EMPTY_STRING, feedbackVector); 
				if (isClash){
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);	
					std::cout << std::endl << MESSAGE_CLASH << std::endl;
					displayInformationInVector(clashVector, displayUser, searchDateVector);
				}			
				searchDateVector.clear();
				clashVector.clear();
				displayUser.clear();
				contEditBlock = false;
			}
			else if (command == COMMAND_EDITALL){
				taskString = readTask(command, KEYWORD_EMPTY_STRING);
				tbLogic.editBlock(taskString, displayUser);
				tbLogic.save();
				displayFeedback(command, taskString, KEYWORD_EMPTY_STRING, feedbackVector);
				contEditBlock = false;			
			}
			else if (command == COMMAND_DELETE){
				command = COMMAND_DELETEBLOCK;
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				std::vector<int> compareOption;

				while (!ss.eof() && ss >> option){
					flag = false;
					if (option > displayUser.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
					for (unsigned int i = 0; i < compareOption.size(); i++){
						if (option == compareOption[i]){
							contEditBlock = false;
							throw std::runtime_error(ERROR_REPEATED_OPTION);
						}
					}
					compareOption.push_back(option);
					tbLogic.del(displayUser[option-1], false);
					tbLogic.save();
					displayFeedback(command, displayUser[option-1], KEYWORD_EMPTY_STRING, feedbackVector);
				}
				contEditBlock = false;
			}
			else if (command == COMMAND_FINALISE || command == COMMAND_FINALIZE){
				std::stringstream ss(readTask(command, KEYWORD_EMPTY_STRING));
				if (!ss.eof() && ss >> option){
					flag = false;
					if (option > displayUser.size()){
						throw std::runtime_error(ERROR_OUT_OF_VECTOR_RANGE);
					}
				}
				if (flag){
					throw std::runtime_error(ERROR_INVALID_OPTION);
				}
				tbLogic.finaliseBlock(option, displayUser);
				tbLogic.save();
				displayFeedback(command, displayUser[option-1], KEYWORD_EMPTY_STRING, feedbackVector);
				contEditBlock = false;
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
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			std::cout << error.what() << std::endl;
		}
		std::cout << std::endl;
	} while (contEditBlock);
	
	system("PAUSE");
	system("CLS");
}

//To display welcome message after the program is initialised
void UserInterface::displayWelcomeMessage(){
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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
	std::vector<std::string> searchDateVector;
	std::vector<std::string> displayUser;
	try{
		tbLogic.generalSearch(KEYWORD_TODAY, todayTask, searchDateVector);
		std::cout << MESSAGE_TODAY_TASK << std::endl;
		displayInformationInVector(todayTask, displayUser, searchDateVector);
	}
	catch (std::runtime_error &error){
		std::cout << error.what() << std::endl;
	}
	std::cout << std::endl;
}

//To display all information in a vector
void UserInterface::displayInformationInVector(std::vector<std::string> vec, std::vector<std::string>& displayUser, std::vector<std::string> searchDateVector){
	int alternate = 1;
	int countEmptyString = 0;

	if (!searchDateVector.empty()){																	
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << KEYWORD_EQUAL_LEFT << searchDateVector[countEmptyString] << KEYWORD_EQUAL_RIGHT << std::endl << std::endl;
	}

	for (unsigned int i = 0; i < vec.size(); i++){
		if (vec[i] != KEYWORD_EMPTY_STRING){
			if (i+1-countEmptyString < 10){
				std::cout << KEYWORD_SPACE;
			}
			if (alternate % 2 == 1){
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
			}
			else{
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);				
			}
			std::cout << i+1-countEmptyString << KEYWORD_BULLETING << vec[i] << std::endl;
			displayUser.push_back(vec[i]);
		}
		else{
			assert(!searchDateVector.empty());
			std::cout << vec[i] << std::endl;
			countEmptyString++;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << KEYWORD_EQUAL_LEFT << searchDateVector[countEmptyString] << KEYWORD_EQUAL_RIGHT << std::endl << std::endl;
			alternate++;
		}
	}
}

//To display feedback to users
void UserInterface::displayFeedback(std::string command, std::string oldTask, std::string newTask, std::vector<std::string> feedbackVector){
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (command == COMMAND_ADD || command == COMMAND_ADDBLOCK){
		for (unsigned int i = 0; i < feedbackVector.size(); i++){
			std::cout << KEYWORD_QUOTE << feedbackVector[i] << KEYWORD_QUOTE << MESSAGE_ADD << std::endl;
		}
	}
	else if (command == COMMAND_DELETE || command == COMMAND_DELETEBLOCK){
		std::cout << KEYWORD_QUOTE << oldTask << KEYWORD_QUOTE << MESSAGE_DELETE;
	}
	else if (command == COMMAND_EDIT){
		std::cout << KEYWORD_QUOTE << oldTask << KEYWORD_QUOTE << std::endl
				  << MESSAGE_EDIT << std::endl
				  << KEYWORD_QUOTE << newTask << KEYWORD_QUOTE;
	}
	else if (command == COMMAND_EDITALL){
		std::cout << MESSAGE_EDITALL << KEYWORD_QUOTE << oldTask << KEYWORD_QUOTE;
	}
	else if (command == COMMAND_FINALISE || command == COMMAND_FINALIZE){
		std::cout << KEYWORD_QUOTE << oldTask << KEYWORD_QUOTE << MESSAGE_FINALISE; 
	}
	else if (command == COMMAND_MARKDONE){
		std::cout << KEYWORD_QUOTE << oldTask << KEYWORD_QUOTE << MESSAGE_MARKDONE;
	}
	else if (command == COMMAND_CLEAROVERDUE){
		std::cout << MESSAGE_CLEAROVERDUE;
	}

	if (command != COMMAND_ADD && command != COMMAND_ADDBLOCK){
		std::cout << std::endl;
	}
}

//To display messages when commands are executed successfully
void UserInterface::displaySuccessfulMessage(const std::string command){
	if (command != COMMAND_EXIT){
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}

	if (command == COMMAND_CLEAROVERDUE){
		std::cout << MESSAGE_CLEAROVERDUE;
	}
	else if (command == COMMAND_CLEAR){
		std::cout << MESSAGE_CLEAR;
	}
	else if (command == COMMAND_EXIT){
		std::cout << MESSAGE_EXIT;
	}
	std::cout << std::endl;
}

//To display messages when commands fail to execute successfully
void UserInterface::displayFailMessage(const std::string command){
	assert(command == COMMAND_DONE || command == COMMAND_OVERDUE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (command == COMMAND_DONE){
		std::cout << MESSAGE_INVALID_DONE;
	}
	else if (command == COMMAND_OVERDUE){
		std::cout << MESSAGE_INVALID_OVERDUE;
	}
	std::cout << std::endl;
}

//To display feedback to user for undo function
void UserInterface::displayUndoFeedback(std::string undoCommand, std::vector<std::string> feedbackOldVector, std::vector<std::string> feedbackNewVector){
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (undoCommand == COMMAND_ADD){
		for (unsigned int i = 0; i < feedbackOldVector.size(); i++){
			std::cout << KEYWORD_QUOTE << feedbackOldVector[i] << KEYWORD_QUOTE << MESSAGE_DELETE << std::endl;
		}
	}
	else if (undoCommand == COMMAND_DELETE){
		for (unsigned int i = 0; i < feedbackOldVector.size(); i++){
			std::cout << KEYWORD_QUOTE << feedbackOldVector[i] << KEYWORD_QUOTE << MESSAGE_ADD << std::endl;
		}
	}
	else if (undoCommand == COMMAND_EDIT){
		for (unsigned int i = 0; i < feedbackOldVector.size(); i++){
			std::cout << KEYWORD_QUOTE << feedbackNewVector[i] << KEYWORD_QUOTE << std::endl
					  << MESSAGE_EDIT << std::endl
					  << KEYWORD_QUOTE << feedbackOldVector[i] << KEYWORD_QUOTE << std::endl;
		}
	}
	else if (undoCommand == COMMAND_MARKDONE){
		for (unsigned int i = 0; i < feedbackOldVector.size(); i++){
			std::cout << KEYWORD_QUOTE << feedbackOldVector[i] << KEYWORD_QUOTE << MESSAGE_UNDONE << std::endl;
		}
	}
}

//To display the help message for commandUI
void UserInterface::displayHelpCommandUI(){
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "@-----------------------------------------------------------------------------------------------------------@" << std::endl
	          << "|";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Add(timed tasks)";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "add";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"action\" ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "at"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"location\" ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "from"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "to"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm                       ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: add swimming at school from 20/11/2013 0900 to 20/11/2013 1000                                    ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Add(deadline tasks)";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "add";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"action\" ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "at";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"location\" "; 

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "by";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm                                         ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: add do homework at home by 20/11/2013 2000                                                        ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Add(floating tasks)";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "add";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"action\" "; 

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "at";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"location\"                                                            ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: add play computer game at home                                                                    ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Add(block off time slots)"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "add"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"action\" "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "at"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"location\" "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "blockoff"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "[press ENTER]                                ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "                         : "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "from"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "to"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm [press ENTER]                           ";
		
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "                         : "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "by"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm [press ENTER]                                                ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout<< "                         : "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "end                                                                             ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: add swimming at school blockoff                                                                   ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "       : from 20/11/2013 1100 to 20/11/2013 1200                                                           ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "       : by 21/11/2013 1000                                                                                ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "       : end                                                                                               ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Search"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " for task: ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "search"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"keyword\"                                                                          ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: search home                                                                                       ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Delete"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " a task: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "delete"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " \"option\"                                                                             ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: delete 1                                                                                          ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Edit"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " a task: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "edit"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " \"option\" \"changes in task\"                                                               ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: edit 1 running at school                                                                          ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Edit"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " tasks with "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "block off"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " timings: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "editblock"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"option\"                                                      ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: editblock 1                                                                                       ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Mark done"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " a task: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "markdone"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"option\"                                                                        ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: markdone 1                                                                                        ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Display tasks that are "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "done"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "done                                                                          ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Display tasks that are "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "overdue"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "overdue                                                                    ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Clear overdue"; 

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " tasks list: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "clearoverdue                                                                     ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Undo"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " previous command: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "undo                                                                                ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);	  
	std::cout << "Clear"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " display screen: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "clear                                                                                ";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);	  
	std::cout << "Exit"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	std::cout << " program: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "exit                                                                                         ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl
			  << "@-----------------------------------------------------------------------------------------------------------@" << std::endl;
}

//To display the help message for editBlockUI
void UserInterface::displayHelpEditBlockUI(){
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "@-----------------------------------------------------------------------------------------------------------@" << std::endl
	          << "|";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Add block off"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "add blockoff"; 

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " [press ENTER]                                                                  ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "            : "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "from"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "to"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm [press ENTER]                                        ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "            : "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "by"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " dd/mm/yyyy hhmm [press ENTER]                                                             ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "            : "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "end                                                                                          ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: add blockoff                                                                                      ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "       : from 20/11/2013 1100 to 20/11/2013 1200                                                           ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "       : by 21/11/2013 1000                                                                                ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "       : end                                                                                               ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Edit"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " action and location of all "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "block off"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "editall"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"action\" "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "at"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"location\"                                  ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: editall running at school                                                                         ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Delete block off"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << ": "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "delete"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"option\"                                                                          ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: delete 1                                                                                          ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Finalise"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " time slot for task: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "finalise"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " \"option\"                                                             ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Example: finalise 1 (option 1 is the time slot that user wants)                                            ";
			  
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" <<std::endl
			  << "|                                                                                                           |" << std::endl
			  << "|";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Return"; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << " to main menu: "; 
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "return                                                                                ";

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "|" << std::endl
			  << "@-----------------------------------------------------------------------------------------------------------@" << std::endl;
}