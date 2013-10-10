#pragma once

#include <string>
#include <vector>
#include <fstream>

class Storage{

private:
	std::string _fileName;

public:
	Storage();

	void getExistingTasks(std::vector<std::string> &);

	void saveTasksIntoFile(std::vector<std::string> &);

};