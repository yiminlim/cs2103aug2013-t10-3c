#include "Parse.h" 
#include <iostream>

const std::string Parse::KEYWORD_ADD = "add";
const std::string Parse::KEYWORD_LOCATION = "at";
const std::string Parse::KEYWORD_STARTING = "from";
const std::string Parse::KEYWORD_ENDING = "to";
const std::string Parse::KEYWORD_DEADLINE = "by";
const std::string Parse::KEYWORD_BLOCK = "blockoff";

//takes in Task string and breaks it down into its various Task details

void Parse::processTaskStringFromUI(std::string taskString, std::string & action, std::string & location, std::vector<Date> & startingDate, std::vector<int> & startingTime, std::vector<Date> & endingDate, std::vector<int> & endingTime, std::vector<Date> & deadlineDate, std::vector<int> & deadlineTime, bool & block, std::vector<std::string> & dateVector){
	std::istringstream userInputTask(taskString);
	std::string word;
	std::vector<std::string> taskDetails;

	while (userInputTask >> word) {
		taskDetails.push_back(word);
	}

	std::string keyword = "";

	for (unsigned int i = 0; i < taskDetails.size(); i++) { //must always start with command
		if (isKeyword(taskDetails[i])) {
			keyword = taskDetails[i];
		}
		else if (keyword == KEYWORD_ADD) {
			if (action != "") {
				action += " ";
			}
			action += taskDetails[i];
		}
		else if (keyword == KEYWORD_LOCATION) {
			if (location != "") {
				location += " ";
			}
			location += taskDetails[i];
		}
		else if (keyword == KEYWORD_STARTING) {
			if (taskDetails[i].find("/") != std::string::npos) {
				startingDate.push_back(convertToDate(taskDetails[i]));
				endingDate.push_back(Date()); //check
			} 
			else if (isDayKeyword(taskDetails[i])) {
				startingDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
				endingDate.push_back(Date()); //check
			}
			else {
				startingTime.push_back(convertToTime(taskDetails[i]));
				endingTime.push_back(-1);
			}
		}
		else if (keyword == KEYWORD_ENDING) {
			if (taskDetails[i].find("/") != std::string::npos) {
				endingDate[endingDate.size()-1] = convertToDate(taskDetails[i]);
			}
			else if (isDayKeyword(taskDetails[i])) {
				endingDate[endingDate.size()-1] = convertToDate(changeDayToDate(taskDetails[i], dateVector));
			}
			else {
				endingTime[endingTime.size()-1] = convertToTime(taskDetails[i]);
			}
		}
		else if (keyword == KEYWORD_DEADLINE) {
			if (taskDetails[i].find("/") != std::string::npos) {
				deadlineDate.push_back(convertToDate(taskDetails[i]));
			}
			else if (isDayKeyword(taskDetails[i])) {
				deadlineDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
			}
			else {
				deadlineTime.push_back(convertToTime(taskDetails[i]));
			}
		}
		else if (keyword == KEYWORD_BLOCK) {
			block = true;
		}
	}	
	return;
}

