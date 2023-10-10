#include <iostream>
#include <string>
#include <format>
#include "Dialog.h"
#include "Terminal.h"
#include "LogicElement.h"
#include "Vector.h"

namespace dialog {

	const char* types_of_terminals[] = { "0. Input terminal", "1. Output terminal" };
	const int number_of_types = sizeof(types_of_terminals) / sizeof(types_of_terminals[0]);
	const char* types_of_signals[] = { "0. Terminal is off","1. Terminal is on", "2. State X" };
	const int number_of_signals = sizeof(types_of_signals) / sizeof(types_of_signals[0]);

	//Terminals' dialog functions

	int dialog(const char* msgs[], const int number_of_msgs) {

		for (int i{ 0 }; i < number_of_msgs; i++) {

			std::puts(msgs[i]);

		}
		int alternative;

		alternative = NumInput<int>(-1, number_of_msgs);
		return alternative;
	}
	int createFull(vector::Vector<terminal::Terminal>& terminals) {

		terminal::Type type;
		int connections;
		terminal::Signal signal;
		std::cout << std::format("{}\n{}\n{}\n", "Enter type of terminal", "0.Output terminal", "1.Input terminal");
		type = static_cast<terminal::Type>(NumInput(0, 1));
		std::cout << std::format("{}\n", "Enter number of connections");
		if (type == terminal::Type::INPUT) {
			std::cout << std::format("{}\n", "Maximum number connections for this type is 1");
			connections = NumInput<int>(0, 1);
		}
		else {
			std::cout << std::format("{}\n", "Maximum number connections for this type is 3");
			connections = NumInput<int>(0, 3);
		}
		if (type == terminal::Type::INPUT && !connections) {
			std::cout << std::format("{}\n", "For input terminal with 0 connections, type of signal is X");
			signal = terminal::Signal::X;
		}
		else {
			std::cout << std::format("{}\n{}\n{}\n{}\n", "Enter state of signal", "0.Off", "1.On", "2.X");
			signal = static_cast<terminal::Signal>(NumInput<int>(0, 2));
		}
		try {
			terminals.pushback(terminal::Terminal(type, connections, signal, terminals.getSize() + 1));
			return 1;
		}
		catch (std::bad_alloc& ba) {
			std::cout << std::format("{}\n", "Not enough memory to create new terminal");
			return 1;
		}
	}
	int createWithType(vector::Vector<terminal::Terminal>& terminals) {

		std::cout << std::format("{}\n{}\n{}\n", "Enter type of terminal", "0.Output terminal", "1.Input terminal");
		terminal::Type type = static_cast<terminal::Type>(NumInput<int>(0, 1));
		try {
			terminals.pushback(terminal::Terminal(type, terminals.getSize() + 1));
			return 1;
		}
		catch (std::bad_alloc& ba) {

			std::cout << "Not enough memory to create new terminal" << std::endl;
			return 1;
		}

	}
	int enter(vector::Vector<terminal::Terminal>& terminals) {

		if (terminals.getSize() == 0) {
			std::cout << "There are no terminals to enter" << std::endl;
			return 1;
		}
		std::cout << "Choose number of terminal you want to enter" << std::endl;
		for (int i{ 1 }; i <= terminals.getSize(); ++i)
			std::cout << std::format("{} ", i);
		std::cout << std::endl;
		int number = dialog::NumInput<int>(1, terminals.getSize());
		terminals[number - 1].scan();
		return 1;
	}
	int connect(vector::Vector<terminal::Terminal>& terminals) {


		if (!terminals.getSize() || terminals.getSize() == 1) {
			std::cout << std::format("There are no terminals to connect\n");
			return 1;
		}
		int firstTerminal;
		int secondTerminal;
		std::cout << "Choose terminals to connect" << std::endl;
		for (int i{ 1 }; i <= terminals.getSize(); ++i)
			std::cout<<std::format("{} ", i);
		std::cout << std::endl;
		std::cout << "Enter number of the first terminal" << std::endl;
		firstTerminal = NumInput<int>(0, terminals.getSize() + 1);
		std::cout << "Enter number of the second terminal" << std::endl;
		secondTerminal = NumInput<int>(0, terminals.getSize() + 1);
		try {
			terminals[firstTerminal - 1].connect(terminals[secondTerminal - 1]);
			return 1;
		}
		catch(const std::invalid_argument& ia){
			std::cout << ia.what() << std::endl;
			return 1;
		}
	}
	int disconnect(vector::Vector<terminal::Terminal>& terminals) {

		if (!terminals.getSize() && terminals.getSize() == 1) {
			std::cout << std::format("There are no terminals to disconnect\n");
			return 1;
		}
		int firstTerminal;
		int secondTerminal;
		std::cout << "Choose terminals to disconnect" << std::endl;
		for (int i{ 1 }; i <= terminals.getSize(); ++i)
			std::cout << std::format("{} ", i);
		std::cout << std::endl;
		std::cout << "Enter number of the first terminal" << std::endl;
		firstTerminal = NumInput<int>(0, terminals.getSize() + 1);
		std::cout << "Enter number of the second terminal" << std::endl;
		secondTerminal = NumInput<int>(0, terminals.getSize() + 1);
		try {
				terminals[firstTerminal - 1].disconnect(terminals[secondTerminal - 1]);
				return 1;
			}
		catch (const std::invalid_argument& ia)
		{
			std::cout << ia.what() << std::endl;
			return 1;

		}
	}
	int print(vector::Vector<terminal::Terminal>& terminals) {

		int i{ 0 };
		if (terminals.getSize() == 0) {
			std::cout << "No terminals"<<std::endl;
			return 1;
		}
		while (i < terminals.getSize()) {

			terminals[i].print();
			++i;
		}
		return 1;
	}

