//@author A0101362Y
#include <gtest\gtest.h>
#include <Parse.h>
#include <Task.h>
#include <Date.h>
#include <sstream>

class ParseTest : public ::testing::Test {
protected:
	virtual void SetUp(){
	static const int EMPTY_TIME = -1;
	}

	Parse taskParse;

};