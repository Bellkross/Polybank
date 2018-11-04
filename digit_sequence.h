#ifndef DIGIT_SEQUENCE_H_
#define DIGIT_SEQUENCE_H_
#include <exception>
#include <iostream>

/**
* Class for card number and pin representation
* size must be more than 0
* digit bounds: [0;9]
*/
template <size_t size>
class DigitSequence
{
	friend class Tester; // friend class only for tests
private:
	unsigned short* _numbers;
public:
	DigitSequence();
	explicit DigitSequence(const char*);
	explicit DigitSequence(const unsigned short*);
	DigitSequence(const DigitSequence<size>&); // Copying constructor
	DigitSequence<size>& operator=(const DigitSequence<size>&); // Assignment operator
	~DigitSequence();
	void set(const size_t, const unsigned short); // We need setter, because we have to control input digits
	unsigned short get(const size_t) const; // Add getter in pair with the necessary setter instead of operator[]
};
template <size_t size>
bool operator==(const DigitSequence<size>&, const DigitSequence<size>&);
template <size_t size>
bool operator!=(const DigitSequence<size>&, const DigitSequence<size>&);
template <size_t size>
std::ostream& operator<<(std::ostream&, const DigitSequence<size>&);

// > and < operators will be defined only for need

/* Digit Sequence implementation */

template <size_t size>
DigitSequence<size>::DigitSequence(): _numbers(new unsigned short[size])
{
	if( size < 1) throw std::logic_error("Incorrect size error");
}

template <size_t size>
DigitSequence<size>::DigitSequence(const char* numbers): _numbers(new unsigned short[size])
{
	if( size < 1) throw std::logic_error("Incorrect size error");
	if(numbers == 0) throw std::invalid_argument("Attempt to use undefined pointer");
	int zeroPos = '0'; // position of 0 in ASCII table
	for(int i = 0; i < size; ++i) {
		set(i, numbers[i] - zeroPos); // char - zeroPos = char integer representation
	}								  // if this char located between '0' and '9'
}


template <size_t size>
DigitSequence<size>::DigitSequence(const unsigned short* numbers): _numbers(new unsigned short[size])
{
	if(size < 1) throw std::logic_error("Incorrect size error");
	if(numbers == 0) throw std::invalid_argument("Attempt to use undefined pointer");

	for(int i = 0; i < 0; ++i) {
		set(i, numbers[i]);
	}
}

template <size_t size>
DigitSequence<size>::DigitSequence(const DigitSequence<size>& ds): _numbers(new unsigned short[size])
{
	for(int i = 0; i < size; ++i) {
		_numbers[i] = ds.get(i);
	}
}

template <size_t size>
DigitSequence<size>& DigitSequence<size>::operator=(const DigitSequence<size>& ds)
{
	if(_numbers == ds._numbers) return *this;
	for(int i = 0; i < size; ++i) {
		_numbers[i] = ds.get(i);
	}
	return *this;
}

template <size_t size>
DigitSequence<size>::~DigitSequence()
{
	delete[] _numbers;
}

template <size_t size>
void DigitSequence<size>::set(const size_t i, const unsigned short digit)
{
	if(i >= size) throw std::out_of_range("Index more or equals than size");
	if(digit > 9) throw std::invalid_argument("Incorrect digit value");

	_numbers[i] = digit;
}

template <size_t size>
unsigned short DigitSequence<size>::get(const size_t i) const
{
	if(i >= size) throw std::out_of_range("Index more or equals than size");
	return _numbers[i];
}

/* Utills */

template <size_t size>
bool operator==(const DigitSequence<size>& ds1, const DigitSequence<size>& ds2)
{
	for(int i = 0; i < size; ++i) {
		if(ds1.get(i) != ds2.get(i)) return false;
	}
	return true;
}

template <size_t size>
bool operator!=(const DigitSequence<size>& ds1, const DigitSequence<size>& ds2)
{
	return !(ds1 == ds2);
}

template <size_t size>
std::ostream& operator<<(std::ostream& os, const DigitSequence<size>& ds)
{
	for(int i = 0; i < size; i++) {
		os << ds.get(i);
	}
	return os;
}
#endif // DIGIT_SEQUENCE_H_