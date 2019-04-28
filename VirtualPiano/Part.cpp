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
	auto last_measure = this->measures_.back();
	try {
		auto temp = music_symbol->clone();
		last_measure.push_back(std::move(temp));
	}
	catch (MeasureDurationOverflow & e) {
		// TODO: legato
		auto temp = music_symbol->clone();
		const auto difference = Duration::abs_difference(last_measure.current_duration(), last_measure.measure_duration());
		const auto next_duration = Duration::abs_difference(music_symbol->duration(), difference);
		music_symbol->set_duration(difference);
		last_measure.push_back(std::move(music_symbol));
		temp->set_duration(next_duration);
		this->measures_.emplace_back(this->measure_duration_);
		this->push_back(std::move(temp));
	}

}

std::ostream & operator<<(std::ostream & os, const Part & part) {
	os << "Measure duration: " << part.measure_duration_ << "\n";
	for (auto & measure : part.measures_) {
		os << measure << "\n";
	}
	return os;
}
