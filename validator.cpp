#include "validator.h"
#include <exception>

Validator::Validator(const size_t cardNumberLength, const size_t pinLength):
	_cardNumberLength(cardNumberLength), _pinLength(pinLength) {}

bool Validator::validateCardNumber(const char* cn, const size_t len, CardNumber*& p) const
{
	if(len != _cardNumberLength) return false;
	try {
		DigitSequence<16> ds(cn);
		p = new CardNumber(ds);
	} catch(const std::logic_error&) {
		p = 0;
		return false;
	}
	return true;
}

bool Validator::validatePin(const char* pin, const size_t len, Pin*& p) const
{
	if(len != _pinLength) return false;
	try {
		DigitSequence<4> ds(pin);
		p = new Pin(ds);
	} catch(const std::logic_error&) {
		p = 0;
		return false;
	}
	return true;
}

Validator::~Validator() {}