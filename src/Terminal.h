#pragma once
#include <string>
namespace terminal {

	struct bunchOfTerminals {

		Terminal** arr = new Terminal * [5]();
		int size{ 5 };
		int capacity{ 0 };
	};


	class Terminal{

	private:

		int number;
		std::string type;
		int connections;
		char signal;
		Terminal* ConnectedTerminals[3];

	protected:

		int setConnectedTerminals(Terminal*);
		int reSetConnectedTerminals(Terminal*);

	public:

		Terminal();
		Terminal(std::string&, int, char, int);
		Terminal(std::string&, int);
		Terminal(std::string&);


		std::string getType() const;
		int getConnections() const;
		char getSignal() const;
		int getNumber() const;


		void setType();
		void setConnections();
		void setSignal();
		void setNumber();


		void print() const;
		void scan();

		void connect(Terminal*);
		void disconnect(Terminal*);

		bool isFullyConnected() const;
		void printConnections() const;
		void IncreaseConnections();
		void DecreaseConnections();
	};


}