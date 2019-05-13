#ifndef _MENUINTERFACE_H_
#define _MENUINTERFACE_H_

#include <iostream>
#include "Composition.h"

class VirtualPianoParser;

class MenuInterface {
public:
	static void print_menu();

	static void read_menu_option(std::istream& is = std::cin);

	static void execute_option(Composition<2U> & composition, VirtualPianoParser & parser, std::istream& is = std::cin);

	static bool is_program_running() {
		return is_program_running_;
	}

	class InvalidMenuOption : std::exception {
	public:
		const char* what() const override {
			return "Error: invalid menu option\n";
		}

	};

private:
	enum MenuOptions { EXIT, LOAD_COMPOSITION, EXPORT_MIDI, EXPORT_XML, EXPORT_BMP, 
		ITERATE_THROUGH_COMPOSITION, PRINT_COMPOSITION, SHIFT_OCTAVE, CHANGE_MEASURE_DURATION, NUM_OF_OPTIONS };

	void iterate_through_composition(Composition<2U> & composition, std::istream& is = std::cin);

	static MenuOptions menu_option_;
	static bool is_program_running_;
	static bool has_exported_;
};

#endif
