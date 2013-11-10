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
	bool prevIsDate = false;

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
				endingDate.push_back(Date());
				startingTime.push_back(EMPTY_TIME);
				endingTime.push_back(EMPTY_TIME);
				prevIsDate = true;
			} 
			else if (isDayKeyword(taskDetails[i])) {
				startingDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
				endingDate.push_back(Date()); 
				startingTime.push_back(EMPTY_TIME);
				endingTime.push_back(EMPTY_TIME);
				prevIsDate = true;
			}
			else {
				if (!prevIsDate) {
					throw std::runtime_error("Missing starting date");
				}
				else if (!startingTime.empty()) {
					startingTime[startingTime.size()-1] = convertToTime(taskDetails[i]);
					prevIsDate = false;
				}
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
				prevIsDate = true;
			}
			else if (isDayKeyword(taskDetails[i])) {
				if(!endingDate.empty()) {
					endingDate[endingDate.size()-1] = convertToDate(changeDayToDate(taskDetails[i], dateVector));
				}
				else {
					endingDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
				}
				prevIsDate = true;
			}
			else {
				if (!prevIsDate) {
					throw std::runtime_error("Missing ending date");
				}
				else if (!endingTime.empty()) {
					endingTime[endingTime.size()-1] = convertToTime(taskDetails[i]);
					prevIsDate = false;
				}	
			}
		}
		else if (keyword == KEYWORD_DEADLINE) {
			if (taskDetails[i].find(DATE_SEPARATOR) != std::string::npos) {
				deadlineDate.push_back(convertToDate(taskDetails[i]));
				deadlineTime.push_back(EMPTY_TIME);
				prevIsDate = true;
			}
			else if (isDayKeyword(taskDetails[i])) {
				deadlineDate.push_back(convertToDate(changeDayToDate(taskDetails[i], dateVector)));
				deadlineTime.push_back(EMPTY_TIME);
				prevIsDate = true;
			}
			else {
				if (!prevIsDate) {
					throw std::runtime_error("Missing deadline date");
				}
				else if (!deadlineTime.empty()) {
					deadlineTime[deadlineTime.size()-1] = convertToTime(taskDetails[i]);
					prevIsDate = false;
				}
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
	
	assert(startingDate.size() == startingTime.size());
	assert(endingDate.size() == endingTime.size());
	assert(startingDate.size() == endingDate.size());
	assert(startingTime.size() == endingTime.size());
	assert(deadlineDate.size() == deadlineTime.size());

	try { 
		if (!block && (startingDate.size() > 1 || endingDate.size() > 1 || deadlineDate.size() > 1)) {
			throw (std::runtime_error("Task should only indicate one start/end/deadline"));
		}
		if (!block && ((!startingDate[0].isEmptyDate() && !deadlineDate[0].isEmptyDate()) || (!endingDate[0].isEmptyDate() && !deadlineDate[0].isEmptyDate()))) {
			throw (std::runtime_error("Task should indicate either a start date or deadline date"));
		}
		for (unsigned int i = 0; i < startingDate.size(); i++) {
			if (!startingDate[i].isEmptyDate() && !endingDate[i].isEmptyDate() && startingTime[i] == EMPTY_TIME && endingTime[i] != EMPTY_TIME) {
				throw (std::runtime_error("No starting time to match ending time"));
			}
			if (!startingDate[i].isEmptyDate() && !endingDate[i].isEmptyDate() && startingTime[i] != EMPTY_TIME && endingTime[i] == EMPTY_TIME) {
				throw (std::runtime_error("No ending time to match starting time"));
			}
		}
		for (unsigned int i = 0; i < startingDate.size(); i++) {
			if (!startingDate[i].isEmptyDate() && !endingDate[i].isEmptyDate() && !startingDate[i].isLaterDate(endingDate[i])) {
				throw (std::runtime_error("End date occurs before start date"));
			}
			else if (isSameDate(startingDate[i], endingDate[i])) {
				if (!startingDate[i].isEmptyDate() && !endingDate[i].isEmptyDate() && !isLaterTime(startingTime[i], endingTime[i])) {
					if (isSameTime(startingTime[i], endingTime[i])){
						throw std::runtime_error("Start and end dates and times are the same");
					}
					else { 
						throw std::runtime_error("End time occurs before start time");
					}
				}
			}
		}
	}
	catch (...) {
		throw;
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
	
	//Deadline task case
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

	//Activity task case
	else if (taskDetails[0].find(DATE_SEPARATOR) != std::string::npos){
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

	//Floating task case
	else{			
		unsigned int i = 0;
		while (i < taskDetails.size() && taskDetails[i] != KEYWORD_LOCATION){
			if (action != EMPTY_STRING) {
				action += SINGLE_SPACE;
			}
			action += taskDetails[i];
			i++;
		}
		if (i < taskDetails.size() && taskDetails[i] == KEYWORD_LOCATION){
			i++;
		}
		while (i < taskDetails.size()){
			if (location != EMPTY_STRING){
				location += SINGLE_SPACE;
			}
			location += taskDetails[i];
			i++;
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
Date Parse::convertToDate(std::string dateString){
	Date date; 

	size_t posFirstDateSeparator = dateString.find(DATE_SEPARATOR);
	size_t posSecondDateSeparator = dateString.find(DATE_SEPARATOR, posFirstDateSeparator+1);

	std::string dayString = dateString.substr(0, posFirstDateSeparator-0); 
	std::string monthString = dateString.substr(posFirstDateSeparator+1, posSecondDateSeparator-posFirstDateSeparator-1);
	std::string yearString = dateString.substr(posSecondDateSeparator+1);

	try {
		if (yearString.empty()) {
			throw (std::runtime_error("Missing year input"));
		}
		else if (monthString.empty()) {
			throw (std::runtime_error("Missing month input"));
		}
		else if (dayString.empty()) {
			throw (std::runtime_error("Missing day input"));
		}
		else if (!yearString.empty() && !isValidYearFormat(yearString)) {
			throw (std::runtime_error("Invalid year input format"));
		}
		else if (!monthString.empty() && !isValidMonthFormat(monthString)) {
			throw (std::runtime_error("Invalid month input format"));
		}
		else if (!dayString.empty() && !isValidDayFormat(dayString)) {
			throw (std::runtime_error("Invalid day input format"));
		}
	}
	catch (...) {
		throw;
	}

	std::istringstream dayInput(dayString);
	std::istringstream monthInput(monthString);
	std::istringstream yearInput(yearString);

	dayInput >> date._day;
	monthInput >> date._month;
	yearInput >> date._year;

	try {
		if (!isValidDate(date)) {
			throw (std::runtime_error("Invalid date input: day/month/year out of range"));
		}
	}
	catch (...) {
		throw;
	}

	if (date._year < 100){
		date._year += 2000;
	}

	return date;
}

/*
	Purpose: Takes a time in string type and converts it into integer type.
	Pre-conditions: Time string is made up of 4 numerical digits.
	Post-conditions: Returns time as an integer type value. 
	Equivalence Partitions: less than 4 digits, 4 digits, 5 digits 
	Boundary values: 3 digits, 4 digits, 5 digits
*/
int Parse::convertToTime(std::string timeString){
	int time;

	try {
		if (!isValidTimeFormat(timeString)) {
			throw (std::runtime_error("Invalid time input format"));
		}
	}
	catch (...) {
		throw;
	}

	std::istringstream timeInput(timeString);
	
	timeInput >> time;

	try {
		if (!isValidTime(time)) {
			throw (std::runtime_error("Invalid time input"));
		}
	}
	catch (...) {
		throw;
	}

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
	Equivalence Partitions: < 0, 1-23, > 23 
	Boundary values: -1, 0, 1, 22, 23, 24
*/
bool Parse::isValidHour(int hour) {
	return hour >= 0 && hour <= 23;
}

/* 
	Purpose: Checks if minutes value of time is valid. 
	Pre-condition: Minutes value is an integer.
	Post-condition: Returns true if minutes value of time is valid and false otherwise. 
	Equivalence Partitions: < 1, 1-59, > 59
	Boundary values: -1, 0, 1, 58, 59, 60
*/
bool Parse::isValidMins(int mins) {
	return mins >= 0 && mins <= 59;
}

/* 
	Purpose: Checks if end date is not before start date. 
	Pre-condition: Dates are valid.
	Post-condition: Returns true if starting date value is not before ending date and false otherwise. 
*/
bool Parse::isValidEndDate(Date startingDate, Date endingDate) {
	if (startingDate._year > endingDate._year) {
		return false;
	}
	else if ((startingDate._year == endingDate._year) && (startingDate._month > endingDate._month)) {
		return  false; 
	}
	else if ((startingDate._month == endingDate._month) && (startingDate._day > endingDate._day)) {
		return false;
	}
	return true;
}

/* 
	Purpose: Checks if dates are equal. 
	Pre-condition: Dates are valid.
	Post-condition: Returns true if  dates have same value and false otherwise. 
*/
bool Parse::isSameDate(Date firstDate, Date secondDate) {
	return firstDate._year == secondDate._year && firstDate._month == secondDate._month && firstDate._day == secondDate._day;
}

/* 
	Purpose: Checks if end time is after start time. 
	Pre-condition: Time values are integers.
	Post-condition: Returns true if ending time value of time is after starting time and false otherwise. 
*/
bool Parse::isLaterTime(int time1, int time2) {
	return time1 < time2;
}

/*
	Purpose: Checks if times are equal.
	Pre-condition: Time values are integers.
	Post-condition: Returns true if times are of the same value and false if otherwise.
*/
bool Parse::isSameTime(int time1, int time2){
	return time1 == time2;
}

/* 
	Purpose: Checks if the input month format is correct (m, mm). 
	Pre-condition: String is not empty.
	Post-condition: Returns true if month string has 1/2 characters and false otherwise. 
	Equivalence Partitions: less than 1 character, 1-2 characters, more than 2 characters
	Boundary values:  empty string, 1 character, 2 characters, 3 characters
*/
bool Parse::isValidMonthFormat(std::string monthString) {
	return monthString.size() == 1 || monthString.size() == 2;
}

/* 
	Purpose: Checks if the input day format is correct (d, dd). 
	Pre-condition: String is not empty.
	Post-condition: Returns true if day string has 1/2 characters and false otherwise. 
	Equivalence Partitions: less than 1 character, 1-2 characters, more than 2 characters
	Boundary values: empty string, 1 character, 2 characters, 3 characters
*/
bool Parse::isValidDayFormat(std::string dayString) {
	return dayString.size() == 1 || dayString.size() == 2;
}

/* 
	Purpose: Checks if the input year format is correct (yy or yyyy). 
	Pre-condition: String is not empty.
	Post-condition: Returns true if year string has 2/4 characters and false otherwise. 
	Equivalence Partitions: less than 2 characters,  2/3/4 characters, more than 4 characters
	Boundary values: 0/1/2/3/4/5 characters 
*/
bool Parse::isValidYearFormat(std::string yearString) {
	return yearString.size() == 2 || yearString.size() == 4;
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