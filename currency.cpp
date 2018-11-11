/*****************************
 * Author: Polina Shlepakova *
 *****************************/

#include "currency.h"

const unsigned int Currency::kFractionsInUnit = 100;

Currency::Currency(unsigned int unit, unsigned int fraction): 
	_unit(unit), _fraction(fraction)
{
	normalize();
}

Currency::Currency(const Currency& c): 
	_unit(c.unit()), _fraction(c.fraction())
{}

Currency& Currency::operator=(const Currency& c)
{
	_unit = c.unit();
	_fraction = c.fraction();
	return *this;
}

Currency::~Currency() {}

unsigned int Currency::unit() const {return _unit;}
unsigned int Currency::fraction() const {return _fraction;}

void Currency::setUnit(unsigned int unit) {
	_unit = unit;
}

void Currency::setFraction(unsigned int fraction) {
	_fraction = fraction;
	normalize();
}

void Currency::normalize() {
	_unit += fraction() / kFractionsInUnit;
	_fraction %= kFractionsInUnit;
}

const Currency operator+(const Currency& c1, const Currency& c2)
{
	Currency res(c1);
	return res += c2;
}

const Currency operator-(const Currency& c1, const Currency& c2)
{
	Currency res(c1);
	return res -= c2;
}

const Currency& operator+=(Currency& c1, const Currency& c2)
{
	c1.setUnit(c1.unit() + c2.unit());
	c1.setFraction(c1.fraction() + c2.fraction());
	return c1;
}

const Currency& operator-=(Currency& c1, const Currency& c2)
{
	if (c1 < c2) {
		throw std::logic_error("Negative value");
	}
	int unit = c1.unit() - c2.unit();
	int fract = c1.fraction() - c2.fraction();
	if (fract < 0) {
		--unit;
		fract += Currency::kFractionsInUnit;
	}
	c1.setUnit(unit);
	c1.setFraction(fract);
	return c1;
}

bool operator==(const Currency& c1, const Currency& c2)
{
	return c1.unit() == c2.unit() && c1.fraction() == c2.fraction();
}

bool operator!=(const Currency& c1, const Currency& c2)
{
	return !(c1 == c2);
}

bool operator<(const Currency& c1, const Currency& c2)
{
	if (c1.unit() != c2.unit()) {
		return c1.unit() < c2.unit();
	}
	return c1.fraction() < c2.fraction();
}

bool operator>(const Currency& c1, const Currency& c2)
{
	return c2 < c1;
}

bool operator<=(const Currency& c1, const Currency& c2)
{
	return c1 == c2 ? true : c1 < c2;
}

bool operator>=(const Currency& c1, const Currency& c2)
{
	return c2 <= c1;
}

std::ostream& operator<<(std::ostream& os, const Currency& c) {
	return os << c.unit() << '.' << c.fraction();
}