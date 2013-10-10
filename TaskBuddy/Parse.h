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
	std::string formatTask(std::string, std::string, Task::Date, int, Task::Date, int, Task::Date, int, bool);
	Task retrieveTask(std::string);
	Task::Date convertToDate(std::string);
	int convertToTime(std::string);
};