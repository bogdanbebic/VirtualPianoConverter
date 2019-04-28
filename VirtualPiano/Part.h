#ifndef _PART_H_
#define _PART_H_

#include <iostream>
#include <vector>
#include "Measure.h"
#include "MusicSymbol.h"

class Part {
public:
	explicit Part(const Duration & measure_duration);

	void push_back(const Measure & measure);
	void push_back(Measure && measure);
	bool push_back(std::unique_ptr<MusicSymbol> music_symbol);

	friend std::ostream & operator << (std::ostream & os, const Part & part);

private:
	Duration measure_duration_;
	std::vector<Measure> measures_;
};

#endif
