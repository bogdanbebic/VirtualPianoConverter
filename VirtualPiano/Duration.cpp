#include "Duration.h"

Duration::Duration(const unsigned numerator, const unsigned denominator)
	: numerator_(numerator)
	, denominator_(denominator)
{
	const auto greatest_common_divisor = gcd(numerator, denominator);
	if (greatest_common_divisor != 1) {
		this->numerator_ /= greatest_common_divisor;
		this->denominator_ /= greatest_common_divisor;
	}

}

unsigned Duration::gcd(const unsigned a, const unsigned b) {
	if (b == 0) {
		return a;
	}

	return gcd(b, a % b);
}

unsigned Duration::lcm(const unsigned a, const unsigned b) {
	// division first, to avoid overflow
	return a * (b / gcd(a, b));
}

bool operator<(const Duration &d1, const Duration &d2) {
	const auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	return d1.numerator_ * (d2.denominator_ / greatest_common_divisor)
		< d2.numerator_ * (d1.denominator_ / greatest_common_divisor);
}

bool operator>(const Duration &d1, const Duration &d2) {
	const auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	return d1.numerator_ * (d2.denominator_ / greatest_common_divisor)
		> d2.numerator_ * (d1.denominator_ / greatest_common_divisor);
}

bool operator!=(const Duration & d1, const Duration & d2) {
	const auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	return d1.numerator_ * (d2.denominator_ / greatest_common_divisor)
		!= d2.numerator_ * (d1.denominator_ / greatest_common_divisor);
}

bool operator==(const Duration & d1, const Duration & d2) {
	const auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	return d1.numerator_ * (d2.denominator_ / greatest_common_divisor)
		== d2.numerator_ * (d1.denominator_ / greatest_common_divisor);
}
