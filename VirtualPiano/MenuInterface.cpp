#include "MenuInterface.h"

#include "MidiFormatter.h"
#include "MxmlFormatter.h"
#include "VirtualPianoParser.h"

#include <string>
#include <memory>

void MenuInterface::print_menu() {
	std::cout 
		<< LOAD_COMPOSITION << ". Load composition\n"
		<< EXPORT_MIDI << ". Export midi\n"
		<< EXPORT_XML << ". Export xml\n"
		<< EXPORT_BMP << ". Export bmp\n"
		<< ITERATE_THROUGH_COMPOSITION << ". Iterate through composition\n"
		<< PRINT_COMPOSITION << ". Print composition\n"
		<< SHIFT_OCTAVE << ". Shift octave\n"
		<< CHANGE_MEASURE_DURATION << ". Change measure duration\n"
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
	static std::string in_file_path;
	std::string file_path;
	char yes_no;
	int octave_transposition_interval;
	unsigned numerator, denominator;
	auto measure_index = 0U;
	static auto is_loaded_composition = false;
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
		is >> in_file_path;
		parser.load_composition(in_file_path, composition);
		is_loaded_composition = true;
		break;
	case EXPORT_MIDI:
		if (!is_loaded_composition) {
			std::cout << "No composition loaded\n";
			break;
		}

		std::cout << "Enter out file path:\n";
		is >> file_path;
		midi_formatter.generate_output_file(file_path, composition);
		has_exported_ = true;
		break;
	case EXPORT_XML:
		if (!is_loaded_composition) {
			std::cout << "No composition loaded\n";
			break;
		}

		std::cout << "Enter out file path:\n";
		is >> file_path;
		mxml_formatter.generate_output_file(file_path, composition);
		has_exported_ = true;
		break;
	case EXPORT_BMP:
		if (!is_loaded_composition) {
			std::cout << "No composition loaded\n";
			break;
		}

		std::cout << "Enter out file path:\n";
		is >> file_path;
		std::cout << "NOT YET IMPLEMENTED :(\n";	// TODO: implement bmp exporting
		has_exported_ = true;
		break;
	case ITERATE_THROUGH_COMPOSITION:
		if (!is_loaded_composition) {
			std::cout << "No composition loaded\n";
			break;
		}

		iterate_through_composition(composition, is);
		break;
	case PRINT_COMPOSITION:
		if (!is_loaded_composition) {
			std::cout << "No composition loaded\n";
			break;
		}

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
	case SHIFT_OCTAVE:
		if (!is_loaded_composition) {
			std::cout << "No composition loaded\n";
			break;
		}

		std::cout << "Input octave transposition interval: ";
		is >> octave_transposition_interval;
		composition.shift_octave(octave_transposition_interval);
		break;
	case CHANGE_MEASURE_DURATION:
		if (!is_loaded_composition) {
			std::cout << "No composition loaded\n";
			break;
		}

		while (true) {
			std::cout << "Enter composition duration (numerator/denominator)\n"
				<< "denominator must be 4 or 8:\n";
			is >> numerator;
			is.get();
			is >> denominator;
			if (denominator == 4 || denominator == 8) {
				break;
			}

			std::cerr << "Invalid input for composition duration\n";
		}

		composition.change_measure_duration(Duration(numerator, denominator));
		if (in_file_path.length() > 0) {
			parser.load_composition(in_file_path, composition);
		}

		break;
	default: 
		break;

	}

	std::cout << "\n";
}

