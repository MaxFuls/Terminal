#include <iostream>
#include "LogicElement.h"
#include "Terminal.h"
#include "Dialog.h"

namespace logicElement {

	TerminalsDefinitionStruct::TerminalsDefinitionStruct(int numberOfTerminals) {

		numberOfInputTerminals = 0;
		numberOfOutputTerminals = 0;
		length = numberOfTerminals;
		terminalDefinitions = new TerminalsDefinition[numberOfTerminals];
	}
	void TerminalsDefinitionStruct::scan(int i) {
		
		if (terminalDefinitions != nullptr) {
			terminalDefinitions[i].scan();
		}
		if (terminalDefinitions[i].type == "Input")
			++numberOfInputTerminals;
		else
			++numberOfOutputTerminals;
	}
	bunchOfLogicElements::~bunchOfLogicElements() {

		if (size != 0) {
			for (int i{ 0 }; i < size; ++i)
				delete logicElements[i];
		}
		delete[] logicElements;
	}
	TerminalsDefinitionStruct::~TerminalsDefinitionStruct() {

		if (terminalDefinitions != nullptr)
			delete[] terminalDefinitions;
	}

	void TerminalsDefinition::scan() {

		type = dialog::getType();
		connections = dialog::getNum(type);
		if (connections == 0 && type == "Input"){
			std::cout << "For input terminal without connections state of signal is X" << std::endl;
			signal = 'X';
		}
		else
			signal = dialog::getSignal();
	}

	LogicElement::LogicElement() {

		number = 0;
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
		this->numberOfInputTerminals = terminalsDefinitionStruct.numberOfInputTerminals;
		outputTerminals = new terminal::Terminal * [terminalsDefinitionStruct.numberOfOutputTerminals];
		this->numberOfOutputTerminals = terminalsDefinitionStruct.numberOfOutputTerminals;
		while (i < terminalsDefinitionStruct.length) {
			if (terminalsDefinitionStruct.terminalDefinitions[i].type == "Input") {
				inputTerminals[j] = new terminal::Terminal(terminalsDefinitionStruct.terminalDefinitions[i].type, 
					terminalsDefinitionStruct.terminalDefinitions[i].connections,terminalsDefinitionStruct.terminalDefinitions[i].signal, i + 1);
				++j;
			}
			else {
				outputTerminals[k] = new terminal::Terminal(terminalsDefinitionStruct.terminalDefinitions[i].type,
					terminalsDefinitionStruct.terminalDefinitions[i].connections, terminalsDefinitionStruct.terminalDefinitions[i].signal, i + 1);
				++k;
			}
			++i;
		}
	}
	LogicElement::~LogicElement() {

		int i{ 0 };
		for (i; i < numberOfInputTerminals; ++i)
			delete inputTerminals[i];
		for (i = 0; i < numberOfOutputTerminals; ++i)
			delete outputTerminals[i];
		delete[] inputTerminals;
		delete[] outputTerminals;
	}

	int LogicElement::getNumber() {

		return number;
	}
	int LogicElement::getNumberOfInput() {

		return numberOfInputTerminals;
	}
	int LogicElement::getNumberOfOutput() {

		return numberOfOutputTerminals;
	}

	void LogicElement::print() {
		
		int i{ 0 };
		std::cout << "Logic element number " << number << std::endl;
		std::cout << "Number of input terminals is " << numberOfInputTerminals << std::endl;
		std::cout << "Their states are " << std::endl << std::endl;
		for (i; i < numberOfInputTerminals; ++i)
			inputTerminals[i]->print();
		std::cout << "Number of output terminals is " << numberOfOutputTerminals << std::endl;
		std::cout << "Their states are " << std::endl;
		for (i = 0; i < numberOfOutputTerminals; ++i)
			outputTerminals[i]->print();

	}
	void LogicElement::scan() {

	}
}