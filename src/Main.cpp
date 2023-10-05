#include "Dialog.h"
#include "Terminal.h"
#include <vld.h>
namespace dialog {

	const char* messagesForDialog[] = { "0.Quite", "1.Dialog for terminals", "2.Dialog for logic elements"};
	const int numberOfMessagesForDialog = sizeof(messagesForDialog) / sizeof(messagesForDialog[0]);

	const char* messagesForTerminal[] = { "0.Quite", "1.Create terminal with type of terminal, number of connections and state of signal",
											"2.Create terminal only with type of terminal",  "3.Enter the terminal", "4.Connect two terminals",
												"5.Disconnect two terminals","6.Print state of terminal", "7.Print connected terminals"}; 
	const int numberOfMessagesForTerminal = sizeof(messagesForTerminal) / sizeof(messagesForTerminal[0]);
	int (*dialogFunctionsForTerminal[])(terminal::bunchOfTerminals&) = { D_Create_Full, D_Create, D_Enter, D_Connect, D_Disconnect, D_Print, D_Print_Connections };

	const char* messagesForLogicElement[] = {"0.Quite", "1.Create terminal with number of input and output terminals",
												"2.Create with array of definitions of terminals", "3.Enter terminals of logic element",
													"4.Connect terminals from different logic elements", "5.Get information about terminal in logic element",
															"6.Print logic elements" };
	const int numberOfMessagesForLogicElement = sizeof(messagesForLogicElement) / sizeof(messagesForLogicElement[0]);
	int (*dialogFunctionsForLogicElement[])(logicElement::bunchOfLogicElements&) = { D_Create_With_Number, D_Create_With_Array,
																						D_Enter_Logic_Element, D_Connect_Logic_Elements, D_Get_Terminal,
																							D_Print_Logic_Elements};
}
int main() {
	
	terminal::bunchOfTerminals bunchOfTerminals;
	logicElement::bunchOfLogicElements bunchOfLogicElements;
	int al1;
	int al2;
	try
	{
		while (al2=dialog::dialog(dialog::messagesForDialog, dialog::numberOfMessagesForDialog)) {
			if (al2 == 1) {
				while (al1 = dialog::dialog(dialog::messagesForTerminal, dialog::numberOfMessagesForTerminal))
					dialog::dialogFunctionsForTerminal[al1 - 1](bunchOfTerminals);
			}
			else {
				while (al1 = dialog::dialog(dialog::messagesForLogicElement, dialog::numberOfMessagesForLogicElement))
					dialog::dialogFunctionsForLogicElement[al1 - 1](bunchOfLogicElements);
			}
		}
	}
	catch (const std::runtime_error& ra)
	{
		std::cout << ra.what() << std::endl;
		return 1;
	}
	return 0;
}