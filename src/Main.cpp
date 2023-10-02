#include "Dialog.h"
#include "Terminal.h"
#include <vld.h>
namespace dialog {

	const char* msgs[] = { "0.Quite", "1.Create terminal with type of terminal, number of connections and state of signal",
								"2.Create terminal only with type of terminal", "3.Connect two terminals",
										"4.Disconnect two terminals","5.Print connected terminals", "6.Print state of terminal",
													"7.Enter the terminal" };
	const int number_of_msgs = sizeof(msgs) / sizeof(msgs[0]);
	int (*dialog_functions[])(terminal::bunchOfTerminals&) = { D_Create_Full, D_Create, D_Connect, D_Disconnect,D_Print_Connections, D_Print, D_Enter };
}
int main() {

	terminal::bunchOfTerminals bunchOfTerminals;
	int i{ 0 };
	int al;
	try
	{
		while (al = dialog::dialog(dialog::msgs, dialog::number_of_msgs))
			dialog::dialog_functions[al - 1](bunchOfTerminals);
		dialog::ArrErase(bunchOfTerminals);
		delete[] bunchOfTerminals.arr;
	}
	catch (const std::runtime_error& ra)
	{
		std::cout << ra.what() << std::endl;
		dialog::ArrErase(bunchOfTerminals);
		delete[] bunchOfTerminals.arr;
		return 1;
	}
	return 0;
}