#include "TaskLogic.h"
#include <typeinfo>
#include <exception>
#include <iostream>
#include <ctime>

const std::string TaskLogic::COMMAND_ADD = "add";
const std::string TaskLogic::COMMAND_DELETE = "delete";
const std::string TaskLogic::COMMAND_EDIT = "edit";

TaskLogic::TaskLogic(){

}

TaskLogic::~TaskLogic(){

}

//-----INITIALISATION, SAVE & EXIT-------------------------------------------------------------------------------

/*
	Purpose: Tasks are saved into tbLinkedList
	Equivalence Partition: Empty Vector, Non-empty Vector
	Boundary: Empty Vector, Any Non-empty Vector
*/
void TaskLogic::initLogic(){
	initDate();
	std::vector<std::string> tbVector;
	tbStorage.getExistingTasks(tbVector);
	for (unsigned int i = 0; i < tbVector.size(); i++){
		addExistingTask(tbVector[i]); 
	}
	return;
}

/*
	Purpose: Initialises all dates within the next week into dateVector
*/
void TaskLogic::initDate(){
   time_t current = time(0);
   std::string currentDateTime;
   std::string today;
   std::string dateArray[9];

   currentDateTime = ctime(&current);

   std::istringstream iss(currentDateTime);
   std::string dayArray[8] = {" ","Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
   int i = 1;

   iss >> today;
   while(today != dayArray[i])
	  i++;

   dateArray[0] = extractDate(currentDateTime);
  
   // goes to next week's today
   for(int j = 1; j <= 7; j++){
		current += 86400;
		currentDateTime = ctime(&current);
		i++;
		if(i > 7)
			i = 1;  // reset to Monday after Sunday
		dateArray[i] = extractDate(currentDateTime);
		if(j == 1)
			dateArray[8] = dateArray[i];
   }

   for(i = 0; i <= 8 ; i++)
	   dateVector.push_back(dateArray[i]);

   return;
}

/*
	Purpose: Get task in string format from TaskLinkedList and saves them into a storage file.
	Post-Conditions: Task are saved into storage file in sorted order and in proper string format.
	Equivalence Partition: Empty Vector, Non-empty Vector
	Boundary: Empty Vector, Any non-empty vector
*/
void TaskLogic::save(){
    std::vector<std::string> tbVector;
	tbLinkedList.updateStorageVector(tbVector);
	tbStorage.saveTasksIntoFile(tbVector);
}

/*
	Purpose: Do necessary calling of destructors in LinkedList
*/
void TaskLogic::exitLogic(){
	//tbVector.clear();
}

//-----ADD TASK---------------------------------------------------------------------------------------------------

/*
	Purpose: Converts a task input string into a Task and adds it into tbLinkedList and indicates to UI if there's clashes
	Pre-conditions: taskString is not empty and should not contain the command word
	Post-conditions: true is returned only if task is added successfully, given that the input given by user is valid
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
bool TaskLogic::add(const std::string taskString, bool& isClash){
	std::vector<Task> taskObjectVector; 
    taskObjectVector = createTask(taskString, 1);   //generating task from user input.
	bool checkAdded = true;
	bool clash;

	for(unsigned int i = 0; i < taskObjectVector.size() ; i++){
		clash = false;
		if(tbLinkedList.insert(taskObjectVector[i], isClash))              //remove clash as parameter to let program compile first cause Sharmane haven't include
			update(COMMAND_ADD, taskObjectVector[0].getTask(), "");
		else
			checkAdded = false;
		if(clash)
			isClash = true;
	}
	return checkAdded;
}

/*
	Purpose: Converts a task input string from storage file into a Task and adds it into tbLinkedList
	Pre-conditions: taskString is not empty and is in the proper format
	Post-conditions: true is returned only if task is added successfully, given that the input is in proper format
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
bool TaskLogic::addExistingTask(const std::string taskString){
	std::vector<Task> taskObjectVector;
	bool isClash = false;
    taskObjectVector = createTask(taskString, 2);     //generating task from file
	if(tbLinkedList.insert(taskObjectVector[0], isClash))  //there is no need to check if isClashed since these are pre-existing task.
		return true;
	else
		return false;
}

//-----DELETE TASK-------------------------------------------------------------------------------------------------
	
/*
	Purpose: Search for a Task with the taskString and delete it from tbLinkedList.
			 isUndoDel indicates if it was a delete function call from undo, thus no updating required.
	Pre-conditions: taskString is not empty and should be in the proper format
	Post-conditions: true is returned only if the task is found successfully and removed from tbLinkedList
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
bool TaskLogic::del(const std::string taskString, bool isUndoDel){
	bool checkDeleted = true;

	checkDeleted = tbLinkedList.remove(taskString, getActionLocation(taskString));

	if(checkDeleted)
		if(!isUndoDel)
			update(COMMAND_DELETE, taskString, "");

	return checkDeleted;
}

//-----SEARCH TASK--------------------------------------------------------------------------------------------------

/*
	Purpose: Search for all task in the list that contains keyword and place these tasks into vector parameter
	Pre-conditions: userInput is not empty
	Post-conditions: true is returned only if task(s) can be found, given that all input given by user is valid
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
bool TaskLogic::generalSearch(std::string userInput, std::vector<std::string>& vectorOutput){
	std::vector<std::string> keywordVector;
	std::stringstream iss;
	std::string keyword;
	iss << userInput;
	
	while (iss >> keyword){
		if(isDay(keyword)){
			keyword = taskParse.changeDayToDate(keyword, dateVector);
		}
		keywordVector.push_back(keyword);
	}
	return tbLinkedList.retrieve(keywordVector, vectorOutput);
}

//-----EDIT TASK-----------------------------------------------------------------------------------------------------

/*
	Purpose: Edit a task by breaking down and comparing the intial taskString and the editString. The initial task is 
			 removed from tbLinkedList and the edited task is added in.
	Pre-conditions: taskString is not-empty and is in proper format. editString is non-empty and is valid user input.
	Post-conditions: true is returned only if intial task(s) is found and edited, given that all inputs are valid
	Equivalence Partition: Empty strings, Invalid strings, Valid strings
	Boundary: Empty strings, Any valid strings, Any invalid strings
*/
bool TaskLogic::edit(std::string taskString, std::string editString){
	std::string newTask, newAction = "", newLocation = "", currentAction = "", currentLocation = "";
	std::vector<Date> newStartingDate, newEndingDate, newDeadlineDate, currentStartingDate, currentEndingDate, currentDeadlineDate;
	std::vector<int> newStartingTime, newEndingTime, newDeadlineTime, currentStartingTime, currentEndingTime, currentDeadlineTime; 
	bool isBlock = false;
	bool newIsBlock = false;
	bool isClash = false;  //PLEASE CHECK!!!

	stringParse(taskString,2,currentAction,currentLocation,currentStartingDate,currentStartingTime,currentEndingDate,currentEndingTime,currentDeadlineDate,currentDeadlineTime, isBlock);
	stringParse(editString,1,newAction,newLocation,newStartingDate,newStartingTime,newEndingDate,newEndingTime,newDeadlineDate,newDeadlineTime, newIsBlock);  

	if (newAction == "" && currentAction != "") {
		newAction = currentAction;
	}
	
	if (newLocation == "" && currentLocation != "") {
		newLocation = currentLocation;
	}

	newIsBlock = isBlock;
	
	bool isDateEdited = false;

	if(newDeadlineDate[0].isValidDate() || newStartingDate[0].isValidDate() || newEndingDate[0].isValidDate() ) //check is by Date instead of time because we want to be able to allow time to be undefined. Also check if we want to allow only to.
		isDateEdited = true;

	if(!isDateEdited){
		if(currentStartingDate[0].isValidDate() )  //actually necessary to have all these checks?
			newStartingDate[0] = currentStartingDate[0];
		if(currentEndingDate[0].isValidDate() )
			newEndingDate[0] = currentEndingDate[0];
		if(currentDeadlineDate[0].isValidDate() )
			newDeadlineDate[0] = currentDeadlineDate[0];
		if(currentStartingTime[0] != -1)
			newStartingTime[0] = currentStartingTime[0];
		if(currentEndingTime[0] != -1)
			newEndingTime[0] = currentEndingTime[0];
		if(currentDeadlineTime[0] != -1)
			newDeadlineTime[0] = currentDeadlineTime[0];
	}
	
	Task taskObject(newAction,newLocation,newStartingDate[0],newStartingTime[0],newEndingDate[0],newEndingTime[0],newDeadlineDate[0],newDeadlineTime[0],newIsBlock);
	
	tbLinkedList.remove(taskString, getActionLocation(taskString));
	tbLinkedList.insert(taskObject, isClash);

	update(COMMAND_EDIT, taskObject.getTask(), taskString);
	return true; // need to do checking
}

//-----EDIT BLOCK-----------------------------------------------------------------------------------------------------

/*
	Purpose: Search for all task that is blocked together with the task and input strings into blockTaskVector and
			 taskActionLocation (action + " at " + location)
	Pre-conditions: taskString is not-empty and is in proper format
	Post-conditions: true is returned only if task(s) is found, given that the input is valid
					 
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
bool TaskLogic::getBlock(std::string& taskString, std::string& taskActionLocation, std::vector<std::string>& blockTaskVector){	
	taskActionLocation = getActionLocation(taskString);
	generalSearch(taskActionLocation, blockTaskVector);
	
	if(blockTaskVector.size() > 0)
		return true;
	else
		return false;
}

/*
	Purpose: edit the action and location of all task in the block to the newTaskActionLocation
	Pre-conditions: newTaskActionLocation is not empty and is valid
					blockTaskVector is not-empty and is in proper format
	Post-conditions: true is returned only if all tasks are edited correctly, given that all inputs are valid
					 
	Equivalence Partition: Empty string, Invalid string, Valid string, empty vector, invalid vector strings, valid vector strings
	Boundary: Empty string, Any valid string, Any invalid string, empty vector, any invalid vector strings, any valid vector strings
*/
bool TaskLogic::editBlock(const std::string newTaskActionLocation, std::vector<std::string>& blockTaskVector){
	bool isValidEdit = true;
	for(unsigned int i = 0; i < blockTaskVector.size(); i++){
		if(!edit( blockTaskVector[i], newTaskActionLocation))
			isValidEdit = false;
	}
	return isValidEdit;
}

/*
	Purpose: Adds in all new tasks into tbLinkedList and also mark the original task as blocked if not already blocked.
	Pre-conditions: taskString is not empty and is valid (contains key word such as "blockoff"
	Post-conditions: true is returned only if all tasks are added successfully, given that all inputs are valid
	Equivalence Partition: Empty strings, Invalid strings, Valid strings
	Boundary: Empty strings, Any valid strings, Any invalid strings
*/
bool TaskLogic::addBlock(const std::string taskString, const std::string originalTaskString){
	tbLinkedList.setBlock(originalTaskString);   
	bool isClash = false;
	
	if(add(taskString, isClash))
		return true;
	else
		return false;
}

/*
	Purpose: Finalise blocking to only one task by removing all others. Del ensures that the sole task remaining is not marked
			 as blocked anymore
	Pre-conditions: all strings in blockTaskVector is of proper format. delIndex is withing the range of blockTaskVector
	Post-conditions: true is returned only if block is finalised, given that all inputs are valid
	Equivalence Partition: valid int index, invalid int index, empty vector, empty strings, valid strings, invalid strings
	Boundary: index 0, index 1, index size-1, any invalid index, Empty vector, Empty strings, Any valid strings, Any invalid strings
*/
bool TaskLogic::finaliseBlock(int delIndex, std::vector<std::string>& blockTaskVector){
	unsigned int count = 0;
	delIndex -= 1; //convert to 0-based
	for(unsigned int i=0; i < blockTaskVector.size() ; i++){
		if(i != delIndex){
			del(blockTaskVector[i],false);
			count++;
		}
	}

	return (count == blockTaskVector.size() - 1);
}

//-----UNDO--------------------------------------------------------------------------------------------------------

/*
	Purpose: Keeps track of commands made by pushing command keywords into stack commandStackHistory and pushing the
			 taskString into taskStackHistory
	Pre-conditions: command string is a valid command, newTask and oldTask are in the proper processed format needed
	Equivalence Partition: command == COMMAND_EDIT, command == COMMAND_ADD, command == COMMAND_DELETE
	Boundary: any invalid command, command == COMMAND_EDIT, command == COMMAND_ADD, command == COMMAND_DELETE
*/
void TaskLogic::update(std::string command, std::string newTask, std::string oldTask){

	if (command == COMMAND_EDIT){
		commandStackHistory.push(command);   // newTask is to be added in, while old task is to be deleted.
		taskStackHistory.push(oldTask);  //deleted
		taskStackHistory.push(newTask);  //added
		// must be in this specific order, and newTask and oldTask must be in proper form
	}
	else if(command == COMMAND_ADD || command == COMMAND_DELETE){
		commandStackHistory.push(command);
		taskStackHistory.push(newTask); //use newTask even for delete
	}
	return;
}

/*
	Purpose: Undo the last previous command stored at the top of commandStackHistory
	Pre-conditions: commandStackHistory is not empty, and taskStackHistory is not empty and contains sufficient tasks
					to undo the command.
	Post-condition: returns true if undo is successful.
	Equivalence Partition: empty commandStackHistory, empty taskStackHistory, insufficient taskStackHistory, invalid command, command == COMMAND_EDIT, command == COMMAND_ADD, command == COMMAND_DELETE
	Boundary: empty commandStackHistory, empty taskStackHistory, insufficient taskStackHistory, invalid command, command == COMMAND_EDIT, command == COMMAND_ADD, command == COMMAND_DELETE
*/
bool TaskLogic::undo(){
	bool result = true;

	if(commandStackHistory.top() == COMMAND_EDIT){
		if(!del(taskStackHistory.top(),true))
			result = false;
		taskStackHistory.pop();   //if delete fails we should still remove the task to be done from the system?
		
		if(!addExistingTask(taskStackHistory.top()))
			result = false;
		taskStackHistory.pop();
	
		commandStackHistory.pop();  //whether result true or not, let the command be popped out cos otherwise it can never be done
	}
	else if(commandStackHistory.top() == COMMAND_ADD){
		if(!del(taskStackHistory.top(),true))
			result = false;
		taskStackHistory.pop();
		
		commandStackHistory.pop();
	}
	else if(commandStackHistory.top() == COMMAND_DELETE){
		if(!addExistingTask(taskStackHistory.top()))
			result = false;
		taskStackHistory.pop();
		
		commandStackHistory.pop();
	}	
	else if(commandStackHistory.empty())
		result = false;
	else
		//wrong command sent in or the command Stack is empty i.e nothing to undo

	return result;
}

//-----HELPER FUNCTIONS---------------------------------------------------------------------------------------------

//method 1 : User Input ; Method 2 : Pre-Existing Task in file
void TaskLogic::stringParse(const std::string taskString, const int method, std::string &action, std::string &location, std::vector<Date> &startingDateVector, std::vector<int> &startingTimeVector, std::vector<Date> &endingDateVector, std::vector<int> &endingTimeVector, std::vector<Date> &deadlineDateVector, std::vector<int> &deadlineTimeVector, bool &isBlock){
	if(method == 1){
		taskParse.processTaskStringFromUI(taskString,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock,dateVector);
	}
	else if(method == 2){
		taskParse.processTaskStringFromFile(taskString,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock,dateVector);
	}

	return;
	//add in exceptions
}

//method 1 : User Input ; Method 2 : Pre-Existing Task in file
std::vector<Task> TaskLogic::createTask(std::string taskString, int method){
	std::string task = "", action = "", location ="";
	std::vector<Date> startingDateVector, endingDateVector, deadlineDateVector; 
	std::vector<int> startingTimeVector, endingTimeVector, deadlineTimeVector; //check if we really want to set it as -1
	bool isBlock = false;
	stringParse(taskString,method,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock);   
	
	if(startingDateVector.size() > 1 || endingDateVector.size() > 1 || deadlineDateVector.size() > 1)
		isBlock = true;
	
	//PROBLEM!! HOW TO CREATE SO MANY TASK AT ONE GO? MUST BE IN ADD
	//WHAT IF YOU HAVE DIFFERENT NUMBER OF STARTING AND ENDING? Must indicate in that same ending vector / starting vector

	std::vector<Task> taskObjectVector;

	//MUST DO A CHECK TO ENSURE THAT StartingDate Vector and Endng Date Vector must be the same size!
	for(unsigned int i = 0 ; i < startingDateVector.size() && startingDateVector[i].isValidDate(); i++){
		Date deadlineDate;
		int deadlineTime = -1;
		Task taskObject(action,location,startingDateVector[i],startingTimeVector[i],endingDateVector[i],endingTimeVector[i],deadlineDate,deadlineTime,isBlock);
		taskObjectVector.push_back(taskObject);
	}
	for(unsigned int i = 0 ; i < deadlineDateVector.size() && deadlineDateVector[i].isValidDate() ; i++){
		Date startingDate, endingDate;
		int startingTime = -1, endingTime = -1;
		Task taskObject(action,location,startingDate,startingTime,endingDate,endingTime,deadlineDateVector[i],deadlineTimeVector[i],isBlock);
		taskObjectVector.push_back(taskObject);
	}
	//task string must be created upon constrution!

	return taskObjectVector;
}

bool TaskLogic::isDay(std::string& keyword){
	std::string possibleDay[20] = {"today","tmr","tomorrow","mon","monday","tue","tues","tuesday","wed","wednesday","thu","thur","thurs","thursday","fri","friday","sat","saturday","sun","sunday"};
	bool keyWordIsDay = false;
    std::string lowerCaseKeyWord = keyword;
		
	for(int i = 0; lowerCaseKeyWord[i] != '\0'; i++){
		lowerCaseKeyWord[i] = tolower(lowerCaseKeyWord[i]);
	}

	for(int i = 0; i < 20; i++){
		if(lowerCaseKeyWord == possibleDay[i]){
			keyWordIsDay = true;
			keyword = lowerCaseKeyWord;
		}
	}
	return keyWordIsDay;
}
	
std::string TaskLogic::extractDate(std::string currentDateTime){
	std::string day, month, time, monthArray[13] = {" ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    int date, year, monthNum = 1;	
	std::istringstream iss(currentDateTime);
	iss >> day >> month >> date >> time >> year;

	while(month != monthArray[monthNum])
		monthNum ++;     // can Parse take in single digit month?

	std::ostringstream oss;
	oss << date << "/" << monthNum << "/" << year; 
	return oss.str();
}   

std::string TaskLogic::getActionLocation(std::string taskString){
	std::string action = "", location ="";
	std::vector<Date> startingDateVector, endingDateVector, deadlineDateVector; 
	std::vector<int> startingTimeVector, endingTimeVector, deadlineTimeVector; //check if we really want to set it as -1
	bool isBlock = false;
	taskParse.processTaskStringFromFile(taskString,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock,dateVector);
	
	std::string taskActionLocation = action;
	if(location != "")
		taskActionLocation = taskActionLocation + " at " + location; //just the common details. i.e action and location only
	return taskActionLocation;
}