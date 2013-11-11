#include <gtest\gtest.h>
#include <Date.h>

class DateTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		date1._day = 11;
		date1._month = 11;
		date1._year = 2013;
		date2._day = 27;
		date2._month = 11;
		date2._year = 2013;
		date1._day = 11;
		date1._month = 11;
		date1._year = 2013;
	}
	Date date1;
	Date date2;
	Date date3;
};