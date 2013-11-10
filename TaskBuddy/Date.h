#pragma once

class Date{ 
public:
	int _day;
	int _month;
	int _year;

	Date();
	Date(int, int, int);
	bool isEmptyDate();
	bool isSameDate(Date);
	bool isLaterDate(Date);
};