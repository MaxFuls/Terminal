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
		Terminal(std::string&, int, char);
		Terminal(std::string&);

		std::string getType();
		int getConnections();
		char getSignal();

		void setType(const std::string&);
		void setConnections(const int&);
		void setSignal(const char&);
		void setNumber(const int&);
	};
}