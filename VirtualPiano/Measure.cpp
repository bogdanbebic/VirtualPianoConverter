#include "Measure.h"

Measure::Measure(const Duration & measure_duration)
	: measure_duration_(measure_duration)
	, current_duration_(Duration(0, 1))
{
	// empty body
}

Measure::~Measure() {
	for (auto & music_symbol : this->music_symbols_) {
		delete music_symbol;
	}

}

void Measure::push_back(const MusicSymbol & music_symbol) {
	if (this->current_duration_ + music_symbol.duration() <= this->measure_duration_) {
		this->current_duration_ += music_symbol.duration();
		// TODO: push_back music_symbol
	}

}
