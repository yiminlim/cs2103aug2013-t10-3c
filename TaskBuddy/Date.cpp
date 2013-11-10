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
	return true;
}

bool Date::isLaterDate(Date checkDate){
	return true;
}