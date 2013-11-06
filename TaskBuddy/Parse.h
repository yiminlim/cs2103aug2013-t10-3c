#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "Task.h"

class Parse{
private:
//-----CONSTANT STRINGS------------------------------------------------------------------------

	//KEYWORDS
	static const std::string KEYWORD_LOCATION;
	static const std::string KEYWORD_STARTING;
	static const std::string KEYWORD_ENDING;
	static const std::string KEYWORD_DEADLINE;
	static const std::string KEYWORD_HOURS;
	static const std::string KEYWORD_BLOCK;
	static const std::string KEYWORD_BLOCK_BRACKETS;

	//MISC
	static const std::string EMPTY_STRING;
	static const std::string SINGLE_SPACE;
	static const std::string DATE_SEPARATOR;
	static const std::string SYMBOL_DASH;
	static const std::string SYMBOL_COLLON;

	//DAY KEYWORDS
	static const std::string DAY_KEYWORD_TODAY;
	static const std::string DAY_KEYWORD_TOMORROW;
	static const std::string DAY_KEYWORD_TMR;
	static const std::string DAY_KEYWORD_MONDAY;
	static const std::string DAY_KEYWORD_MON;
	static const std::string DAY_KEYWORD_TUESDAY;
	static const std::string DAY_KEYWORD_TUES;
	static const std::string DAY_KEYWORD_TUE;
	static const std::string DAY_KEYWORD_WEDNESDAY;
	static const std::string DAY_KEYWORD_WED;
	static const std::string DAY_KEYWORD_THURSDAY;
	static const std::string DAY_KEYWORD_THURS;
	static const std::string DAY_KEYWORD_THUR;
	static const std::string DAY_KEYWORD_THU;
	static const std::string DAY_KEYWORD_FRIDAY;
	static const std::string DAY_KEYWORD_FRI;
	static const std::string DAY_KEYWORD_SATURDAY;
	static const std::string DAY_KEYWORD_SAT;
	static const std::string DAY_KEYWORD_SUNDAY;
	static const std::string DAY_KEYWORD_SUN;

//-----CONSTANT INTEGERS-----------------------------------------------------------------------

	static const int EMPTY_TIME;

public:
//-----PROCESSING METHODS----------------------------------------------------------------------
	
	//Takes task string from user input and processes it into its various Task variables
	void processTaskStringFromUI(std::string, std::string &, std::string &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, bool &, std::vector<std::string> &);

	//Takes task string from file storage and processes it into its various Task variables
	void processTaskStringFromFile(std::string, std::string &, std::string &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, bool &, std::vector<std::string> &);

//-----CONVERSION METHODS----------------------------------------------------------------------

	//Takes a date in string type and converts it into Date type
	Date convertToDate(std::string);

	//Takes a time in string type and converts it into integer type
	int convertToTime(std::string);

	//Takes a day keyword and changes it into its corresponding date string
	std::string changeDayToDate(std::string, std::vector<std::string>);

//-----CHECK METHODS---------------------------------------------------------------------------

	//Checks if word is a keyword or not
	bool isKeyword(std::string word);

	//Checks if word is a valid day keyword or not
	bool isDayKeyword(std::string);

	//Checks if date value is empty i.e. 0/0/0
	bool isEmptyDate(Date);

	//Checks if date value is valid
	bool isValidDate(Date);

	//Checks if day value of date is valid
	bool isValidDay(int);

	//Checks if month value of date is valid
	bool isValidMonth(int);

	//Checks if year value of date is valid
	bool isValidYear(int);

	//Checks if time value is empty i.e. -1
	bool isEmptyTime(int);

	//Checks if time value is valid 
	bool isValidTime(int);

	//Checks if hour value of time is valid
	bool isValidHour(int);

	//Checks if minutes value of time is valid
	bool isValidMins(int);

	//Checks if end date is not before the start date
	bool isValidEndDate(Date, Date);

	//Checks if end time is after the start time
	bool isValidEndTime(int, int);

	//Checks if the input year format is correct (yyyy)
	bool isValidYearFormat(std::string);

	//Checks if the input month format is correct (m, mm)
	bool isValidMonthFormat(std::string);
	
	//Checks if the input day format is correct (d,dd)
	bool isValidDayFormat(std::string);

	//Checks if the input time format is correct 
	bool isValidTimeFormat(std::string);
};