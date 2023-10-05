#include <iostream>
#include <string>
#include "Dialog.h"
#include "Terminal.h"
#include "LogicElement.h"

namespace dialog {

	const char* types_of_terminals[] = { "0. Input terminal", "1. Output terminal" };
	const int number_of_types = sizeof(types_of_terminals) / sizeof(types_of_terminals[0]);
	const char* types_of_signals[] = { "0. Terminal is off","1. Terminal is on", "2. State X" };
	const int number_of_signals = sizeof(types_of_signals) / sizeof(types_of_signals[0]);

	int dialog(const char* msgs[], const int number_of_msgs) {

		for (int i{ 0 }; i < number_of_msgs; i++) {

			std::puts(msgs[i]);

		}
		int alternative;

		alternative = NumInput<int>(-1, number_of_msgs);
		return alternative;
	}
	int D_Create_Full(terminal::bunchOfTerminals& bunchOfTerminals) {

		std::cout << "Enter type of terminal" << std::endl;
		std::string type = getType();
		std::cout << "Enter number of connections" << std::endl;
		if (type == "Input")
			std::cout << "Maximum number connections for this type is 1" << std::endl;
		else
			std::cout << "Maximum number connections for this type is 3" << std::endl;
		int connections = getNum(type);
		char signal;
		if (type == "Input" && connections == 0) {
			std::cout << "For input terminal with 0 connections, type of signal is X" << std::endl;
			signal = 'X';
		}
		else {
			std::cout << "Enter type of signal" << std::endl;
			signal = getSignal();
		}
		try {
			createTerminal(bunchOfTerminals, type, connections, signal);
			return 1;
		}
		catch (std::bad_alloc& ba) {
			std::cout << "Not enough memory to create new terminal" << std::endl;
			return 1;
		}
	}
	int D_Create(terminal::bunchOfTerminals& bunchOfTerminals) {

		std::cout << "Enter type of terminal" << std::endl;
		std::string type = getType();
		try {
			createTerminal(bunchOfTerminals, type);
			return 1;
		}
		catch (std::bad_alloc& ba) {

			std::cout << "Not enough memory to create new terminal" << std::endl;
			return 1;
		}

	}
	int D_Enter(terminal::bunchOfTerminals& bunchOfTerminals) {

		if (bunchOfTerminals.size == 0) {
			std::cout << "There are no terminals to enter" << std::endl;
			return 1;
		}
		std::cout << "Choose number of terminal you want to enter" << std::endl;
		for (int i{ 1 }; i <= bunchOfTerminals.size; ++i)
			std::cout <<  i  << " ";
		std::cout << std::endl;
		int number = dialog::NumInput<int>(0,bunchOfTerminals.size +1);
		bunchOfTerminals.arr[number-1]->scan();
		return 1;
	}
	int D_Connect(terminal::bunchOfTerminals& bunchOfTerminals) {

		try {
			if (bunchOfTerminals.size == 0)
				throw std::logic_error("There are no terminals to connect");
			if (bunchOfTerminals.size == 1)
				throw std::logic_error("There is only one terminal to connect");
			int firstTerminal;
			int secondTerminal;
			std::cout << "Choose terminals to connect" << std::endl;
			for (int i{ 1 }; i <= bunchOfTerminals.size; ++i)
				std::cout << i << " ";
			std::cout << std::endl;
			std::cout << "Enter number of the first terminal" << std::endl;
			firstTerminal = NumInput<int>(0, bunchOfTerminals.size + 1);
			std::cout << "Enter number of the second terminal" << std::endl;
			secondTerminal = NumInput<int>(0, bunchOfTerminals.size + 1);
			bunchOfTerminals.arr[firstTerminal - 1]->connect(bunchOfTerminals.arr[secondTerminal - 1]);
			return 1;
		}
		catch(const std::logic_error& le){
			std::cout << le.what() << std::endl;
			return 1;
		}
	}
	int D_Disconnect(terminal::bunchOfTerminals& bunchOfTerminals) {
		try
		{
			if (bunchOfTerminals.size == 0)
				throw std::logic_error("There are no terminals to disconnect");
			if (bunchOfTerminals.size == 1)
				throw std::logic_error("There is only one terminal to disconnect");
			int firstTerminal;
			int secondTerminal;
			std::cout << "Choose terminals to disconnect" << std::endl;
			for (int i{ 1 }; i <= bunchOfTerminals.size; ++i)
				std::cout << i << " ";
			std::cout << std::endl;
			std::cout << "Enter number of the first terminal" << std::endl;
			firstTerminal = NumInput<int>(0, bunchOfTerminals.size + 1);
			std::cout << "Enter number of the second terminal" << std::endl;
			secondTerminal = NumInput<int>(0, bunchOfTerminals.size + 1);
			bunchOfTerminals.arr[firstTerminal - 1]->disconnect(bunchOfTerminals.arr[secondTerminal - 1]);
			return 1;
		}
		catch (const std::logic_error& le)
		{
			std::cout << le.what() << std::endl;
			return 1;

		}
	}
	int D_Print(terminal::bunchOfTerminals& bunchOfTerminals) {

		int i{ 0 };
		if (bunchOfTerminals.size==0) {
			std::cout << "No terminals"<<std::endl;
			return 1;
		}
		while (i < bunchOfTerminals.size) {

			bunchOfTerminals.arr[i]->print();
			++i;
		}
		return 1;
	}
	int D_Print_Connections(terminal::bunchOfTerminals& bunchOfTerminals) {

		int i{ 0 };
		if (bunchOfTerminals.size==0) {
			std::cout << "No terminals" << std::endl;
			return 1;
		}
		while (i < bunchOfTerminals.size) {
			bunchOfTerminals.arr[i]->printConnections();
			++i;
		}
		return 1;

	}


