#include <iostream>
#include <string>
#include "Dialog.h"
#include "Terminal.h"

namespace Dialog {

	const char* types_of_terminals[] = { "0. Input terminal", "1. Output terminal" };
	const int number_of_types = sizeof(types_of_terminals) / sizeof(types_of_terminals[0]);
	const char* types_of_signals[] = { "0. Terminal is off","1. Terminal is on", "2. State X" };
	const int number_of_signals = sizeof(types_of_signals) / sizeof(types_of_signals[0]);

	int dialog(const char* msgs[], const int number_of_msgs) {
		
		for (int i{ 0 }; i < number_of_msgs; i++) {
			
			std::puts(msgs[i]);

		}
		int alternative;
		try
		{
			alternative = NumInput<int>(-1, number_of_msgs);
			return alternative;
		}
		catch (const std::exception&)
		{
			throw;
		}
	}
	int D_Create_Full(Terminal::Terminal** pointer, int& size) {
		try {
			std::cout << "Enter type of terminal" << std::endl;
			std::string type = getType();
			std::cout << "Enter number of connections" << std::endl;
			if (type == "Input")
				std::cout << "Maximum number connections for this type is 1" << std::endl;
			else
				std::cout << "Maximum number connections for this type is 3" << std::endl;
			int connections = getNum(type);
			std::cout << "Enter type of signal" << std::endl;
			char signal = getSignal();
			createTerminal(pointer, size, type, connections, signal);
			return 1;
		}
		catch (std::exception&) {

		}
	}
	int D_Create(Terminal::Terminal** pointer, int& size) {
		try
		{
			std::cout << "Enter type of terminal" << std::endl;
			std::string type = getType();
			createTerminal(pointer, size, type);
			return 1;
		}
		catch (const std::exception&)
		{

		}
		
	}
	int D_Connect(Terminal::Terminal** pointer, int& size) {

		return 1;
	}
	int D_Disconnect(Terminal::Terminal** pointer, int& size){

		return 1;
	}
	int D_Print(Terminal::Terminal** pointer, int& size) {

		int i{ 0 };
		if (*pointer == nullptr) {
			std::cout << "No terminals"<<std::endl;
			return 1;
		}
		while (*(pointer + i) != nullptr && i < size) {

			std::cout << "Terminal number " << i+1 << std::endl << "Type of terminal is " << (*(pointer + i))->getType() << std::endl;
			std::cout << "Number of connections is " << (*(pointer + i))->getConnections() << std::endl << "State of signal is ";
			std::cout << (*pointer + i)->getSignal() << std::endl;
			std::cout << std::endl;
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
			return  '1';
		else
			return 'X';
	}
	int getNum(std::string& type) {
		if (type == types_of_terminals[0])
			return NumInput(-1, 2);
		else
			return NumInput(-1, 4);
	}
	void createTerminal(Terminal::Terminal** pointer, int& size, std::string& type, int connections, char signal) {

		int i{ 0 };
		while (*(pointer + i) != nullptr && i < size) {
			i++;
		}
		if (i == size) {

			pointer = expansion(pointer, size);
			*(pointer + i) = new Terminal::Terminal(type,connections,signal);

		}
		else {
			*(pointer + i) = new Terminal::Terminal(type, connections, signal);
		}
	}
	void createTerminal(Terminal::Terminal** pointer, int& size, std::string& type) {

		int i{ 0 };
		while (*(pointer + i) != nullptr && i < size) {
			i++;
		}
		if (i == size) {

			pointer = expansion(pointer, size);
			*(pointer + i) = new Terminal::Terminal(type);

		}
		else {
			*(pointer + i) = new Terminal::Terminal(type);
		}
	}
	Terminal::Terminal** expansion(Terminal::Terminal** pointer, int& size) {

		try
		{
			Terminal::Terminal** NewArr = new Terminal::Terminal * [2 * size];
			pointer = copy(pointer, NewArr, size);
			return pointer;
		}
		catch (const std::exception&)
		{
			throw;
			return pointer;
		}
	}
	Terminal::Terminal** copy(Terminal::Terminal** FirstPtr, Terminal::Terminal** SecondPtr, int& size) {

		int i = 0;
		for (i = 0; i < size; i++) {
			*(SecondPtr + i) = *(FirstPtr + i);
		}
		while (i < 2 * size) {
			*(SecondPtr + i) = nullptr;
			++i;
		}
		size *= 2;
		return SecondPtr;
	}
}