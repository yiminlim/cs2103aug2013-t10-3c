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

//Takes in filename and takes all existing tasks inside file into tbLinkedList
void TaskLogic::initLogic(){
	initDate();
	std::vector<std::string> tbVector;
	tbStorage.getExistingTasks(tbVector);
	for (unsigned int i = 0; i < tbVector.size(); i++){
		addExistingTask(tbVector[i]); 
	}
	return;
}

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
	
bool TaskLogic::add(const std::string taskString){
	std::vector<Task> taskObjectVector; 
    taskObjectVector = createTask(taskString, 1); //generating task from user input.
	bool checkAdded = true;

	for(unsigned int i = 0; i < taskObjectVector.size() ; i++){
		//tbVector.push_back(taskObjectVector[i].getTask()); //only need to push in for user inputs
		if(tbLinkedList.insert(taskObjectVector[i]))
			update(COMMAND_ADD, taskObjectVector[0].getTask(), "");
		else
			checkAdded = false;
	}
	return checkAdded;
}

bool TaskLogic::addExistingTask(const std::string taskString){
	std::vector<Task> taskObjectVector; 
    taskObjectVector = createTask(taskString, 2); //generating task from file
	if(tbLinkedList.insert(taskObjectVector[0]))//FOR EXISTING FILE MUST NOTE THE BLOCKING AS WELL!! 
		return true;
	else
		return false;
}

bool TaskLogic::checkIsValidInput(std::string taskString){
	//check that if there is "at" then there must be a location string behind it.
	//check that if there is "by" then there should not be any timing after that.
	//check that if there is "from" there must be a "to"

	return true;
}
	
//delete a task from the list at the index given
bool TaskLogic::del(const std::string taskString){
	bool checkDeleted = true;

	//delFromVector(taskString);
	checkDeleted = tbLinkedList.remove(taskString);

	if (checkDeleted){
		update(COMMAND_DELETE, taskString, "");
	}

	return checkDeleted;
}

/*  NOT NECESSARY IF NO VECTOR
bool TaskLogic::delFromVector(const std::string taskString){
	std::vector<std::string>::iterator delIter;

	for(delIter = tbVector.begin(); delIter != tbVector.end(); delIter++){
		if(*delIter == taskString){
			tbVector.erase(delIter); //problem with this
		    return true;
		}
	}
	//Should we check all occurences instead?
	//assert that it can be found or use exception
	return false;
}
*/
	
