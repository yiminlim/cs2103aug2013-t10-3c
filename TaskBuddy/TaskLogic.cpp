#include "TaskLogic.h"
#include <typeinfo>
#include <exception>
#include <iostream>
#include <ctime>

const std::string TaskLogic::COMMAND_ADD = "add";
const std::string TaskLogic::COMMAND_DELETE = "delete";
const std::string TaskLogic::COMMAND_EDIT = "edit";
const std::string TaskLogic::COMMAND_MARKDONE = "markdone";
const std::string TaskLogic::KEYWORD_FROM = "from";
const std::string TaskLogic::KEYWORD_TO = "to";
const std::string TaskLogic::KEYWORD_BY = "by";
const std::string TaskLogic::FILENAME_TB_STORAGE = "taskBuddyStorage.txt";
const std::string TaskLogic::FILENAME_TB_DONE_STORAGE = "taskBuddyDoneStorage.txt";
const std::string TaskLogic::FILENAME_TB_OVERDUE_STORAGE = "taskBuddyOverdueStorage.txt";
const std::string TaskLogic::UI_FORMAT = "ui_format";
const std::string TaskLogic::PROCESSED_FORMAT = "processed_format";
const std::string TaskLogic::BLOCK_OFF = "(blockoff)";
const std::string TaskLogic::FLOATING_TASK = "Floating Task";
const std::string TaskLogic::THROW_MESSAGE_MISSING_ACTION = "Missing action input";
const std::string TaskLogic::THROW_MESSAGE_TASK = "Task \"";
const std::string TaskLogic::THROW_MESSAGE_ADD_FAILURE = "\" cannot be added sucessfully";
const std::string TaskLogic::THROW_MESSAGE_NO_TASK_FOR = "No task for \"";
const std::string TaskLogic::THROW_MESSAGE_NO_TASK_WITH = "No task with \"";
const std::string TaskLogic::THROW_MESSAGE_FOUND = "\" found";
const std::string TaskLogic::THROW_MESSAGE_ONLY_ACTION_LOCATION = "Edit input should only contain task action and/or location";
const std::string TaskLogic::THROW_MESSAGE_DATE_PASSED = "Invalid date input: date has already passed";

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
	std::vector<std::string> tbVector;
	std::vector<std::string> tbDoneVector;
	
	initDate();
	tbStorage.initStorage(FILENAME_TB_STORAGE);
	tbDoneStorage.initStorage(FILENAME_TB_DONE_STORAGE);
	
	tbStorage.getExistingTasks(tbVector);
	tbDoneStorage.getExistingTasks(tbDoneVector);
	
	for(unsigned int i = 0; i < tbVector.size(); i++){
		addExistingTask(tbVector[i]);
	}
	for(unsigned int i = 0; i < tbDoneVector.size(); i++){
		addExistingDoneTask(tbDoneVector[i]);
	}
		
	Date today = taskParse.convertToDate(dateVector[0]);
	tbDoneLinkedList.update(today);

	initOverdue();    //initialisation of Overdue must only be done after all tasks is added into tbLinkedList
	return;
}

