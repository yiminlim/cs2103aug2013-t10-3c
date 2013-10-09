#include "Parse.h" 

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
	Task::Date startingDate = Task::Date();
	int startingTime = 0;
	Task::Date endingDate = Task::Date();
	int endingTime = 0;
	Task::Date deadlineDate = Task::Date();
	int deadlineTime = 0;

	std::istringstream userInput(taskString);
	std::string word;
	std::vector<std::string> input;

	while (userInput) {
		userInput >> word; 
		input.push_back(word);
	}

	std::string keyword = "";

	for (int i = 0; i < input.size(); i++) {
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
			if (input[i].find("/")) {
				startingDate = convertToDate(input[i]);
			}
			else {
				startingTime = convertToTime(input[i]);
			}
		}
		else if (keyword == KEYWORD_ENDING) {
			if (input[i].find("/")) {
				endingDate = convertToDate(input[i]);
			}
			else {
				endingTime = convertToTime(input[i]);
			}
		}
		else if (keyword == KEYWORD_DEADLINE) {
			if (input[i].find("/")) {
				deadlineDate = convertToDate(input[i]);
			}
			else {
				deadlineTime = convertToTime(input[i]);
			}
		}
	}

	task = formatTask(action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime);

	Task taskObject(task, action, location, startingDate, startingTime, endingDate, endingTime, deadlineDate, deadlineTime);
	
	return taskObject;
}

bool Parse::isKeyword(std::string word) {
	return word == KEYWORD_ADD || word == KEYWORD_DEADLINE || word == KEYWORD_ENDING || word == KEYWORD_LOCATION || word == KEYWORD_STARTING;
}

std::string Parse::formatTask(std::string action, std::string location, Task::Date startingDate, int startingTime, Task::Date endingDate, int endingTime, Task::Date deadlineDate, int deadlineTime) {
	std::ostringstream output;
	if (deadlineDate.day && deadlineDate.month && deadlineDate.year) {
		output << "by " << deadlineDate.day << "/" << deadlineDate.month << "/" << deadlineDate.year;
		output << " " << deadlineTime << " hrs";
		output << ": " << action;
		if (location.size() > 0) {
			output << " at " << location;
		}
	}
	else {
		output << startingDate.day << "/" << startingDate.month << "/" << startingDate.year;
		output << " " << startingTime << " hrs";
		if (endingDate.day && endingDate.month && endingDate.year) {
			output << " - " << endingDate.day << "/" << endingDate.month << "/" << endingDate.year;
			output << " " << endingTime << " hrs";
			output << ": " << action;
			if (location.size() > 0) {
				output << " at " << location;
			}
		}
	}

	output << "\n";
	
	return output.str();
}

Task Parse::retrieveTask(std::string){
	Task taskObject;
	return taskObject;
}

Task::Date Parse::convertToDate(std::string dateString){
	Task::Date date; 
	char dateSeparator = '/';

	size_t posFirstDateSeparator = dateString.find(dateSeparator);
	size_t posSecondDateSeparator = dateString.find(dateSeparator, posFirstDateSeparator+1);

	std::string dayString = dateString.substr(0, posFirstDateSeparator-0); 
	std::string monthString = dateString.substr(posFirstDateSeparator+1, posSecondDateSeparator-posFirstDateSeparator-1);
	std::string yearString = dateString.substr(posSecondDateSeparator+1);

	std::istringstream dayInput(dayString);
	std::istringstream monthInput(monthString);
	std::istringstream yearInput(yearString);

	dayInput >> date.day;
	monthInput >> date.month;
	yearInput >> date.year;

	return date;

}

int Parse::convertToTime(std::string){
	return 0;
}