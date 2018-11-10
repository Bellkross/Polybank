#ifndef VALIDATOR_H_
#define VALIDATOR_H_
#include "card_number.h"
#include "pin.h"

class Validator
{
	friend class Tester;
public:
	Validator(const size_t cardNumberLength = 16, const size_t pinLength = 4);
	bool validateCardNumber(const std::string&) const;
	bool validatePin(const std::string&) const;
	~Validator();
private:
	/* Validation rules */
	size_t _cardNumberLength;
	size_t _pinLength;
	/* Without realization */
	Validator(const Validator&);
	Validator& operator=(const Validator&);
};

#endif // VALIDATOR_H_