#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include "Terminal.h"
#include "LogicElement.h"

namespace dialog {

	int dialog(const char* [], const int);


	int D_Create_Full (terminal::bunchOfTerminals&);
	int D_Create(terminal::bunchOfTerminals&);
	int D_Connect(terminal::bunchOfTerminals&);
	int D_Disconnect(terminal::bunchOfTerminals&);
	int D_Print(terminal::bunchOfTerminals&);
	int D_Print_Connections(terminal::bunchOfTerminals&);
	int D_Enter(terminal::bunchOfTerminals&);


	std::string getType();
	int getNum(std::string&);
	char getSignal();


	void createTerminal(terminal::bunchOfTerminals&, std::string&, int, char);
	void createTerminal(terminal::bunchOfTerminals&, std::string&);
	void createTerminal(terminal::bunchOfTerminals&);


	terminal::Terminal** expansion(terminal::bunchOfTerminals&);
	void copyValues(terminal::bunchOfTerminals& , terminal::Terminal**);
	
	
	int D_Create_With_Number(logicElement::bunchOfLogicElements&);
	int D_Create_With_Array(logicElement::bunchOfLogicElements&);
	int D_Enter_Logic_Element(logicElement::bunchOfLogicElements&);
	int D_Get_Terminal(logicElement::bunchOfLogicElements&);
	int D_Connect_Logic_Elements(logicElement::bunchOfLogicElements&);
	int D_Print_Logic_Elements(logicElement::bunchOfLogicElements&);

	void createLogicElement(logicElement::bunchOfLogicElements&);
	void createLogicElement(logicElement::bunchOfLogicElements& ,int, int);
	void createLogicElement(logicElement::bunchOfLogicElements&, logicElement::TerminalsDefinitionStruct&);

	logicElement::LogicElement** expansionLogic(logicElement::bunchOfLogicElements&);
	void copyValuesLogic(logicElement::bunchOfLogicElements&, logicElement::LogicElement**);

	void logicErase(logicElement::bunchOfLogicElements&);

	template <class T>
	T NumInput(T min, T max) {
		T a;
		while (true) {
			std::cin >> a;
			if (std::cin.eof())
				throw std::runtime_error("Error of input: EOF");
			else if (std::cin.bad())
				throw std::runtime_error(std::string("Error of input: ") + strerror(errno));
			else if (std::cin.fail()) {
				std::cout << "Repeat please" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (a > min && a < max)
				return a;
			else {
				std::cout << "Repeat please" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

}