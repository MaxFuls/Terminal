#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include "Terminal.h"
namespace Dialog {

	int dialog(const char* [], const int);
	int D_Create_Full (Terminal::Terminal**, int&);
	int D_Create(Terminal::Terminal** , int& );
	int D_Connect(Terminal::Terminal**, int&);
	int D_Disconnect(Terminal::Terminal**, int& );
	int D_Print(Terminal::Terminal**, int& );
	int D_Print_Connections(Terminal::Terminal**, int&);
	int D_Enter(Terminal::Terminal** pointer, int& size);
	std::string getType();
	int getNum(std::string&);
	char getSignal();
	void createTerminal(Terminal::Terminal**, int&, std::string&, int, char);
	Terminal::Terminal** expansion(Terminal::Terminal**, int&);
	void copyValues(Terminal::Terminal**, Terminal::Terminal**, int&);
	void createTerminal(Terminal::Terminal**, int&, std::string&);
	int Available(Terminal::Terminal**, int, int*);
	void ArrErase(Terminal::Terminal**, int);
	int AvailableDis(Terminal::Terminal**, int, int*);
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