	//Logic elements' dialog functions

	int createWithNumber(vector::Vector<logicElement::LogicElement>& logicElements){

		int numInput;
		int numOutput;
		std::cout << "Enter number of input terminals" << std::endl;
		numInput = NumInput<int>(0,std::numeric_limits<int>::max());
		std::cout << "Enter number of output terminals" << std::endl;
		numOutput = NumInput<int>(0, std::numeric_limits<int>::max());
		logicElements.pushback(logicElement::LogicElement(numInput,numOutput,logicElements.getSize()+1));
		return 1;
	}
	int createWithArray(vector::Vector<logicElement::LogicElement>& logicElements){

		std::cout << "Enter number of terminals you want to create" << std::endl;
		int numTerminals = NumInput<int>(0, std::numeric_limits<int>::max());
		logicElement::DefStruct defStruct(numTerminals);
		defStruct.scan();
		logicElements.pushback(logicElement::LogicElement(defStruct,logicElements.getSize()+1));
		return 1;
	}
	int enter(vector::Vector<logicElement::LogicElement>& logicElements){

		if (logicElements.getSize() == 0) {
			std::cout << std::format("There are no logic element to reenter. Firstly create logic element\n");
			return 1;
		}
		std::cout << std::format("Choose the number of logic element you want to enter\n");
		for (int i{ 0 }; i < logicElements.getSize(); ++i)
			std::cout << std::format("{} ", i+1);
		std::cout << std::endl;
		int numLogic = NumInput<int>(0, logicElements.getSize() + 1);
		logicElements[numLogic - 1].scan();
		return 1;
	}
	int getTerminal(vector::Vector<logicElement::LogicElement>& logicElements){

		return 1;
	}
	int connect(vector::Vector<logicElement::LogicElement>& logicElements){

		return 1;
	}
	int print(vector::Vector<logicElement::LogicElement>& logicElements) {

		if (logicElements.getSize() == 0) {
			std::cout << "Thera are no logic elements to print" << std::endl;
			return 1;
		}
		for (int i{ 0 }; i < logicElements.getSize(); ++i)
			logicElements[i].print();
		return 1;
	}

}
