#ifndef _CardNumber_h_
#define _CardNumber_h_
#include "DigitSequence.h"

class CardNumber
{
	friend class Tester; // friend class only for tests
private:
	DigitSequence<16> _number;
public:
	CardNumber();
	CardNumber(const DigitSequence<16>&);
	CardNumber(const CardNumber&);
	~CardNumber();
	CardNumber& operator=(const CardNumber&);
	// add getter and setter because of DigitSequence realization
	void set(const size_t, const unsigned short);
	unsigned short get(const size_t) const;
};
bool operator==(const CardNumber&, const CardNumber&);
bool operator!=(const CardNumber&, const CardNumber&);
std::ostream& operator<<(std::ostream&, const CardNumber&);

// > and < operators will be defined only for need

#endif