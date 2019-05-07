#ifndef _MIDINUMBERSSTRUCT_H_
#define _MIDINUMBERSSTRUCT_H_

#include <map>

namespace midi_formatter {
	typedef struct MidiNumbersStruct {
		int midi_number = 0;
		int midi_rhythm = 0;
		bool is_chord_with_previous = false;
		bool is_pause = false;
		MidiNumbersStruct() = default;
		explicit MidiNumbersStruct(int midi_number, int midi_rhythm, bool is_chord_with_previous);
		explicit MidiNumbersStruct(int midi_rhythm, bool is_pause);
	} midi_numbers;

	extern std::map<std::string, int> note_str_to_midi_number;

}
#endif
