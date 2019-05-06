#include "Note.h"
#include <cctype>

Note::Note(Pitch pitch, Octave octave, const Duration & duration, bool is_in_chord_with_previous)
	: MusicSymbol(duration)
	, pitch_(pitch)
	, octave_(octave)
	, is_in_chord_with_previous_(is_in_chord_with_previous)
{
	// empty body
}

Note::Note(Pitch pitch, Accidental accidental, Octave octave, const Duration & duration, bool is_in_chord_with_previous)
	: MusicSymbol(duration)
	, pitch_(pitch)
	, accidental_(accidental)
	, octave_(octave)
	, is_in_chord_with_previous_(is_in_chord_with_previous)
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

Duration Note::duration() const {
	return this->is_in_chord_with_previous_ ? Duration(0, 1) : this->duration_;
}

std::unique_ptr<MusicSymbol> Note::clone() const {
	auto ret{ *this };
	return std::make_unique<Note>(ret);
}

bool Note::is_in_chord_with_previous() const {
	return this->is_in_chord_with_previous_;
}

void Note::set_legato_start() {
	this->legato_start_ = true;
}

void Note::set_legato_end() {
	this->legato_end_ = true;
}

bool Note::has_no_accidental() const {
	return this->accidental_ == NO_ACCIDENTAL;
}

bool Note::is_sharp() const {
	return this->accidental_ == SHARP;
}

std::string Note::to_mxml() {
	auto ret = std::string("\t<note>\n")
		+ "\t\t<pitch>\n"
		+ "\t\t\t<step>" + static_cast<char>(this->pitch_) + "</step>\n"
		+ "\t\t\t<octave>" + std::to_string(this->octave_) + "</octave>\n"
		+ "\t\t</pitch>\n"
		+ "\t\t<duration>" + std::to_string(duration_to_mxml_duration(this->duration_)) + "</duration>\n";

	if (this->is_in_chord_with_previous_) {
		ret += "\t\t<chord/>\n";
	}

	if (this->legato_start_) {
		ret += "\t\t<tie type=\"start\"/>\n";
	}

	if (this->legato_end_) {
		ret += "\t\t<tie type=\"end\"/>\n";
	}

	ret += "\t</note>\n";
	return ret;
}

std::ostream & operator<<(std::ostream & os, const Note & note) {
	os << note.to_string();
	return os;
}
