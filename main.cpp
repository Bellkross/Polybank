/************************************************************
 * Polybank: Polina Shlepakova and Vasylenko Kyrylo project *
 ************************************************************/
#include <iostream>
#include "tester.h"

int main()
{
#ifndef NDEBUG
	Tester tester;
	tester.run();
	return 0;
#endif // NDEBUG
#ifdef NDEBUG // turn release mode if you wish to try manual test
	Storage st;
	Server server(st);
	Atm atm(std::cin, std::cout, server);
	atm.run();
#endif // NDEBUG
}
