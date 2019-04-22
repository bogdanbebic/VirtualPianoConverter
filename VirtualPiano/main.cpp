#include <iostream>
#include <string>
#include "VirtualPianoParser.h"

class MenuInterface {
public:
	static void print_menu() {
		std::cout << "0. Exit program" << std::endl
			<< "Choose menu option (index of option): ";
	}

	static void read_menu_option(std::istream &is = std::cin) {
		int temp;
		is >> temp;
		if (temp < EXIT || temp >= NUM_OF_OPTIONS) {
			throw InvalidMenuOption();
		}

		menu_option_ = static_cast<MenuOptions>(temp);

	}

	static void execute_option() {
		switch (menu_option_) {
		case EXIT:
			is_program_running_ = false;
			break;
		default: 
			break;
		}

	}

	static bool is_program_running() {
		return is_program_running_;
	}

	class InvalidMenuOption : std::exception {
	public:
		const char *what() const override {
			return "Error: invalid menu option\n";
		}

	};

private:
	enum MenuOptions { EXIT, NUM_OF_OPTIONS };

	static MenuOptions menu_option_;
	static bool is_program_running_;
	
};

bool MenuInterface::is_program_running_ = true;
MenuInterface::MenuOptions MenuInterface::menu_option_ = EXIT;

int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	if (argc < 2) {
		std::cout << "Error: invalid usage of program."
			<< std::endl << "Usage: program.exe file_path" << std::endl
			<< std::endl << "param file_path - file which contains key to note and midi number mapping"
			<< std::endl;

		return 0;
	}

	VirtualPianoParser parser(argv[1]);

	while (MenuInterface::is_program_running()) {
		try {
			MenuInterface::print_menu();
			MenuInterface::read_menu_option();
			MenuInterface::execute_option();
		}
		catch (MenuInterface::InvalidMenuOption &ex) {
			std::cerr << ex.what();
		}

	}

	return 0;
}
