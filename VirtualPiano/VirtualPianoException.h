#ifndef _VIRTUALPIANOEXCEPTION_H_
#define _VIRTUALPIANOEXCEPTION_H_
#include <exception>

class VirtualPianoException : public std::exception {
public:
	char const* what() const override;
};

class MeasureDurationOverflow : public VirtualPianoException {
public:
	char const* what() const override;
};

#endif
