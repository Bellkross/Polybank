/****************************
 * Author: Vasylenko Kyrylo *
 ****************************/

#ifndef PIN_H_
#define PIN_H_
#include "digit_sequence.h"

class Pin 
{
	friend class Tester;
public:
	Pin();
	explicit Pin(const DigitSequence<4>&);
	explicit Pin(const char*);
	explicit Pin(const std::string&);
	explicit Pin(const unsigned short*);
	Pin(const Pin&);
	~Pin();
	Pin& operator=(const Pin&);
	/* Add getter and setter because of DigitSequence realization */
	void set(const size_t, const unsigned short);
	unsigned short get(const size_t) const;
private:
	DigitSequence<4> _number;
};
bool operator==(const Pin&, const Pin&);
bool operator!=(const Pin&, const Pin&);
std::ostream& operator<<(std::ostream&, const Pin&);

#endif // PIN_H_