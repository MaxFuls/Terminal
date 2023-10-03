#pragma once
#include "Terminal.h"
namespace logicElement {
	
	struct TerminalsDefinition {

		std::string type;
		int connections;
		char signal;
	};

	struct TerminalsDefinitionStruct {

		int length;
		int numberOfInputTerminals;
		int numberOfOutputTerminals;
		TerminalsDefinition* terminalDefinitions;

		TerminalsDefinitionStruct(int);

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

	};

	struct bunchOfLogicElements {

		int size;
		int capacity = 5;
		LogicElement** logicElements = new LogicElement*[5]();
	};
}