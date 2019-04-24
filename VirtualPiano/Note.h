#ifndef _NOTE_H_
#define _NOTE_H_

#include "MusicSymbol.h"

class Note : public MusicSymbol {
public:
	enum Pitch : char { C = 'C', D = 'D', E = 'E', F = 'F', G = 'G', A = 'A', B = 'B' };
	enum Octave { TWO = 2, THREE, FOUR, FIVE, SIX };
	enum Accidental : char { NO_ACCIDENTAL = '\0', SHARP = '#', FLAT = 'b' };

	Note(Pitch pitch, Octave octave, const Duration & duration);
	Note(Pitch pitch, Accidental accidental, Octave octave, const Duration & duration);

	std::string to_string() const override;

	friend std::ostream & operator << (std::ostream & os, const Note & note);

	bool has_no_accidental() const;
	bool is_sharp() const;

private:
	Pitch pitch_;
	Accidental accidental_ = NO_ACCIDENTAL;
	Octave octave_;
};

#endif	// end Note.h
