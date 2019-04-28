#include "MenuInterface.h"

void MenuInterface::print_menu() {
	std::cout << "0. Exit program\n"
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

void MenuInterface::execute_option() {
	switch (menu_option_) {
	case EXIT:
		is_program_running_ = false;
		break;
	default:
		break;
	}

}

bool MenuInterface::is_program_running_ = true;
MenuInterface::MenuOptions MenuInterface::menu_option_ = EXIT;
