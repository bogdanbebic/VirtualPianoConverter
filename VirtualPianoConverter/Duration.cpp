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

Duration & Duration::operator+=(const Duration & other) {
	const auto ret = *this + other;
	this->numerator_ = ret.numerator_;
	this->denominator_ = ret.denominator_;
	return *this;
}

unsigned Duration::numerator() const {
	return this->numerator_;
}

unsigned Duration::denominator() const {
	return this->denominator_;
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

Duration operator+(const Duration & d1, const Duration & d2) {
	auto den = Duration::lcm(d1.denominator_, d2.denominator_);
	auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	auto num = d1.numerator_ * (d2.denominator_ / greatest_common_divisor)
		+ d2.numerator_ * (d1.denominator_ / greatest_common_divisor);

	greatest_common_divisor = Duration::gcd(num, den);
	if (greatest_common_divisor != 1) {
		num /= greatest_common_divisor;
		den /= greatest_common_divisor;
	}

	return Duration(num, den);
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

bool operator<=(const Duration & d1, const Duration & d2) {
	const auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	return d1.numerator_ * (d2.denominator_ / greatest_common_divisor)
		<= d2.numerator_ * (d1.denominator_ / greatest_common_divisor);
}

bool operator>=(const Duration & d1, const Duration & d2) {
	const auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	return d1.numerator_ * (d2.denominator_ / greatest_common_divisor)
		>= d2.numerator_ * (d1.denominator_ / greatest_common_divisor);
}

std::ostream & operator<<(std::ostream & os, const Duration & duration) {
	os << duration.numerator_ << "/" << duration.denominator_;
	return os;
}

Duration Duration::abs_difference(const Duration & d1, const Duration & d2) {
	const auto denominator = Duration::lcm(d1.denominator_, d2.denominator_);
	const auto greatest_common_divisor = Duration::gcd(d1.denominator_, d2.denominator_);
	const auto num1 = d1.numerator_ * (d2.denominator_ / greatest_common_divisor);
	const auto num2 = d2.numerator_ * (d1.denominator_ / greatest_common_divisor);
	const auto numerator = num1 >= num2 ? num1 - num2 : num2 - num1;
	return Duration(numerator, denominator);
}
