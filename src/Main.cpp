#include "Dialog.h"
#include "Terminal.h"
#include <vld.h>
namespace Dialog {

	const char* msgs[] = { "0.Quite", "1.Create terminal with type of terminal, number of connections and state of signal",
									"2.Create terminal only with type of terminal", "3.Connect two terminals",
											"4.Disconnect two terminals","5.Print connected terminals", "6.Print state of terminal",
														"7.Enter the terminal"};
	const int number_of_msgs = sizeof(msgs) / sizeof(msgs[0]);
	int (*dialog_functions[])(Terminal::Terminal** pointer, int& size) = { D_Create_Full, D_Create, D_Connect, D_Disconnect,D_Print_Connections, D_Print, D_Enter };
}
namespace Terminal {

	Terminal** arr = new Terminal * [5]();
	int ArrLength = 5;
}
int main() {

	int i{ 0 };
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
	Dialog::ArrErase(Terminal::arr, Terminal::ArrLength);
	delete[] Terminal::arr;
	return 0;
}