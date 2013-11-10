#include "Date.h"

Date::Date() {
	_day = 0;
	_month = 0;
	_year = 0;
}

Date::Date(int day, int month, int year) {
	_day = day;
	_month = month;
	_year = year;
}

bool Date::isEmptyDate(){
	return _day == 0 && _month == 0 && _year == 0;
}

bool Date::isSameDate(Date checkDate){
	return _year == checkDate._year && _month == checkDate._month && _day == checkDate._day;
}

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
	return true;
}

bool Date::isValidDate(){
	return isValidDay() && isValidMonth() && isValidYear();
}

bool Date::isValidDay(){
	return _day >= 1 && _day <= 31;
}

bool Date::isValidMonth(){
	return _month >= 1 && _month <= 12;
}

bool Date::isValidYear(){
	return _year > 0;
}