//return all tasks in the list that contains keyword and copy these tasks into vector parameter
bool TaskLogic::generalSearch(std::string userInput, std::vector<std::string>& vectorOutput){
	std::vector<std::string> keywordVector;
	std::stringstream iss;
	std::string keyword;
	iss << userInput;
	// check that userInput not empty
	while (iss >> keyword){
		if(isDay(keyword)){
			keyword = taskParse.changeDayToDate(keyword, dateVector);
		}
		keywordVector.push_back(keyword);
	}
	return tbLinkedList.retrieve(keywordVector, vectorOutput);
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
	
	
//edit a task from the list at the index given
//edit firsts breaks it down to check if it needs to edit which component (task, action, location, Date, time) etc.
bool TaskLogic::edit(std::string taskString, std::string editString){
	std::string newTask, newAction = "", newLocation = "", currentAction = "", currentLocation = "";
	std::vector<Date> newStartingDate, newEndingDate, newDeadlineDate, currentStartingDate, currentEndingDate, currentDeadlineDate;
	std::vector<int> newStartingTime, newEndingTime, newDeadlineTime, currentStartingTime, currentEndingTime, currentDeadlineTime; 
	bool isBlock = false;
	bool dummy;

	stringParse(taskString,2,currentAction,currentLocation,currentStartingDate,currentStartingTime,currentEndingDate,currentEndingTime,currentDeadlineDate,currentDeadlineTime, isBlock);
	stringParse(editString,1,newAction,newLocation,newStartingDate,newStartingTime,newEndingDate,newEndingTime,newDeadlineDate,newDeadlineTime, dummy);  

	if (newAction == "" && currentAction != "") {
		newAction = currentAction;
		//isBlock = false;
	}
	//if there is new action we need to change status of block? Current set as if action and location changes, block will be removed!!
	if (newLocation == "" && currentLocation != "") {
		newLocation = currentLocation;
	}
	
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
	
	Task taskObject(newAction,newLocation,newStartingDate[0],newStartingTime[0],newEndingDate[0],newEndingTime[0],newDeadlineDate[0],newDeadlineTime[0],isBlock);

	//delFromVector(taskString);
//	tbVector.push_back(taskObject.getTask()); //only need to push in for user inputs
	
	tbLinkedList.remove(taskString);
	tbLinkedList.insert(taskObject);

	update(COMMAND_EDIT, taskObject.getTask(), taskString);
	return true; // need to do checking
		
	/*
	bool isCurrentDeadlineType = false;
	bool isNewDeadlineType = false;
	if (currentDeadlineTime[0] != -1 && currentStartingTime[0] == -1) {  //on the basis that time must always be placed??!! what if no time placed
		isCurrentDeadlineType = true;	
	}
	if ((newDeadlineTime[0] != -1 && newStartingTime[0] == -1) || (newDeadlineTime[0] == -1  && currentDeadlineTime[0] != -1 && newStartingTime[0] == -1)) {
		isNewDeadlineType = true;
	}

	if (isCurrentDeadlineType && isNewDeadlineType) {
		if(!newDeadlineDate[0].isValidDate() && currentDeadlineDate[0].isValidDate()){
			newDeadlineDate = currentDeadlineDate;
		}
		if(newDeadlineTime[0] == -1 && currentDeadlineTime[0] != -1){
		newDeadlineTime[0] = currentDeadlineTime[0];
		
		}
	}
	else if (!isCurrentDeadlineType && isNewDeadlineType) {
		newStartingDate[0]._day = 0;
		newStartingDate[0]._month = 0;
		newStartingDate[0]._year = 0;
		newStartingTime[0] = -1;
		newEndingDate[0]._day = 0;
		newEndingDate[0]._month = 0;
		newEndingDate[0]._year = 0;
		newEndingTime[0] = -1;
	}
	else if (!isNewDeadlineType && isCurrentDeadlineType) {
		newDeadlineDate[0]._day = 0;
		newDeadlineDate[0]._month = 0;
		newDeadlineDate[0]._year = 0;
		newDeadlineTime[0] = -1;
	}
	else if (!isNewDeadlineType && !isCurrentDeadlineType) {
		if (!newStartingDate[0].isValidDate() && currentStartingDate[0].isValidDate()) {
			newStartingDate = currentStartingDate;
			newStartingTime[0] = currentStartingTime[0];
			if (!newEndingDate[0].isValidDate() && currentEndingDate[0].isValidDate()) {
				newEndingDate[0]._day = 0;
				newEndingDate[0]._month = 0;
				newEndingDate[0]._year = 0;
				newEndingTime[0] = -1;
			}
			
		}
		//if (!newEndingDate[0].isValidDate() && currentEndingDate[0].isValidDate()) {
		//	newEndingDate = currentEndingDate;
		//	newEndingTime[0] = currentEndingTime[0];
		//}
	}
*/	

	//add update for block
}

//gives back entire block of taskStrings and also a string that contains the task (action + " at " location )
bool TaskLogic::getBlock(std::string& taskString, std::string& taskActionLocation, std::vector<std::string>& blockTaskVector){
	std::string action = "", location ="";
	std::vector<Date> startingDateVector, endingDateVector, deadlineDateVector; 
	std::vector<int> startingTimeVector, endingTimeVector, deadlineTimeVector; //check if we really want to set it as -1
	bool isBlock = false;
	taskParse.processTaskStringFromFile(taskString,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock,dateVector);
	
	taskActionLocation = action + " at " + location; //just the common details. i.e action and location only
	generalSearch(taskActionLocation, blockTaskVector);
	
	if(blockTaskVector.size() > 0)
		return true;
	else
		return false;
}
	
	//for editing location, action of all blocked item.
bool TaskLogic::editBlock(const std::string taskActionLocation, std::vector<std::string>& blockTaskVector){
	for(unsigned int i = 0; i < blockTaskVector.size(); i++)
		edit(taskActionLocation, blockTaskVector[i]);
	return true;
}

	//for adding in new blocks, const string contains action + location while vector string contains timings and dates
bool TaskLogic::addBlock(const std::string taskActionLocation, const std::string originalTaskStrng, std::vector<std::string>& taskDateTimeVector){
	std::string taskString = taskActionLocation + " blockoff";
	tbLinkedList.setBlock(originalTaskString);   //originalTaskString
	for(unsigned int i = 0; i < taskDateTimeVector.size(); i++)
		taskString = taskString + " " + taskDateTimeVector[i];
	if(add(taskString))
		return true;
	else
		return false;
}

	//delete all the blocks of the string given
	//finaliseBlock is the same as deleteBlock. Just give in all those that is meant to be deleted. If only one left, send in isBloack = false
bool TaskLogic::deleteBlock(std::vector<std::string>& blockTaskVector){
	for(unsigned int i=0; i < blockTaskVector.size() ; i++)
		del(blockTaskVector[i]);

	//what if it is finalising? then we must remove the blockoff
	return true;
}


	
//returns number of tasks in the list
//int TaskLogic::getNumTasks(){
//	return 0;
//}
	
//returns a task at the index given
//Task TaskLogic::getTasks(int){
//	Task temp;
//	return temp;
//}
	
void TaskLogic::save(){
    std::vector<std::string> tbVector;
	tbLinkedList.updateStorageVector(tbVector);
	tbStorage.saveTasksIntoFile(tbVector);
}

//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
void TaskLogic::exitLogic(){
	//tbVector.clear();
}

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

//To update taskVector with new command and task by user
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
}

//To undo the most recent command made by user
bool TaskLogic::undo(){
	bool result = true;

	if(commandStackHistory.top() == COMMAND_EDIT){
		if(!del(taskStackHistory.top()))
			result = false;
		taskStackHistory.pop();   //if delete fails we should still remove the task to be done from the system?
		
		if(!addExistingTask(taskStackHistory.top()))
			result = false;
		taskStackHistory.pop();
	
		commandStackHistory.pop();  //whether result true or not, let the command be popped out cos otherwise it can never be done
	}
	else if(commandStackHistory.top() == COMMAND_ADD){
		if(!del(taskStackHistory.top()))
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