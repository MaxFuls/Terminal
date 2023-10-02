#pragma once
#include <string>
namespace Terminal {


	class Terminal{

	private:

		int number;
		std::string type;
		int connections;
		char signal;
		Terminal* ConnectedTerminals[3];

	public:

		Terminal();
		Terminal(std::string&, int, char, int);
		Terminal(std::string&, int);

		std::string getType() const;
		int getConnections() const;
		char getSignal() const;
		int getNumber() const;
		Terminal** getConnectedTerminals();

		void setType(const std::string&);
		void setConnections(const int&);
		void setSignal(const char&);
		void setNumber(const int&);
		int setConnectedTerminals(Terminal*);
		int resetConnectedTerminals(Terminal*);
		
		bool isConnected() const;
		void print() const;
		void scan();
		void printConnections() const;
		void IncreaseConnections();
		void DecreaseConnections();
	};
}