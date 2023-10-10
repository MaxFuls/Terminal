#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include "Terminal.h"
#include "LogicElement.h"
#include "Vector.h"

namespace dialog {

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
			else if (a >= min && a <= max)
				return a;
			else {
				std::cout << "Repeat please" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}

	int dialog(const char* [], const int);

	//Terminals' dialog functions

	int createFull(vector::Vector<terminal::Terminal>&);
	int createWithType(vector::Vector<terminal::Terminal>&);
	int connect(vector::Vector<terminal::Terminal>&);
	int disconnect(vector::Vector<terminal::Terminal>&);
	int print(vector::Vector<terminal::Terminal>&);
	int enter(vector::Vector<terminal::Terminal>&);

	//Logic Elements' dialog functions

	int createWithNumber(vector::Vector<logicElement::LogicElement>&);
	int createWithArray(vector::Vector<logicElement::LogicElement> &);
	int enter(vector::Vector<logicElement::LogicElement> &);
	int getTerminal(vector::Vector<logicElement::LogicElement> &);
	int connect(vector::Vector<logicElement::LogicElement> &);
	int print(vector::Vector<logicElement::LogicElement> &);


}