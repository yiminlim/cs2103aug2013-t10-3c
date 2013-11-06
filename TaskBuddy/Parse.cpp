#include "Parse.h" 
#include <iostream>

//-----CONSTANT STRINGS------------------------------------------------------------------------

//KEYWORDS
const std::string Parse::KEYWORD_LOCATION = "at";
const std::string Parse::KEYWORD_STARTING = "from";
const std::string Parse::KEYWORD_ENDING = "to";
const std::string Parse::KEYWORD_DEADLINE = "by";
const std::string Parse::KEYWORD_HOURS = "hrs";
const std::string Parse::KEYWORD_BLOCK = "blockoff";
const std::string Parse::KEYWORD_BLOCK_BRACKETS = "(blockoff)";

//MISC
const std::string Parse::EMPTY_STRING = "";
const std::string Parse::SINGLE_SPACE = " ";
const std::string Parse::DATE_SEPARATOR = "/";
const std::string Parse::SYMBOL_DASH = "-";
const std::string Parse::SYMBOL_COLLON = ":";

//DAY KEYWORDS
const std::string Parse::DAY_KEYWORD_TODAY = "today";
const std::string Parse::DAY_KEYWORD_TOMORROW = "tomorrow";
const std::string Parse::DAY_KEYWORD_TMR = "tmr";
const std::string Parse::DAY_KEYWORD_MONDAY = "monday";
const std::string Parse::DAY_KEYWORD_MON = "mon";
const std::string Parse::DAY_KEYWORD_TUESDAY = "tuesday";
const std::string Parse::DAY_KEYWORD_TUES = "tues";
const std::string Parse::DAY_KEYWORD_TUE = "tue";
const std::string Parse::DAY_KEYWORD_WEDNESDAY = "wednesday";
const std::string Parse::DAY_KEYWORD_WED = "wed";
const std::string Parse::DAY_KEYWORD_THURSDAY = "thursday";
const std::string Parse::DAY_KEYWORD_THURS = "thurs";
const std::string Parse::DAY_KEYWORD_THUR = "thur";
const std::string Parse::DAY_KEYWORD_THU = "thu";
const std::string Parse::DAY_KEYWORD_FRIDAY = "friday";
const std::string Parse::DAY_KEYWORD_FRI = "fri";
const std::string Parse::DAY_KEYWORD_SATURDAY = "saturday";
const std::string Parse::DAY_KEYWORD_SAT = "sat";
const std::string Parse::DAY_KEYWORD_SUNDAY = "sunday";
const std::string Parse::DAY_KEYWORD_SUN = "sun";

//-----CONSTANT INTEGERS-----------------------------------------------------------------------

const int Parse::EMPTY_TIME = -1;

//-----PROCESSING METHODS----------------------------------------------------------------------

