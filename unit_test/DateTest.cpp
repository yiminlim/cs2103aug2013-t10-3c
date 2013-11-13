//@author A0101362Y
#include <gtest\gtest.h>
#include "DateTest.h"

TEST_F(DateTest, ConstructDefaultEmptyDate){
	Date date; 
	EXPECT_EQ(0, date._day);
	EXPECT_EQ(0, date._month);
	EXPECT_EQ(0, date._year);
	EXPECT_EQ(true, date.isEmptyDate());
}

TEST_F(DateTest, ConstructDateWithInvalidDay){
	Date date(32,1,2013);
	EXPECT_EQ(false, date.isValidDate());
	EXPECT_EQ(false, date.isValidDay());
	EXPECT_EQ(true, date.isValidMonth());
}

TEST_F(DateTest, ConstructDateWithInvalidMonth){
	Date date(31,13,2013);
	EXPECT_EQ(false, date.isValidDate());
	EXPECT_EQ(true, date.isValidDay());
	EXPECT_EQ(false, date.isValidMonth());
}

TEST_F(DateTest, CheckForComparingDates){
	EXPECT_EQ(true, date1.isLaterDate(date2));
	EXPECT_EQ(false, date2.isLaterDate(date1));
	EXPECT_EQ(false, date1.isSameDate(date2));
	EXPECT_EQ(true, date1.isSameDate(date3));
	EXPECT_EQ(false, date1.isLaterDate(date3));
}

