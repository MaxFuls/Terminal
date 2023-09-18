#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include "Terminal.h"
namespace Dialog {

	int dialog(const char* [], const int);
	int D_Create_Full (Terminal::Terminal** pointer, int& size);
	int D_Create(Terminal::Terminal** pointer, int& size);
	int D_Connect(Terminal::Terminal** pointer, int& size);
	int D_Disconnect(Terminal::Terminal** pointer, int& size);
	int D_Print(Terminal::Terminal** pointer, int& size);
	std::string getType();
	int getNum(std::string&);
	char getSignal();
	void createTerminal(Terminal::Terminal**, int&, std::string&, int, char);
	Terminal::Terminal** expansion(Terminal::Terminal**, int&);
	Terminal::Terminal** copy(Terminal::Terminal**, Terminal::Terminal**, int&);
	void createTerminal(Terminal::Terminal**, int&, std::string&);

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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

}