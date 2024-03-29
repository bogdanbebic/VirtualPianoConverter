#include "Measure.h"
#include "VirtualPianoException.h"

Measure::Measure(const Duration & measure_duration)
	: measure_duration_(measure_duration)
	, current_duration_(Duration(0, 1))
{
	// empty body
}

Measure::Measure(const Measure & other)
	: measure_duration_(other.measure_duration_)
	, current_duration_(Duration(0, 1))
{
	this->clone(other);
}

Measure & Measure::operator=(const Measure & other) {
	if (this != &other) {
		this->clone(other);
	}

	return *this;
}

Measure::~Measure() {
	this->music_symbols_.clear();
}

Duration Measure::measure_duration() const {
	return measure_duration_;
}

Duration Measure::current_duration() const {
	return current_duration_;
}

std::vector<std::unique_ptr<MusicSymbol>>::iterator Measure::begin() {
	return this->music_symbols_.begin();
}

std::vector<std::unique_ptr<MusicSymbol>>::const_iterator Measure::begin() const {
	return this->music_symbols_.begin();
}

std::vector<std::unique_ptr<MusicSymbol>>::iterator Measure::end() {
	return this->music_symbols_.end();
}

std::vector<std::unique_ptr<MusicSymbol>>::const_iterator Measure::end() const {
	return this->music_symbols_.end();
}

void Measure::push_back(std::unique_ptr<MusicSymbol> music_symbol) {
	if (this->current_duration_ + music_symbol->duration() > this->measure_duration_) {
		throw MeasureDurationOverflow();
	}

	this->current_duration_ += music_symbol->duration();
	this->music_symbols_.push_back(std::move(music_symbol));
}

void Measure::clone(const Measure & other) {
	this->measure_duration_ = other.measure_duration_;
	for (auto & music_symbol_ptr : other.music_symbols_) {
		this->push_back(music_symbol_ptr->clone());
	}

}

std::ostream & operator<<(std::ostream & os, const Measure & measure) {
	for (auto & music_symbol : measure.music_symbols_) {
		os << *music_symbol;
	}

	return os;
}
