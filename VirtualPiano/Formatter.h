#ifndef _FORMATTER_H_
#define _FORMATTER_H_

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

	virtual void generate_output_file(const std::string out_file_path, const Composition<NumberOfParts> & composition) = 0;

	virtual ~Formatter() = default;
};

#endif
