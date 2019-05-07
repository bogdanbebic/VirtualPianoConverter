#include "MidiNumbersStruct.h"

midi_formatter::MidiNumbersStruct::MidiNumbersStruct(int midi_number, int midi_rhythm, bool is_chord_with_previous) {
	this->midi_number = midi_number;
	this->midi_rhythm = midi_rhythm;
	this->is_chord_with_previous = is_chord_with_previous;
}

midi_formatter::MidiNumbersStruct::MidiNumbersStruct(int midi_rhythm, bool is_pause) {
	this->midi_rhythm = midi_rhythm;
	this->is_pause = is_pause;
}

std::map<std::string, int> midi_formatter::note_str_to_midi_number;
