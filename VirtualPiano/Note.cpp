#include "Note.h"

Note::Note(Pitch pitch, Octave octave, const Duration & duration)
	: pitch_(pitch)
	, octave_(octave)
	, duration_(duration)
{
	// empty body
}

Note::Note(Pitch pitch, Accidental accidental, Octave octave, const Duration & duration)
	: pitch_(pitch)
	, accidental_(accidental)
	, octave_(octave)
	, duration_(duration)
{
	// empty body
}

bool Note::has_no_accidental() const {
	return this->accidental_ == NO_ACCIDENTAL;
}

bool Note::is_sharp() const {
	return this->accidental_ == SHARP;
}

std::ostream & operator<<(std::ostream & os, const Note & note) {
	os << static_cast<char>(note.pitch_);
	if (note.accidental_ != Note::NO_ACCIDENTAL) {
		os << static_cast<char>(note.accidental_);
	}
	
	os << note.octave_;
	return os;
}
