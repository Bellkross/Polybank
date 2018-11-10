#ifndef TESTER_H_
#define TESTER_H_
#include "server_access_layer.h"
#include "digit_sequence.h"
#include "card_number.h"
#include "pin.h"
#include "validator.h"
#include "atm.h"
#include "currency.h"
#include "account.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <cassert>
#include <vector>

class Tester {
public:
	void run();
	void manualTest();

private:
	void showTestResult(const bool passed, const std::string& msg);

	void digitSequenceTests();
	template <size_t size>
	bool digitSequenceTest();
	
	void cardNumberTests();
	bool cardNumberTest();
	
	void pinTests();
	bool pinTest();
	
	void validatorTests();
	bool validatorTest(const std::string&);

	void atmTests();
	bool atmReadTest();

	void currencyTests();
	bool currencyTest(const int unit, const int fraction);
	bool currencyCtorTest(const int unit, const int fraction);
	bool currencyCopyTest(const int unit, const int fraction);
	bool currencyAssignTest(const int unit, const int fraction);
	bool currencySetTest(const int unit, const int fraction);
	bool currencyComparisonTest();
	bool currencyMathTest();

	void accountTests();
};

void Tester::manualTest()
{
	Atm atm(std::cin, std::cout);
	atm.run();
}

void Tester::run()
{
	digitSequenceTests();
	cardNumberTests();
	pinTests();
	validatorTests();
	atmTests();
	currencyTests();
	accountTests();
}

void Tester::accountTests() {
	Person ow;
	ow._patronymic = "Shlepakova";
	ow._name = "Polina";
	ow._patronymic = "Dmytryevna";

	CardNumber cn1("1234567890123456");
	CardNumber cn2("1234567890654321");
	Pin p1("1234");
	Pin p2("0000");
	Currency b(1000, 25);
	Currency minus(200);
	Currency plus(1000);
	Currency bigger = b + b;

	Account a(cn1, p1, b, ow);
	bool res = true;
	res = a.owner()._name == ow._name && res;
	res = a.owner()._surname == ow._surname && res;
	res = a.owner()._patronymic == ow._patronymic && res;

	res = a.card() == cn1 && res;
	res = a.card() != cn2 && res;
	res = a.pin() == p1 && res;
	res = a.pin() != p2 && res;

	res = a.balance() == b && res;
	res = b > minus && res;
	res = !a.withdraw(bigger) && res;
	res = a.withdraw(minus) && res;
	res = a.balance() == (b - minus) && res;
	res = a.deposit(plus) && res;
	res = a.balance() == (b - minus + plus) && res;

	showTestResult(res, "account tests");
}

void Tester::atmTests()
{
#ifndef NDEBUG
	bool result = atmReadTest();
	std::cout << (result ? "[passed]" : "[failed]") << " atmReadTest" << std::endl;
	assert(result);
#endif // NDEBUG
}

bool Tester::atmReadTest()
{
	std::ifstream is;
	std::ofstream os;
	try {
		is.open("resources/test1.txt", std::fstream::in);
		os.open("resources/output.txt", std::fstream::out);
	} catch(std::iostream::failure&) {
		std::cout << "File opening or reading or closing exception while testing" << std::endl;
		return false;
	}
	Atm atm(is, os);
	try {
		DigitSequence<16> ds(atm.readCardNumber());
		CardNumber cn(ds);
	} catch (std::logic_error&) {
		return false;
	}

	is.close();
	os.close();
	return true;
}

void Tester::showTestResult(const bool passed, const std::string& msg)
{
#ifndef NDEBUG
	std::cout << (passed ? "[passed]" : "[failed]") << ' ' << msg << std::endl;
#endif // NDEBUG
	assert(passed);
}

void Tester::currencyTests()
{
	const size_t nUnits = 2;
	int units[nUnits] = {0, 10};
	const size_t nFractions = 5;
	int fractions[nFractions] = {30, 99, 100, 123, 789};
	bool res = false;
	for (size_t u = 0; u < nUnits; ++u) {
		for (size_t f = 0; f < nFractions; ++f) {
			res = currencyTest(units[u], fractions[f]);
#ifndef NDEBUG
			std::cout << (res ? "[passed]" : "[failed]") << " currencyTest with " << 
				units[u] << '.' << fractions[f] << std::endl;
#endif // NDEBUG
			assert(res);
		}
	}

	showTestResult(currencyComparisonTest(), "currency comparison test");
	showTestResult(currencyMathTest(), "currency math test");
}

bool Tester::currencyTest(const int unit, const int fraction)
{
	return	currencyCtorTest(unit, fraction) &&
			currencyCopyTest(unit, fraction) &&
			currencyAssignTest(unit, fraction) &&
			currencySetTest(unit, fraction);
}