	std::string getType() {

		if (dialog(types_of_terminals, number_of_types) == 0)
			return "Input";
		else
			return "Output";
	}
	char getSignal() {
		
		int signal = dialog(types_of_signals, number_of_signals);
		if (signal == 0)
			return '0';
		else if (signal == 1)
			return '1';
		else 
			return 'X';

	}
	int getNum(std::string& type) {

		if (type == "Input") {
			return NumInput(-1, 2);
		}
		else {
			return NumInput(-1, 4);
		}
	}


	void createTerminal(terminal::bunchOfTerminals& bunchOfTerminals, std::string& type, int connections, char signal) {


		if (bunchOfTerminals.size == bunchOfTerminals.capacity) {

			bunchOfTerminals.arr = expansion(bunchOfTerminals);
			bunchOfTerminals.arr[bunchOfTerminals.size] = new terminal::Terminal(type, connections, signal, bunchOfTerminals.size + 1);
			++bunchOfTerminals.size;

		}
		else {

			bunchOfTerminals.arr[bunchOfTerminals.size] = new terminal::Terminal(type, connections, signal, bunchOfTerminals.size + 1);
			++bunchOfTerminals.size;
		}
	}
	void createTerminal(terminal::bunchOfTerminals& bunchOfTerminals, std::string& type) {

		if (bunchOfTerminals.size == bunchOfTerminals.capacity) {

			bunchOfTerminals.arr = expansion(bunchOfTerminals);
			bunchOfTerminals.arr[bunchOfTerminals.size] = new terminal::Terminal(type, bunchOfTerminals.size + 1);
			++bunchOfTerminals.size;

		}
		else {

			bunchOfTerminals.arr[bunchOfTerminals.size] = new terminal::Terminal(type, bunchOfTerminals.size + 1);
			++bunchOfTerminals.size;
		}
	}
	void createTerminal(terminal::bunchOfTerminals& bunchOfTerminals) {

		if (bunchOfTerminals.size == bunchOfTerminals.capacity) {

			bunchOfTerminals.arr = expansion(bunchOfTerminals);
			bunchOfTerminals.arr[bunchOfTerminals.size] = new terminal::Terminal();
			++bunchOfTerminals.size;

		}
		else {

			bunchOfTerminals.arr[bunchOfTerminals.size] = new terminal::Terminal();
			++bunchOfTerminals.size;
		}
	}


	terminal::Terminal** expansion(terminal::bunchOfTerminals& bunchOfTerminals) {

		terminal::Terminal** NewArr = new terminal::Terminal * [2 * bunchOfTerminals.capacity]();
		copyValues(bunchOfTerminals, NewArr);
		delete[] bunchOfTerminals.arr;
		return NewArr;
	}
	void copyValues(terminal::bunchOfTerminals& bunchOfTerminals, terminal::Terminal** SecondPtr) {

		int i{ 0 };
		for ( i ; i < bunchOfTerminals.capacity; ++i) {
			SecondPtr[i] = bunchOfTerminals.arr[i];
		}
		bunchOfTerminals.capacity *= 2;
	}

	//Logic element functions

