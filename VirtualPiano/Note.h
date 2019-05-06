#ifndef _NOTE_H_
#define _NOTE_H_

#include "MusicSymbol.h"

class Note : public MusicSymbol {
public:
	enum Pitch : char { C = 'C', D = 'D', E = 'E', F = 'F', G = 'G', A = 'A', B = 'B' };
	enum Octave { TWO = 2, THREE, FOUR, FIVE, SIX };
	enum Accidental : char { NO_ACCIDENTAL = '\0', SHARP = '#', FLAT = 'b' };

	Note(Pitch pitch, Octave octave, const Duration & duration, bool is_in_chord_with_previous = false);
	Note(Pitch pitch, Accidental accidental, Octave octave, const Duration & duration, bool is_in_chord_with_previous = false);

	std::string to_string() const override;

	Duration duration() const override;

	std::unique_ptr<MusicSymbol> clone() const override;

	friend std::ostream & operator << (std::ostream & os, const Note & note);

	bool is_in_chord_with_previous() const;
	void set_legato_start();
	void set_legato_end();
	bool has_no_accidental() const;
	bool is_sharp() const;

	std::string to_mxml() override;

private:
	Pitch pitch_;
	Accidental accidental_ = NO_ACCIDENTAL;
	Octave octave_;
	bool is_in_chord_with_previous_ = false;
	bool legato_start_ = false;
	bool legato_end_ = false;
};

#endif	// end Note.h