void MenuInterface::iterate_through_composition(Composition<2U>& composition, std::istream & is) {
	enum PartIterationMenuOptions { BACK_TO_MENU, NEXT_MEASURE, PREVIOUS_MEASURE, ITERATE_THROUGH_MEASURE, NUM_OF_PART_OPTIONS };
	void (*print_part_iteration_menu)(Measure &current) = [](Measure &current) {
		std::cout << "Current measure: \"" << current << "\"\n"
			<< BACK_TO_MENU << ". Back to menu\n"
			<< NEXT_MEASURE << ". Next measure\n"
			<< PREVIOUS_MEASURE << ". Previous measure\n"
			<< ITERATE_THROUGH_MEASURE << ". Iterate through measure\n"
			<< "Choose option: ";
	};

	enum MeasureIterationMenuOptions { BACK_TO_PART, NEXT_SYMBOL, PREVIOUS_SYMBOL, CHANGE_OCTAVE, CHANGE_PITCH, TOGGLE_SHARP, NUM_OF_MEASURE_OPTIONS };
	void(*print_measure_iteration_menu)(std::unique_ptr<MusicSymbol> current) = [](std::unique_ptr<MusicSymbol> current) {
		std::cout << "Current symbol: \"" << current->to_string() << "\"\n"
			<< BACK_TO_PART << ". Back to part\n"
			<< NEXT_SYMBOL << ". Next symbol\n"
			<< PREVIOUS_SYMBOL << ". Previous symbol\n"
			<< CHANGE_OCTAVE << ". Change octave\n"
			<< CHANGE_PITCH << ". Change pitch\n"
			<< TOGGLE_SHARP << ". Toggle sharp\n"
			<< "Choose option: ";
	};

	unsigned part_index;
	std::cout << "Select part on which to iterate: ";
	is >> part_index;
	auto part = composition.at(part_index);
	std::cout << part << "\n";
	auto measure_it = part.begin();
	auto is_in_part_menu = true;
	while (is_in_part_menu) {
		print_part_iteration_menu(*measure_it);
		int temp;
		is >> temp;
		if (temp < BACK_TO_MENU || temp >= NUM_OF_PART_OPTIONS) {
			throw InvalidMenuOption();
		}

		const auto part_menu_option = static_cast<PartIterationMenuOptions>(temp);
		auto is_in_measure_iteration_menu = true;
		auto music_symbol_pointer_it = measure_it->begin();
		switch (part_menu_option) {
		case BACK_TO_MENU:
			is_in_part_menu = false;
			break;
		case NEXT_MEASURE:
			if (++measure_it == part.end()) {
				std::cout << "End of part, this is the last measure\n";
				--measure_it;
			}

			break;
		case PREVIOUS_MEASURE:
			if (measure_it == part.begin()) {
				std::cout << "Beginning of part, this is the first measure\n";
			}
			else {
				--measure_it;
			}
			
			break;
		case ITERATE_THROUGH_MEASURE:
			music_symbol_pointer_it = measure_it->begin();
			while (is_in_measure_iteration_menu) {
				char new_pitch;
				print_measure_iteration_menu((*music_symbol_pointer_it)->clone());
				is >> temp;
				if (temp < BACK_TO_PART || temp >= NUM_OF_MEASURE_OPTIONS) {
					throw InvalidMenuOption();
				}

				const auto measure_menu_option = static_cast<MeasureIterationMenuOptions>(temp);
				switch (measure_menu_option) {
				case BACK_TO_PART:
					is_in_measure_iteration_menu = false;
					break;
				case NEXT_SYMBOL:
					if (++music_symbol_pointer_it == measure_it->end()) {
						std::cout << "End of measure, this is the last symbol\n";
						--music_symbol_pointer_it;
					}
					
					break;
				case PREVIOUS_SYMBOL:
					if (music_symbol_pointer_it == measure_it->begin()) {
						std::cout << "Beginning of measure, this is the first symbol\n";
					}
					else {
						--music_symbol_pointer_it;
					}

					break;
				case CHANGE_OCTAVE:
					std::cout << "Input new octave [2 - 6]: ";
					is >> temp;
					if (temp >= Note::Octave::TWO && temp <= Note::Octave::SIX) {
						(*music_symbol_pointer_it)->set_octave(temp);
					}

					break;
				case CHANGE_PITCH:
					std::cout << "Input new pitch in { C, D, E, F, G, A, B }: ";
					is >> new_pitch;
					if (std::string("CDEFGAB").find(new_pitch) != std::string::npos) {
						(*music_symbol_pointer_it)->set_pitch(new_pitch);
					}
					break;
				case TOGGLE_SHARP:
					(*music_symbol_pointer_it)->toggle_sharp();
					break;
				default:
					break;
				}

			}

			break;
		default:
			break;
		}
		
	}

}

bool MenuInterface::is_program_running_ = true;
MenuInterface::MenuOptions MenuInterface::menu_option_ = EXIT;
bool MenuInterface::has_exported_ = false;
