#include "Date.h"

//-----CONSTRUCTORS----------------------------------------------------------------------------

/* 
	Purpose: Constructs an empty date object.
	Pre-conditions: N/A
	Post-conditions: Date object is constructed with all values initialised to 0. (empty date) 
*/
Date::Date() {
	_day = 0;
	_month = 0;
	_year = 0;
}

/* 
	Purpose: Constructs an empty date object given specified values.
	Pre-conditions: All values should be integers.
	Post-conditions: Date object is constructed with values initialised as specified. 
*/
Date::Date(int day, int month, int year) {
	_day = day;
	_month = month;
	_year = year;
}

//-----CHECK METHODS---------------------------------------------------------------------------

/* 
	Purpose: Checks if date value is empty i.e. 0/0/0. 
	Pre-condition: Date value has been initialised.
	Post-condition: Returns true if date is empty (i.e. 0/0/0) and false otherwise.
*/
bool Date::isEmptyDate(){
	return _day == 0 && _month == 0 && _year == 0;
}

/*
	Purpose: Checks if dates are equal.
	Pre-condition: Day/month/year values are integers.
	Post-condition: Returns true if dates are of the same value and false if otherwise.
*/
bool Date::isSameDate(Date checkDate){
	return _year == checkDate._year && _month == checkDate._month && _day == checkDate._day;
}

/* 
	Purpose: Checks if checkDate is strictly after 'this' date. 
	Pre-condition: Day/month/year values are integers.
	Post-condition: Returns true if checkDate is after 'this' date and false otherwise. 
*/
bool Date::isLaterDate(Date checkDate){
	if (_year > checkDate._year) {
		return false;
	}
	else if ((_year == checkDate._year) && (_month > checkDate._month)) {
		return  false; 
	}
	else if ((_month == checkDate._month) && (_day > checkDate._day)) {
		return false;
	}
	else if (_day == checkDate._day) {
		return false;
	}
	return true;
}

/* 
	Purpose: Checks if date value exists and is valid. 
	Pre-condition: Date value has been initialised.
	Post-condition: Returns true if date is valid and false otherwise. 
*/
bool Date::isValidDate(){
	return isValidDay() && isValidMonth() && isValidYear();
}

/* 
	Purpose: Checks if day value of year exists and is valid. 
	Pre-condition: Day value has been initialised.
	Post-condition: Returns true if day value of date is valid and false otherwise. 
*/
bool Date::isValidDay(){
	return _day >= 1 && _day <= 31;
}

/* 
	Purpose: Checks if month value of date exists and is valid. 
	Pre-condition: Month value has been initialised.
	Post-condition: Returns true if month value of date is valid and false otherwise. 
*/
bool Date::isValidMonth(){
	return _month >= 1 && _month <= 12;
}

/* 
	Purpose: Checks if year value of date is valid. 
	Pre-condition: Year value has been initialised.
	Post-condition: Returns true if year value of date is valid and false otherwise. 
*/
bool Date::isValidYear(){
	return _year > 0;
}