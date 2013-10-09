#ifndef _TASK_H_
#define _TASK_H_

#include <string>
#include <vector>


class Task{
public:
	struct Date{
		int day;
		int month;
		int year;
	};
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
	//std::vector <std::string> _block;

public:
	//empty constructor
	Task();

	//constructor
	Task(std::string, std::string, std::string, Date, int, Date, int, Date, int);

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
};
#endif;