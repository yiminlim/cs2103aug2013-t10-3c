#include "Parse.h" 
#include <iostream>
#include <assert.h>

const std::string Parse::KEYWORD_ADD = "add";
const std::string Parse::KEYWORD_LOCATION = "at";
const std::string Parse::KEYWORD_STARTING = "from";
const std::string Parse::KEYWORD_ENDING = "to";
const std::string Parse::KEYWORD_DEADLINE = "by";

//takes in a string creates a Task object 
Task Parse::generateTaskFromUserInput(std::string taskString){
	std::string task = "";
	std::string action = "";
	std::string location = "";
	Date startingDate;
	int startingTime = 0;
	Date endingDate;
	int endingTime = 0;
	Date deadlineDate;
	int deadlineTime = 0;

	bool isDeadLineType = false; //type is to show if its deadline type or not. true if it is deadline type

	std::istringstream userInput(taskString);
	std::string word;
	std::vector<std::string> input;

	while (userInput >> word) {
		input.push_back(word);
	}

	std::string keyword = "";

	for (unsigned int i = 0; i < input.size(); i++) { //must always start with command
		if (isKeyword(input[i])) {
			keyword = input[i];
		}
		else if (keyword == KEYWORD_ADD) {
			if (action != "") {
				action += " ";
			}
			action += input[i];
		}
		else if (keyword == KEYWORD_LOCATION) {
			if (location != "") {
				location += " ";
			}
			location += input[i];
		}
		else if (keyword == KEYWORD_STARTING) {
			if (input[i].find("/") != std::string::npos) {
				startingDate = convertToDate(input[i]);
			}
			else {
				startingTime = convertToTime(input[i]);
			}
		}
		else if (keyword == KEYWORD_ENDING) {
			if (input[i].find("/") != std::string::npos) {
				endingDate = convertToDate(input[i]);
			}
			else {
				endingTime = convertToTime(input[i]);
			}
		}
		else if (keyword == KEYWORD_DEADLINE) {
			if (input[i].find("/") != std::string::npos) {
				deadlineDate = convertToDate(input[i]);
			}
			else {
				deadlineTime = convertToTime(input[i]);
			}
			isDeadLineType = true;
		}
	}
	task = formatTask(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, isDeadLineType);

	Task taskObject(task, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime);
	
	return taskObject;
}

bool Parse::isKeyword(std::string word) {
	return word == KEYWORD_ADD || word == KEYWORD_DEADLINE || word == KEYWORD_ENDING || word == KEYWORD_LOCATION || word == KEYWORD_STARTING;
}

std::string Parse::formatTask(std::string action, std::string location, Date startingDate, int startingTime, Date endingDate, int endingTime, Date deadlineDate, int deadlineTime, bool isDeadLineType) {
	std::ostringstream output;
	if (isDeadLineType) {
		assert (deadlineTime >= 0 && deadlineTime <= 2359);
		output << "by " << deadlineDate._day << "/" << deadlineDate._month << "/" << deadlineDate._year;
		output << " " << deadlineTime << " hrs";
		output << ": " << action;
		if (location.size() > 0) {
			output << " at " << location;
		}
	}
	else {
		output << startingDate._day << "/" << startingDate._month << "/" << startingDate._year;
		output << " " << startingTime << " hrs";
		if (endingDate._day && endingDate._month && endingDate._year) {
			output << " - " << endingDate._day << "/" << endingDate._month << "/" << endingDate._year;
			output << " " << endingTime << " hrs";
		}
		output << ": " << action;
		if (location.size() > 0) {
		output << " at " << location;
		}
	}

	return output.str();
}

Task Parse::retrieveTask(std::string taskString){
	std::string task = "";
	std::string action = "";
	std::string location = "";
	Date startingDate;
	int startingTime = 0;
	Date endingDate;
	int endingTime = 0;
	Date deadlineDate;
	int deadlineTime = 0;

	bool isDeadLineType = false; //CHECK LATER!!

	std::istringstream retrievedTask(taskString);
	std::string word;
	std::vector<std::string> taskDetails;

	while (retrievedTask >> word) {
		taskDetails.push_back(word);
	}

	if (taskDetails[0] == KEYWORD_DEADLINE) {
		isDeadLineType = true; //NOTE!!
		deadlineDate = convertToDate(taskDetails[1]);
		deadlineTime = convertToTime(taskDetails[2]);
		unsigned int i = 4;
		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_LOCATION) {
			if (action != "") {
				action += " ";
			}
			action += taskDetails[i];
			i++;
		}
		
		if (i < taskDetails.size() && taskDetails[i] == KEYWORD_LOCATION) {
			i++;
		}

		while (i < taskDetails.size()) {
			if (location != "") {
				location += " ";
			}
			location += taskDetails[i];
			i++;
		}
	}

	else {
		startingDate = convertToDate(taskDetails[0]);
		startingTime = convertToTime(taskDetails[1]);
		unsigned int i = 3;
		if (taskDetails[3] == "-") {
			endingDate = convertToDate(taskDetails[4]);
			endingTime = convertToTime(taskDetails[5]);
			i = 7;
		}

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_LOCATION) {
			if (action != "") {
				action += " ";
			}
			action += taskDetails[i];
			i++;
		}
		
		if (i < taskDetails.size() && taskDetails[i] == KEYWORD_LOCATION) {
			i++;
		}

		while (i < taskDetails.size()) {
			if (location != "") {
				location += " ";
			}
			location += taskDetails[i];
			i++;
		}
	}

	task = formatTask(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime, isDeadLineType);

	Task taskObject(task, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime);
	
	return taskObject;

}


Date Parse::convertToDate(std::string dateString){
	Date date; 
	char dateSeparator = '/';


	size_t posFirstDateSeparator = dateString.find(dateSeparator);
	size_t posSecondDateSeparator = dateString.find(dateSeparator, posFirstDateSeparator+1);

	std::string dayString = dateString.substr(0, posFirstDateSeparator-0); 
	std::string monthString = dateString.substr(posFirstDateSeparator+1, posSecondDateSeparator-posFirstDateSeparator-1);
	std::string yearString = dateString.substr(posSecondDateSeparator+1);

	std::istringstream dayInput(dayString);
	std::istringstream monthInput(monthString);
	std::istringstream yearInput(yearString);

	dayInput >> date._day;
	monthInput >> date._month;
	yearInput >> date._year;

	return date;
}


int Parse::convertToTime(std::string timeString){
	int time;
	std::istringstream timeInput(timeString);
	
	timeInput >> time;

	return time;
}