#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "MusicSymbol.h"

class Pause : public MusicSymbol {
public:
	explicit Pause(const Duration & duration);

	std::string to_string() const override;

	std::unique_ptr<MusicSymbol> clone() const override;
	
	friend std::ostream & operator << (std::ostream & os, const Pause & pause);

	std::string to_mxml() override;
};

#endif	// end Pause.h