bool Tester::currencyCtorTest(const int unit, const int fraction)
{
	bool res = true;
	Currency c(unit, fraction);
	
	res = c.fraction() < 100 && res;
	if (fraction < 100) {
		res = unit == c.unit() && fraction == c.fraction() && res;
	} else {
		res = unit + (fraction / 100) == c.unit() && res;
		res = fraction % 100 == c.fraction() && res;
	}

	Currency c3(unit);
	res = c3.fraction() == 0 && res;
	return res;
}

bool Tester::currencyCopyTest(const int unit, const int fraction)
{
	bool res = true;
	Currency c(unit, fraction);
	Currency cc(c);
	res = c.unit() == cc.unit() && res;
	res = c.fraction() == cc.fraction() && res;
	return res;
}

bool Tester::currencyAssignTest(const int unit, const int fraction)
{
	bool res = true;
	Currency c(unit, fraction);
	Currency cc(235253);
	cc = c;
	res = c.unit() == cc.unit() && res;
	res = c.fraction() == cc.fraction() && res;
	return res;
}

bool Tester::currencySetTest(const int unit, const int fraction)
{
	bool res = true;
	Currency c(unit, fraction);
	
	Currency cc(c);
	cc.setUnit(200);
	res = c.fraction() == cc.fraction() && res;
	
	cc = c;
	cc.setFraction(200);
	res = c.unit() < cc.unit() && res;
	res = unit + (fraction / 100) == c.unit() && res;
	res = fraction % 100 == c.fraction() && res;
	return res;
}

bool Tester::currencyComparisonTest()
{
	bool res = true;
	Currency c1(10, 50);
	Currency c2(10, 51);
	Currency c3(12, 10);

	res = (c1 == c1) && !(c1 == c2) && !(c1 == c3) && res;
	res = !(c1 != c1) && (c2 != c3) && (c2 != c3) && res;
	
	res = !(c1 < c1) && (c1 < c2) && !(c2 < c1) && (c1 < c3) && !(c3 < c2) && res;
	res = !(c1 > c1) && (c2 > c1) && !(c2 > c3) && !(c1 > c2) && (c3 > c1) && res;
	res = (c1 <= c2) && (c1 <= c2) && !(c2 <= c1) && (c1 <= c3) && !(c3 <= c2) && res;
	res = (c1 >= c1) && (c2 >= c1) && !(c2 >= c3) && !(c1 >= c2) && (c3 >= c1) && res;
	return res;
}

bool Tester::currencyMathTest()
{
	bool res = true;
	int u1 = 10, f1 = 35;
	int u2 = 10, f2 = 70;
	int u3 = 9, f3 = 60;
	Currency c1(u1, f1);
	Currency c2(u2, f2);
	Currency c3(u3, f3);

	res = (c1 + c2) == (c2 + c1) && res;
	Currency plus = c1 + c2;
	res = plus == (c1 += c2) && res;
	if (f1 + f2 < 100) {
		res = plus.unit() == u1 + u2 && res;
		res = plus.fraction() == f1 + f2 && res;
	} else {
		res = plus.unit() == u1 + u2 + 1 && res;
		res = plus.fraction() == f1 + f2 - 100 && res;
	}
	c1.setUnit(u1); 
	c1.setFraction(f1);
	
	try {
		c1 - c2;
		return false;
	} catch (std::logic_error&) {}

	try {
		c1 -= c2;
		return false;
	} catch (std::logic_error&) {}
	
	Currency minus = c1 - c3; 
	res = minus == (c1 -= c3) && res;
	if (f1 - f3 >= 0) {
		res = minus.unit() == u1 - u3 && res;
		res = minus.fraction() == f1 - f3 && res;
	} else {
		res = minus.unit() == u1 - u3 - 1 && res;
		res = minus.fraction() == f1 - f3 + 100 && res;
	}
	minus = c2 - c2;
	res = minus.unit() == 0 && minus.fraction() == 0 && res;
	return res;
}

void Tester::validatorTests()
{
	std::vector<std::string> v;
	v.push_back("013q");
	v.push_back("013");
	v.push_back("0123");
	v.push_back("0123456789012345");
	v.push_back("0123456789012345");
	v.push_back("Hello World!");
	for (int i = v.size() - 1; i >= 0; --i) {
#ifndef NDEBUG
		bool result = validatorTest(v[i]);
		std::cout << (result ? "[passed]" : "[failed]") << " validatorTest with " << v[i] << std::endl;
		assert(result);
#endif
		v.pop_back();
	}
}

