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

std::ostream & operator<<(std::ostream & os, const Pause & pause) {
	os << pause.to_string();
	return os;
}
