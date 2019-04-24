#include "VirtualPianoParser.h"
#include <utility>

VirtualPianoParser::VirtualPianoParser(std::string in_file_path)
	: in_file_path_(std::move(in_file_path))
{
	// empty body
}
