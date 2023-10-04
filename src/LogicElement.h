#pragma once
#include "Terminal.h"
namespace logicElement {
	
	struct TerminalsDefinition {

		std::string type;
		int connections;
		char signal;

		void scan();
	};

	struct TerminalsDefinitionStruct {

		int length = 0;
		int numberOfInputTerminals = 0;
		int numberOfOutputTerminals = 0;
		TerminalsDefinition* terminalDefinitions = nullptr;

		TerminalsDefinitionStruct(int);
		~TerminalsDefinitionStruct();
		void scan(int);

	};
	
	class LogicElement {
	private:

		int number;
		terminal::Terminal** inputTerminals;
		int numberOfInputTerminals;
		terminal::Terminal** outputTerminals;
		int numberOfOutputTerminals;

	public:

		LogicElement();
		LogicElement(int, int, int);
		LogicElement(const TerminalsDefinitionStruct&, int);
		~LogicElement();

		int getNumber();
		int getNumberOfInput();
		int getNumberOfOutput();

		void print();
		void scan();



	};

	struct bunchOfLogicElements {

		int size = 0;
		int capacity = 5;
		LogicElement** logicElements = new LogicElement*[5]();

		~bunchOfLogicElements();
	};
}