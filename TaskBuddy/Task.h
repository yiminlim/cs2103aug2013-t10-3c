#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <assert.h>
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

public:
//-----CONSTRUCTORS----------------------------------------------------------------------------

	//Default constructor
	Task();

	//Constructor with values
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

	//Checks if hour value of time is valid i.e. between 0-23
	bool isValidHour(int);

	//Checks if minutes value of time is valid i.e. between 0-59
	bool isValidMins(int);
};