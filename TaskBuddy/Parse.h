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
	Task generateTask(std::string);
	void splitTaskString(std::string);
	void setTask(std::string);
	void setAction(std::string);
	void setLocation(std::string);
	void setStartingDate(std::string);
	void setStartingTime(std::string);
	void setEndingDate(std::string);
	void setEndingTime(std::string);
	void setDeadlineDate(std::string);
	void setDeadlineTime(std::string);
	Task::Date convertToDate(std::string);
	int convertToTime(std::string);
};
#endif;