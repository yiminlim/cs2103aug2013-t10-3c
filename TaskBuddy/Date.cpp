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

bool Date::isValidDate(){
	if (_day==0 && _month==0 && _year==0){
		return false;
	}
	else{
		return true;
	}
}