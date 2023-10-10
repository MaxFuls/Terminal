#pragma once
#include "Terminal.h"
#include "Dialog.h"
#include "Vector.h"

namespace logicElement {

	struct Definitions {

		terminal::Type type;
		int connections;
		terminal::Signal signal;

		void scan();
	};
	struct DefStruct {

		int	length;
		int numInput = 0;
		int numOutput = 0;
		Definitions* definitions;

		DefStruct(int);
		~DefStruct();
		void scan();

	};
	class LogicElement {

	private:

		int number;
		int numInput;
		vector::Vector<terminal::Terminal> inputTerminals;
		int numOutput;
		vector::Vector<terminal::Terminal> outputTerminals;

	public:

		LogicElement();
		LogicElement(int, int, int);
		LogicElement(const DefStruct&, int);
		LogicElement(const LogicElement&);
		LogicElement& operator=(const LogicElement&);

		int getNumber() const;
		int getNumberOfInput() const;
		int getNumberOfOutput() const;

		void setNumber(int);
		void setNumberOfInput(int);
		void setNumberOfOutput(int);

		void print();
		void scan();
		void addTerminal(const terminal::Terminal&);
		void connect(LogicElement&);
		const terminal::Terminal& getTerminal(int);

	};
}
