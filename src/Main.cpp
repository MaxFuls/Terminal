#include "Dialog.h"
#include "Terminal.h"
#include "Global.h"
int main() {

	int al;
	try
	{
		while (al = Dialog::dialog(Dialog::msgs, Dialog::number_of_msgs)) {

			Dialog::dialog_functions[al - 1](Terminal::arr, Terminal::ArrLength);
		}
	}
	catch (const std::exception&)
	{

	}
	return 0;
}