bool Tester::validatorTest(const std::string& s)
{
	bool result = true;
	Validator v;
	const size_t kCardSize = 16;
	const size_t kPinSize = 4;
	if (v.validateCardNumber(s)) {
		DigitSequence<kCardSize> ds(s);
		CardNumber testCn(ds);
		result = !v.validatePin(s);
	} else {
		try {
			DigitSequence<kPinSize> ds(s); // can't catch exception here in the first test
			Pin testPin(ds);
			result = v.validatePin(s);
		} catch (std::invalid_argument&) {}
	}

	return result;
}

void Tester::digitSequenceTests()
{
	const size_t testCasesNumber = 9;
	bool results[testCasesNumber] = { 
		digitSequenceTest<0>(), digitSequenceTest<1>(), digitSequenceTest<2>(), digitSequenceTest<8>(),
		digitSequenceTest<10>(), digitSequenceTest<11>(), digitSequenceTest<15>(), digitSequenceTest<16>(),
		digitSequenceTest<100>() 
	};
	for (int i = 0; i < testCasesNumber; ++i) {
#ifndef NDEBUG
		bool res = results[i];
		std::cout << (res ? "[passed]" : "[failed]") << " digitSequenceTest " << i + 1 << std::endl;
		assert(res);
#endif // NDEBUG
	}
}

