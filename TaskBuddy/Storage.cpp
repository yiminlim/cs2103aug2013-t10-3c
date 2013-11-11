//@author A0004661R
#include "Storage.h"

Storage::Storage(){

}

/*
	Purpose: Set file name of storage
	Pre-condition: storageFileName must not be empty and must have ".txt" at the back
	Post-condition: _fileName is updated
*/
void Storage::initStorage(std::string storageFileName){
	assert(!storageFileName.empty());
	assert(storageFileName.find(".txt") != std::string::npos);
	_fileName = storageFileName;
}

/*
	Purpose: Update tasks in file into taskStorage
	Pre-condition: _fileName must be initialised with a proper file name
	Post-condition: taskStorage is updated with tasks in the processed format
*/
void Storage::getExistingTasks(std::vector<std::string>& taskStorage){
	std::string _task; //whole line in proper format
	std::ifstream readFile(_fileName);

	while(getline(readFile, _task)){
		taskStorage.push_back(_task);
	}
	readFile.close();
}

/*
	Purpose: Save tasks into external file
	Pre-condition: _fileName must be initialised with a proper file name
	Post-condition: Tasks are saved into external file in processed format
*/
void Storage::saveTasksIntoFile(std::vector<std::string>& taskStorage){
	std::ofstream writeFile(_fileName);
	writeFile.clear();
	
	for(unsigned int i=0; i< taskStorage.size(); i++){
		writeFile << taskStorage[i] << std::endl;
	}
	writeFile.close();
}
