#ifndef _MEASURE_H_
#define _MEASURE_H_

#include <iostream>
#include <vector>
#include <memory>
#include "MusicSymbol.h"

class Measure {
public:
	explicit Measure(const Duration & measure_duration);

	Measure(const Measure& other);
	Measure(Measure&& other);

	Measure& operator=(const Measure& other);
	Measure& operator=(Measure&& other);

	~Measure();

	bool push_back(std::unique_ptr<MusicSymbol> music_symbol);

	friend std::ostream & operator << (std::ostream & os, const Measure & measure);

private:
	Duration measure_duration_;
	Duration current_duration_;
	std::vector<std::unique_ptr<MusicSymbol>> music_symbols_;
};

#endif	// end Measure.h