	int D_Create_With_Number(logicElement::bunchOfLogicElements& bunchOfLogicElements){
		
		int numberOfInputTerminals;
		int numberOfOutputTerminals;
		std::cout << "Enter number of input terminals" << std::endl;
		numberOfInputTerminals = NumInput<int>(0,std::numeric_limits<int>::max());
		std::cout << "Enter number of output terminals" << std::endl;
		numberOfOutputTerminals = NumInput<int>(0, std::numeric_limits<int>::max());
		createLogicElement(bunchOfLogicElements, numberOfInputTerminals, numberOfOutputTerminals);
		return 1;
	}
	int D_Create_With_Array(logicElement::bunchOfLogicElements& bunchOfLogicElements){
	
		std::cout << "Enter number of terminals you want to create" << std::endl;
		int numberOfTerminals = NumInput<int>(0, std::numeric_limits<int>::max());
		logicElement::TerminalsDefinitionStruct terminalDefinitionStruct(numberOfTerminals);
		for (int i{ 0 }; i < numberOfTerminals; ++i)
			terminalDefinitionStruct.scan(i);
		createLogicElement(bunchOfLogicElements, terminalDefinitionStruct);
		return 1;
	}
	int D_Enter_Logic_Element(logicElement::bunchOfLogicElements& bunchOfLogicElements){
		
		if (bunchOfLogicElements.size == 0) {
			std::cout << "There are no logic element to reenter. Firstly create logic element" << std::endl;
			return 1;
		}
		int numberOfLogicElement = NumInput<int>(0, bunchOfLogicElements.size + 1);
		bunchOfLogicElements.logicElements[numberOfLogicElement - 1]->scan();
		return 1;
	}
	int D_Get_Terminal(logicElement::bunchOfLogicElements& bunchOfLogicElements){

		return 1;
	}
	int D_Connect_Logic_Elements(logicElement::bunchOfLogicElements& bunchOfLogicElements){
		
		return 1;
	}
	int D_Print_Logic_Elements(logicElement::bunchOfLogicElements& bunchOfLogicElements) {

		if (bunchOfLogicElements.size == 0) {
			std::cout << "Thera are no logic elements to print" << std::endl;
			return 1;
		}
		for (int i{ 0 }; i < bunchOfLogicElements.size; ++i)
			bunchOfLogicElements.logicElements[i]->print();
		return 1;
	}

	void createLogicElement(logicElement::bunchOfLogicElements& bunchOfLogicElements) {

	}
	void createLogicElement(logicElement::bunchOfLogicElements& bunchOfLogicElements,int numberOfInputTerminals, int numberOfOutputTerminals) {

		if (bunchOfLogicElements.capacity == bunchOfLogicElements.size) {

			expansionLogic(bunchOfLogicElements);
			bunchOfLogicElements.logicElements[bunchOfLogicElements.size] = new logicElement::LogicElement(numberOfInputTerminals, numberOfOutputTerminals,
				bunchOfLogicElements.size + 1);
			++bunchOfLogicElements.size;

		}
		else {
			bunchOfLogicElements.logicElements[bunchOfLogicElements.size] = new logicElement::LogicElement(numberOfInputTerminals, numberOfOutputTerminals,
																														bunchOfLogicElements.size + 1);
			++bunchOfLogicElements.size;
		}
	}
	void createLogicElement(logicElement::bunchOfLogicElements& bunchOfLogicElements, logicElement::TerminalsDefinitionStruct& terminalDefinitionStruct) {

		if (bunchOfLogicElements.size == bunchOfLogicElements.capacity) {

			bunchOfLogicElements.logicElements =  expansionLogic(bunchOfLogicElements);
			bunchOfLogicElements.logicElements[bunchOfLogicElements.size] = new logicElement::LogicElement(terminalDefinitionStruct,
				bunchOfLogicElements.size + 1);
			++bunchOfLogicElements.size;
		}
		else {
			bunchOfLogicElements.logicElements[bunchOfLogicElements.size] = new logicElement::LogicElement(terminalDefinitionStruct,
																												bunchOfLogicElements.size + 1);
			++bunchOfLogicElements.size;
		}
	}

	logicElement::LogicElement** expansionLogic(logicElement::bunchOfLogicElements& bunchOfLogicElements) {

		logicElement::LogicElement** NewArr = new logicElement::LogicElement * [2 * bunchOfLogicElements.capacity];
		copyValuesLogic(bunchOfLogicElements, NewArr);
		delete[] bunchOfLogicElements.logicElements;
		return NewArr;
	}
	void copyValuesLogic(logicElement::bunchOfLogicElements& bunchOfLogicElements, logicElement::LogicElement** NewArr) {

		for (int i{ 0 }; i < bunchOfLogicElements.capacity; ++i) {
			NewArr[i] = bunchOfLogicElements.logicElements[i];
		}
		bunchOfLogicElements.capacity *= 2;
	}

}
