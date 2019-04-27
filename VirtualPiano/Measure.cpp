#include "Measure.h"

Measure::Measure(const Duration & measure_duration)
	: measure_duration_(measure_duration)
	, current_duration_(Duration(0, 1))
{
	// empty body
}

Measure::~Measure() {
	this->music_symbols_.clear();
}

void Measure::push_back(std::unique_ptr<MusicSymbol> music_symbol) {
	if (this->current_duration_ + music_symbol->duration() <= this->measure_duration_) {
		this->current_duration_ += music_symbol->duration();
		this->music_symbols_.push_back(std::move(music_symbol));
	}

}

std::ostream & operator<<(std::ostream & os, const Measure & measure) {
	for (auto & music_symbol : measure.music_symbols_) {
		os << *music_symbol;
	}

	os << "\n";
	return os;
}
