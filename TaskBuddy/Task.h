#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <assert.h>
#include "Date.h"


class Task{
private:
	std::string _task;	//whole line in proper output format 
	std::string _action; 
	std::string _location;
	Date _startingDate;
	int	_startingTime;
	Date _endingDate;
	int _endingTime;
	Date _deadlineDate;
	int	_deadlineTime;
	//char _status;
	bool _block;

public:
	//empty constructor
	Task();

	//constructor
	Task(std::string, std::string, Date, int, Date, int, Date, int, bool);

	//formats the task output string
	std::string Task::formatTask(std::string, std::string, Date, int, Date, int, Date, int, bool);

	//returns formatted task output string
	std::string getTask();

	//returns task action
	std::string getAction();

	//returns task location
	std::string getLocation();

	//returns task starting date
	Date getStartingDate();

	//returns task starting time
	int getStartingTime();

	//returns tsak ending date
	Date getEndingDate();

	//returns task ending time
	int getEndingTime();

	//returns task deadline date
	Date getDeadlineDate();

	//returns task deadline time
	int getDeadlineTime();

	//returns task status
	char getStatus();

	//returns whether block or not
	bool getBlock();

	std::string formatTimeOutputString(int time);

	bool isDeadlineType();
};