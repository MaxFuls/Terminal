#pragma once
#include <string>
namespace Terminal {

	class Terminal{

	private:

		std::string type;
		int connections;
		char signal;

	public:

		std::string getType();
		int getConnections();
		char getSignal();

		void setType();
		void setConnections();
		void setSignal();
	};

	Terminal* TerminalArr[] = {nullptr, nullptr, nullptr, nullptr, nullptr };
	Terminal** expansion(Terminal**);
}