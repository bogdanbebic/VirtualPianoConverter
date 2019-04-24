#ifndef _MUSICSYMBOL_H_
#define _MUSICSYMBOL_H_

#include <string>
#include <iostream>
#include "Duration.h"

class MusicSymbol {
public:
	explicit MusicSymbol(const Duration& duration);

	MusicSymbol(const MusicSymbol& other) = default;
	MusicSymbol(MusicSymbol&& other) = default;

	MusicSymbol& operator=(const MusicSymbol& other) = default;
	MusicSymbol& operator=(MusicSymbol&& other) = default;

	virtual ~MusicSymbol() = default;

	virtual std::string to_string() const = 0;
	
	friend std::ostream & operator << (std::ostream & os, const MusicSymbol & music_symbol);

	static Duration one_quarter;
	static Duration one_eight;
	
protected:
	Duration duration_;
};

#endif	// end MusicSymbol.h
