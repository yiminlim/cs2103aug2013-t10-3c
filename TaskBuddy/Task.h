//@author A0101362Y
#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "Date.h"


class Task{
private:
	std::string _task;		//Formatted task output string 
	std::string _action;	//Task action string
	std::string _location;	//Task location string
	Date _startingDate;		
	int	_startingTime;		
	Date _endingDate;
	int _endingTime;
	Date _deadlineDate;
	int	_deadlineTime;
	bool _block;			//Indicates if task is part of a block

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
	static const std::string ZERO_DIGIT;

//-----CONSTANT INTEGERS-----------------------------------------------------------------------

	static const int EMPTY_TIME;

public:
//-----CONSTRUCTORS----------------------------------------------------------------------------

	//Default constructor
	Task();

	//Constructor with parameters
	Task(std::string, std::string, Date, int, Date, int, Date, int, bool);

//-----GET METHODS-----------------------------------------------------------------------------

	//Returns formatted task output string
	std::string getTask();

	//Returns task action string
	std::string getAction();

	//Returns task location string
	std::string getLocation();

	//Returns task starting date
	Date getStartingDate();

	//Returns task starting time
	int getStartingTime();

	//Returns task ending date
	Date getEndingDate();

	//Returns task ending time
	int getEndingTime();

	//Returns task deadline date
	Date getDeadlineDate();

	//Returns task deadline time
	int getDeadlineTime();

	//Returns whether task is part of a block
	bool getBlock();

//-----SET METHODS-----------------------------------------------------------------------------

	//Set whether task is part of a block
	void setBlock(bool);

//-----FORMATTING METHODS----------------------------------------------------------------------

	//Formats the task output string for display to user
	std::string Task::formatTaskOutputString();

	//Formats the time output string from integer type value
	std::string formatTimeOutputString(int);

	//Formats the date output string from date type value
	std::string formatDateOutputString(Date);

//-----CHECK METHODS---------------------------------------------------------------------------
	
	//Checks if task is deadline type
	bool isDeadlineType();
	
	//Checks if task is activity type (from-to)
	bool isActivityType();

	//Checks if task is floating type
	bool isFloatingType();
	
};