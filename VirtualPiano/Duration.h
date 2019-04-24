#ifndef _DURATION_H_
#define _DURATION_H_

class Duration {
public:
	Duration(const unsigned numerator, const unsigned denominator);

	friend bool operator < (const Duration &d1, const Duration &d2);
	friend bool operator > (const Duration &d1, const Duration &d2);
	friend bool operator != (const Duration &d1, const Duration &d2);
	friend bool operator == (const Duration &d1, const Duration &d2);

private:
	unsigned numerator_;
	unsigned denominator_;
};

#endif	// end Duration.h