template <size_t size>
bool Tester::digitSequenceTest()
{
	if(size == 0) { // Must throw logic_error if digitSequence size == 0
		try {
			DigitSequence<size> ds;
			return false;
		} catch (std::logic_error&) {
			return true;
		}
	}

	try {
		std::string bad = "";
		DigitSequence<size> ds0(bad);
		return false;
	} catch (std::invalid_argument&) {}

	try {
		const unsigned short* undefinedPtr = 0;
		DigitSequence<size> ds0(undefinedPtr);
		return false;
	} catch (std::invalid_argument&) {}

	try {
		const char* undefinedPtr = 0;
		DigitSequence<size> ds0(undefinedPtr);
		return false;
	} catch (std::invalid_argument&) {}

	try {
		char* invalidCstr = new char[size];
		for(int i = 0; i < size; ++i) {
			invalidCstr[i] = '?';
		}

		DigitSequence<size> ds0(invalidCstr);
		return false;
	} catch (std::invalid_argument&) {}

	char* validCstr = new char[size];
	std::string validStr = std::string(new char[size], size);
	for(int i = 0; i < size; ++i) {
		validCstr[i] = '1';
		validStr[i] = '1';
	}


	try {
		DigitSequence<size> ds0(validCstr); // constructor by char* test case 1
	} catch (std::invalid_argument e) {
		return false;
	}

	try {
		DigitSequence<size> ds0(validStr); // constructor by std::string test case 1
	}
	catch (std::invalid_argument e) {
		return false;
	}
	
	DigitSequence<size> ds1(validCstr); // constructor by char* test case 2
	DigitSequence<size> dsStl1(validStr); // constructor by std::struing test case 2
	DigitSequence<size> ds2;
	DigitSequence<size> dsStl2;
	ds1=ds2;
	dsStl1 = dsStl2;

	for(int i = 0; i < size; i++) {
		ds1.get(i % 10); // access to each digit without exceptions
		dsStl1.get(i % 10);
		ds2.set(i, i % 10); // the same
		dsStl2.set(i, i % 10);
	}

	try {
		dsStl1.get(size + 1);
		return false;
	}
	catch (std::out_of_range e) {}

	try {
		dsStl1.get(-1);
		return false;
	}
	catch (std::out_of_range e) {}

	try {
		dsStl1.set(size + 1, -1);
		return false;
	}
	catch (std::out_of_range e) {}

	try {
		dsStl1.set(-1, 1);
		return false;
	}
	catch (std::out_of_range e) {}

	try {
		dsStl1.set(0, 12);
		return false;
	}
	catch (std::invalid_argument e) {}

	try {
		dsStl1.set(0, -1);
		return false;
	}
	catch (std::invalid_argument e) {}

	try {
		ds1.get(size + 1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		ds1.get(-1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		ds1.set(size + 1, -1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		ds1.set(-1,1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		ds1.set(0,12);
		return false;
	} catch(std::invalid_argument&) {}

	try {
		ds1.set(0,-1);
		return false;
	} catch(std::invalid_argument&) {}

	// equality operator test

	DigitSequence<size> ds3;
	for(int i = 0; i < size; ++i) {
		if(ds1.get(i) != ds3.get(i) || ds1.get(i) != dsStl1.get(i)) return false;
	}

	if(ds1._numbers == ds3._numbers) return false;
	if(ds1._numbers == dsStl1._numbers) return false;
	if(ds1 != ds3) return false;
	if(size > 1 && ds3 == ds2) return false;
	if(ds1 != ds1) return false;
	if(dsStl1 != dsStl1) return false;
	if(ds1 != dsStl1) return false;

	// assignment operator test

	ds1 = ds1;
	dsStl1 = dsStl1;

	if(ds1._numbers != ds1._numbers) return false;
	if(dsStl1._numbers != dsStl1._numbers) return false;

	if(ds1 != ds1) return false;
	if(dsStl1 != dsStl1) return false;

	ds1 = ds2;
	dsStl1 = dsStl2;

	if(ds1._numbers == ds2._numbers) return false;
	if(dsStl1._numbers == dsStl2._numbers) return false;
	if(ds1 != ds2) return false;
	if(dsStl1 != dsStl2) return false;

	// Copy constructor test

	DigitSequence<size> ds4(ds1);
	DigitSequence<size> dsStl4(dsStl1);

	if(dsStl1._numbers == dsStl4._numbers) return false;
	if(ds1._numbers == ds4._numbers) return false;
	if(dsStl1._numbers == ds4._numbers) return false;
	if(dsStl1._numbers == ds1._numbers) return false;

	if(ds1 != ds4) return false;
	if(dsStl1 != dsStl4) return false;
	if(ds1 != dsStl1) return false;
	if(ds1 != dsStl4) return false;

	// And if all the stars came together
	return true;
}

void Tester::cardNumberTests()
{
	bool result = true;
	result = cardNumberTest();
#ifndef NDEBUG
	std::cout << (result ? "[passed]" : "[failed]") << " cardNumberTest" << std::endl;
	assert(result);
#endif // NDEBUG
}

bool Tester::cardNumberTest()
{
	const size_t cardNumbersSize = 16;
	// Constructor and destructor tests
	{ 
		CardNumber cn; 
	}
	
	DigitSequence<cardNumbersSize> ds0;
	CardNumber cn0(ds0);

	for(size_t i = 0; i < cardNumbersSize; ++i) {
		if(cn0.get(i) != ds0.get(i)) return false;
	}
	
	DigitSequence<16> ds1;
	for(size_t i = 0; i < cardNumbersSize; ++i) {
		ds1.set(i,(cardNumbersSize-i)%10);
	}
	CardNumber cn1(ds1);

	for(size_t i = 0; i < cardNumbersSize; ++i) {
		if(cn1.get(i)!=ds1.get(i)) return false;
	}
	
	try {
		cn1.get(cardNumbersSize+1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		cn1.get(-1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		cn1.set(cardNumbersSize + 1, -1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		cn1.set(-1,1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		cn1.set(0,12);
		return false;
	} catch(std::invalid_argument&) {}

	try {
		cn1.set(0,-1);
		return false;
	} catch(std::invalid_argument&) {}


	// Copy constructor and assignment operator test
	CardNumber cn3(cn1);
	CardNumber cn4 = cn1;

	for(size_t i = 0; i < cardNumbersSize; ++i) {
		if(cn3.get(i) != cn4.get(i) && cn1.get(i) != cn3.get(i)) return false;
	}

	return (cn3 == cn4 || cn1 == cn3 || cn0 != cn1); // Equality operator test
}

void Tester::pinTests()
{
	bool result = true;
	result = pinTest();
#ifndef NDEBUG
	std::cout << (result ? "[passed]" : "[failed]") << " pinTest" << std::endl;
	assert(result);
#endif // NDEBUG
}

bool Tester::pinTest()
{
	const size_t pinsSize = 4;
	// Constructor and destructor tests
	{ 
		Pin pin; 
	}
	
	DigitSequence<pinsSize> ds0;
	Pin pin0(ds0);

	for(size_t i = 0; i < pinsSize; ++i) {
		if(pin0.get(i) != ds0.get(i)) return false;
	}
	
	DigitSequence<4> ds1;
	for(size_t i = 0; i < pinsSize; ++i) {
		ds1.set(i,(pinsSize-i)%10);
	}
	Pin pin1(ds1);

	for(size_t i = 0; i < pinsSize; ++i) {
		if(pin1.get(i)!=ds1.get(i)) return false;
	}
	
	try {
		pin1.get(pinsSize+1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		pin1.get(-1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		pin1.set(pinsSize + 1, -1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		pin1.set(-1,1);
		return false;
	} catch(std::out_of_range&) {}

	try {
		pin1.set(0,12);
		return false;
	} catch(std::invalid_argument&) {}

	try {
		pin1.set(0,-1);
		return false;
	} catch(std::invalid_argument&) {}


	// Copying constructor and assignment operator test
	Pin pin3(pin1);
	Pin pin4 = pin1;

	for(size_t i = 0; i < pinsSize; ++i) {
		if(pin3.get(i) != pin4.get(i) && pin1.get(i) != pin3.get(i)) return false;
	}

	return (pin3 == pin4 || pin1 == pin3 || pin0 != pin1); // Equality operator test
}

#endif // TESTER_H_