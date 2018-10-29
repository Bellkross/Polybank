#ifndef _DigitSequence_h_
#define _DigitSequence_h_
#include <exception>
#include <iostream>

/*
 * Class for card number and pin representation
 * size always > 0
 */
template <size_t size>
class DigitSequence
{
	// friend function only for tests
	friend class Tester;
private:
	unsigned short* _numbers;

public:

	DigitSequence(): _numbers(new unsigned short[size])
	{
		if( size < 1)
			throw std::logic_error("Incorrect size error");

		for(int i = 0; i < size; i++)
			_numbers[i] = 0;
	}

	// Copying constructor
	DigitSequence(const DigitSequence<size>& ds): _numbers(new unsigned short[size])
	{
		for(int i = 0; i < size; i++)
			_numbers[i] = ds.get(i);
	}

	// Assignment operator
	DigitSequence<size>& operator=(const DigitSequence<size>& ds)
	{
		if(_numbers == ds._numbers)
			return *this;
		for(int i = 0; i < size; i++)
			_numbers[i] = ds.get(i);
		return *this;
	}

	~DigitSequence()
	{
		delete[] _numbers;
	}

	// We need setter, because we have to control input digits
	void set(const size_t i, const unsigned short digit)
	{
		if(i >= size)
			throw std::out_of_range("Index more or equals than size");
		if(digit > 9)
			throw std::invalid_argument("Incorrect digit value");

		_numbers[i] = digit;
	}

	// If we have setter - let's create getter
	unsigned short get(const size_t i) const
	{
		if(i >= size)
			throw std::out_of_range("Index more or equals than size");
		return _numbers[i];
	}
};

template <size_t size>
bool operator==(const DigitSequence<size>& ds1, const DigitSequence<size>& ds2)
{
	for(int i = 0; i < size; i++)
		if(ds1.get(i)!=ds2.get(i))
			return false;
	return true;
}

template <size_t size>
bool operator!=(const DigitSequence<size>& ds1, const DigitSequence<size>& ds2)
{
	return !(ds1==ds2);
}

template <size_t size>
std::ostream& operator<<(std::ostream& os, const DigitSequence<size>& ds)
{
	for(int i = 0; i < size; i++)
		os << ds.get(i);
	return os;
}

// opreator > and operator < will be defined only for need
	 
#endif