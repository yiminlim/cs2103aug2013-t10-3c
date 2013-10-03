#ifndef _TASK_H_
#define _TASK_H_

#include <string>
#include <vector>

class Task{
private:
	std::string _task;
	std::string _action; 
	std::string _location;
	std::string _startingDate;
	int	_startingTime;
	std::string _endingDate;
	int _endingTime;
	std::string _deadlineDate;
	int	_deadlineTime;
	char _status;
	std::vector <std::string> _block;

public:
	//empty constructor
	Task();

	//constructor
	Task(std::string, std::string, std::string, std::string, int, std::string, int, std::string, char, std::vector<std::string>);

	//returns task
	std::string getTask();

	//returns task action
	std::string getAction();

	//returns task location
	std::string getLocation();

	//returns task starting date
	std::string getStartingDate();

	//returns task starting time
	int getStartingTime();

	//returns tsak ending date
	std::string getEndingDate();

	//returns task ending time
	int getEndingTime();

	//returns task deadline date
	std::string getDeadlineDate();

	//returns task deadline time
	std::string getDeadlineTime();

	//returns task status
	char getStatus();
};
#endif;