#include "VirtualPianoException.h"

char const * VirtualPianoException::what() const {
	return "\n*** Error: An unknown error occured ***\n";
}

char const * MeasureDurationOverflow::what() const {
	return "\n*** Error: Could not fit MusicSymbol to current Measure ***\n";
}

char const * IllegalMeasureDuration::what() const {
	return "\n*** Error: Illegal duration of Measure ***\n";
}

char const * IncompleteMeasure::what() const {
	return "\n*** Error: Last measure is not complete, illegal to add new measure after it ***\n";
}

char const * IncompatibleNumberOfParts::what() const {
	return "\n*** Error: Incompatible number of parts ***\n";
}

char const * IllegalMapingFileFormat::what() const {
	return "\n*** Error: Illegal mapping file format ***\n";
}

char const* InvalidBmpWidth::what() const {
	return "*** Error: invalid width of bmp file (width must be divisible by 4) ***\n";
}
