//@author A0101362Y
#pragma once

#include <assert.h>
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

	//-----EXCEPTION FEEDBACK MESSAGES-------------------------------------------------------------

	static const std::string Parse::EXCEPTION_NO_START_DATE;
	static const std::string Parse::EXCEPTION_NO_END_DATE;
	static const std::string Parse::EXCEPTION_NO_DEADLINE_DATE;
	static const std::string Parse::EXCEPTION_DATE_NO_YEAR;
	static const std::string Parse::EXCEPTION_DATE_NO_MONTH;
	static const std::string Parse::EXCEPTION_DATE_NO_DAY;
	static const std::string Parse::EXCEPTION_INVALID_YEAR_INPUT;
	static const std::string Parse::EXCEPTION_INVALID_MONTH_INPUT;
	static const std::string Parse::EXCEPTION_INVALID_DAY_INPUT;
	static const std::string Parse::EXCEPTION_INVALID_TIME_INPUT;
	static const std::string Parse::EXCEPTION_INVALID_YEAR_FORMAT;
	static const std::string Parse::EXCEPTION_INVALID_MONTH_FORMAT;
	static const std::string Parse::EXCEPTION_INVALID_DAY_FORMAT;
	static const std::string Parse::EXCEPTION_INVALID_TIME_FORMAT;
	static const std::string Parse::EXCEPTION_NOBLOCK_MULTIPLE_DATES;
	static const std::string Parse::EXCEPTION_NOBLOCK_MULTIPLE_TYPES;
	static const std::string Parse::EXCEPTION_MISSING_START_TIME;
	static const std::string Parse::EXCEPTION_MISSING_END_TIME;
	static const std::string Parse::EXCEPTION_END_BEFORE_START_DATE;
	static const std::string Parse::EXCEPTION_START_END_SAME;
	static const std::string Parse::EXCEPTION_END_BEFORE_START_TIME;

//-----CONSTANT INTEGERS-----------------------------------------------------------------------

	static const int EMPTY_TIME;

public:
//-----PROCESSING METHODS----------------------------------------------------------------------
	
	//Takes task string from user input and processes it into its various Task variables
	void processTaskStringFromUI(std::string, std::string &, std::string &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, bool &, std::vector<std::string> &);

	//Takes task string from file storage and processes it into its various Task variables
	void processTaskStringFromFile(std::string, std::string &, std::string &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, std::vector<Date> &, std::vector<int> &, bool &);

//-----CONVERSION METHODS----------------------------------------------------------------------

	//Takes a date in string type and converts it into Date type
	Date convertToDate(std::string);

	//Takes a time in string type and converts it into integer type
	int convertToTime(std::string);

	//Takes a day keyword and changes it into its corresponding date string
	std::string changeDayToDate(std::string, std::vector<std::string>);

	//Takes a word and changes it into lowercase form
	std::string convertToLowercase(std::string word);

//-----CHECK METHODS---------------------------------------------------------------------------

	//Checks if word is a keyword or not
	bool isKeyword(std::string word);

	//Checks if word is a valid day keyword or not
	bool isDayKeyword(std::string);

	//Checks if the input year format is correct (yyyy)
	bool isValidYearFormat(std::string);

	//Checks if the input month format is correct (m, mm)
	bool isValidMonthFormat(std::string);
	
	//Checks if the input day format is correct (d,dd)
	bool isValidDayFormat(std::string);

	//Checks if the input time format is correct 
	bool isValidTimeFormat(std::string);

	//Checks if time value is valid 
	bool isValidTime(int);

	//Checks if hour value of time is valid
	bool isValidHour(int);

	//Checks if minutes value of time is valid
	bool isValidMins(int);

	//Checks if second time is after the first time
	bool isLaterTime(int, int);

	//Checks if times are equal
	bool isSameTime(int, int);
};