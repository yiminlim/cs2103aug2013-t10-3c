#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <assert.h>

class Storage{

private:
	std::string _fileName;

public:

	Storage();

	//Initialise storage file 
	void initStorage(std::string);

	//Updates existing items inside file into vector task strings
	void getExistingTasks(std::vector<std::string> &);

	//Save given task strings into file
	void saveTasksIntoFile(std::vector<std::string> &);

};