#ifndef _PARSE_H_
#define _PARSE_H_

#include <string>
#include <sstream>
#include "Task.h"

class Parse{
private:


public:
	static const std::string KEYWORD_ADD;
	static const std::string KEYWORD_LOCATION;
	static const std::string KEYWORD_STARTING;
	static const std::string KEYWORD_ENDING;
	static const std::string KEYWORD_DEADLINE;

	//splits original task string into various parts
	Task generateTaskFromUserInput(std::string);
	Task retrieveTask(std::string);
	void splitTaskString(std::string);
	Task::Date convertToDate(std::string);
	int convertToTime(std::string);
};
#endif;