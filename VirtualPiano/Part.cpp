#include "Part.h"
#include "VirtualPianoException.h"
#include "Duration.h"

Part::Part(const Duration & measure_duration)
	: measure_duration_(measure_duration)
{
	// empty body
}

void Part::push_back(const Measure & measure) {
	if (measure.measure_duration() != this->measure_duration_) {
		throw std::exception("Illegal duration of Measure, does not comply with Part duration");
	}

	if (this->measures_.empty()) {
		this->measures_.push_back(measure);
		return;
	}

	auto & last_measure = this->measures_.back();
	if (last_measure.current_duration() == last_measure.measure_duration())	{
		this->measures_.push_back(measure);
	}
	else {
		throw std::exception("Last measure is not complete, illegal to add new measure after it");
	}

}

void Part::push_back(Measure && measure) {
	if (measure.measure_duration() != this->measure_duration_) {
		throw IllegalMeasureDuration();
	}

	if (this->measures_.empty()) {
		this->measures_.push_back(std::move(measure));
		return;
	}

	auto & last_measure = this->measures_.back();
	if (last_measure.current_duration() == last_measure.measure_duration())	{
		this->measures_.push_back(std::move(measure));
	}
	else {
		throw IncompleteMeasure();
	}

}

void Part::push_back(std::unique_ptr<MusicSymbol> music_symbol) {
	this->measures_.back().push_back(std::move(music_symbol));
}

std::ostream & operator<<(std::ostream & os, const Part & part) {
	os << "Measure duration: " << part.measure_duration_ << "\n";
	for (auto & measure : part.measures_) {
		os << measure << "\n";
	}
	return os;
}
