#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "Task.h"

class Parse{
private:
//-----CONSTANT STRINGS------------------------------------------------------------------------

	static const std::string KEYWORD_EMPTY;
	static const std::string KEYWORD_LOCATION;
	static const std::string KEYWORD_STARTING;
	static const std::string KEYWORD_ENDING;
	static const std::string KEYWORD_DEADLINE;
	static const std::string KEYWORD_BLOCK;
	static const std::string KEYWORD_BLOCK_BRACKETS;

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
};