/****************************
 * Author: Vasylenko Kyrylo *
 ****************************/

#ifndef ADDRESS_H_
#define ADDRESS_H_
#include <string>

struct Address
{
	std::string _country;
	std::string _city;
	std::string _street;
	size_t _homeNumber;
};

#endif