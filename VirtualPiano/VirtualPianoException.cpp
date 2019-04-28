#include "VirtualPianoException.h"

char const * VirtualPianoException::what() const {
	return "\n*** Error: An unknown error occured ***\n";
}

char const * MeasureDurationOverflow::what() const {
	return "\n*** Error: Could not fit MusicSymbol to current Measure ***\n";
}
