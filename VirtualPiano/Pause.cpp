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

std::ostream & operator<<(std::ostream & os, const Pause & pause) {
	os << pause.to_string();
	return os;
}
