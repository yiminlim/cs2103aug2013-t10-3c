#include "Storage.h"

Storage::Storage(){

}

void Storage::initStorage(std::string storageFileName){
	_fileName = storageFileName;
}

void Storage::getExistingTasks(std::vector<std::string>& taskStorage){
	std::string _task; //whole line in proper format
	std::ifstream readFile(_fileName);

	while(getline(readFile, _task)){
		taskStorage.push_back(_task);
	}
	readFile.close();
}

void Storage::saveTasksIntoFile(std::vector<std::string>& taskStorage){
	std::ofstream writeFile(_fileName);
	writeFile.clear();
	
	for(unsigned int i=0; i< taskStorage.size(); i++){
		writeFile << taskStorage[i] << std::endl;
	}
	
	writeFile.close();
}
