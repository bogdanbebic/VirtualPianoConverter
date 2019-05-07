#include <iostream>
#include <string>

#include "MenuInterface.h"

#include "VirtualPianoParser.h"

int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	std::string mapping_file_path;
	if (argc < 2) {
		std::cout << "Please enter file_path - file which contains key to note and midi number mapping:\n";
		std::getline(std::cin, mapping_file_path);
	}
	else {
		mapping_file_path = argv[1];
	}

	VirtualPianoParser parser{ mapping_file_path };

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
