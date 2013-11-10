#include <gtest\gtest.h>
#include <Task.h>
#include <Date.h>

class TaskTest : public ::testing::Test {
protected:
	TaskTest(){
	}

	virtual ~TaskTest(){
	}
	

	virtual void SetUp() {
	
	}

	Task task;
};