/*
	Purpose: Takes task string from user input and processes it into its various Task variables.
	Pre-conditions: Default values ("" for string, empty values for date & time, false for block) have been initialised for parameters.
	Post-conditions: Parameters are updated by reference based on task string.
*/
void Parse::processTaskStringFromUI(std::string taskString, std::string & action, std::string & location, std::vector<Date> & startingDate, std::vector<int> & startingTime, std::vector<Date> & endingDate, std::vector<int> & endingTime, std::vector<Date> & deadlineDate, std::vector<int> & deadlineTime, bool & block, std::vector<std::string> & dateVector) {
	std::istringstream userInputTask(taskString);
	std::string word;
	std::vector<std::string> taskDetails;

	while (userInputTask >> word) {
		taskDetails.push_back(word);
	}

	std::string keyword = EMPTY_STRING;

	for (unsigned int i = 0; i < taskDetails.size(); i++) { //must always start with command
		if (isKeyword(taskDetails[i])) {
			keyword = taskDetails[i];
			if (keyword == KEYWORD_BLOCK) {
				block = true;
			}
		}
		else if (keyword == EMPTY_STRING) {
			if (action != EMPTY_STRING) {
				action += SINGLE_SPACE;
			}
			action += taskDetails[i];
		}
		else if (keyword == KEYWORD_LOCATION) {
			if (location != EMPTY_STRING) {
				location += SINGLE_SPACE;
			}
			location += taskDetails[i];
		}
		else if (keyword == KEYWORD_STARTING) {
			if (taskDetails[i].find(DATE_SEPARATOR) != std::string::npos) {
				startingDate.push_back(convertToDate(taskDetails[i]));
				endingDate.push_back(Date()); //check
			} 
			else if (isDayKeyword(taskDetails[i])) {
				startingDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
				endingDate.push_back(Date()); //check
			}
			else {
				startingTime.push_back(convertToTime(taskDetails[i]));
				endingTime.push_back(EMPTY_TIME);
			}
		}
		else if (keyword == KEYWORD_ENDING) {
			if (taskDetails[i].find(DATE_SEPARATOR) != std::string::npos) {
				if (!endingDate.empty()) {
					endingDate[endingDate.size()-1] = convertToDate(taskDetails[i]);
				}
				else {
					endingDate.push_back(convertToDate(taskDetails[i]));
				}
			}
			else if (isDayKeyword(taskDetails[i])) {
				if(!endingDate.empty()) {
					endingDate[endingDate.size()-1] = convertToDate(changeDayToDate(taskDetails[i], dateVector));
				}
				else {
					endingDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
				}
			}
			else {
				if (!endingTime.empty()) {
					endingTime[endingTime.size()-1] = convertToTime(taskDetails[i]);
				}
				else {
					endingTime.push_back(convertToTime(taskDetails[i]));
				}
			}
		}
		else if (keyword == KEYWORD_DEADLINE) {
			if (taskDetails[i].find(DATE_SEPARATOR) != std::string::npos) {
				deadlineDate.push_back(convertToDate(taskDetails[i]));
			}
			else if (isDayKeyword(taskDetails[i])) {
				deadlineDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
			}
			else {
				deadlineTime.push_back(convertToTime(taskDetails[i]));
			}
		}
	}

	if (deadlineDate.empty()) {
		deadlineDate.push_back(Date());
	}
	if (deadlineTime.empty()) {
		deadlineTime.push_back(EMPTY_TIME);
	}
	if (startingDate.empty()) {
		startingDate.push_back(Date());
	}
	if (startingTime.empty()) {
		startingTime.push_back(EMPTY_TIME);
	}
	if (endingDate.empty()) {
		endingDate.push_back(Date());
	}
	if (endingTime.empty()) {
		endingTime.push_back(EMPTY_TIME);
	}
		
	return;
}

