#include "pin.h"
#define size 4

Pin::Pin(): _number(DigitSequence<size>()) {}

Pin::~Pin() {}

Pin::Pin(const DigitSequence<size>& ds): _number(ds) {}

Pin::Pin(const Pin& cn): _number(cn._number) {}

Pin& Pin::operator=(const Pin& cn)
{
	for(int i = 0; i < size; ++i)
		set(i, cn.get(i));
	return *this;
}

unsigned short Pin::get(const size_t i) const 
{
	return _number.get(i);
}

void Pin::set(const size_t i, const unsigned short digit)
{
	_number.set(i, digit);
}

bool operator==(const Pin& pin1, const Pin& pin2)
{
	for(int i = 0; i < size; ++i) {
		if(pin1.get(i) != pin2.get(i)) return false;
	}
	return true;
}

bool operator!=(const Pin& pin1, const Pin& pin2)
{
	return !(pin1 == pin2);
}

std::ostream& operator<<(std::ostream& os, const Pin& pin)
{
	for(size_t i = 0; i < size; ++i) {
		os << pin.get(i);
	}
	return os;
}