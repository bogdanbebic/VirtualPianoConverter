#ifndef _COMPOSITION_H_
#define _COMPOSITION_H_

#include "Part.h"
#include "Note.h"
#include "Pause.h"
#include "VirtualPianoException.h"

using part_id = unsigned;

template <unsigned NumberOfParts = 2U>
class Composition {
public:
	explicit Composition(const Duration & measure_duration);
	explicit Composition(std::vector<Duration> measure_durations);

	void push_back(std::unique_ptr<Note> note_ptr, part_id part_id);
	void push_back(std::unique_ptr<Pause> pause_ptr, part_id part_id);

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

#endif
