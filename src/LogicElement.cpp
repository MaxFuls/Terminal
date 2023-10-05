#include <iostream>
#include "LogicElement.h"
#include "Terminal.h"
#include "Dialog.h"
#include <format>

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
			if (terminalDefinitions[i].type == "Input")
				++numberOfInputTerminals;
			else
				++numberOfOutputTerminals;
		}
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
		inputTerminals = new terminal::Terminal* [numberOfInputTerminals];
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

	int LogicElement::getNumber() const {

		return number;
	}
	int LogicElement::getNumberOfInput() const {

		return numberOfInputTerminals;
	}
	int LogicElement::getNumberOfOutput() const {

		return numberOfOutputTerminals;
	}

	void LogicElement::setNumber(int) {

	}
	void LogicElement::setNumberOfInput(){
	}
	void LogicElement::setNumberOfOutput() {

	}

	void LogicElement::print() {
		
		int i{ 0 };
		std::string s1 = "Logic element number";
		std::string s2 = "Number of input terminals is";
		std::string s3 = "Number of output terminals is";
		std::string s4 = "Their states are:";
		std::cout << std::format("{} {}\n{} {}\n{}\n\n",s1, number, s2, numberOfInputTerminals, s4);
		for (i; i < numberOfInputTerminals; ++i)
			inputTerminals[i]->print();
		std::cout << std::format("{} {}\n{}\n\n", s3, numberOfOutputTerminals, s4);
		for (i = 0; i < numberOfOutputTerminals; ++i)
			outputTerminals[i]->print();

	}
	void LogicElement::scan() {

		if (inputTerminals != nullptr) {
			delete[] inputTerminals;
			for (int i{ 0 }; i < numberOfInputTerminals; ++i)
				delete inputTerminals[i];
		}
		if (outputTerminals != nullptr) {
			delete[] outputTerminals;
			for (int i{ 0 }; i < numberOfOutputTerminals; ++i)
				delete outputTerminals[i];
		}
		std::cout << "Enter number of logic element" << std::endl;
		number = dialog::NumInput<int>(0, std::numeric_limits<int>::max());
		std::cout << "Enter number of input terminals" << std::endl;
		numberOfInputTerminals = dialog::NumInput<int>(0, std::numeric_limits<int>::max());
		std::cout << "Enter number of output terminals" << std::endl;
		numberOfOutputTerminals = dialog::NumInput<int>(0, std::numeric_limits<int>::max());
		inputTerminals = new terminal::Terminal * [numberOfInputTerminals];
		outputTerminals = new terminal::Terminal * [numberOfOutputTerminals];
		std::cout << "Enter states of input terminals" << std::endl;
		int i{ 0 };
		std::string Input = "Input";
		std::string Output = "Output";
		for (i; i < numberOfInputTerminals; ++i) {
			inputTerminals[i] = new terminal::Terminal(Input, i+1);
			inputTerminals[i]->setConnections();
			inputTerminals[i]->setSignal();
		}
		std::cout << "Enter states of output terminals" << std::endl;
		for (i = 0; i < numberOfOutputTerminals; ++i) {
			outputTerminals[i] = new terminal::Terminal(Output, i + 1);
			outputTerminals[i]->setConnections();
			outputTerminals[i]->setSignal();
		}
	}
}