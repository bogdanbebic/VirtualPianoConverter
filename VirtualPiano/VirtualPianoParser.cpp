#include "VirtualPianoParser.h"
#include "Formatter.h"

VirtualPianoParser::VirtualPianoParser(const std::string & mapping_file_path) {
	this->mapping_file_.open(mapping_file_path);
}

void VirtualPianoParser::parse_mapping_file(std::map<std::string, int> & note_str_to_midi_number) {
	std::string line;
	std::smatch matches;
	const std::regex re{ "^(.),([^,]+),([0-9]+)$" };
	while (std::getline(this->mapping_file_, line)) {
		if (std::regex_match(line, matches, re)) {
			this->virtual_piano_to_note_str_map_[matches[1].str()[0]] = matches[2].str();
			note_str_to_midi_number[matches[2].str()] = std::stoi(matches[3].str());
		}
		else {
			throw IllegalMapingFileFormat();
		}

	}

}
