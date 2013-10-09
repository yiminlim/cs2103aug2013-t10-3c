#include "UserInterface.h"

int main(){

	UserInterface taskBuddyUI;
	
	taskBuddyUI.initUI();
	taskBuddyUI.commandUI();
	taskBuddyUI.exitUI();

	return 0;
}