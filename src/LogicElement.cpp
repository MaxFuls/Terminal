#include <iostream>
#include <format>
#include "Terminal.h"
#include "Dialog.h"
#include "Vector.h"
#include "LogicElement.h"

namespace logicElement {

	DefStruct::DefStruct(int numTerminals): length(numTerminals), numInput(0), numOutput(0) {
	
		definitions = new Definitions[numTerminals];
	}
	DefStruct::~DefStruct() {

		delete[] definitions;
	}
	void DefStruct::scan() {
		
		if (definitions != nullptr) {
			for (int i{ 0 }; i < length; ++i) {
				definitions[i].scan();
				if (definitions[i].type == terminal::Type::INPUT)
					++numInput;
				else
					++numOutput;
			}
		}
	}
	void Definitions::scan() {

		std::cout << std::format("Enter type of terminal\n0.Output\n1.Input\n");
		type = static_cast<terminal::Type>(dialog::NumInput(0, 1));
		std::cout << std::format("Enter number of connections: 0 or 1 for input terminal, from 0 to 3 for output\n");
		if (type == terminal::Type::INPUT)
			connections = dialog::NumInput(0, 1);
		else
			connections = dialog::NumInput(0, 3);
		if (type == terminal::Type::INPUT && !connections) {
			std::cout << std::format("For input terminal with 0 connections state of signal is X");
			signal = terminal::Signal::X;
		}
		else {
			std::cout << std::format("Enter state of signal\n0.Off\n1.On\n2.X\n");
			signal = static_cast<terminal::Signal>(dialog::NumInput(0, 2));
		}
	}


	LogicElement::LogicElement(): number(0), numInput(0) , numOutput(0)	{	}
	LogicElement::LogicElement(int numInput, int numOutput, int number) : number(number), numInput(numInput), inputTerminals(numInput)
									,numOutput(numOutput), outputTerminals(numOutput){

		int i{ 0 };
		for (i; i < numInput; ++i)
			inputTerminals.pushback(terminal::Terminal(terminal::Type::INPUT, i+1));
		for (i = 0; i < numOutput; ++i)
			outputTerminals.pushback(terminal::Terminal(terminal::Type::OUTPUT, i+1));
	}
	LogicElement::LogicElement(const DefStruct& defStruct, int number): number(number), numInput(defStruct.numInput), inputTerminals(defStruct.numInput)
										,numOutput(defStruct.numOutput), outputTerminals(defStruct.numOutput){

		int i{ 0 };
		int j{ 0 };
		int k{ 0 };
		for (i; i < defStruct.length; ++i) {
			if (defStruct.definitions[i].type == terminal::Type::INPUT)
				inputTerminals.pushback(terminal::Terminal(terminal::Type::INPUT, defStruct.definitions[i].connections, defStruct.definitions->signal, ++j));
			else
				outputTerminals.pushback(terminal::Terminal(terminal::Type::OUTPUT, defStruct.definitions[i].connections, defStruct.definitions[i].signal, ++k));
		}
	}
	LogicElement::LogicElement(const LogicElement& logicElement) {

		number = logicElement.number;
		numInput = logicElement.numInput;
		inputTerminals = logicElement.inputTerminals;
		numOutput = logicElement.numOutput;
		outputTerminals = logicElement.outputTerminals;

	}
	LogicElement& LogicElement::operator=(const LogicElement& logicElement) {
		if (this != &logicElement) {
			number = logicElement.number;
			numInput = logicElement.numInput;
			inputTerminals = logicElement.inputTerminals;
			numOutput = logicElement.numOutput;
			outputTerminals = logicElement.outputTerminals;
		}
		return *this;
	}

	int LogicElement::getNumber() const {

		return number;
	}
	int LogicElement::getNumberOfInput() const {

		return numInput;
	}
	int LogicElement::getNumberOfOutput() const {

		return numOutput;
	}

	void LogicElement::setNumber(int number) {

		if (number > 0)
			this->number = number;
		else
			throw std::invalid_argument("Number need pe positive");
	}
	void LogicElement::setNumberOfInput(int numInput){
	
		if (numInput > 0) {
			this->numInput = numInput;
			inputTerminals.setSize(numInput);
		}
		else
			throw std::invalid_argument("Number od input terminals need be positive");
	}
	void LogicElement::setNumberOfOutput(int numOutput) {
		
		if (numOutput > 0) {
			this->numOutput = numOutput;
			outputTerminals.setSize(numOutput);
		}
		else
			throw std::invalid_argument("Number od input terminals need be positive");
	}

	void LogicElement::print() {
		
		int i{ 0 };
		std::cout << std::format("Number of logic element is {}\nNumber of input terminals is {}\n", number, numInput);
		if (numInput) std::cout << std::format("Their states are\n\n");
		for (i; i < numInput; ++i)
			inputTerminals[i].print();
		std::cout << std::format("Number of output terminals is {}\n", numOutput);
		if (numOutput) std::cout << std::format("Their states are\n\n");
		for (i = 0; i < numOutput; ++i)
			outputTerminals[i].print();

	}
	void LogicElement::scan() {

		std::cout << std::format("Enter number of terminals you want to enter\n");
		int numTerminals = dialog::NumInput<int>(1, std::numeric_limits<int>::max());
		DefStruct defStruct(numTerminals);
		defStruct.scan();
		inputTerminals.clear();
		outputTerminals.clear();
		int j{ 1 };
		int k{ 1 };
		for (int i{ 0 }; i < numTerminals; ++i) {
			if (defStruct.definitions[i].type == terminal::Type::INPUT)
				inputTerminals.pushback(terminal::Terminal(terminal::Type::INPUT, defStruct.definitions[i].connections
																,defStruct.definitions[i].signal, j++));
			else
				outputTerminals.pushback(terminal::Terminal(terminal::Type::OUTPUT, defStruct.definitions[i].connections
																,defStruct.definitions[i].signal, k++));
		}
		numInput = defStruct.numInput;
		numOutput = defStruct.numOutput;
	}

	void addTerminal(const terminal::Terminal& terminal) {


	}
	void connect(LogicElement& logicElement){
	
	
	}
	const terminal::Terminal& getTerminal(int number) {

		return terminal::Terminal();
	}
}