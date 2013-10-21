#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "Task.h"

class Parse{

public:
	static const std::string KEYWORD_ADD;
	static const std::string KEYWORD_LOCATION;
	static const std::string KEYWORD_STARTING;
	static const std::string KEYWORD_ENDING;
	static const std::string KEYWORD_DEADLINE;

	
	Task generateTaskFromUserInput(std::string);
	bool isKeyword(std::string word);
	std::string formatTask(std::string, std::string, Date, int, Date, int, Date, int, bool);
	Task retrieveTask(std::string);
	Date convertToDate(std::string);
	int convertToTime(std::string);
	std::string Parse::formatTimeOutputString(int time);
};