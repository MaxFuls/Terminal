#include "Terminal.h"
#include <string>
#include <iostream>
namespace Terminal {


	std::string Terminal::getType() const {

		return type;
	}
	int  Terminal::getConnections() const {

		return connections;
	}
	char  Terminal::getSignal() const {

		return signal;
	}
	int Terminal::getNumber() const {

		return number;
	}
	Terminal** Terminal::getConnectedTerminals() {

		return ConnectedTerminals;
	}


	void  Terminal::setType(const std::string& type) {

		if (type == "Input" || type == "Output")
			this->type = type;
		else
			std::cout << "Incorrect type" << std::endl;
	}
	void  Terminal::setConnections(const int& connections) {

		if (type == "Input") {
			if (connections <= 1 && connections >= 0) {
				this->connections = connections;
			}
			else
				std::cout << "Incorrect number of connections" << std::endl;
		}
		else if (type == "Output") {
			if (connections <= 3 && connections >= 0) {
				this->connections = connections;
			}
			else
				std::cout << "Incorrect number of connections" << std::endl;
		}
		else
			std::cout << "Type of terminal is unknow, firstly enter type of terminal" << std::endl;
		}
	void  Terminal::setSignal(const char& signal) {

			if (type == "Input" && connections == 0) {
				if (signal == 'X') {
					this->signal = signal;
				}
				else
					std::cout << "Input terminal without connections can have only X signal" << std::endl;
			}
			else if (type == "Input" || type == "Output") {
				if (signal == '0' || signal == '1' || signal == 'X') {
					this->signal = signal;
				}
			}
			else {
				std::cout << "Type of terminal is unknow, firstly enter type of terminal" << std::endl;
				std::string s;
				std::cin >> s;
				setType(s);
			}
	}
	void Terminal::setNumber(const int& number) {
			
		if (number > 0) 
			this->number = number;
		else
			std::cout << "Number need be positive" << std::endl;
			
	}
	int Terminal::setConnectedTerminals(Terminal* pointer) {
		
		int i{ 0 };
		while (*(ConnectedTerminals + i) != nullptr && i<3) {
				
			if (*(ConnectedTerminals + i) == pointer) {
					
				return 0;
			}
			else {
				i++;
			}
		}
		*(ConnectedTerminals + i) = pointer;
		IncreaseConnections();
		return 1;

	}
	int Terminal::resetConnectedTerminals(Terminal* pointer) {
		
		int i{ 0 };
		while (ConnectedTerminals[i] != pointer && i<3) {
			i++;
		}
		if (i == 3)
			return 0;
		else {
			ConnectedTerminals[i] = nullptr;
			DecreaseConnections();
			return 1;
		}
	}
	void scan(Terminal* terminal) {

		std::cout << "Enter type of terminal"<<std::endl;
		//setType()

	}
	
	void Terminal::IncreaseConnections() {
		if (type == "Input") {
			if (connections == 0)
				++connections;
			else
				std::cout << "Max number of connections for input terminal is 1" << std::endl;
		}
		else if (type == "Output") {
			if (connections < 3)
				++connections;
			else
				std::cout << "Max number of connections for input terminal is 3";
		}
		else
			std::cout << "Type of terminal is unknow, firstly enter type of terminal" << std::endl;

	}
	void Terminal::DecreaseConnections() {
		if (type == "Input") {

			if (connections >0)
				--connections;
			else
				std::cout << "Number of connections is already 0" << std::endl;
		}
		else if (type == "Output") {

			if (connections >0)
				--connections;
			else
				std::cout << "Number of connections is already 0";
		}
		else
			std::cout << "Type of terminal is unknow, firstly enter type of terminal" << std::endl;
	}
	void Terminal::print() const {

		std::cout << "Terminal number " << number << std::endl << "Type of terminal is " << type << std::endl;
		std::cout << "Number of connections is " <<connections << std::endl << "State of signal is " <<signal;
		std::cout << std::endl;
		std::cout << std::endl;
	}
	void Terminal::printConnections() const{

		int i{ 0 };
		if (connections) {
			std::cout << "Terminal " << number << " is connected with terminals ";
			while (i < 3 && ConnectedTerminals[i]) {
				std::cout << ConnectedTerminals[i]->getNumber() << " ";
				i++;
			}
			std::cout << std::endl;
		}
		else {
			std::cout << "Terminal " << number << " is not connected" << std::endl;
		}
	}
	bool Terminal::isConnected() const{
		
		if (ConnectedTerminals[0] != nullptr)
			return true;
		else
			return false;
	}
	
	
	Terminal::Terminal() {
		 
		number = 0;
		type = "unknown";
		connections = 0;
		signal = 'X';
		ConnectedTerminals[0] = nullptr;
		ConnectedTerminals[1] = nullptr;
		ConnectedTerminals[2] = nullptr;
	}
	Terminal::Terminal(std::string& type, int connections, char signal, int number) {

		this->number = number;
		this->type = type;
		this->connections = connections;
		this->signal = signal;
		ConnectedTerminals[0] = nullptr;
		ConnectedTerminals[1] = nullptr;
		ConnectedTerminals[2] = nullptr;
	}
	Terminal::Terminal(std::string& type, int number) {

		this->number = number;
		this->type = type;
		connections = 0;
		signal = 'X';
		ConnectedTerminals[0] = nullptr;
		ConnectedTerminals[1] = nullptr;
		ConnectedTerminals[2] = nullptr;
	}

}