#include <iostream>
#include <string>
#include "Dialog.h"
#include "Terminal.h"

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
		createTerminal(bunchOfTerminals, type, connections, signal);
		return 1;
	}
	int D_Create(terminal::bunchOfTerminals& bunchOfTerminals) {

		std::cout << "Enter type of terminal" << std::endl;
		std::string type = getType();
		createTerminal(bunchOfTerminals, type);
		return 1;

	}
	int D_Enter(terminal::bunchOfTerminals& bunchOfTerminals) {

		createTerminal(bunchOfTerminals);
		bunchOfTerminals.arr[bunchOfTerminals.capacity]->scan();
		return 1;
	}
	int D_Connect(terminal::bunchOfTerminals& bunchOfTerminals) {

		try {
			if (bunchOfTerminals.capacity == 0)
				throw std::logic_error("There are no terminals to connect");
			if (bunchOfTerminals.capacity == 1)
				throw std::logic_error("There is only one terminal to connect");
			int firstTerminal;
			int secondTerminal;
			std::cout << "Choose terminals to connect" << std::endl;
			std::cout << "Enter number of the first terminal" << std::endl;
			firstTerminal = NumInput<int>(0, bunchOfTerminals.capacity + 1);
			std::cout << "Enter number of the second terminal" << std::endl;
			secondTerminal = NumInput<int>(0, bunchOfTerminals.capacity + 1);
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
			if (bunchOfTerminals.capacity == 0)
				throw std::logic_error("There are no terminals to disconnect");
			if (bunchOfTerminals.capacity == 1)
				throw std::logic_error("There is only one terminal to disconnect");
			int firstTerminal;
			int secondTerminal;
			std::cout << "Choose terminals to disconnect" << std::endl;
			std::cout << "Enter number of the first terminal" << std::endl;
			firstTerminal = NumInput<int>(0, bunchOfTerminals.capacity + 1);
			std::cout << "Enter number of the second terminal" << std::endl;
			secondTerminal = NumInput<int>(0, bunchOfTerminals.capacity + 1);
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
		if (bunchOfTerminals.arr[0] == nullptr) {
			std::cout << "No terminals"<<std::endl;
			return 1;
		}
		while (i < bunchOfTerminals.size && bunchOfTerminals.arr[i] != nullptr) {

			bunchOfTerminals.arr[i]->print();
			++i;
		}
		return 1;
	}
	int D_Print_Connections(terminal::bunchOfTerminals& bunchOfTerminals) {

		int i{ 0 };
		int j{ 0 };
		if (bunchOfTerminals.arr[0] == nullptr) {
			std::cout << "No terminals" << std::endl;
			return 1;
		}
		while (i < bunchOfTerminals.size && bunchOfTerminals.arr[i] != nullptr) {
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
		if (type == types_of_terminals[0])
			return NumInput(-1, 2);
		else
			return NumInput(-1, 4);
	}


	void createTerminal(terminal::bunchOfTerminals& bunchOfTerminals, std::string& type, int connections, char signal) {

		int i{ 0 };
		while (i < bunchOfTerminals.size && bunchOfTerminals.arr[i] != nullptr) {
			++i;
		}
		if (i == bunchOfTerminals.size) {

			bunchOfTerminals.arr = expansion(bunchOfTerminals);
			bunchOfTerminals.arr[i] = new terminal::Terminal(type, connections, signal, i + 1);
			++bunchOfTerminals.capacity;

		}
		else {

			bunchOfTerminals.arr[i] = new terminal::Terminal(type, connections, signal, i + 1);
			++bunchOfTerminals.capacity;
		}
	}
	void createTerminal(terminal::bunchOfTerminals& bunchOfTerminals, std::string& type) {

		int i{ 0 };
		while (i < bunchOfTerminals.size && bunchOfTerminals.arr[i] != nullptr) {
			++i;
		}
		if (i == bunchOfTerminals.size) {

			bunchOfTerminals.arr = expansion(bunchOfTerminals);
			bunchOfTerminals.arr[i] = new terminal::Terminal(type, i + 1);
			++bunchOfTerminals.capacity;
		}
		else {
			bunchOfTerminals.arr[i] = new terminal::Terminal(type, i + 1);
			++bunchOfTerminals.capacity;
		}
	}
	void createTerminal(terminal::bunchOfTerminals& bunchOfTerminals) {

		int i{ 0 };
		while (i < bunchOfTerminals.size && bunchOfTerminals.arr[i] != nullptr) {
			++i;
		}
		if (i == bunchOfTerminals.size) {

			bunchOfTerminals.arr = expansion(bunchOfTerminals);
			bunchOfTerminals.arr[i] = new terminal::Terminal();
			++bunchOfTerminals.capacity;

		}
		else {
			bunchOfTerminals.arr[i] = new terminal::Terminal();
			++bunchOfTerminals.capacity;
		}
	}


	terminal::Terminal** expansion(terminal::bunchOfTerminals& bunchOfTerminals) {

		terminal::Terminal** NewArr = new terminal::Terminal * [2 * bunchOfTerminals.size]();
		copyValues(bunchOfTerminals.arr, NewArr, bunchOfTerminals.size);
		delete[] bunchOfTerminals.arr;
		return NewArr;
	}
	void copyValues(terminal::Terminal** FirstPtr, terminal::Terminal** SecondPtr, int& size) {

		int i{ 0 };
		for ( i ; i < size; ++i) {
			*(SecondPtr + i) = *(FirstPtr + i);
		}
		size *= 2;
	}
	int Available(terminal::Terminal** pointer, int size, int* AvTer) {

		int i{ 0 };
		int j{ 0 };
		if (*pointer == nullptr) {

			return 0;
		}
		else {
			while (*(pointer + i) != nullptr && i<size) {
				if ((*(pointer + i))->getType() == "Input" && (*(pointer + i))->getConnections() == 0) {
					std::cout <<"Terminal number "<< (*(pointer + i))->getNumber()<<std::endl;
					*(AvTer + j) = (*(pointer + i))->getNumber();
					j++;
				}
				else if ((*(pointer + i))->getType() == "Output" && (*(pointer + i))->getConnections() < 3) {
					std::cout<<"Terminal number " << (*(pointer + i))->getNumber() << std::endl;
					*(AvTer + j) = (*(pointer + i))->getNumber();
					j++;
				}
				++i;
			}
			
		}
		return 1;
	}
	void ArrErase(terminal::bunchOfTerminals& bunchOfTerminals) {
		int i{ 0 };
		while (i < bunchOfTerminals.size && bunchOfTerminals.arr[i] != nullptr) {
			delete  bunchOfTerminals.arr[i];
			++i;
		}
	}
	int AvailableDis(terminal::Terminal** pointer, int size, int* arr) {

		int i{ 0 };
		int j{ 0 };
		while (*(pointer + i) && i < size) {
			if ((*(pointer + i))->isConnected()) {
				*(arr + j) = (*(pointer+i))->getNumber();
				j++;
			}
			i++;
		}
		return 1;
	}
}