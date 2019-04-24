#ifndef _MEASURE_H_
#define _MEASURE_H_

#include <vector>
#include "MusicSymbol.h"

class Measure {
public:
	explicit Measure(const Duration & measure_duration);

	Measure(const Measure& other);
	Measure(Measure&& other);

	Measure& operator=(const Measure& other);
	Measure& operator=(Measure&& other);

	~Measure();

	void push_back(const MusicSymbol & music_symbol);

private:
	Duration measure_duration_;
	Duration current_duration_;
	std::vector<MusicSymbol*> music_symbols_;
};

#endif	// end Measure.h