/*
	Purpose: Takes task string from file storage and processes it into its various Task variables.
	Pre-conditions: Default values ("" for string, empty values for date & time, false for block) have been initialised for parameters.
	Post-conditions: Parameters are updated by reference based on task string. 
*/
void Parse::processTaskStringFromFile(std::string taskString, std::string & action, std::string & location, std::vector<Date> & startingDate, std::vector<int> & startingTime, std::vector<Date> & endingDate, std::vector<int> & endingTime, std::vector<Date> & deadlineDate, std::vector<int> & deadlineTime, bool & block, std::vector<std::string> & dateVector){
	std::istringstream fileTask(taskString);
	std::string word;
	std::vector<std::string> taskDetails;

	while (fileTask >> word) {
		taskDetails.push_back(word);
	}
	
	if (taskDetails[0] == KEYWORD_DEADLINE) {
		unsigned int i = 1;

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_HOURS && taskDetails[i] != SYMBOL_COLLON) {
			if (taskDetails[i].find(DATE_SEPARATOR) != std::string::npos) {
				deadlineDate.push_back(convertToDate(taskDetails[i]));
			}
			else {
				deadlineTime.push_back(convertToTime(taskDetails[i]));
			}
			i++;
		}
		if (taskDetails[i] == KEYWORD_HOURS) {
			i++;
		}

		if (taskDetails[i] == SYMBOL_COLLON) {
			i++;
		}

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_LOCATION && taskDetails[i] != KEYWORD_BLOCK_BRACKETS) {
			if (action != EMPTY_STRING) {
				action += SINGLE_SPACE;
			}
			action += taskDetails[i];
			i++;
		}
		
		if (i < taskDetails.size() && taskDetails[i] == KEYWORD_LOCATION) {
			i++;
		}

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_BLOCK_BRACKETS) {
			if (location != EMPTY_STRING) {
				location += SINGLE_SPACE;
			}
			location += taskDetails[i];
			i++;
		}
		
		if (i < taskDetails.size() && taskDetails[i] == KEYWORD_BLOCK_BRACKETS) {
			block = true;
		} 
	}
	else {
		unsigned int i = 0;

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_HOURS && taskDetails[i] != SYMBOL_COLLON && taskDetails[i] != SYMBOL_DASH) {
			if (taskDetails[i].find(DATE_SEPARATOR) != std::string::npos) {
				startingDate.push_back(convertToDate(taskDetails[i]));
			}
			else {
				startingTime.push_back(convertToTime(taskDetails[i]));
			}
			i++;
		}

		if (taskDetails[i] == KEYWORD_HOURS) {
			i++;
		}
		if (taskDetails[i] == SYMBOL_DASH) {
			i++;
		}

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_HOURS && taskDetails[i] != SYMBOL_COLLON) { 
			if (taskDetails[i].find(DATE_SEPARATOR) != std::string::npos) {
				endingDate.push_back(convertToDate(taskDetails[i]));
			}
			else {
				endingTime.push_back(convertToTime(taskDetails[i]));
			}
			i++;
		}

		if (taskDetails[i] == KEYWORD_HOURS) {
			i++;
		}

		if (taskDetails[i] == SYMBOL_COLLON) {
			i++;
		}

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_LOCATION && taskDetails[i] != KEYWORD_BLOCK_BRACKETS) {
			if (action != EMPTY_STRING) {
				action += SINGLE_SPACE;
			}
			action += taskDetails[i];
			i++;
		}
		
		if (i < taskDetails.size() && taskDetails[i] == KEYWORD_LOCATION) {
			i++;
		}

		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_BLOCK_BRACKETS) {
			if (location != EMPTY_STRING) {
				location += SINGLE_SPACE;
			}
			location += taskDetails[i];
			i++;
		}
		
		if (i < taskDetails.size() && taskDetails[i] == KEYWORD_BLOCK_BRACKETS) {
			block = true;
		}
	}

	if (deadlineDate.empty()) {
		deadlineDate.push_back(Date());
	}
	if (deadlineTime.empty()) {
		deadlineTime.push_back(EMPTY_TIME);
	}
	if (startingDate.empty()) {
		startingDate.push_back(Date());
	}
	if (startingTime.empty()) {
		startingTime.push_back(EMPTY_TIME);
	}
	if (endingDate.empty()) {
		endingDate.push_back(Date());
	}
	if (endingTime.empty()) {
		endingTime.push_back(EMPTY_TIME);
	}

	return;
}

//-----CONVERSION METHODS----------------------------------------------------------------------

