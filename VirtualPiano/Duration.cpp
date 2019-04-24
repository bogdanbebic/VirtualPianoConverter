#include "Duration.h"

Duration::Duration(const unsigned numerator, const unsigned denominator)
	: numerator_(numerator)
	, denominator_(denominator)
{
	// empty body
}

bool operator<(const Duration &d1, const Duration &d2) {
	return d1.numerator_ * d2.denominator_ < d2.numerator_ * d1.denominator_;
}

bool operator>(const Duration &d1, const Duration &d2) {
	return d1.numerator_ * d2.denominator_ > d2.numerator_ * d1.denominator_;
}

bool operator!=(const Duration & d1, const Duration & d2) {
	return d1.numerator_ * d2.denominator_ != d2.numerator_ * d1.denominator_;
}

bool operator==(const Duration & d1, const Duration & d2) {
	return d1.numerator_ * d2.denominator_ == d2.numerator_ * d1.denominator_;
}
