#ifndef CURRENCY_H_
#define CURRENCY_H_
#include <exception>
#include <string>

class Currency
{
public:
	static const unsigned int kFractionsInUnit;

	explicit Currency(unsigned int unit, unsigned int fraction = 0);
	Currency(const Currency&);
	~Currency();
	Currency& operator=(const Currency&);

	unsigned int unit() const;
	unsigned int fraction() const;

	void setUnit(unsigned int);
	void setFraction(unsigned int);
private:
	unsigned int _unit;
	unsigned int _fraction;
	
	void normalize();
};

const Currency operator+(const Currency&, const Currency&);
const Currency operator-(const Currency&, const Currency&);
const Currency& operator+=(Currency&, const Currency&);
const Currency& operator-=(Currency&, const Currency&);

bool operator==(const Currency&, const Currency&);
bool operator!=(const Currency&, const Currency&);
bool operator<(const Currency&, const Currency&);
bool operator>(const Currency&, const Currency&);
bool operator<=(const Currency&, const Currency&);
bool operator>=(const Currency&, const Currency&);

std::ostream& operator<<(std::ostream&, const Currency&);

#endif // CURRENCY_H_