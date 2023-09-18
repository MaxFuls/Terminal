#pragma once
#pragma once
namespace Dialog {

	const char* msgs[] = { "0.Quite", "1.Create terminal with type of terminal, number of connections and state of signal",
									"2.Create terminal only with type of terminal", "3.Connect two terminals", 
											"4.Disconnect two terminals", "5.Print state of terminal"};
	const int number_of_msgs = sizeof(msgs) / sizeof(msgs[0]);
	int (*dialog_functions[])(Terminal::Terminal** pointer, int& size) = { D_Create_Full, D_Create, D_Connect, D_Disconnect, D_Print };
}
namespace Terminal {

	Terminal* arr[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
	int ArrLength = 5;
}