/*
	Purpose: Takes a date in string type and converts it into Date type.
	Pre-conditions: Date string is in the correct format 'day/month/year'.
	Post-conditions: Returns date with correct day/month/year values.
	Equivalence Partitions: "", 1 '/', 2 '/'
	Boundary values: '', 1 '/', 2 '/'
*/
//Implement check to make sure user input 2 '/' and 3 numbers 
Date Parse::convertToDate(std::string dateString){
	Date date; 

	size_t posFirstDateSeparator = dateString.find(DATE_SEPARATOR);
	size_t posSecondDateSeparator = dateString.find(DATE_SEPARATOR, posFirstDateSeparator+1);

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

/*
	Purpose: Takes a time in string type and converts it into integer type.
	Pre-conditions: Time string is made up of 4 numerical digits.
	Post-conditions: Returns time as an integer type value. 
	Equivalence Partitions: less than 4 digits, 4 digits, 5 digits 
	Boundary values: 3 digits, 4 digits, 5 digits
*/
//Implement check to make sure 4 digits?
int Parse::convertToTime(std::string timeString){
	int time;
	std::istringstream timeInput(timeString);
	
	timeInput >> time;

	return time;
}

/*
	Purpose: Takes a day keyword and changes it into its corresponding date string.
	Pre-conditions: Parameter dayKeyword is valid, dateStrings vector has been initialised correctly.
	Post-conditions: Returns date string corresponding to day keyword input by user. 
*/
//No instance of invalid because it will check if valid before calling
std::string Parse::changeDayToDate(std::string dayKeyword, std::vector<std::string> dateStrings) {
	if (dayKeyword == DAY_KEYWORD_TODAY) {
		return dateStrings[0];
	}
	else if (dayKeyword == DAY_KEYWORD_MONDAY || dayKeyword == DAY_KEYWORD_MON) {
		return dateStrings[1]; 
	}
	else if (dayKeyword == DAY_KEYWORD_TUESDAY || dayKeyword == DAY_KEYWORD_TUES || dayKeyword == DAY_KEYWORD_TUE) {
		return dateStrings[2]; 
	}
	else if (dayKeyword == DAY_KEYWORD_WEDNESDAY || dayKeyword == DAY_KEYWORD_WED) {
		return dateStrings[3];
	}
	else if (dayKeyword == DAY_KEYWORD_THURSDAY || dayKeyword == DAY_KEYWORD_THURS|| dayKeyword == DAY_KEYWORD_THUR || dayKeyword == DAY_KEYWORD_THU) {
		return dateStrings[4]; 
	}
	else if (dayKeyword == DAY_KEYWORD_FRIDAY || dayKeyword == DAY_KEYWORD_FRI) {
		return dateStrings[5]; 
	}
	else if (dayKeyword == DAY_KEYWORD_SATURDAY || dayKeyword == DAY_KEYWORD_SAT) {
		return dateStrings[6]; 
	}
	else if (dayKeyword == DAY_KEYWORD_SUNDAY || dayKeyword == DAY_KEYWORD_SUN) {
		return dateStrings[7]; 
	}
	else if (dayKeyword == DAY_KEYWORD_TOMORROW || dayKeyword == DAY_KEYWORD_TMR) {
		return dateStrings[8];
	}
	else
		return NULL; // need to return error or something!
}

//-----CHECK METHODS---------------------------------------------------------------------------

/*
	Purpose: Checks if word is a keyword or not.
	Pre-conditions: String word has been initialised.
	Post-conditions: Returns true if it is a keyword and false otherwise.
	Equivalence Partitions: valid keyword, invalid keyword
*/
bool Parse::isKeyword(std::string word) {
	return word == KEYWORD_DEADLINE || word == KEYWORD_ENDING || word == KEYWORD_LOCATION || word == KEYWORD_STARTING || word == KEYWORD_BLOCK;
}

/*
	Purpose: Checks if word is a valid day keyword or not. 
	Pre-conditions: String word has been initialised. 
	Post-conditions: Returns true if it is a day keyword and false otherwise. 
	Equivalence Partitions: valid day keyword, invalid day keyword
*/
bool Parse::isDayKeyword(std::string word) {
	std::string dayKeywords[20] = {DAY_KEYWORD_TODAY, DAY_KEYWORD_TOMORROW, DAY_KEYWORD_TMR, DAY_KEYWORD_MONDAY, DAY_KEYWORD_MON, DAY_KEYWORD_TUESDAY, DAY_KEYWORD_TUES, DAY_KEYWORD_TUE, DAY_KEYWORD_WEDNESDAY, DAY_KEYWORD_WED, DAY_KEYWORD_THURSDAY, DAY_KEYWORD_THURS, DAY_KEYWORD_THUR, DAY_KEYWORD_THU, DAY_KEYWORD_FRIDAY, DAY_KEYWORD_FRI, DAY_KEYWORD_SATURDAY, DAY_KEYWORD_SAT, DAY_KEYWORD_SUNDAY, DAY_KEYWORD_SUN};
	
	for(int i = 0; word[i] != '\0'; i++) {
		word[i] = tolower(word[i]);
	}

	for (int i = 0; i < 20; i++) {
		if (word == dayKeywords[i]) {
			return true;
		}
	}

	return false;
}

/* 
	Purpose: Checks if date value is empty i.e. 0/0/0. 
	Pre-condition: Date value has been initialised.
	Post-condition: Returns true if date is empty (i.e. 0/0/0) and false otherwise.
	Equivalence Partitions: day/month/year = 0, valid integer values.
	Boundary values: 0, 1
*/
bool Parse::isEmptyDate(Date date) {
	return (date._day == 0 && date._month == 0 && date._year == 0);
}

/* 
	Purpose: Checks if date value is valid. 
	Pre-condition: Date value has been initialised.
	Post-condition: Returns true if date is valid and false otherwise. 
*/
bool Parse::isValidDate(Date date) {
	return isValidDay(date._day) && isValidMonth(date._month) && isValidYear(date._year);
}

/* 
	Purpose: Checks if day value of year is valid. 
	Pre-condition: Day value has been initialised.
	Post-condition: Returns true if day value of date is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-31, > 31
	Boundary values: 0, 1, 2, 30, 31, 32
*/
bool Parse::isValidDay(int day) {
	return day >= 1 && day <= 31;
}

/* 
	Purpose: Checks if month value of date is valid. 
	Pre-condition: Month value has been initialised.
	Post-condition: Returns true if month value of date is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-12, > 12
	Boundary values: 0, 1, 2, 11, 12, 13
*/
bool Parse::isValidMonth(int month) {
	return month >= 1 && month <= 12;
}

/* 
	Purpose: Checks if year value of date is valid. 
	Pre-condition: Year value has been initialised.
	Post-condition: Returns true if year value of date is valid and false otherwise. 
	Equivalence Partitions: < 1, >= 1
	Boundary values:  0, 1, 2
*/
bool Parse::isValidYear(int year) {
	return year > 0;
}

/* 
	Purpose: Checks if time value is empty i.e. -1. 
	Pre-condition: Time value has been initialised.
	Post-condition: Returns true if time is empty (i.e. -1) and false otherwise. 
	Equivalence Partitions: -1, any positive integer
	Boundary values: -1, 1
*/
bool Parse::isEmptyTime(int time) {
	return time == -1;
}

/* 
	Purpose: Checks if time value is valid. 
	Pre-condition: Time value has been initialised.
	Post-condition: Returns true if time is valid and false otherwise. 
*/
bool Parse::isValidTime(int time) {
	int hour = time/100;
	int mins = time - (hour*100);

	return isValidHour(hour) && isValidMins(mins);
}

/* 
	Purpose: Checks if hour value of time is valid. 
	Pre-condition: Hour value is an integer.
	Post-condition: Returns true if hour value of time is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-23, > 23 
	Boundary values: 0, 1, 2, 22, 23, 24
*/
bool Parse::isValidHour(int hour) {
	return hour >= 1 && hour <= 23;
}

/* 
	Purpose: Checks if end date is not before start date. 
	Pre-condition: Dates are valid.
	Post-condition: Returns true if starting date value is not before ending date and false otherwise. 
*/
bool Parse::isValidEndDate(Date startingDate, Date endingDate) {
	return startingDate._year <= endingDate._year && startingDate._month <= endingDate._month && startingDate._day <= endingDate._year;
}

/* 
	Purpose: Checks if end time is after start time. 
	Pre-condition: Minutes value is an integer.
	Post-condition: Returns true if ending time value of time is after starting time and false otherwise. 
*/
bool Parse::isValidEndTime(int startingTime, int endingTime) {
	return startingTime < endingTime;
}

/* 
	Purpose: Checks if the input year format is correct (yyyy). 
	Pre-condition: String is not empty.
	Post-condition: Returns true if year string has 4 characters and false otherwise. 
	Equivalence Partitions: less than 4 characters, 4 characters, more than 4 characters
	Boundary values: 3 characters, 4 characters, 5 characters
*/
bool Parse::isValidYearFormat(std::string yearString) {
	return yearString.size() == 4;
}

/* 
	Purpose: Checks if the input time format is correct. 
	Pre-condition: String is not empty.
	Post-condition: Returns true if year string has 4 characters and false otherwise. 
	Equivalence Partitions: less than 4 characters, 4 characters, more than 4 characters
	Boundary values: 3 characters, 4 characters, 5 characters
*/
bool Parse::isValidTimeFormat(std::string timeString) {
	return timeString.size() == 4;
}