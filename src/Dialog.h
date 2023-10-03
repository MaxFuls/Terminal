#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include "Terminal.h"

namespace dialog {

	int dialog(const char* [], const int);


	int D_Create_Full (terminal::bunchOfTerminals&);
	int D_Create(terminal::bunchOfTerminals&);
	int D_Connect(terminal::bunchOfTerminals&);
	int D_Disconnect(terminal::bunchOfTerminals&);
	int D_Print(terminal::bunchOfTerminals&);
	int D_Print_Connections(terminal::bunchOfTerminals&);
	int D_Enter(terminal::bunchOfTerminals&);


	std::string getType();
	int getNum(std::string&);
	char getSignal();


	void createTerminal(terminal::bunchOfTerminals&, std::string&, int, char);
	void createTerminal(terminal::bunchOfTerminals&, std::string&);
	void createTerminal(terminal::bunchOfTerminals&);


	terminal::Terminal** expansion(terminal::bunchOfTerminals&);
	void copyValues(terminal::Terminal**, terminal::Terminal**, int&);
	int Available(terminal::Terminal**, int, int*);
	void ArrErase(terminal::bunchOfTerminals& );
	int AvailableDis(terminal::Terminal**, int, int*);
	
	
	int D_Create_With_Number();
	int D_Create_With_Array();
	int D_Enter_Logic_Element();
	int D_Get_Terminal();
	int D_Connect_Logic_Elements();


	template <class T>
	T NumInput(T min, T max) {
		T a;
		while (true) {
			std::cin >> a;
			if (std::cin.eof())
				throw std::runtime_error("Error of input: EOF");
			else if (std::cin.bad())
				throw std::runtime_error(std::string("Error of input: ") + strerror(errno));
			else if (std::cin.fail()) {
				std::cout << "Repeat please" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else if (a > min && a < max)
				return a;
			else {
				std::cout << "Repeat please" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

}