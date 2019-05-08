#include "MenuInterface.h"
#include "MidiFormatter.h"
#include "MxmlFormatter.h"
#include "VirtualPianoParser.h"

void MenuInterface::print_menu() {
	std::cout 
		<< LOAD_COMPOSITION << ". Load composition\n"
		<< EXPORT_MIDI << ". Export midi\n"
		<< EXPORT_XML << ". Export xml\n"
		<< EXPORT_BMP << ". Export bmp\n"
		<< ITERATE_THROUGH_COMPOSITION << ". Iterate through composition\n"
		<< PRINT_COMPOSITION << ". Print composition\n"
		<< EXIT << ". Exit program\n"
		<< "Choose menu option (index of option): ";
}

void MenuInterface::read_menu_option(std::istream& is) {
	int temp;
	is >> temp;
	if (temp < EXIT || temp >= NUM_OF_OPTIONS) {
		throw InvalidMenuOption();
	}

	menu_option_ = static_cast<MenuOptions>(temp);

}

void MenuInterface::execute_option(Composition<2U> & composition, VirtualPianoParser & parser, std::istream& is) {
	MidiFormatter<2U> midi_formatter;
	MxmlFormatter<2U> mxml_formatter;
	std::string file_path;
	char yes_no;
	auto measure_index = 0U;
	switch (menu_option_) {
	case EXIT:
		if (!has_exported_) {
			std::cout << "You have not exported any files\n"
				<< "Are you sure you want to quit (y/n)?";
			is >> yes_no;
			if (yes_no == 'n') {
				break;
			}

		}

		is_program_running_ = false;
		break;
	case LOAD_COMPOSITION:
		std::cout << "Enter file path:\n";
		is >> file_path;
		parser.load_composition(file_path, composition);
		break;
	case EXPORT_MIDI:
		std::cout << "Enter out file path:\n";
		is >> file_path;
		midi_formatter.generate_output_file(file_path, composition);
		has_exported_ = true;
		break;
	case EXPORT_XML:
		std::cout << "Enter out file path:\n";
		is >> file_path;
		mxml_formatter.generate_output_file(file_path, composition);
		has_exported_ = true;
		break;
	case EXPORT_BMP:
		std::cout << "Enter out file path:\n";
		is >> file_path;
		std::cout << "NOT YET IMPLEMENTED :(\n";	// TODO: implement
		has_exported_ = true;
		break;
	case ITERATE_THROUGH_COMPOSITION:
		std::cout << "NOT YET IMPLEMENTED :(\n";	// TODO: implement
		break;
	case PRINT_COMPOSITION:
		while (true) {
			try {
				for (auto & part_it : composition) {
					std::cout << part_it.at(measure_index) << "\n";
				}

				measure_index++;
				std::cout << "\n";
			}
			catch(...) {
				break;
			}
		}

		break;
	default: 
		break;

	}

	std::cout << "\n";
}

bool MenuInterface::is_program_running_ = true;
MenuInterface::MenuOptions MenuInterface::menu_option_ = EXIT;
bool MenuInterface::has_exported_ = false;
