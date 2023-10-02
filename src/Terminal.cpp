#include "Terminal.h"
#include "Dialog.h"
#include <string>
#include <iostream>
namespace terminal {

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
	int Terminal::getNumber() const {

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
	void Terminal::setNumber() {
			
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


	void Terminal::scan() {

		std::cout << "Enter type of terminal"<<std::endl;
		setType();
		std::cout << "Enter number of connections" << std::endl;
		setConnections();
		std::cout << "Enter type of signal" << std::endl;
		setSignal();

	}
	void Terminal::print() const {

		std::cout << "Terminal number " << number << std::endl << "Type of terminal is " << type << std::endl;
		std::cout << "Number of connections is " << connections << std::endl << "State of signal is " << signal;
		std::cout << std::endl;
		std::cout << std::endl;
	}

	void Terminal::connect(Terminal* terminal) {

		if (terminal->number == number)
			throw std::logic_error("You try to connect the same terminal");
		
		if (isFullyConnected()) 
			throw std::logic_error("First terminal can not be connected more, firstly you need to disconnect it");
		
		if (terminal->isFullyConnected())
			throw std::logic_error("First terminal can not be connected more, firstly you need to disconnect it");
		
		while (true) {
			if (type == "Input") {
				ConnectedTerminals[0] = terminal;
				++connections;
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
		
		if (terminal->number == number) {
			throw std::logic_error("You try to dissconnect the same terminal");
		}
		while (true) {
			if (type == "Input") {
				if (connections) {
					if (ConnectedTerminals[0] == terminal) {
						ConnectedTerminals[0] = nullptr;
						--connections;
						break;
					}
					else
						throw std::logic_error("This terminals is not connected");
				}
				else
					throw std::logic_error("This terminals is not connected");

			}
			else if (type == "Output") {
				if (connections) {
					int i{ 0 };
					while (i < 3 && ConnectedTerminals[i] != terminal)
						i++;
					if (i == 3)
						throw std::logic_error("This terminals is not connected");
					else {
						ConnectedTerminals[i] = nullptr;
						--connections;
						break;
					}
				}
				else
					throw std::logic_error("This terminals is not connected");
			}
			else {
				std::cout << "Type of terminal is unknown. Firstly you need to initialize this terminal" << std::endl;
				scan();
			}
		}
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
	bool Terminal::isFullyConnected() const{
		
		if (type == "Input") {
			if (ConnectedTerminals[0] != nullptr)
				return true;
			else
				return false;
		}
		else if (type == "Output") {
			int i{ 0 };
			while (i < 3 && ConnectedTerminals[i] != nullptr)
				i++;
			if (i == 3)
				return true;
			else
				return false;
		}
		else {
			return true;
		}
	}
	

}