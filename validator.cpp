#include "validator.h"
#include <exception>

Validator::Validator(const size_t cardNumberLength, const size_t pinLength):
	_cardNumberLength(cardNumberLength), _pinLength(pinLength) {}

bool Validator::validateCardNumber(const std::string& cn, CardNumber*& p) const
{
	if (cn.length() != _cardNumberLength) return false;
	try {
		DigitSequence<16> ds(cn);
		p = new CardNumber(ds);
	}
	catch (const std::logic_error&) {
		p = 0;
		return false;
	}
	return true;
}

bool Validator::validatePin(const std::string& pin, Pin*& p) const
{
	if (pin.length() != _pinLength) return false;
	try {
		DigitSequence<4> ds(pin);
		p = new Pin(ds);
	}
	catch (const std::logic_error&) {
		p = 0;
		return false;
	}
	return true;
}

Validator::~Validator() {}