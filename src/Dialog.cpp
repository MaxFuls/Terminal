#include <iostream>
#include "Dialog.h"

namespace Dialog {

	int dialog(const char* msgs[], const int number_of_msgs) {
		
		for (int i{ 0 }; i < number_of_msgs; i++) {
			
			std::puts(msgs[i]);

		}
		int alternative;
		try
		{
			alternative = NumInput<int>(0, number_of_msgs - 1);
			return alternative;
		}
		catch (const std::exception&)
		{
			throw;
		}
	}
}