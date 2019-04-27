#ifndef _DURATION_H_
#define _DURATION_H_

#include <iostream>

class Duration {
public:
	explicit Duration(const unsigned numerator, const unsigned denominator);

	friend Duration operator + (const Duration &d1, const Duration &d2);

	friend bool operator < (const Duration &d1, const Duration &d2);
	friend bool operator > (const Duration &d1, const Duration &d2);
	friend bool operator != (const Duration &d1, const Duration &d2);
	friend bool operator == (const Duration &d1, const Duration &d2);
	friend bool operator <= (const Duration &d1, const Duration &d2);
	friend bool operator >= (const Duration &d1, const Duration &d2);

	friend std::ostream & operator << (std::ostream & os, const Duration & duration);

	friend Duration abs_difference(const Duration &d1, const Duration &d2);

	Duration & operator += (const Duration &other);

private:

	static unsigned gcd(const unsigned a, const unsigned b);
	static unsigned lcm(const unsigned a, const unsigned b);

	unsigned numerator_;
	unsigned denominator_;
};

#endif	// end Duration.h
