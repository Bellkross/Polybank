/**
  * Polybank: Polina Shlepakova and Vasylenko Kyrylo project
  */
#include <iostream>
#include "tester.h"

int main()
{
#ifndef NDEBUG
	Tester tester;
	tester.run();
	// uncomment if you wish to try manual test
	// tester.manualTest();
	return 0;
#endif // NDEBUG
#ifdef NDEBUG
	Storage st;
	Server server(st);
	Atm atm(std::cin, std::cout, server);
	atm.run();
#endif // NDEBUG
}
