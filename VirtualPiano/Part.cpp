#include "Part.h"

Part::Part(const Duration & measure_duration)
	: measure_duration_(measure_duration)
{
	// empty body
}

bool Part::push_back(const Measure & measure) {
	if (measure.measure_duration() == this->measure_duration_ && this->measures_.empty()) {
		this->measures_.push_back(measure);
		return true;
	}

	auto & last_measure = this->measures_.back();
	if (
		measure.measure_duration() == this->measure_duration_
		&& last_measure.current_duration() == last_measure.measure_duration()
		)
	{
		this->measures_.push_back(measure);
		return true;
	}

	return false;
}

bool Part::push_back(Measure && measure) {
	if (measure.measure_duration() == this->measure_duration_ && this->measures_.empty()) {
		this->measures_.push_back(std::move(measure));
		return true;
	}

	auto & last_measure = this->measures_.back();
	if (
		measure.measure_duration() == this->measure_duration_
		&& last_measure.current_duration() == last_measure.measure_duration()
		)
	{
		this->measures_.push_back(std::move(measure));
		return true;
	}

	return false;
}

std::ostream & operator<<(std::ostream & os, const Part & part) {
	os << "Measure duration: " << part.measure_duration_ << "\n";
	for (auto & measure : part.measures_) {
		os << measure << "\n";
	}
	return os;
}
