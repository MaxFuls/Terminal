#include "Terminal.h"
#include "Dialog.h"
#include <string>
#include <iostream>
#include <format>
namespace terminal {

	bunchOfTerminals::~bunchOfTerminals() {

		if (capacity != 0) {
			for (int i{ 0 }; i < capacity; ++i)
				delete arr[i];
		}
		delete[] arr;
	}

	Terminal::Terminal() {

		number = 0;
		type = "unknown";
		connections = 0;
		signal = 'X';
		//std::fill
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
	Terminal::Terminal(std::string& type) {

		number = 0;
		this->type = type;
		connections = 0;
		signal = 'X';
		ConnectedTerminals[0] = nullptr;
		ConnectedTerminals[1] = nullptr;
		ConnectedTerminals[2] = nullptr;
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
	void Terminal::DecreaseConnections(){
		if (type == "Input") {

			if (connections > 0)
				--connections;
			else
				std::cout << "Number of connections is already 0" << std::endl;
		}
		else if (type == "Output") {

			if (connections > 0)
				--connections;
			else
				std::cout << "Number of connections is already 0";
		}
		else
			std::cout << "Type of terminal is unknow, firstly enter type of terminal" << std::endl;
	}

	std::string Terminal::getType() const {

		return type;
	}
	int  Terminal::getConnections() const {

		return connections;
	}
	char  Terminal::getSignal() const {

		return signal;
	}
	int Terminal::getNumber() const{

		return number;
	}


	void Terminal::setType() {

		int type;
		std::cout << "0.Input" << std::endl << "1.Output" << std::endl;
		type = dialog::NumInput<int>(-1, 2);
		if (type)
			this->type = "Output";
		else
			this->type = "Input";
	}
	void Terminal::setConnections() {

		int connections;
		while (true) {
			if (type == "Input") {

				std::cout << "For input terminal max number of connections is 1" << std::endl;
				connections = dialog::NumInput<int>(-1, 2);
				this->connections = connections;
				break;
			}
			else if (type == "Output") {

				std::cout << "For output terminal max number of connections is 3" << std::endl;
				connections = dialog::NumInput<int>(-1, 4);
				this->connections = connections;
				break;
			}
			else {
				std::cout << "Type of terminal is unknow, firstly enter type of terminal" << std::endl;
				setType();
			}
		}
	}
	void Terminal::setSignal() {

		int signal;
		while (true) {
			if (type == "Input" && connections == 0) {

					std::cout << "Input terminal without connections can have only X signal" << std::endl;
					this->signal = 'X';
					break;
			}
			else if (type == "Input" || type == "Output") {

				std::cout << "0.Type of signal is 0" << std::endl << "1.Type of signal is 1" << std::endl << "2.Type of signal is X"<<std::endl;
				signal = dialog::NumInput<int>(-1, 4);
				if (!signal)
					this->signal = '0';
				else if (signal == 1)
					this->signal = '1';
				else
					this->signal = 'X';
				break;
			}
			else {
				std::cout << "Type of terminal is unknow, firstly enter type of terminal" << std::endl;
				setType();
			}
		}
	}
	void Terminal::setNumber(int number) {
			
		if (number > 0) 
			this->number = number;
		else
			std::cout << "Number need be positive" << std::endl;
			
	}


	int Terminal::setConnectedTerminals(Terminal* pointer) {
		
		int i{ 0 };
		while (i < 3  && ConnectedTerminals[i] != nullptr) {
			++i;
		}
		ConnectedTerminals[i] = pointer;
		++connections;
		return 1;

	}
	int Terminal::reSetConnectedTerminals(Terminal* pointer) {

		int i{ 0 };
		while (i < 3 && ConnectedTerminals[i] != pointer) {
			i++;
		}
		ConnectedTerminals[i] = nullptr;
		--connections;
		return 1;
	}


	void Terminal::scan() {

		std::cout << "Enter type of terminal"<<std::endl;
		setType();
		std::cout << "Enter number of connections" << std::endl;
		setConnections();
		std::cout << "Enter type of signal" << std::endl;
		setSignal();

	}
	void Terminal::print() const {

		std::string s1 = "Terminal number";
		std::string s2 = "Type of terminal is";
		std::string s3 = "Number of connections is";
		std::string s4 = "State of signal is";
		std::string s5 = std::format("{} {}\n{} {}\n{} {}\n{} {}\n\n", s1, number, s2, type, s3, connections, s4, signal);
		std::cout << s5;
	}

	void Terminal::connect(Terminal* terminal) {

		if (terminal->number == number)
			throw std::logic_error("You try to connect the same terminal");
		if (type=="Input")
			throw std::logic_error("The first terminal need to be output");
		if (terminal->type == "Output")
			throw std::logic_error("The second terminal need to be input");
		if (isFullyConnected())
			throw std::logic_error("The first terminal can not be connected more, firstly you need to disconnect it");
		if (terminal->isFullyConnected())
			throw std::logic_error("The second terminal can not be connected more, firstly you need to disconnect it");
		
		while (true) {
			if (type == "Input") {
				
				std::cout << "First terminal need to be output" << std::endl;
				break;
			}
			else if (type == "Output") {
				int i{ 0 };
				while (ConnectedTerminals[i] != nullptr) {
					if (ConnectedTerminals[i] == terminal)
						throw std::logic_error("This terminals are already connected");
					++i;
				}
				ConnectedTerminals[i] = terminal;
				terminal->setConnectedTerminals(this);
				++connections;
				break;
			}
			else {
				std::cout << "Type of terminal is unknown. Firstly you need to initialize this terminal" << std::endl;
				scan();
			}
		}
	}
	void Terminal::disconnect(Terminal* terminal) {

		if (terminal->number == number)
			throw std::logic_error("You try to disconnect the same terminal");
		if (type == "Input")
			throw std::logic_error("The first terminal need to be output");
		if (!connections)
			throw std::logic_error("The first terminal is not connected at all");
		if (!terminal->connections)
			throw std::logic_error("The second terminal is not connected at all");
		int i{ 0 };
		while (i < 3 && ConnectedTerminals[i] != terminal)
			++i;
		if (i == 3)
			throw std::logic_error("This terminals are not connected");
		else {
			ConnectedTerminals[i] = nullptr;
			terminal->reSetConnectedTerminals(this);
			--connections;
		}
	}
	
	
	void Terminal::printConnections() const{

		int i{ 0 };
		if (ConnectedTerminals[0]!=nullptr) {
			std::cout << "Terminal " << number << " is connected with terminals ";
			while (i < 3 && ConnectedTerminals[i]!=nullptr) {
				std::cout << ConnectedTerminals[i]->getNumber() << " ";
				++i;
			}
			std::cout << std::endl;
		}
		else {
			std::cout << "Terminal " << number << " is not connected" << std::endl;
		}
	}
	bool Terminal::isFullyConnected() const{
		
		if (type == "Input") {
			if (connections==1)
				return true;
			else
				return false;
		}
		else if (type == "Output") {
			if (connections == 3)
				return true;
			else
				return false;
		}
		else {
			return true;
		}
	}
	
}