#include "TaskLogic.h"
#include <typeinfo>
#include <exception>
#include <iostream>
#include <ctime>


TaskLogic::TaskLogic(){

}

TaskLogic::~TaskLogic(){
}

//Takes in filename and takes all existing tasks inside file into tbLinkedList
void TaskLogic::initLogic(){
	initDate();
	tbStorage.getExistingTasks(tbVector);
	for (unsigned int i = 0; i < tbVector.size(); i++){
		addExistingTask(tbVector[i]); 
	}
	return;
}

//method 1 : User Input ; Method 2 : Pre-Existing Task in file
void TaskLogic::stringParse(const std::string taskString, const int method, std::string &action, std::string &location, std::vector<Date> &startingDate, int &startingTime, std::vector<Date> &endingDate, int &endingTime, std::vector<Date> &deadlineDate, int &deadlineTime){
	if(method == 1){
		taskParse.processTaskStringFromUI(taskString,action,location,startingDate,startingTime,endingDate,endingTime,deadlineDate,deadlineTime,dateVector);
	}
	else if(method == 2){
		taskParse.processTaskStringFromFile(taskString,action,location,startingDate,startingTime,endingDate,endingTime,deadlineDate,deadlineTime,dateVector);
	}

	//add in exceptions
	return;
}

//method 1 : User Input ; Method 2 : Pre-Existing Task in file
std::vector<Task> TaskLogic::createTask(std::string taskString, int method){
	std::string task = "", action = "", location ="";
	std::vector<Date> startingDateVector, endingDateVector, deadlineDateVector; 
	int startingTime = -1, endingTime = -1, deadlineTime = -1; //check if we really want to set it as -1
	bool block = false;

	stringParse(taskString,method,action,location,startingDateVector,startingTime,endingDateVector,endingTime,deadlineDateVector,deadlineTime);   
	
	if(startingDateVector.size() > 1 || endingDateVector.size() > 1 || deadlineDateVector.size() > 1)
		block = true;

	Date startingDate, endingDate, deadlineDate; 
	//PROBLEM!! HOW TO CREATE SO MANY TASK AT ONE GO? MUST BE IN ADD
	//WHAT IF YOU HAVE DIFFERENT NUMBER OF STARTING AND ENDING? Must indicate in that same ending vector / starting vector

	std::vector<Task> taskObjectVector;

	//MUST DO A CHECK TO ENSURE THAT StartingDate Vector and Endng Date Vector must be the same size!
	for(unsigned int i = 0 ; i < startingDateVector.size() ; i++){
		Date deadlineDate;
		Task taskObject(action,location,startingDateVector[i],startingTime,endingDateVector[i],endingTime,deadlineDate,deadlineTime,block);
		taskObjectVector.push_back(taskObject);
	}
	for(unsigned int i = 0 ; i < deadlineDateVector.size() ; i++){
		Date startingDate, endingDate;
		Task taskObject(action,location,startingDate,startingTime,endingDate,endingTime,deadlineDateVector[i],deadlineTime,block);
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
		tbVector.push_back(taskObjectVector[i].getTask()); //only need to push in for user inputs
		if(!tbLinkedList.insert(taskObjectVector[i]))
			checkAdded = false;
	}
	return checkAdded;
}

void TaskLogic::addExistingTask(const std::string taskString){
	std::vector<Task> taskObject; 
    taskObject = createTask(taskString, 2); //generating task from file
	tbLinkedList.insert(taskObject[0]); //FOR EXISTING FILE MUST NOTE THE BLOCKING AS WELL!! 

	return;
}

bool TaskLogic::checkIsValidInput(std::string taskString){
	//check that if there is "at" then there must be a location string behind it.
	//check that if there is "by" then there should not be any timing after that.
	//check that if there is "from" there must be a "to"

	return true;
}
	
//delete a task from the list at the index given
bool TaskLogic::del(const std::string taskString){
	delFromVector(taskString);
	return tbLinkedList.remove(taskString);
}

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

	for(int i = 0; i < 17; i++){
		if(lowerCaseKeyWord == possibleDay[i]){
			keyWordIsDay = true;
			keyword = lowerCaseKeyWord;ve
		}
	}
	return keyWordIsDay;
}
	
	
//edit a task from the list at the index given
//edit firsts breaks it down to check if it needs to edit which component (task, action, location, Date, time) etc.
bool TaskLogic::edit(std::string taskString, std::string editString){
	std::string newTask, newAction = "", newLocation = "", currentAction = "", currentLocation = "";
	Date newStartingDate, newEndingDate, newDeadlineDate, currentStartingDate, currentEndingDate, currentDeadlineDate;
	int newStartingTime = -1, newEndingTime = -1, newDeadlineTime = -1, currentStartingTime = -1, currentEndingTime = -1, currentDeadlineTime = -1; //check if we really want to set it as -1
	bool newBlock = false;

	stringParse(taskString,2,currentAction,currentLocation,currentStartingDate,currentStartingTime,currentEndingDate,currentEndingTime,currentDeadlineDate,currentDeadlineTime);
	stringParse(editString,1,newAction,newLocation,newStartingDate,newStartingTime,newEndingDate,newEndingTime,newDeadlineDate,newDeadlineTime);
	
	newAction = currentAction + newAction;
	newLocation = currentLocation + newLocation;
	if(!newStartingDate.isValidDate()){
		newStartingDate = currentStartingDate;
	}
	if(!newEndingDate.isValidDate()){
		newEndingDate = currentEndingDate;
	}
	if(!newDeadlineDate.isValidDate()){
		newDeadlineDate = currentDeadlineDate;
	}
	if(newStartingTime == -1){
		newStartingTime = currentStartingTime;
	}
	if(newEndingTime == -1){
		newEndingTime = currentEndingTime;
	}
	if(newDeadlineTime == -1){
		newDeadlineTime = currentDeadlineTime;
	}
	
	//add update for block


	Task taskObject(newAction,newLocation,newStartingDate,newStartingTime,newEndingDate,newEndingTime,newDeadlineDate,newDeadlineTime,newBlock);

	delFromVector(taskString);
	tbVector.push_back(taskObject.getTask()); //only need to push in for user inputs
	
	tbLinkedList.remove(taskString);
	tbLinkedList.insert(taskObject);

	return true; // need to do checking
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
	tbStorage.saveTasksIntoFile(tbVector);
}

//Takes in filename and stores all tasks inside tbLinkedList into the file to prepare for exit.
void TaskLogic::exitLogic(){
	save();
	tbVector.clear();
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