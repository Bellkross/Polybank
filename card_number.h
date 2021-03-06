/****************************
 * Author: Vasylenko Kyrylo *
 ****************************/

#ifndef CARD_NUMBER_H_
#define CARD_NUMBER_H_
#include "digit_sequence.h"
#include <cassert>

class CardNumber
{
	friend class Tester;
public:
	CardNumber();
	explicit CardNumber(const DigitSequence<16>&);
	explicit CardNumber(const char*);
	explicit CardNumber(const std::string&);
	explicit CardNumber(const unsigned short*);
	CardNumber(const CardNumber&);
	~CardNumber();
	CardNumber& operator=(const CardNumber&);
	/* add getter and setter because of DigitSequence realization */
	void set(const size_t i, const unsigned short digit);
	unsigned short get(const size_t i) const;
private:
	DigitSequence<16> _number;
};

bool operator==(const CardNumber&, const CardNumber&);
bool operator!=(const CardNumber&, const CardNumber&);

bool operator<(const CardNumber&, const CardNumber&);
bool operator>(const CardNumber&, const CardNumber&);
bool operator<=(const CardNumber&, const CardNumber&);
bool operator>=(const CardNumber&, const CardNumber&);

std::ostream& operator<<(std::ostream&, const CardNumber&);

#endif // CARD_NUMBER_H_