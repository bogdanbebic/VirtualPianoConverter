#ifndef _MIDIFORMATTER_H_
#define _MIDIFORMATTER_H_

#include <string>
#include "Formatter.h"

#include "MidiFile.h"

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
	


	this->midi_file_.sortTracks();
	this->midi_file_.write(out_file_path);
}

#endif
