#include "validator.h"
#include <exception>

Validator::Validator(const size_t cardNumberLength, const size_t pinLength):
	_cardNumberLength(cardNumberLength), _pinLength(pinLength) {}

bool Validator::validateCardNumber(const std::string& cn) const
{
	if (cn.length() != _cardNumberLength) return false;
	try {
		DigitSequence<16> ds(cn);
	} catch (const std::logic_error&) {
		return false;
	}
	return true;
}

bool Validator::validatePin(const std::string& pin) const
{
	if (pin.length() != _pinLength) return false;
	try {
		DigitSequence<4> ds(pin);
	} catch (const std::logic_error&) {
		return false;
	}
	return true;
}

Validator::~Validator() {}