#ifndef _COMPOSITION_H_
#define _COMPOSITION_H_

#include "Part.h"
#include "Note.h"
#include "Pause.h"
#include "VirtualPianoException.h"

using part_id = unsigned;

namespace composition {
	constexpr unsigned default_number_of_parts = 2U;
}

template <unsigned NumberOfParts = composition::default_number_of_parts>
class Composition {
public:
	explicit Composition(const Duration & measure_duration);
	explicit Composition(std::vector<Duration> measure_durations);

	void push_back(std::unique_ptr<Note> note_ptr, part_id id);
	void push_back(std::unique_ptr<Pause> pause_ptr, part_id id);

	void shift_octave(int transposition_interval);
	void change_measure_duration(const Duration & measure_duration);

	unsigned num_parts() const;

	std::vector<Part>::reference at(part_id pos);
	std::vector<Part>::const_reference at(part_id pos) const;

	std::vector<Part>::iterator begin();
	std::vector<Part>::const_iterator begin() const;
	std::vector<Part>::iterator end();
	std::vector<Part>::const_iterator end() const;

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
		if (note_ptr->is_in_chord_with_previous() && this->parts_[id].back().current_duration() == MusicSymbol::one_eight) {
			temp->set_duration(MusicSymbol::one_eight);
			temp->set_legato_end();
			note_ptr->set_legato_start();
			note_ptr->set_duration(MusicSymbol::one_eight);
			this->parts_[id].at(this->parts_[id].size() - 2).push_back(std::move(note_ptr));
		}
				
		this->parts_[id].push_back(std::move(temp));
	}
	catch (MeasureDurationOverflow &) {
		auto temp = std::make_unique<Note>(Note(*note_ptr));
		auto & last_measure = this->parts_[id].back();
		auto duration_left_in_measure = Duration::abs_difference(last_measure.measure_duration(), last_measure.current_duration());
		if (duration_left_in_measure != Duration(0, 1)) {
			temp->set_duration(duration_left_in_measure);
			note_ptr->set_duration(Duration::abs_difference(note_ptr->duration(), duration_left_in_measure));
			temp->set_legato_start();
			note_ptr->set_legato_end();
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

template <unsigned NumberOfParts>
void Composition<NumberOfParts>::shift_octave(int transposition_interval) {
	for (auto part_it = this->begin(); part_it != this->end(); ++part_it) {
		for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
			for (auto & music_symbol_pointer : *measure_it) {
				music_symbol_pointer->shift_octave(transposition_interval);
			}

		}

	}

}

template <unsigned NumberOfParts>
void Composition<NumberOfParts>::change_measure_duration(const Duration& measure_duration) {
	this->parts_.clear();
	for (auto i = 0U; i < NumberOfParts; i++) {
		this->parts_.push_back(Part(measure_duration));
	}

}

template<unsigned NumberOfParts>
unsigned Composition<NumberOfParts>::num_parts() const {
	return this->parts_.size();
}

template<unsigned NumberOfParts>
std::vector<Part>::reference Composition<NumberOfParts>::at(part_id pos) {
	return this->parts_.at(pos);
}

template<unsigned NumberOfParts>
std::vector<Part>::const_reference Composition<NumberOfParts>::at(part_id pos) const {
	return this->parts_.at(pos);
}

template<unsigned NumberOfParts>
std::vector<Part>::iterator Composition<NumberOfParts>::begin() {
	return this->parts_.begin();
}

template<unsigned NumberOfParts>
std::vector<Part>::const_iterator Composition<NumberOfParts>::begin() const {
	return this->parts_.begin();
}

template<unsigned NumberOfParts>
std::vector<Part>::iterator Composition<NumberOfParts>::end() {
	return this->parts_.end();
}

template<unsigned NumberOfParts>
std::vector<Part>::const_iterator Composition<NumberOfParts>::end() const {
	return this->parts_.end();
}

#endif
