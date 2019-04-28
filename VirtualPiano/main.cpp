#include <iostream>
#include <string>

#include "MenuInterface.h"

#include "VirtualPianoParser.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	if (argc < 2) {
		std::cout << "Error: invalid usage of program.\n"
			<< "Usage: program.exe file_path\n"
			<< "param file_path - file which contains key to note and midi number mapping\n";

		return 0;
	}

	VirtualPianoParser parser{ argv[1] };

	while (MenuInterface::is_program_running()) {
		try {
			MenuInterface::print_menu();
			MenuInterface::read_menu_option();
			MenuInterface::execute_option();
		}
		catch (MenuInterface::InvalidMenuOption& ex) {
			std::cerr << ex.what();
		}

	}

	return 0;
}