void Parse::processTaskStringFromFile(std::string taskString, std::string & action, std::string & location, std::vector<Date> & startingDate, std::vector<int> & startingTime, std::vector<Date> & endingDate, std::vector<int> & endingTime, std::vector<Date> & deadlineDate, std::vector<int> & deadlineTime, bool & block, std::vector<std::string> & dateVector){
	std::istringstream fileTask(taskString);
	std::string word;
	std::vector<std::string> taskDetails;

	while (fileTask >> word) {
		taskDetails.push_back(word);
	}

	if (taskDetails[0] == KEYWORD_DEADLINE) {
		deadlineDate.push_back(convertToDate(taskDetails[1]));
		deadlineTime.push_back(convertToTime(taskDetails[2]));
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
		startingDate.push_back(convertToDate(taskDetails[0]));
		startingTime.push_back(convertToTime(taskDetails[1]));
		unsigned int i = 3;
		if (taskDetails[3] == "-") {
			endingDate.push_back(convertToDate(taskDetails[4]));
			endingTime.push_back(convertToTime(taskDetails[5]));
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

		while (i < taskDetails.size() && taskDetails[i] != ("("+KEYWORD_BLOCK+")")) {
			if (location != "") {
				location += " ";
			}
			location += taskDetails[i];
			i++;
		}

		if (i < taskDetails.size() && taskDetails[i] == ("("+KEYWORD_BLOCK+")")) {
			block = true;
		}
	}
	return;
}

bool Parse::isKeyword(std::string word) {
	return word == KEYWORD_ADD || word == KEYWORD_DEADLINE || word == KEYWORD_ENDING || word == KEYWORD_LOCATION || word == KEYWORD_STARTING;
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


bool Parse::isDayKeyword(std::string word) {
	std::string dayKeywords[20] = {"today","tmr","tomorrow","mon","monday","tue","tues","tuesday","wed","wednesday","thu", "thur","thurs","thursday","fri","friday","sat","saturday","sun","sunday"};
	
	for(int i = 0; word[i] != '\0'; i++){
		word[i] = tolower(word[i]);
	}

	for (int i = 0; i < 17; i++) {
		if (word == dayKeywords[i]) {
			return true;
		}
	}

	return false;
}

int Parse::convertToTime(std::string timeString){
	int time;
	std::istringstream timeInput(timeString);
	
	timeInput >> time;

	return time;
}

std::string Parse::changeDayToDate(std::string dayKeyword, std::vector<std::string> dateStrings) {
	if (dayKeyword == "today") {
		return dateStrings[0];
	}
	else if (dayKeyword == "mon" || dayKeyword == "monday") {
		return dateStrings[1]; 
	}
	else if (dayKeyword == "tue" || dayKeyword == "tues" || dayKeyword == "tuesday") {
		return dateStrings[2]; 
	}
	else if (dayKeyword == "wed" || dayKeyword == "wednesday") {
		return dateStrings[3];
	}
	else if (dayKeyword == "thu" || dayKeyword == "thur"|| dayKeyword == "thurs" || dayKeyword == "thursday") {
		return dateStrings[4]; 
	}
	else if (dayKeyword == "fri" || dayKeyword == "friday") {
		return dateStrings[5]; 
	}
	else if (dayKeyword == "sat" || dayKeyword == "saturday") {
		return dateStrings[6]; 
	}
	else if (dayKeyword == "sun" || dayKeyword == "sunday") {
		return dateStrings[7]; //verify that it really is "sun"/"sunday"?
	}
	else if (dayKeyword == "tmr" || dayKeyword == "tomorrow") {
		return dateStrings[8];
	}
	else
		return NULL; // need to return error or something!
}

/*std::string Parse::formatTask(std::string action, std::string location, Date startingDate, int startingTime, Date endingDate, int endingTime, Date deadlineDate, int deadlineTime, bool isDeadLineType) {
	std::ostringstream output;
	if (isDeadLineType) {
		assert (deadlineTime >= 0 && deadlineTime <= 2359);
		output << "by " << deadlineDate._day << "/" << deadlineDate._month << "/" << deadlineDate._year;
		output << " " << formatTimeOutputString(deadlineTime) << " hrs";
		output << ": " << action;
		if (location.size() > 0) {
			output << " at " << location;
		}
	}
	else {
		output << startingDate._day << "/" << startingDate._month << "/" << startingDate._year;
		output << " " << formatTimeOutputString(startingTime) << " hrs";
		if (endingDate._day && endingDate._month && endingDate._year) {
			output << " - " << endingDate._day << "/" << endingDate._month << "/" << endingDate._year;
			output << " " << formatTimeOutputString(endingTime) << " hrs";
		}
		output << ": " << action;
		if (location.size() > 0) {
		output << " at " << location;
		}
	}

	return output.str();
}
*/
/*std::string Parse::formatTimeOutputString(int time){
	std::ostringstream timeString;

	if (time < 1000) {
		timeString << "0";
	}
	if (time < 100) {
		timeString << "0";
	}
	if (time < 10) {
		timeString << "0";
	}
	timeString << time;

	return timeString.str();
}*/