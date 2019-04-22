#include <iostream>
#include <string>

class MenuInterface {
public:
	static void print_menu() {
		std::cout << "0. Exit program" << std::endl
			<< "Choose menu option: ";
	}

	static void read_menu_option(std::istream &is = std::cin) {
		int temp;
		is >> temp;
		if (temp < EXIT || temp >= NUM_OF_OPTIONS) {
			throw BadMenuOption();
		}

	}

	static void execute_option() {
		switch (menu_option_) {
		case EXIT:
			// TODO: deallocation of everything
			is_program_running_ = false;
		default: 
			break;
		}

	}

	static bool is_program_running() {
		return is_program_running_;
	}

	class BadMenuOption : std::exception {
	public:
		const char *what() const override {
			return "Error: bad menu option\n";
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
	while (MenuInterface::is_program_running()) {
		try {
			MenuInterface::print_menu();
			MenuInterface::read_menu_option();
			MenuInterface::execute_option();
		}
		catch (MenuInterface::BadMenuOption &ex) {
			std::cerr << ex.what();
		}

	}

	return 0;
}
