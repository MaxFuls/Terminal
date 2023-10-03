#include <iostream>
#include "LogicElement.h"
#include "Terminal.h"

namespace logicElement {

	TerminalsDefinitionStruct::TerminalsDefinitionStruct(int numberOfTerminals) {

		numberOfInputTerminals = 0;
		numberOfOutputTerminals = 0;
		length = numberOfTerminals;
		terminalDefinitions = new TerminalsDefinition[numberOfTerminals];
	}

	LogicElement::LogicElement() {

		inputTerminals = nullptr;
		numberOfInputTerminals = 0;
		outputTerminals = nullptr;
		numberOfOutputTerminals = 0;
	}
	LogicElement::LogicElement(int numberOfInputTerminals, int numberOfOutputTerminals, int number) {

		std::string Input = "Input";
		std::string Output = "Output";
		int i{ 0 };
		this->number = number;
		inputTerminals = new terminal::Terminal*[numberOfInputTerminals];
		for (i; i < numberOfInputTerminals; ++i)
			inputTerminals[i] = new terminal::Terminal(Input, i + 1);
		this->numberOfInputTerminals = numberOfInputTerminals;
		outputTerminals = new terminal::Terminal*[numberOfOutputTerminals];
		for (i = 0; i < numberOfOutputTerminals; ++i)
			outputTerminals[i] = new terminal::Terminal(Output, i + 1);
		this->numberOfOutputTerminals = numberOfOutputTerminals;
	}
	LogicElement::LogicElement(const TerminalsDefinitionStruct& terminalsDefinitionStruct, int number) {

		int i{ 0 };
		int j{ 0 };
		int k{ 0 };
		this->number = number;
		inputTerminals = new terminal::Terminal * [terminalsDefinitionStruct.numberOfInputTerminals];
		this->numberOfInputTerminals = numberOfInputTerminals;
		outputTerminals = new terminal::Terminal * [terminalsDefinitionStruct.numberOfOutputTerminals];
		this->numberOfOutputTerminals = numberOfOutputTerminals;
		while (i < terminalsDefinitionStruct.length) {
			if (terminalsDefinitionStruct.terminalDefinitions[i].type == "Input") {
				inputTerminals[j] = new terminal::Terminal(terminalsDefinitionStruct.terminalDefinitions[i].type, 
					terminalsDefinitionStruct.terminalDefinitions[i].connections,terminalsDefinitionStruct.terminalDefinitions[i].signal, i + 1);
				++j;
			}
			else {
				outputTerminals[k] = new terminal::Terminal(terminalsDefinitionStruct.terminalDefinitions[i].type,
					terminalsDefinitionStruct.terminalDefinitions[i].connections, terminalsDefinitionStruct.terminalDefinitions[i].signal, i + 1);
				++j;
			}

		}
	}


}