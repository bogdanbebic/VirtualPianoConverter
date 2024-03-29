#ifndef _MUSICSYMBOL_H_
#define _MUSICSYMBOL_H_

#include <string>
#include <iostream>
#include <memory>
#include "Duration.h"
#include "MidiNumbersStruct.h"
#include "MusicSymbolBmpStruct.h"

class MusicSymbol {
public:
	explicit MusicSymbol(const Duration& duration);

	MusicSymbol(const MusicSymbol& other) = default;
	MusicSymbol(MusicSymbol&& other) = default;

	MusicSymbol& operator=(const MusicSymbol& other) = default;
	MusicSymbol& operator=(MusicSymbol&& other) = default;

	virtual ~MusicSymbol() = default;


	virtual Duration duration() const;

	void set_duration(const Duration& duration);

	virtual void shift_octave(int transposition_interval) {}
	virtual void set_octave(int octave) {}
	virtual void set_pitch(char pitch) {}
	virtual void toggle_sharp() {}
	virtual bool is_in_chord_with_previous() const { return false; }

	virtual std::string to_string() const = 0;

	virtual std::unique_ptr<MusicSymbol> clone() const = 0;
	
	friend std::ostream & operator << (std::ostream & os, const MusicSymbol & music_symbol);

	static Duration one_quarter;
	static Duration one_eight;

	virtual std::string to_mxml() = 0;
	virtual midi_formatter::midi_numbers to_midi() = 0;
	virtual bmp_formatter::MusicSymbolBmpStruct to_bmp() = 0;

	static unsigned duration_to_mxml_duration(const Duration & duration);
protected:
	Duration duration_;
};

#endif	// end MusicSymbol.h
