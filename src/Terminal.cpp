#include "Terminal.h"
#include <string>
namespace Terminal {
	std::string Terminal::getType() {

		return type;
	}

	int  Terminal::getConnections() {

		return connections;
	}

	char  Terminal::getSignal() {

		return signal;
	}
	void  Terminal::setType(const std::string& type) {

		this->type = type;
	}
	void  Terminal::setConnections(const int& connections) {

		this->connections = connections;
	}
	void  Terminal::setSignal(const char& signal) {

		this->signal = signal;
	}
	void Terminal::setNumber(const int& number) {

		this->number = number;
	}
	Terminal::Terminal() {
		 
		this->type = "unknown";
		this->connections = 0;
		this->signal = 'X';
		this->ConnectedTerminals[0] = nullptr;
		this->ConnectedTerminals[1] = nullptr;
		this->ConnectedTerminals[2] = nullptr;
	}
	Terminal::Terminal(std::string& type, int connections, char signal) {

		this->type = type;
		this->connections = connections;
		this->signal = signal;
		this->ConnectedTerminals[0] = nullptr;
		this->ConnectedTerminals[1] = nullptr;
		this->ConnectedTerminals[2] = nullptr;
	}
	Terminal::Terminal(std::string& type) {

		this->type = type;
		this->connections = 0;
		this->signal = 'X';
		this->ConnectedTerminals[0] = nullptr;
		this->ConnectedTerminals[1] = nullptr;
		this->ConnectedTerminals[2] = nullptr;
	}
}