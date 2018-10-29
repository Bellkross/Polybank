#ifndef _Tester_h_
#define _Tester_h_
#include "DigitSequence.h"
#include <iostream>
#include <exception>
#include <cassert>

class Tester {

public:

	void run()
	{
		digitSequenceTests();
	}

private:

	void digitSequenceTests()
	{
		bool result = true;
#ifndef NDEBUG
		result = digitSequenceTest<0>();
		std::cout << (result ? "[passed]" : "[failed]") << " digitSequenceTest<0>" << std::endl;
		assert(result);
#endif
#ifndef NDEBUG
		result = digitSequenceTest<1>();
		std::cout << (result ? "[passed]" : "[failed]") << " digitSequenceTest<1>" << std::endl;
		assert(result);
#endif
#ifndef NDEBUG
		result = digitSequenceTest<2>();
		std::cout << (result ? "[passed]" : "[failed]") << " digitSequenceTest<2>" << std::endl;
		assert(result);
#endif
#ifndef NDEBUG
		result = digitSequenceTest<10>();
		std::cout << (result ? "[passed]" : "[failed]") << " digitSequenceTest<10>" << std::endl;
		assert(result);
#endif
#ifndef NDEBUG
		result = digitSequenceTest<11>();
		std::cout << (result ? "[passed]" : "[failed]") << " digitSequenceTest<11>" << std::endl;
		assert(result);
#endif
#ifndef NDEBUG
		result = digitSequenceTest<15>();
		std::cout << (result ? "[passed]" : "[failed]") << " digitSequenceTest<15>" << std::endl;
		assert(result);
#endif
#ifndef NDEBUG
		result = digitSequenceTest<16>();
		std::cout << (result ? "[passed]" : "[failed]") << " digitSequenceTest<16>" << std::endl;
		assert(result);
#endif
	}

	template <size_t size>
	bool digitSequenceTest()
	{
		if(size == 0) // Must throw logic_error if digitSequence size == 0
		{
			try {
				DigitSequence<size> ds;
				return false;
			} catch (std::logic_error e) {
				return true;
			}
		}

		DigitSequence<size> ds1;
		DigitSequence<size> ds2;

		for(int i = 0; i < size; i++) {
			ds1.get(i%10); // acces to each digit without exceptions
			ds2.set(i,i%10); // the same
		}

		try {
			ds1.get(size+1);
			return false;
		} catch(std::out_of_range e) {
			// not implemented, test case
		}

		try {
			ds1.get(-1);
			return false;
		} catch(std::out_of_range e) {
			// not implemented, test case		
		}

		try {
			ds1.set(size + 1, -1);
			return false;
		} catch(std::out_of_range e) {
			// not implemented, test case		
		}

		try {
			ds1.set(-1,1);
			return false;
		} catch(std::out_of_range e) {
			// not implemented, test case		
		}

		try {
			ds1.set(0,12);
			return false;
		} catch(std::invalid_argument e) {
			// not implemented, test case		
		}

		try {
			ds1.set(0,-1);
			return false;
		} catch(std::invalid_argument e) {
			// not implemented, test case		
		}

		// equality operator test

		DigitSequence<size> ds3;
		for(int i = 0; i < size; i++) 
			if( ds1.get(i) != ds3.get(i) )
				return false;

		if(ds1._numbers == ds3._numbers)
			return false;
		if(ds1!=ds3)
			return false;
		if(size > 1 && ds3==ds2)
			return false;

		if(ds1!=ds1)
			return false;

		// assginment operator test

		ds1 = ds1;

		if(ds1._numbers != ds1._numbers)
			return false;

		if(ds1 != ds1)
			return false;

		ds1 = ds2;

		if(ds1._numbers == ds2._numbers)
			return false;
		if (ds1 != ds2)
			return false;

		// Copying constructor test

		DigitSequence<size> ds4(ds1);

		if(ds1._numbers == ds4._numbers)//here
			return false;

		if(ds1 != ds4)
			return false;

		// And if all the stars came together
		return true;
	}

};

#endif