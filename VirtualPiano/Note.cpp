#include "Note.h"
#include <cctype>

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
	std::string ret;
	if (this->duration_ == one_quarter) {
		ret += static_cast<char>(this->pitch_);
	}
	else if (this->duration_ == one_eight) {
		ret += std::tolower(static_cast<char>(this->pitch_));
	}

	if (this->accidental_ != NO_ACCIDENTAL) {
		 ret += static_cast<char>(this->accidental_);
	}

	ret += '0' + static_cast<unsigned>(this->octave_);
	return ret;
}

std::unique_ptr<MusicSymbol> Note::clone() const {
	auto ret{ *this };
	return std::make_unique<Note>(ret);
}

void Note::set_legato() {
	this->legato_ = true;
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
