#ifndef _FORMATTER_H_
#define _FORMATTER_H_

#include <string>
#include <fstream>

#include "Composition.h"

template <unsigned NumberOfParts = composition::default_number_of_parts>
class Formatter {
public:
	Formatter() = default;

	Formatter(const Formatter & other) = default;
	Formatter(Formatter && other) = default;

	Formatter& operator = (const Formatter & other) = default;
	Formatter& operator = (Formatter && other) = default;

	virtual std::string to_string(const Composition<NumberOfParts> & composition) const = 0;

	void output_to_file(std::ofstream & file, const Composition<NumberOfParts> & composition) const;

	virtual ~Formatter() = default;
};

template <unsigned NumberOfParts>
void Formatter<NumberOfParts>::output_to_file(std::ofstream& file, const Composition<NumberOfParts>& composition) const {
	file << this->to_string(composition);
}

#endif
