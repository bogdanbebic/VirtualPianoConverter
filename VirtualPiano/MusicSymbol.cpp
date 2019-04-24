#include "MusicSymbol.h"

MusicSymbol::MusicSymbol(const Duration & duration)
	: duration_(duration)
{
	// empty body
}

Duration MusicSymbol::one_quarter = Duration(1, 4);

Duration MusicSymbol::one_eight = Duration(1, 8);

std::ostream & operator<<(std::ostream & os, const MusicSymbol & music_symbol) {
	os << music_symbol.to_string();
	return os;
}