/*
	Purpose: Initialises all dates within the next week into dateVector
*/
void TaskLogic::initDate(){
   int i = 1;
   time_t current = time(0);
   std::string currentDateTime;
   std::string today;
   std::string dateArray[9];
   std::istringstream iss(currentDateTime);
   std::string dayArray[8] = {" ","Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

   currentDateTime = ctime(&current);

   iss >> today;
   while(today != dayArray[i])
	  i++;

   dateArray[0] = extractDate(currentDateTime);
   
   // goes till next week's today
   for(int j = 1; j <= 7; j++){
		current += 86400;
		currentDateTime = ctime(&current);
		i++;
		if(i > 7)
			i = 1;  // reset to Monday after Sunday
		dateArray[i] = extractDate(currentDateTime);
		if(j == 1)  //setting for tomorrow's date
			dateArray[8] = dateArray[i];
   }

   for(i = 0; i <= 8 ; i++)
	   dateVector.push_back(dateArray[i]);
   
   assert(!dateVector.empty());
   assert(dateVector.size() == 9);
   return;
}

//The list must be drawn from the file first before drawing from linkedlist
void TaskLogic::initOverdue(){
	std::vector<std::string> tbOverdueVector;
	Date today = taskParse.convertToDate(dateVector[0]);
	
	tbOverdueStorage.initStorage(FILENAME_TB_OVERDUE_STORAGE);
	tbOverdueStorage.getExistingTasks(tbOverdueVector);
	for(unsigned int i=0; i< tbOverdueVector.size(); i++){
		addOverdueTask(tbOverdueVector[i]);
	}
	tbOverdueVector.clear();

	tbLinkedList.getOverdueList(today, tbOverdueVector);
	for(unsigned int i=0; i< tbOverdueVector.size(); i++){
		del(tbOverdueVector[i], false);
		addOverdueTask(tbOverdueVector[i]);
	}
	//initialisation of tbLinkedList must be done first.
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

void TaskLogic::saveDone(){
    std::vector<std::string> tbDoneVector;
	tbDoneLinkedList.updateStorageVector(tbDoneVector);
	tbDoneStorage.saveTasksIntoFile(tbDoneVector);
}

void TaskLogic::saveOverdue(){
    std::vector<std::string> tbOverdueVector;
	tbOverdueLinkedList.updateStorageVector(tbOverdueVector);
	tbOverdueStorage.saveTasksIntoFile(tbOverdueVector);
}


//-----ADD TASK---------------------------------------------------------------------------------------------------

/*
	Purpose: Converts a task input string into a Task and adds it into tbLinkedList and indicates to UI if there's clashes
	Pre-conditions: taskString is not empty and should not contain the command word
	Post-conditions: true is returned only if task is added successfully, given that the input given by user is valid
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
void TaskLogic::add(const std::string taskString, bool& isClash, std::vector<std::string>& clashTasks, std::vector<std::string>& addedTask){
	std::vector<Task> taskObjectVector;
	bool clash;
	int addCount = 0;
	assert(clashTasks.empty());

    try{
		taskObjectVector = createTask(taskString, UI_FORMAT);
		for (unsigned int i = 0; i < taskObjectVector.size(); i++) {
			if(taskObjectVector[i].getAction() == "") {
				throw (std::runtime_error(THROW_MESSAGE_MISSING_ACTION));
			}
			checkValidTask(taskObjectVector[i]);
		}
	}
	catch(...){
		throw;
	}

	assert(!taskObjectVector.empty());

	for(unsigned int i = 0; i < taskObjectVector.size() ; i++){
		clash = false;
		if(tbLinkedList.insert(taskObjectVector[i], clash, clashTasks)){
			addedTask.push_back(taskObjectVector[i].getTask());
			update(COMMAND_ADD, taskObjectVector[i].getTask(), "");
			addCount++;
		}
		else
			throw std::runtime_error(THROW_MESSAGE_TASK+ taskObjectVector[i].getTask() + THROW_MESSAGE_ADD_FAILURE);
		if(clash)
			isClash = true;
	}
	updateCount(addCount);
}

/*
	Purpose: Converts a task input string from storage file into a Task and adds it into tbLinkedList
	Pre-conditions: taskString is not empty and is in the proper format
	Post-conditions: true is returned only if task is added successfully, given that the input is in proper format
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
void TaskLogic::addExistingTask(const std::string taskString){
	std::vector<Task> taskObjectVector;
	std::vector<std::string> dummyVector;
	bool isClash = false;
    
	taskObjectVector = createTask(taskString, PROCESSED_FORMAT); 
	assert(taskObjectVector.size() == 1);
	
	assert(tbLinkedList.insert(taskObjectVector[0], isClash, dummyVector));  //there is no need to check if isClashed since these are pre-existing task.
}

void TaskLogic::addExistingDoneTask(const std::string taskString){
	std::vector<Task> taskObjectVector;
    
	taskObjectVector = createTask(taskString, PROCESSED_FORMAT);
	assert(taskObjectVector.size() == 1);
	
	assert(tbDoneLinkedList.insert(taskObjectVector[0]));  
}

void TaskLogic::addOverdueTask(const std::string taskString){
	std::vector<Task> taskObjectVector;
    
	taskObjectVector = createTask(taskString, PROCESSED_FORMAT);
	assert(taskObjectVector.size() == 1);

	assert(tbOverdueLinkedList.insert(taskObjectVector[0]));  
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
void TaskLogic::del(const std::string taskString, bool isUndoDel){
	assert(!taskString.empty());
	std::string editedString = removeBlockoff(taskString);

	if(tbLinkedList.checkIfRemainingTask(editedString))
		assert(tbLinkedList.remove(editedString, getActionLocation(editedString)));
	else
		assert(tbLinkedList.remove(taskString, getActionLocation(taskString)));
	
	if(!isUndoDel){
		update(COMMAND_DELETE, taskString, "");
		updateCount(1);
	}
}


//-----SEARCH TASK--------------------------------------------------------------------------------------------------

/*
	Purpose: Search for all task in the list that contains keyword and place these tasks into vector parameter
	Pre-conditions: userInput is not empty
	Post-conditions: true is returned only if task(s) can be found, given that all input given by user is valid
	Equivalence Partition: Empty string, Invalid string, Valid string
	Boundary: Empty string, Any valid string, Any invalid string
*/
void TaskLogic::generalSearch(std::string userInput, std::vector<std::string>& vectorOutput, std::vector<std::string>& dates){
	assert(vectorOutput.empty());
	assert(dates.empty());
	
	std::vector<std::string> keywordVector;
	std::string dayKeyword;
	std::string keyword;
	
	std::stringstream iss;
	iss << userInput;

	while (iss >> keyword){
		if(isDay(keyword)){
			dayKeyword = keyword;
			keyword = taskParse.changeDayToDate(keyword, dateVector);			
		}
		keywordVector.push_back(keyword);
	}
	tbLinkedList.retrieve(keywordVector, vectorOutput);
	
	if(vectorOutput.empty()){
		if(!dayKeyword.empty())
			throw std::runtime_error(THROW_MESSAGE_NO_TASK_FOR + dayKeyword + THROW_MESSAGE_FOUND);
		else
			throw std::runtime_error(THROW_MESSAGE_NO_TASK_WITH + userInput + THROW_MESSAGE_FOUND);
	}
	else
		vectorOutput = processSearchOutputVector(vectorOutput, dates);
}

std::vector<std::string> TaskLogic::processSearchOutputVector(std::vector<std::string> vectorOutput, std::vector<std::string>& dates){
	assert(!vectorOutput.empty());
	assert(dates.empty());
	std::vector<std::string> newVectorOutput;
	std::vector<Date> outputDateVector = getSearchOutputDateVector(vectorOutput);
	
	newVectorOutput.push_back(vectorOutput[0]);
	dates.push_back(convertToDateString(outputDateVector[0]));
	for(unsigned int i=1; i< vectorOutput.size(); i++){
		if(!checkSameDate(outputDateVector[i-1], outputDateVector[i])){
			newVectorOutput.push_back("");
			dates.push_back(convertToDateString(outputDateVector[i]));
		}
		newVectorOutput.push_back(vectorOutput[i]);
	}

	return newVectorOutput;
}

std::vector<Date> TaskLogic::getSearchOutputDateVector(std::vector<std::string> vectorOutput){
	assert(!vectorOutput.empty());
	std::vector<Date> outputDateVector;

	for(unsigned int i = 0; i < vectorOutput.size() ; i++){
		std::string task = "", action = "", location ="";
		std::vector<Date> startingDateVector, endingDateVector, deadlineDateVector; 
		std::vector<int> startingTimeVector, endingTimeVector, deadlineTimeVector;
		Date floatingDate;
		bool isBlock = false;
		
		stringParse(vectorOutput[i],PROCESSED_FORMAT,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock);   
		
		if(!startingDateVector[0].isEmptyDate())
			outputDateVector.push_back(startingDateVector[0]);
		else if(!deadlineDateVector[0].isEmptyDate())
			outputDateVector.push_back(deadlineDateVector[0]);
		else														
			outputDateVector.push_back(floatingDate);
	}
	assert(vectorOutput.size() == outputDateVector.size());
	return outputDateVector;
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
void TaskLogic::edit(std::string taskString, std::string editString, bool isBlock, std::vector<std::string>& clashTasks, std::string& editedTask){
	std::string newTask;
	std::string newAction = "";
	std::string newLocation = "";
	std::string currentAction = "";
	std::string currentLocation = "";
	std::vector<Date> newStartingDate; 
	std::vector<Date> newEndingDate; 
	std::vector<Date> newDeadlineDate; 
	std::vector<Date> currentStartingDate; 
	std::vector<Date> currentEndingDate; 
	std::vector<Date> currentDeadlineDate;
	std::vector<int> newStartingTime; 
	std::vector<int> newEndingTime;
	std::vector<int> newDeadlineTime; 
	std::vector<int> currentStartingTime; 
	std::vector<int> currentEndingTime;
	std::vector<int> currentDeadlineTime; 
	bool newIsBlock = false;
	bool isClashDummy = false;  

	try{
		stringParse(taskString,PROCESSED_FORMAT,currentAction,currentLocation,currentStartingDate,currentStartingTime,currentEndingDate,currentEndingTime,currentDeadlineDate,currentDeadlineTime, isBlock);
		stringParse(editString,UI_FORMAT,newAction,newLocation,newStartingDate,newStartingTime,newEndingDate,newEndingTime,newDeadlineDate,newDeadlineTime, newIsBlock);  
	}
	catch(...){
		throw;
	}
	
	if (newAction == "" && currentAction != "")
		newAction = currentAction;
	if (newLocation == "" && currentLocation != "")
		newLocation = currentLocation;

	newIsBlock = isBlock;

	//true if date has been edited
	if(!newDeadlineDate[0].isEmptyDate() || !newStartingDate[0].isEmptyDate() || !newEndingDate[0].isEmptyDate() ){
		changeDateCurrentIntoNew(newStartingDate[0],currentStartingDate[0],newEndingDate[0],currentEndingDate[0],newDeadlineDate[0],currentDeadlineDate[0]);
		changeTimeCurrentIntoNew(newStartingTime[0],currentStartingTime[0],newEndingTime[0],currentEndingTime[0],newDeadlineTime[0],currentDeadlineTime[0]);
	}
	
	Task taskObject(newAction,newLocation,newStartingDate[0],newStartingTime[0],newEndingDate[0],newEndingTime[0],newDeadlineDate[0],newDeadlineTime[0],newIsBlock);
	
	std::string editedString = removeBlockoff(taskString);
	if(tbLinkedList.checkIfRemainingTask(editedString))
		tbLinkedList.remove(editedString, getActionLocation(editedString));
	else
		tbLinkedList.remove(taskString, getActionLocation(taskString));

	tbLinkedList.insert(taskObject, isClashDummy, clashTasks);
	editedTask = taskObject.getTask();

	update(COMMAND_EDIT, editedTask, taskString);
	updateCount(1);
}

void TaskLogic::changeDateCurrentIntoNew(Date& newStartingDate, Date currentStartingDate, Date& newEndingDate, Date currentEndingDate, Date& newDeadlineDate, Date currentDeadlineDate){
	newStartingDate = currentStartingDate;
	newEndingDate = currentEndingDate;
	newDeadlineDate = currentDeadlineDate;
}

void TaskLogic::changeTimeCurrentIntoNew(int& newStartingTime, int currentStartingTime, int& newEndingTime, int currentEndingTime, int& newDeadlineTime, int currentDeadlineTime){
	newStartingTime = currentStartingTime;
	newEndingTime = currentEndingTime;
	newDeadlineTime = currentDeadlineTime;
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
void TaskLogic::getBlock(std::string& taskString, std::string& taskActionLocation, std::vector<std::string>& blockTaskVector, std::vector<std::string>& dates){	
	assert(!taskString.empty());
	assert(blockTaskVector.empty());
	assert(dates.empty());
	
	taskActionLocation = getActionLocation(taskString);
	generalSearch(taskActionLocation, blockTaskVector,dates);
	
	assert(!blockTaskVector.empty());
	assert(!dates.empty());
}

/*
	Purpose: edit the action and location of all task in the block to the newTaskActionLocation
	Pre-conditions: newTaskActionLocation is not empty and is valid
					blockTaskVector is not-empty and is in proper format
	Post-conditions: true is returned only if all tasks are edited correctly, given that all inputs are valid
					 
	Equivalence Partition: Empty string, Invalid string, Valid string, empty vector, invalid vector strings, valid vector strings
	Boundary: Empty string, Any valid string, Any invalid string, empty vector, any invalid vector strings, any valid vector strings
*/
void TaskLogic::editBlock(const std::string newTaskActionLocation, std::vector<std::string>& blockTaskVector){
	bool isValidEdit = true;
	bool dummyBlock = false;
	int editCount=0;
	std::string editedTaskString;
	std::vector<std::string> dummyVector;
	
	if(!isOnlyActionLocation(newTaskActionLocation))
		throw (std::runtime_error(THROW_MESSAGE_ONLY_ACTION_LOCATION));

	try{
		for(unsigned int i = 0; i < blockTaskVector.size(); i++){
		edit( blockTaskVector[i], newTaskActionLocation, dummyBlock, dummyVector, editedTaskString);
		editCount++;
		}
	}
	catch(...){
		throw;
	}

	for(int i=1; i <= editCount; i++)
		countStackHistory.pop();
	countStackHistory.push(editCount);
}

bool TaskLogic::isOnlyActionLocation(std::string newTaskActionLocation){
	newTaskActionLocation = taskParse.convertToLowercase(newTaskActionLocation);
	std::istringstream iss(newTaskActionLocation);
	std::string word;
	bool noDate = true;
	
	while(iss >> word && noDate == true){
		if(word == KEYWORD_FROM || word == KEYWORD_TO || word == KEYWORD_BY)
			noDate = false;
	}
	return noDate;
}

std::string TaskLogic::removeBlockoff(std::string taskString){
	assert(!taskString.empty());
	
	size_t posBlockOff = taskString.find(BLOCK_OFF);
	
	if(posBlockOff != std::string::npos)
		return taskString.substr(0, posBlockOff-1);
	return taskString;
}

/*
	Purpose: Adds in all new tasks into tbLinkedList and also mark the original task as blocked if not already blocked.
	Pre-conditions: taskString is not empty and is valid (contains key word such as "blockoff"
	Post-conditions: true is returned only if all tasks are added successfully, given that all inputs are valid
	Equivalence Partition: Empty strings, Invalid strings, Valid strings
	Boundary: Empty strings, Any valid strings, Any invalid strings
*/
void TaskLogic::addBlock(const std::string taskString, const std::string originalTaskString, bool isClash, std::vector<std::string>& clashTasks, std::vector<std::string>& addedTask){
	assert(!taskString.empty());
	
	tbLinkedList.setBlock(originalTaskString);   
	add(taskString, isClash, clashTasks, addedTask);
}

/*
	Purpose: Finalise blocking to only one task by removing all others. Del ensures that the sole task remaining is not marked
			 as blocked anymore
	Pre-conditions: all strings in blockTaskVector is of proper format. delIndex is withing the range of blockTaskVector
	Post-conditions: true is returned only if block is finalised, given that all inputs are valid
	Equivalence Partition: valid int index, invalid int index, empty vector, empty strings, valid strings, invalid strings
	Boundary: index 0, index 1, index size-1, any invalid index, Empty vector, Empty strings, Any valid strings, Any invalid strings
*/
void TaskLogic::finaliseBlock(int delIndex, std::vector<std::string>& blockTaskVector){
	assert(!blockTaskVector.empty());
	
	int deleteCount = 0;
	delIndex -= 1; //convert to 0-based
	try{
		for(unsigned int i=0; i < blockTaskVector.size() ; i++){
			if(i != delIndex){
				del(blockTaskVector[i],false);
				deleteCount++;
			}
		}
	}catch(...){
		throw;
	}
	for(int i=1; i<=deleteCount; i++)
		countStackHistory.pop();
	countStackHistory.push(deleteCount);
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

	if (command == COMMAND_EDIT || command == COMMAND_MARKDONE){
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

void TaskLogic::updateCount(int count){
	countStackHistory.push(count);
}

void TaskLogic::undoEdit(std::vector<std::string>& undoTask1, std::vector<std::string>& undoTask2){
	undoTask2.push_back(taskStackHistory.top());
	del(taskStackHistory.top(),true);
	taskStackHistory.pop();   //if delete fails we should still remove the task to be done from the system?
			
	undoTask1.push_back(taskStackHistory.top());
	addExistingTask(taskStackHistory.top());
	taskStackHistory.pop();
	
	commandStackHistory.pop();  //whether result true or not, let the command be popped out cos otherwise it can never be done	
}

void TaskLogic::undoAdd(std::vector<std::string>& undoTask){
	undoTask.push_back(taskStackHistory.top());
	del(taskStackHistory.top(),true);
	taskStackHistory.pop();
		
	commandStackHistory.pop();
}

void TaskLogic::undoDelete(std::vector<std::string>& undoTask){
	undoTask.push_back(taskStackHistory.top());
	addExistingTask(taskStackHistory.top());
	taskStackHistory.pop();

	commandStackHistory.pop();
}

void TaskLogic::undoMarkDone(std::vector<std::string>& undoTask){
	undoTask.push_back(taskStackHistory.top());
	tbDoneLinkedList.removeTask(taskStackHistory.top());
	taskStackHistory.pop();   //if delete fails we should still remove the task to be done from the system?
		
	addExistingTask(taskStackHistory.top());
	taskStackHistory.pop();

	commandStackHistory.pop();  //whether result true or not, let the command be popped out cos otherwise it can never be done
}


/*
	Purpose: Undo the last previous command stored at the top of commandStackHistory
	Pre-conditions: commandStackHistory is not empty, and taskStackHistory is not empty and contains sufficient tasks
					to undo the command.
	Post-condition: returns true if undo is successful.
	Equivalence Partition: empty commandStackHistory, empty taskStackHistory, insufficient taskStackHistory, invalid command, command == COMMAND_EDIT, command == COMMAND_ADD, command == COMMAND_DELETE
	Boundary: empty commandStackHistory, empty taskStackHistory, insufficient taskStackHistory, invalid command, command == COMMAND_EDIT, command == COMMAND_ADD, command == COMMAND_DELETE
*/
void TaskLogic::undo(std::string& command, std::vector<std::string>& undoTask1, std::vector<std::string>& undoTask2){
	assert(!checkUndoStackEmpty());
	command = commandStackHistory.top();
	int undoCount = countStackHistory.top();

	for(int i=1; i<= undoCount; i++){
		if(commandStackHistory.top() == COMMAND_EDIT){
			assert(commandStackHistory.top() == command);
			undoEdit(undoTask1, undoTask2);
		}
		else if(commandStackHistory.top() == COMMAND_ADD){
			assert(commandStackHistory.top() == command);
			undoAdd(undoTask1);
		}
		else if(commandStackHistory.top() == COMMAND_DELETE){
			assert(commandStackHistory.top() == command);
			undoDelete(undoTask1);
		}
		else if(commandStackHistory.top() == COMMAND_MARKDONE){
			assert(commandStackHistory.top() == command);
			undoMarkDone(undoTask1);
		}
	}
	countStackHistory.pop();
}

//-----HELPER FUNCTIONS---------------------------------------------------------------------------------------------

//method 1 : User Input ; Method 2 : Pre-Existing Task in file
void TaskLogic::stringParse(const std::string taskString, const std::string format, std::string &action, std::string &location, std::vector<Date> &startingDateVector, std::vector<int> &startingTimeVector, std::vector<Date> &endingDateVector, std::vector<int> &endingTimeVector, std::vector<Date> &deadlineDateVector, std::vector<int> &deadlineTimeVector, bool &isBlock){
	assert(format == UI_FORMAT || format == PROCESSED_FORMAT);
	try{	
		if(format == UI_FORMAT)
			taskParse.processTaskStringFromUI(taskString,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock,dateVector);
		else // PROCESSED_FORMAT
			taskParse.processTaskStringFromFile(taskString,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock);
	}
	catch(...){
		throw;
	}
	return;
}

//method 1 : User Input ; Method 2 : Pre-Existing Task in file
std::vector<Task> TaskLogic::createTask(std::string taskString, std::string format){
	std::string task = "";
	std::string	action = "";
	std::string	location ="";
	std::vector<Date> startingDateVector;
	std::vector<Date> endingDateVector;
	std::vector<Date> deadlineDateVector; 
	std::vector<int> startingTimeVector;
	std::vector<int> endingTimeVector; 
	std::vector<int> deadlineTimeVector; 
	bool isBlock = false;
	
	try{
		stringParse(taskString,format,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock);   
	}
	catch(...){
		throw;
	}
	if(startingDateVector.size() > 1 || endingDateVector.size() > 1 || deadlineDateVector.size() > 1)
		isBlock = true;

	std::vector<Task> taskObjectVector;

	assert(startingDateVector.size() == endingDateVector.size());

	Date nullDate;
	int nullTime = -1;
	
	// true if floating type
	if(startingDateVector.size()==1 && startingDateVector[0].isEmptyDate() && deadlineDateVector.size()==1 && deadlineDateVector[0].isEmptyDate()){
		Task taskObject(action,location,nullDate,nullTime,nullDate,nullTime,nullDate,nullTime,isBlock);
		taskObjectVector.push_back(taskObject);
	}
	else{
		for(unsigned int i = 0 ; i < startingDateVector.size() && !startingDateVector[i].isEmptyDate(); i++){
			Task taskObject(action,location,startingDateVector[i],startingTimeVector[i],endingDateVector[i],endingTimeVector[i],nullDate,nullTime,isBlock);
			taskObjectVector.push_back(taskObject);
		}
		for(unsigned int i = 0 ; i < deadlineDateVector.size() && !deadlineDateVector[i].isEmptyDate() ; i++){
			Task taskObject(action,location,nullDate,nullTime,nullDate,nullTime,deadlineDateVector[i],deadlineTimeVector[i],isBlock);
			taskObjectVector.push_back(taskObject);
		}
	}
	return taskObjectVector;
}

bool TaskLogic::isDay(std::string& keyword){
	std::string possibleDay[20] = {"today","tmr","tomorrow","mon","monday","tue","tues","tuesday","wed","wednesday","thu","thur","thurs","thursday","fri","friday","sat","saturday","sun","sunday"};
	bool keyWordIsDay = false;
    std::string lowerCaseKeyWord = taskParse.convertToLowercase(keyword);

	for(int i = 0; i < 20 && !keyWordIsDay ; i++){
		if(lowerCaseKeyWord == possibleDay[i]){
			keyWordIsDay = true;
			keyword = lowerCaseKeyWord;
		}
	}
	return keyWordIsDay;
}
	
std::string TaskLogic::extractDate(std::string currentDateTime){
	std::ostringstream oss;
	std::istringstream iss(currentDateTime);
	std::string day, month, time, monthArray[13] = {" ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    int date, year, monthNum = 1;	

	iss >> day >> month >> date >> time >> year;

	while(month != monthArray[monthNum])
		monthNum ++;
	
	if(isSingleDigit(date))
		oss << "0";
	oss << date << "/";
	if(isSingleDigit(monthNum))
		oss << "0";
	oss << monthNum << "/" << year; 
	return oss.str();
}   

bool TaskLogic::isSingleDigit(int num){
	assert(num > 0);
	if(num/10)
		return false;
	else
		return true;
}

std::string TaskLogic::convertToDateString(Date date){
	std::ostringstream oss;
	if(!date.isEmptyDate())
		oss << date._day << "/" << date._month << "/" << date._year;
	else
		oss << FLOATING_TASK;
	return oss.str();
}

std::string TaskLogic::getActionLocation(std::string taskString){
	std::string task = "";
	std::string	action = "";
	std::string	location ="";
	std::vector<Date> startingDateVector;
	std::vector<Date> endingDateVector;
	std::vector<Date> deadlineDateVector; 
	std::vector<int> startingTimeVector;
	std::vector<int> endingTimeVector; 
	std::vector<int> deadlineTimeVector; 
	bool isBlock = false;
	
	taskParse.processTaskStringFromFile(taskString,action,location,startingDateVector,startingTimeVector,endingDateVector,endingTimeVector,deadlineDateVector,deadlineTimeVector,isBlock);
	
	assert(action != "");
	std::string taskActionLocation = action;
	if(location != "")
		taskActionLocation = taskActionLocation + " at " + location;
	return taskActionLocation;
}

bool TaskLogic::checkUndoStackEmpty(){
	return (commandStackHistory.empty() || taskStackHistory.empty());
}

void TaskLogic::checkValidTask(Task task){
	if(task.isDeadlineType()){
		assert(task.getStartingDate().isEmptyDate());
		assert(task.getEndingDate().isEmptyDate());
		assert(task.getStartingTime() == -1);
		assert(task.getEndingTime() == -1);
		assert(!task.getDeadlineDate().isEmptyDate());
		if(!(taskParse.convertToDate(dateVector[0]).isLaterDate(task.getDeadlineDate()) || taskParse.convertToDate(dateVector[0]).isSameDate(task.getDeadlineDate())))
			throw (std::runtime_error(THROW_MESSAGE_DATE_PASSED));
	}
	else if(task.isActivityType()){
		assert(task.getDeadlineDate().isEmptyDate());
		assert(task.getDeadlineTime() == -1);
		assert(!task.getStartingDate().isEmptyDate());
		if(!(taskParse.convertToDate(dateVector[0]).isLaterDate(task.getStartingDate()) || taskParse.convertToDate(dateVector[0]).isSameDate(task.getStartingDate())))
			throw (std::runtime_error(THROW_MESSAGE_DATE_PASSED));

	}
	else if(task.isFloatingType()){
		assert(task.getStartingDate().isEmptyDate());
		assert(task.getEndingDate().isEmptyDate());
		assert(task.getDeadlineDate().isEmptyDate());
		assert(task.getStartingTime() == -1);
		assert(task.getEndingTime() == -1);
		assert(task.getDeadlineTime() == -1);
	}
}
	
bool TaskLogic::checkSameDate(Date earlierDate, Date laterDate){
	assert(earlierDate.isEmptyDate() || earlierDate.isValidDate());
	assert(laterDate.isEmptyDate() || laterDate.isValidDate());
	
	return(earlierDate._year == laterDate._year) && (earlierDate._month == laterDate._month) && (earlierDate._day == laterDate._day);
}

//-----MARK DONE----------------------------------------------------------------------------------------------------------
void TaskLogic::markDone(std::string taskString){
	assert(!taskString.empty());

	del(taskString,false); 
	std::vector<Task> taskObjectVector;
	
	taskObjectVector = createTask(taskString, PROCESSED_FORMAT);
	assert(taskObjectVector.size() == 1);

	assert(tbDoneLinkedList.insert(taskObjectVector[0]));
	update(COMMAND_MARKDONE,taskString,taskString);
	updateCount(1);
}

bool TaskLogic::retrieveDoneList(std::vector<std::string>& tbDoneVector){
	tbDoneLinkedList.updateStorageVector(tbDoneVector);
	if(tbDoneVector.empty())
		return false;
	else
		return true;
}


//-----OVERDUE------------------------------------------------------------------------------------------------------------

void TaskLogic::clearOverdueList(){
	tbOverdueLinkedList.clear();
	assert(tbOverdueLinkedList.isEmpty());
}

bool TaskLogic::retrieveOverdueList(std::vector<std::string>& tbOverdueVector){
	tbOverdueLinkedList.updateStorageVector(tbOverdueVector);
	if(tbOverdueVector.empty())
		return false;
	else
		return true;
}