#include "Pause.h"

Pause::Pause(const Duration & duration)
	: MusicSymbol(duration)
{
	// empty body
}

std::string Pause::to_string() const {
	std::string ret;
	if (this->duration_ == MusicSymbol::one_quarter) {
		ret = " | ";
	}
	else if (this->duration_ == MusicSymbol::one_eight) {
		ret = " ";
	}

	return ret;
}

std::unique_ptr<MusicSymbol> Pause::clone() const {
	auto ret{ *this };
	return std::make_unique<Pause>(ret);
}

std::string Pause::to_mxml() {
	auto ret = std::string("\t<note>\n")
		+ "\t\t<rest/>\n"
		+ "\t\t<duration>" + std::to_string(duration_to_mxml_duration(this->duration_)) + "</duration>\n"
		+ "\t</note>\n";

	return ret;
}

midi_formatter::midi_numbers Pause::to_midi() {
	auto midi_rhythm = 0;
	if (this->duration_ == one_quarter) {
		midi_rhythm = 2;
	}
	else if (this->duration_ == one_eight) {
		midi_rhythm = 1;
	}

	return midi_formatter::midi_numbers(midi_rhythm, true);
}

bmp_formatter::MusicSymbolBmpStruct Pause::to_bmp() {
	return bmp_formatter::MusicSymbolBmpStruct(255, 255, 255, this->duration_ == one_quarter ? 2 : 1);
}

std::ostream & operator<<(std::ostream & os, const Pause & pause) {
	os << pause.to_string();
	return os;
}
