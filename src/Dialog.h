#pragma once
namespace Dialog {

	const char* msgs[] = { "0.Quite", "1.Create terminal with type of terminal, number of connections and state of signal",
								"2.Create terminal only with type of terminal", "3.Connect two terminals", "4.Disconnect two terminals" };
	const int number_of_msgs = sizeof(msgs) / sizeof(msgs[0]);

	int dialog(const char* [], const int);


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