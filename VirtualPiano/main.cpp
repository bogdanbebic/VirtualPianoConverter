#include <iostream>
#include <string>

#include "MenuInterface.h"

#include "VirtualPianoParser.h"

#include "MxmlFormatter.h"
void test() {
	std::vector<std::unique_ptr<Pause>> vec_pauses;
	vec_pauses.push_back(std::make_unique<Pause>(Pause(MusicSymbol::one_quarter)));
	vec_pauses.push_back(std::make_unique<Pause>(Pause(MusicSymbol::one_eight)));
	vec_pauses.push_back(std::make_unique<Pause>(Pause(MusicSymbol::one_quarter)));
	vec_pauses.push_back(std::make_unique<Pause>(Pause(MusicSymbol::one_eight)));

	std::vector<std::unique_ptr<Note>> vec_notes;
	vec_notes.push_back(std::make_unique<Note>(Note(Note::C, Note::THREE, MusicSymbol::one_quarter)));
	vec_notes.push_back(std::make_unique<Note>(Note(Note::C, Note::THREE, MusicSymbol::one_eight)));
	vec_notes.push_back(std::make_unique<Note>(Note(Note::A, Note::TWO, MusicSymbol::one_quarter)));
	vec_notes.push_back(std::make_unique<Note>(Note(Note::D, Note::SHARP, Note::FOUR, MusicSymbol::one_eight)));

	Composition<> composition(Duration(3, 4));
	for (auto i = 0U; i < vec_notes.size(); i++) {
		std::cout << vec_notes[i]->to_mxml();
		std::cout << vec_pauses[i]->to_mxml();
		composition.push_back(std::move(vec_notes[i]), 0);
		composition.push_back(std::move(vec_pauses[i]), 0);
	}

	MxmlFormatter<> mxml_formatter;
	mxml_formatter.generate_output_file(std::cout, composition);
	
	system("pause");
}


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

	test();

	return 0;
}
