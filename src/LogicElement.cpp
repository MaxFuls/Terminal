#include <iostream>
#include "LogicElement.h"
#include "Terminal.h"

namespace logicElement {

	LogicElement::LogicElement() {

		inputTerminals = nullptr;
		numberOfInputTerminals = 0;
		outputTerminals = nullptr;
		numberOfOutputTerminals = 0;
	}
	LogicElement::LogicElement(int numberOfInput, int numberOfOutput) {

		inputTerminals = new terminal::Terminal[numberOfInput]("Input");
	}
	LogicElement::LogicElement(TerminalsDefinition*) {


	}


}