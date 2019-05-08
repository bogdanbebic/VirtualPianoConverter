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
		throw IllegalMeasureDuration();
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
		throw IncompleteMeasure();
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
	if (this->measures_.empty()) {
		this->measures_.emplace_back(this->measure_duration_);
	}

	this->measures_.back().push_back(std::move(music_symbol));
}

Duration Part::measure_duration() const {
	return this->measure_duration_;
}

const Measure & Part::back() const {
	return this->measures_.back();
}

const Measure & Part::at(const unsigned index) const {
	return this->measures_.at(index);
}

std::vector<Measure>::iterator Part::begin() {
	return this->measures_.begin();
}

std::vector<Measure>::const_iterator Part::begin() const {
	return this->measures_.begin();
}

std::vector<Measure>::iterator Part::end() {
	return this->measures_.end();
}

std::vector<Measure>::const_iterator Part::end() const {
	return this->measures_.end();
}

std::ostream & operator<<(std::ostream & os, const Part & part) {
	os << "Measure duration: " << part.measure_duration_ << "\n";
	for (auto & measure : part.measures_) {
		os << measure << "\n";
	}
	return os;
}
