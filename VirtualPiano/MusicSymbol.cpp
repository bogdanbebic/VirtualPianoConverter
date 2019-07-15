#include "MusicSymbol.h"

MusicSymbol::MusicSymbol(const Duration & duration)
	: duration_(duration)
{
	// empty body
}

Duration MusicSymbol::duration() const {
	return this->duration_;
}

void MusicSymbol::set_duration(const Duration& duration) {
	this->duration_ = duration;
}

unsigned MusicSymbol::duration_to_mxml_duration(const Duration & duration) {
	if (duration == one_quarter) {
		return 2U;
	}
	
	if (duration == one_eight) {
		return 1U;
	}

	return 0U;
}

Duration MusicSymbol::one_quarter = Duration(1, 4);

Duration MusicSymbol::one_eight = Duration(1, 8);

std::ostream & operator<<(std::ostream & os, const MusicSymbol & music_symbol) {
	os << music_symbol.to_string();
	return os;
}
