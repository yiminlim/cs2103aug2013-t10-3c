#pragma once

class Date{ 
public:
	int _day;
	int _month;
	int _year;

//-----CONSTRUCTORS----------------------------------------------------------------------------

	//Default constructor (initialises all values to zero by default)
	Date();
	
	//Constructor with parameters
	Date(int, int, int);

//-----CHECK METHODS---------------------------------------------------------------------------

	//Checks if date value is empty i.e. 0/0/0
	bool isEmptyDate();

	//Checks if dates are equal
	bool isSameDate(Date);

	//Checks if checkDate is after 'this' date
	bool isLaterDate(Date);

	//Checks if date value is valid
	bool isValidDate();

	//Checks if day value of date is valid
	bool isValidDay();

	//Checks if month value of date is valid
	bool isValidMonth();

	//Checks if year value of date is valid
	bool isValidYear();
};