#ifndef _MIDIFORMATTER_H_
#define _MIDIFORMATTER_H_

#include <string>
#include "Formatter.h"

#include "MidiFile.h"
#include "MidiNumbersStruct.h"

namespace midi_formatter {
	constexpr int default_ticks_per_quarter_note = 48;
	constexpr int default_attack_release_velocity = 64;
}

template <unsigned NumberOfParts = composition::default_number_of_parts>
class MidiFormatter : public Formatter<NumberOfParts> {
public:
	MidiFormatter();

	void generate_output_file(const std::string out_file_path, const Composition<NumberOfParts> & composition) override;

private:
	smf::MidiFile midi_file_;
	int ticks_per_quarter_note_ = midi_formatter::default_ticks_per_quarter_note;
	int attack_release_velocity_ = midi_formatter::default_attack_release_velocity;
	std::vector<unsigned char> midi_event_;
	int action_time_ = 0;

	static constexpr int store_note_start = 0x90;
	static constexpr int store_note_end = 0x80;
};

template<unsigned NumberOfParts>
MidiFormatter<NumberOfParts>::MidiFormatter() {
	this->midi_file_.absoluteTicks();
	this->midi_event_.resize(3);
	this->midi_file_.setTicksPerQuarterNote(this->ticks_per_quarter_note_);
	this->midi_file_.addTrack(1);
	this->midi_event_[2] = this->attack_release_velocity_;
}

template <unsigned NumberOfParts>
void MidiFormatter<NumberOfParts>::generate_output_file(const std::string out_file_path, const Composition<NumberOfParts>& composition) {
	auto part_index = 0;
	for (auto part_it = composition.begin(); part_it != composition.end(); ++part_it, part_index++) {
		this->action_time_ = 0;
		for (auto measure_it = part_it->begin(); measure_it != part_it->end(); ++measure_it) {
			for (auto & music_symbol_ptr : *measure_it) {
				midi_formatter::midi_numbers midi_numbers_mapped = music_symbol_ptr->to_midi();
				if (!midi_numbers_mapped.is_pause) {
					this->midi_event_[0] = store_note_start;
					this->midi_event_[1] = midi_numbers_mapped.midi_number;
					this->midi_file_.addEvent(part_index, this->action_time_, this->midi_event_);
					if (midi_numbers_mapped.is_chord_with_previous) {
						this->action_time_ -= this->ticks_per_quarter_note_ * midi_numbers_mapped.midi_rhythm;
					}

					this->action_time_ += this->ticks_per_quarter_note_ * midi_numbers_mapped.midi_rhythm;
					this->midi_event_[0] = store_note_end;
					this->midi_file_.addEvent(part_index, this->action_time_, this->midi_event_);
					

				}
				else {
					this->action_time_ += this->ticks_per_quarter_note_ * midi_numbers_mapped.midi_rhythm;
				}
				
			}

		}

	}

	this->midi_file_.sortTracks();
	this->midi_file_.write(out_file_path);
}

#endif
