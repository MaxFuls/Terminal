#pragma once
#include "Terminal.h"
namespace logicElement {
	
	struct TerminalsDefinition {

		std::string type;
		int connections;
		char signal;
	};

	class LogicElement {
	private:

		terminal::Terminal** inputTerminals;
		int numberOfInputTerminals;
		terminal::Terminal** outputTerminals;
		int numberOfOutputTerminals;

	public:

		LogicElement();
		LogicElement(int, int);
		LogicElement(TerminalsDefinition*);

	};

}