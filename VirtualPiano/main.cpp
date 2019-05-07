#include <iostream>
#include <string>

#include "MenuInterface.h"
#include "VirtualPianoParser.h"
#include "MidiNumbersStruct.h"
#include "Formatter.h"

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
	try {
		parser.parse_mapping_file(midi_formatter::note_str_to_midi_number);
	}
	catch (IllegalMapingFileFormat & ex) {
		std::cerr << ex.what();
		std::cout << "Fatal error occured, terminating\n";
		system("pause");
		return 0;
	}

	Composition<2U> composition{Duration(0, 1)};

	while (MenuInterface::is_program_running()) {
		try {
			MenuInterface::print_menu();
			MenuInterface::read_menu_option();
			MenuInterface::execute_option(composition);
		}
		catch (MenuInterface::InvalidMenuOption& ex) {
			std::cerr << ex.what();
		}

	}

	return 0;
}
