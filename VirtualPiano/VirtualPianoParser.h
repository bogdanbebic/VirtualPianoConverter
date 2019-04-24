#ifndef _VIRTUALPIANOPARSER_H_
#define _VIRTUALPIANOPARSER_H_

#include <string>
#include <regex>

class VirtualPianoParser {
public:
	explicit VirtualPianoParser(std::string in_file_path);


	

private:
	std::string in_file_path_;
};

#endif	// end VirtualPianoParser.h
