#include "card_number.h"
#define cardlen 16 

CardNumber::CardNumber(): _number(DigitSequence<cardlen>()) {}

CardNumber::CardNumber(const char* pc): _number(DigitSequence<cardlen>(pc)) {}

CardNumber::CardNumber(const std::string& s): _number(DigitSequence<cardlen>(s)) {}

CardNumber::CardNumber(const unsigned short* arr): _number(DigitSequence<cardlen>(arr)) {}

CardNumber::~CardNumber() {}

CardNumber::CardNumber(const DigitSequence<cardlen>& ds): _number(ds) {}

CardNumber::CardNumber(const CardNumber& cn): _number(cn._number) {}

CardNumber& CardNumber::operator=(const CardNumber& cn)
{
	for(int i = 0; i < cardlen; ++i)
		set(i, cn.get(i));
	return *this;
}

unsigned short CardNumber::get(const size_t i) const 
{
	return _number.get(i);
}

void CardNumber::set(const size_t i, const unsigned short digit)
{
	_number.set(i, digit);
}

bool operator==(const CardNumber& cn1, const CardNumber& cn2)
{
	for (int i = 0; i < cardlen; ++i) {
		if (cn1.get(i) != cn2.get(i)) return false;
	}
	return true;
}

bool operator!=(const CardNumber& cn1, const CardNumber& cn2)
{
	return !(cn1 == cn2);
}

bool operator<(const CardNumber& cn1, const CardNumber& cn2)
{
	for (int i = 0; i < cardlen; ++i) {
		if (cn1.get(i) != cn2.get(i)) {
			return cn1.get(i) < cn2.get(i);
		}
	}
	assert(cn1 == cn2);
	return false;
}

bool operator>(const CardNumber& cn1, const CardNumber& cn2)
{
	return cn2 < cn1;
}

bool operator<=(const CardNumber& cn1, const CardNumber& cn2)
{
	return cn1 == cn2 ? true : cn1 < cn2;
}

bool operator>=(const CardNumber& cn1, const CardNumber& cn2)
{
	return cn2 <= cn1;
}

std::ostream& operator<<(std::ostream& os, const CardNumber& cn)
{
	for(size_t i = 0; i < cardlen; ++i) {
		os << cn.get(i);
	}
	return os;
}