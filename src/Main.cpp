#include <vld.h>
#include "Dialog.h"
#include "Terminal.h"
#include "Vector.h"

namespace dialog {

	const char* dialogMsgs[] = { "0.Quite", "1.Dialog for terminals", "2.Dialog for logic elements"};
	const int numDialogMsgs = sizeof(dialogMsgs) / sizeof(dialogMsgs[0]);

	const char* terminalMsgs[] = { "0.Quite", "1.Create terminal with type of terminal, number of connections and state of signal",
											"2.Create terminal only with type of terminal",  "3.Enter the terminal", "4.Connect two terminals",
												"5.Disconnect two terminals","6.Print state of terminal"}; 
	const int numTerminalMsgs = sizeof(terminalMsgs) / sizeof(terminalMsgs[0]);
	int (*terminalFunc[])(vector::Vector<terminal::Terminal> &) = { createFull, createWithType, enter, connect, disconnect, print};

	const char* logicMsgs[] = {"0.Quite", "1.Create terminal with number of input and output terminals",
												"2.Create with array of definitions of terminals", "3.Enter terminals of logic element",
													"4.Connect terminals from different logic elements", "5.Get information about terminal in logic element",
															"6.Print logic elements" };
	const int numLogicMsgs = sizeof(logicMsgs) / sizeof(logicMsgs[0]);
	int (*logicFunc[])(vector::Vector<logicElement::LogicElement>&) = { createWithNumber, createWithArray, enter, connect, getTerminal, print};
}
int main() {

	vector::Vector<terminal::Terminal> terminals;
	vector::Vector<logicElement::LogicElement> logicElements;
	int al1;
	int al2;
	try
	{
		while (al2=dialog::dialog(dialog::dialogMsgs, dialog::numDialogMsgs)) {
			if (al2 == 1) {
				while (al1 = dialog::dialog(dialog::terminalMsgs, dialog::numTerminalMsgs))
					dialog::terminalFunc[al1 - 1](terminals);
			}
			else {
				while (al1 = dialog::dialog(dialog::logicMsgs, dialog::numLogicMsgs))
					dialog::logicFunc[al1 - 1](logicElements);
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