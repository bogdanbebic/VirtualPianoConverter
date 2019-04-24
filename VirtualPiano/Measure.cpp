#include "Measure.h"

Measure::~Measure() {
	for (auto & music_symbol : this->music_symbols_) {
		delete music_symbol;
	}

}
