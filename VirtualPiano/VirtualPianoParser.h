#ifndef _VIRTUALPIANOPARSER_H_
#define _VIRTUALPIANOPARSER_H_

#include <fstream>
#include <string>
#include <regex>
#include <map>

class VirtualPianoParser {
public:
	explicit VirtualPianoParser(const std::string & mapping_file_path);

	void parse_mapping_file(std::map<std::string, int> & note_str_to_midi_number);
	
private:
	std::ifstream mapping_file_;
	std::map<char, std::string> virtual_piano_to_note_str_map_;
};

#endif	// end VirtualPianoParser.h
