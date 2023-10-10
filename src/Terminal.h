#pragma once
#include <string>
namespace terminal {

	enum class Type { OUTPUT, INPUT };
	enum class Signal { OFF, ON, X };

	class Terminal{
	
	private:

		int number;
		Type type;
		int connections;
		Signal signal;
	
	public:

		Terminal();
		Terminal(Type, int, Signal, int);
		Terminal(Type, int);
		Terminal(const Terminal&);

		const std::string& getType() const;
		int getConnections() const;
		char getSignal() const;
		int getNumber() const;

		void setType(Type);
		void setConnections(int);
		void setSignal(Signal);
		void setNumber(int);

		void print() const;
		void scan();

		void connect(Terminal&);
		void disconnect(Terminal&);

		void increaseConnections();
		void decreaseConnections();
	};
}