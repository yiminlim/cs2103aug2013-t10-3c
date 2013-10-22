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

	
	void processTaskStringFromUI(std::string &, std::string &, std::string &, Date &, int &, Date &, int &, Date &, int &, std::vector<std::string> &);
	void processTaskStringFromFile(std::string &, std::string &, std::string &, Date &, int &, Date &, int &, Date &, int &, std::vector<std::string> &);
	bool isKeyword(std::string word);
	std::string formatTask(std::string, std::string, Date, int, Date, int, Date, int, bool);
	Date convertToDate(std::string);
	int convertToTime(std::string);
	bool isDayKeyword(std::string);
	std::string changeDayToDate(std::string, std::vector<std::string>);
};