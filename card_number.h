#ifndef _CARD_NUMBER_H_
#define _CARD_NUMBER_H_
#include "digit_sequence.h"

class CardNumber
{
	friend class Tester; // friend class only for tests
public:
	CardNumber();
	explicit CardNumber(const DigitSequence<16>&);
	CardNumber(const CardNumber&);
	~CardNumber();
	CardNumber& operator=(const CardNumber&);
	// add getter and setter because of DigitSequence realization
	void set(const size_t, const unsigned short);
	unsigned short get(const size_t) const;
private:
	DigitSequence<16> _number;
};
bool operator==(const CardNumber&, const CardNumber&);
bool operator!=(const CardNumber&, const CardNumber&);
std::ostream& operator<<(std::ostream&, const CardNumber&);
// > and < operators will be defined only for need

#endif // _CARD_NUMBER_H_