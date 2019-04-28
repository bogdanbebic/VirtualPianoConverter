#ifndef _MENUINTERFACE_H_
#define _MENUINTERFACE_H_

#include <iostream>

class MenuInterface {
public:
	static void print_menu();

	static void read_menu_option(std::istream& is = std::cin);

	static void execute_option();

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
	enum MenuOptions { EXIT, NUM_OF_OPTIONS };

	static MenuOptions menu_option_;
	static bool is_program_running_;

};

#endif
