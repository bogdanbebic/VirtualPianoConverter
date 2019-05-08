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

void VirtualPianoParser::load_composition(const std::string & file_path, Composition<2U>& composition) {
	std::ifstream in_file{ file_path };
	std::string line;
	std::smatch matches;
	const std::regex re{"^\\[([^\\]]+)\\](.*)"};  // NOLINT(modernize-raw-string-literal)
	while (std::getline(in_file, line)) {
		while (line.length() != 0) {
			if (std::regex_match(line, matches, re)) {
				// is with []
				const auto is_chord = line.find(' ') == std::string::npos;
				const auto note_duration = is_chord ? MusicSymbol::one_quarter : MusicSymbol::one_eight;
				auto pushed_to_left = false;
				auto pushed_to_right = false;

				for (auto i = 0U; i < matches[1].str().length(); i++) {
					// map matches[1].str()[i] to note
					auto note_str = this->virtual_piano_to_note_str_map_[matches[1].str()[i]];
					auto pitch = static_cast<Note::Pitch>(note_str[0]);
					auto octave = static_cast<Note::Octave>(note_str[1] == '#' ? note_str[2] - '0' : note_str[1] - '0');
					auto accidental = note_str[1] == '#' ? Note::Accidental::SHARP : Note::Accidental::NO_ACCIDENTAL;

					if (octave > Note::Octave::THREE) {
						composition.push_back(std::make_unique<Note>(pitch, accidental, octave, note_duration, is_chord && pushed_to_right), 0);
						composition.push_back(std::make_unique<Pause>(note_duration), 1);
						pushed_to_right = true;
					}
					else {
						composition.push_back(std::make_unique<Note>(pitch, accidental, octave, note_duration, is_chord && pushed_to_left), 1);
						composition.push_back(std::make_unique<Pause>(note_duration), 0);
						pushed_to_left = true;
					}
					

					if (!is_chord) {
						i++;
					}

				}

				line = matches[2].str();
			}
			else {
				if (line[0] == ' ') {
					composition.push_back(std::make_unique<Pause>(MusicSymbol::one_eight), 0);
					composition.push_back(std::make_unique<Pause>(MusicSymbol::one_eight), 1);
				}
				else if (line[0] == '|') {
					composition.push_back(std::make_unique<Pause>(MusicSymbol::one_quarter), 0);
					composition.push_back(std::make_unique<Pause>(MusicSymbol::one_quarter), 1);
				}
				else {
					auto note_str = this->virtual_piano_to_note_str_map_[line[0]];
					auto pitch = static_cast<Note::Pitch>(note_str[0]);
					auto octave = static_cast<Note::Octave>(note_str[1] == '#' ? note_str[2] - '0' : note_str[1] - '0');
					auto accidental = note_str[1] == '#' ? Note::Accidental::SHARP : Note::Accidental::NO_ACCIDENTAL;

					if (octave > Note::Octave::THREE) {
						composition.push_back(std::make_unique<Note>(pitch, accidental, octave, MusicSymbol::one_quarter, false), 0);
						composition.push_back(std::make_unique<Pause>(MusicSymbol::one_quarter), 1);
					}
					else {
						composition.push_back(std::make_unique<Note>(pitch, accidental, octave, MusicSymbol::one_quarter, false), 1);
						composition.push_back(std::make_unique<Pause>(MusicSymbol::one_quarter), 0);
					}

				}

				line = line.substr(1);
			}

		}

	}

}
