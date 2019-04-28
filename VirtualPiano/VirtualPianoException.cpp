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
