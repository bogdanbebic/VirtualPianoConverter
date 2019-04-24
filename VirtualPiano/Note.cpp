#include "Note.h"

Note::Note(Pitch pitch, Octave octave, const Duration & duration)
	: MusicSymbol(duration)
	, pitch_(pitch)
	, octave_(octave)
{
	// empty body
}

Note::Note(Pitch pitch, Accidental accidental, Octave octave, const Duration & duration)
	: MusicSymbol(duration)
	, pitch_(pitch)
	, accidental_(accidental)
	, octave_(octave)
{
	// empty body
}

std::string Note::to_string() const {
	std::string ret({ static_cast<char>(this->pitch_) });
	if (this->accidental_ != NO_ACCIDENTAL) {
		 ret += static_cast<char>(this->accidental_);
	}

	ret += '0' + static_cast<unsigned>(this->octave_);
	return ret;
}

bool Note::has_no_accidental() const {
	return this->accidental_ == NO_ACCIDENTAL;
}

bool Note::is_sharp() const {
	return this->accidental_ == SHARP;
}

std::ostream & operator<<(std::ostream & os, const Note & note) {
	os << note.to_string();
	return os;
}
