#ifndef _COMPOSITION_H_
#define _COMPOSITION_H_

#include "Part.h"
#include "Note.h"
#include "Pause.h"
#include "VirtualPianoException.h"

using part_id = unsigned;

namespace composition {
	extern const unsigned default_number_of_parts;
}

template <unsigned NumberOfParts = composition::default_number_of_parts>
class Composition {
public:
	explicit Composition(const Duration & measure_duration);
	explicit Composition(std::vector<Duration> measure_durations);

	void push_back(std::unique_ptr<Note> note_ptr, part_id id);
	void push_back(std::unique_ptr<Pause> pause_ptr, part_id id);

	unsigned num_parts() const;

private:
	std::vector<Part> parts_;
};


template <unsigned NumberOfParts>
Composition<NumberOfParts>::Composition(const Duration& measure_duration) {
	for (auto i = 0U; i < NumberOfParts; i++) {
		parts_.push_back(Part(measure_duration));
	}

}

template<unsigned NumberOfParts>
Composition<NumberOfParts>::Composition(std::vector<Duration> measure_durations) {
	if (measure_durations.size() != NumberOfParts) {
		throw IncompatibleNumberOfParts();
	}

	for (auto & measure_duration : measure_durations) {
		parts_.push_back(Part(measure_duration));
	}

}

template<unsigned NumberOfParts>
void Composition<NumberOfParts>::push_back(std::unique_ptr<Note> note_ptr, part_id id) {
	try {
		auto temp = std::make_unique<Note>(Note(*note_ptr));
		this->parts_[id].push_back(std::move(temp));
	}
	catch (MeasureDurationOverflow &) {
		auto temp = std::make_unique<Note>(Note(*note_ptr));
		auto & last_measure = this->parts_[id].back();
		auto duration_left_in_measure = Duration::abs_difference(last_measure.measure_duration(), last_measure.current_duration());
		if (duration_left_in_measure != Duration(0, 1)) {
			temp->set_duration(duration_left_in_measure);
			note_ptr->set_duration(Duration::abs_difference(note_ptr->duration(), duration_left_in_measure));
			temp->set_legato();
			note_ptr->set_legato();
			this->parts_[id].push_back(std::move(temp));
		}
		this->parts_[id].push_back(Measure(this->parts_[id].measure_duration()));
		this->push_back(std::move(note_ptr), id);
	}
	
}

template <unsigned NumberOfParts>
void Composition<NumberOfParts>::push_back(std::unique_ptr<Pause> pause_ptr, part_id id) {
	try {
		auto temp = pause_ptr->clone();
		this->parts_[id].push_back(std::move(temp));
	}
	catch (MeasureDurationOverflow &) {
		auto temp = pause_ptr->clone();
		auto & last_measure = this->parts_[id].back();
		auto duration_left_in_measure = Duration::abs_difference(last_measure.measure_duration(), last_measure.current_duration());
		if (duration_left_in_measure != Duration(0, 1)) {
			temp->set_duration(duration_left_in_measure);
			pause_ptr->set_duration(Duration::abs_difference(pause_ptr->duration(), duration_left_in_measure));
			this->parts_[id].push_back(std::move(temp));
		}
		this->parts_[id].push_back(Measure(this->parts_[id].measure_duration()));
		this->push_back(std::move(pause_ptr), id);
	}

}

template<unsigned NumberOfParts>
unsigned Composition<NumberOfParts>::num_parts() const {
	return this->parts_.size();
}

#endif
