#include "Terminal.h"
#include "Dialog.h"
#include <string>
#include <iostream>
#include <format>
namespace terminal {


	Terminal::Terminal() : number(0), type(Type::INPUT), connections(0), signal(Signal::X) {	}																	
	Terminal::Terminal(Type type, int connections, Signal signal, int number) : number(number), type(type) {
		
		if (type == Type::INPUT) {
			if (connections == 1) {
				this->connections = connections;
				this->signal = signal;
			}
			else if(connections == 0) {
				this->connections = 0;
				this->signal = Signal::X;
			}
			else {
				this->connections = 0;
				this->signal = Signal::X;
				throw std::invalid_argument("Incorrect number of connections for this type of terminal");
			}
		
		}
		else {
			if (connections >= 0 && connections <= 3) {
				this->connections = connections;
				this->signal = signal;
			}
			else {
				this->connections = 0;
				this->signal = Signal::X;
				throw std::invalid_argument("Incorrect number of connections for this type of terminal");
			}
		}
	}
	Terminal::Terminal(Type type, int number) : number(number), type(type), connections(0), signal(Signal::X) {  }
	Terminal::Terminal(const Terminal& terminal) {

		number = terminal.number;
		type = terminal.type;
		connections = terminal.connections;
		signal = terminal.signal;
	}

	void Terminal::increaseConnections() {
		if (type == Type::INPUT) {
			if (!connections)
				++connections;
			else
				throw std::logic_error("Max number of connections for input terminal is 1");
		}
		else {
			if (connections < 3)
				++connections;
			else
				throw std::logic_error("Max number of connections for input terminal is 3");
		}

	}
	void Terminal::decreaseConnections(){
		if (type == Type::INPUT) {

			if (connections)
				--connections;
			else
				throw std::logic_error("Number of connections is already 0");
		}
		else {

			if (connections)
				--connections;
			else
				throw std::logic_error("Number of connections is already 0");
		}
	}

	const std::string& Terminal::getType() const {

		if (type == Type::INPUT)
			return "Input";
		else
			return "Output";
	}
	int  Terminal::getConnections() const {

		return connections;
	}
	char  Terminal::getSignal() const {
		if (signal == Signal::ON)
			return '1';
		else if (signal == Signal::OFF)
			return '0';
		else
			return 'X';
	}
	int Terminal::getNumber() const{

		return number;
	}

	void Terminal::setType(Type type) {

		this->type = type;
	}
	void Terminal::setConnections(int connections) {

		if (type == Type::INPUT) {
			if (connections < 0 || connections>1) {
				throw std::invalid_argument("Number of connections for input terminal is 0 or 1");
			}
			else if (connections == 0) {
				this->connections = connections;
				signal = Signal::X;
			}
			else
				this->connections = connections;
		}
		else {
			if (connections < 0 || connections>3) {
				throw std::invalid_argument("Number of connections for output terminal is 0, 1, 2 or 3");
			}
			else
				this->connections = connections;
		}
		
	}
	void Terminal::setSignal(Signal signal) {

		if (type == Type::INPUT) {
			if (!connections && signal != Signal::X)
				throw std::invalid_argument("state of signal for input terminal without connections is X");
			else
				this->signal = signal;
		}
		else
			this->signal = signal;
	}
	void Terminal::setNumber(int number) {
			
		if (number > 0) 
			this->number = number;
		else
			throw std::invalid_argument("Number need be positive");
			
	}

	void Terminal::scan() {

		std::cout << std::format("{}\n", "Enter number of terminal");
		setNumber(dialog::NumInput<int>(0, std::numeric_limits<int>::max()));
		std::cout << std::format("{}\n{}\n{}\n", "Enter type of terminal", "0.Output", "1.Input");
		setType(static_cast<Type>(dialog::NumInput<int>(0,1)));
		std::cout << std::format("{}\n", "Enter number of connections: for input 0 or 1, for output: 0, 1, 2 or 3");
		setConnections(dialog::NumInput<int>(0, 3));
		std::cout << std::format("{}\n{}\n{}\n","Enter state of signal","0.Off","1.On","2.X");
		setSignal(static_cast<Signal>(dialog::NumInput(0, 2)));

	}
	void Terminal::print() const {

		std::string type;
		char signal;
		if (this->signal == Signal::ON)
			signal = '1';
		else if (this->signal == Signal::OFF)
			signal = '0';
		else
			signal = 'X';
		if (this->type == Type::INPUT)
			type = "Input";
		else
			type = "Output";
		std::cout << std::format("{} {}\n{} {}\n{} {}\n{} {}\n\n","Terminal number is", number,"Type of terminal is", type, "Number of connections is",
									connections, "State of signal is", signal);			
	}

	void Terminal::connect(Terminal& terminal) {

		if (type != Type::OUTPUT || terminal.type != Type::INPUT)
			throw std::invalid_argument("Type of the first terminal need to output, the second is input");
		if (connections == 3 || terminal.connections == 1)
			throw std::invalid_argument("Incorrect number of connections for connect");
		++connections;
		++terminal.connections;
	}
	void Terminal::disconnect(Terminal& terminal) {
		
		if (type != Type::OUTPUT || terminal.type != Type::INPUT)
			throw std::invalid_argument("Type of the first terminal need to output, the second is input");
		if (!connections || !terminal.connections)
			throw std::invalid_argument("Incorrect number of connections for disconnect");
		--connections;
		--terminal.connections;
	}
	
}