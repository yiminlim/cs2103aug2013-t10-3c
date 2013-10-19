#include "UserInterface.h"
#include <ctime>

void printCurrentDateTime(){
   time_t now = time(0);
   std::cout << "Number of sec since January 1,1970:" << now << std::endl;

   tm *ltm = localtime(&now);

   // print various components of tm structure.
   std::cout << "Year: "<< 1900 + ltm->tm_year << std::endl;
   std::cout << "Month: "<< 1 + ltm->tm_mon<< std::endl;
   std::cout << "Day: "<<  ltm->tm_mday << std::endl;
   std::cout << "Time: "<< ltm->tm_hour << ":";
   std::cout << ltm->tm_min << ":";
   std::cout << ltm->tm_sec << std::endl;

   /* Code is referrenced from http://www.tutorialspoint.com/cplusplus/cpp_date_time.htm */

}

int main(){
	UserInterface taskBuddyUI;
	taskBuddyUI.initUI();
	
	/*
	time_t now = time(0);
	std::string currentDateTime = ctime(&now);
	std::cout << "Local Date and Time now is: " << currentDateTime << std::endl;
	*/
	printCurrentDateTime();

	taskBuddyUI.commandUI();
	return 0;
}

