#include <iostream>
#include <string>
#include "Dialog.h"
#include "Terminal.h"
//setType
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
			return 0;
		}
	}
	int D_Create(Terminal::Terminal** pointer, int& size) {
		try
		{
			std::cout << "Enter type of terminal" << std::endl;
			std::string type = getType();
			createTerminal(pointer, size, type);
			std::cout << size << std::endl;
			return 1;
		}
		catch (const std::exception&)
		{
			return 0;
		}
		
	}
	int D_Connect(Terminal::Terminal** pointer, int& size) {

		std::cout << "Available terminals to connect" << std::endl;
		int* AvailableTerminals = new int[size]();
		int i{ 0 };
		Available(pointer, size, AvailableTerminals);
		int firstTerminal, secondTerminal;
		if ((!*(AvailableTerminals))) {

			std::cout << "No terminals to connect" << std::endl;
			return 1;
		}
		else if (*(AvailableTerminals + 1) == 0) {
			std::cout << "There are only one terminal" << std::endl;
			return 1;
		}
		else {
			std::cout << "Choose numbers of terminals to connect" << std::endl;
			std::cout << "Choose the first one" << std::endl;
			while (true) {
				firstTerminal = NumInput<int>(-1, size+1);
				while (firstTerminal != *(AvailableTerminals + i) && *(AvailableTerminals + i) != 0 && i < size) {
					i++;
				}
				if (i != size && *(AvailableTerminals + i) != 0) {
					i = 0;
					break;
				}
				std::cout << "Incorrect number of terminal" << std::endl;
				i = 0;
			}
			std::cout << "Choose the second one" << std::endl;
			while (true) {
				secondTerminal = NumInput<int>(-1, size+1);
				while (secondTerminal != *(AvailableTerminals + i) && *(AvailableTerminals + i) != 0 && i < size) {
					i++;
				}
				if (i != size && *(AvailableTerminals + i) != 0 && secondTerminal!=firstTerminal) {
					i = 0;
					break;
				}
				std::cout << "Incorrect number of terminal" << std::endl;
				i = 0;

			}
			if ((*(pointer + firstTerminal - 1))->setConnectedTerminals(*(pointer + secondTerminal - 1)))
					(*(pointer + secondTerminal - 1))->setConnectedTerminals(*(pointer + firstTerminal - 1));
			else
				std::cout << "This terminals are already connected"<<std::endl;


		}
		delete[] AvailableTerminals;
		return 1;
	}
	int D_Disconnect(Terminal::Terminal** pointer, int& size){
		
		int i{ 0 };
		if (*pointer == nullptr) {
			std::cout << "There are no terminals to disconnect" << std::endl;
			return 1;
		}
		else {
			int* Available = new int[size]();
			int firstTerminal, secondTerminal;
			std::cout << "Chose terminals to disconnect" << std::endl;
			while (i < size && *(pointer + i) != nullptr) {
				(*(pointer + i))->printConnections();
				i++;
			}
			AvailableDis(pointer, size, Available);
			if (*Available || *(Available + 1)) {
				std::cout << "There are no terminals to disconnect" << std::endl;
				return 1;
			}
			std::cout << "Choose the first terminal" << std::endl;
			while (true) {
				firstTerminal = NumInput<int>(-1, size + 1);
				while (firstTerminal != *(Available + i) && *(Available + i) != 0 && i < size) {
					i++;
				}
				if (i != size && *(Available + i) != 0) {
					i = 0;
					break;
				}
				std::cout << "Incorrect number of terminal" << std::endl;
				i = 0;
			}
			while (true) {
				secondTerminal = NumInput<int>(-1, size + 1);
				while (secondTerminal != *(Available + i) && *(Available + i) != 0 && i < size) {
					i++;
				}
				if (i != size && *(Available + i) != 0 && secondTerminal != firstTerminal) {
					i = 0;
					break;
				}
				std::cout << "Incorrect number of terminal" << std::endl;
				i = 0;
			}
			if ((*(pointer + firstTerminal - 1))->resetConnectedTerminals(*(pointer + secondTerminal - 1)))
				(*(pointer + secondTerminal - 1))->resetConnectedTerminals(*(pointer + firstTerminal - 1));
			else
				std::cout << "This terminals are already disconnected" << std::endl;
			delete[] Available;
			return 1;
		}
		}
	int D_Print(Terminal::Terminal** pointer, int& size) {

		int i{ 0 };
		if (*pointer == nullptr) {
			std::cout << "No terminals"<<std::endl;
			return 1;
		}
		while (*(pointer + i) != nullptr && i < size) {

			(*(pointer + i))->print();
			++i;
		}
		return 1;
	}
	int D_Print_Connections(Terminal::Terminal** pointer, int& size) {

		int i{ 0 };
		int j{ 0 };
		if (*pointer == nullptr) {
			std::cout << "No terminals" << std::endl;
			return 1;
		}
		while (*(pointer + i) != nullptr && i < size) {
			(*(pointer + i))->printConnections();
			i++;
		}
		return 1;

	}
	int D_Enter(Terminal::Terminal** pointer, int& size) {


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
	void createTerminal(Terminal::Terminal** pointer, int& size, std::string& type, int connections, char signal) {

		int i{ 0 };
		while (*(pointer + i) != nullptr && i < size) {
			i++;
		}
		if (i == size) {

			pointer = expansion(pointer, size);
			*(pointer + i) = new Terminal::Terminal(type, connections, signal, i+1);

		}
		else {

			*(pointer + i) = new Terminal::Terminal(type, connections, signal, i+1);
		}
	}
	void createTerminal(Terminal::Terminal** pointer, int& size, std::string& type) {

		int i{ 0 };
		while (*(pointer + i) != nullptr && i < size) {
			i++;
		}
		if (i == size) {

			pointer = expansion(pointer, size);
			*(pointer + i) = new Terminal::Terminal(type, i+1);

		}
		else {
			*(pointer + i) = new Terminal::Terminal(type, i+1);
		}
	}
	Terminal::Terminal** expansion(Terminal::Terminal** pointer, int& size) {

		try
		{
			Terminal::Terminal** NewArr = new Terminal::Terminal * [2 * size]();
			copyValues(pointer, NewArr, size);
			delete[] pointer;
			return NewArr;
		}
		catch (const std::exception&)
		{
			throw;
			return pointer;
		}
	}
	void copyValues(Terminal::Terminal** FirstPtr, Terminal::Terminal** SecondPtr, int& size) {

		int i{ 0 };
		for ( i ; i < size; ++i) {
			*(SecondPtr + i) = *(FirstPtr + i);
		}
		size *= 2;
	}
	int Available(Terminal::Terminal** pointer, int size, int* AvTer) {

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
	void ArrErase(Terminal::Terminal** pointer, int size) {
		int i{ 0 };
		while (*(pointer + i) != nullptr && i<size) {
			delete  *(pointer + i);
			i++;
		}
	}
	int AvailableDis(Terminal::Terminal** pointer, int size, int* arr) {

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