/****************************
 * Author: Vasylenko Kyrylo *
 ****************************/

#include "atm.h"
#define cardlen 16
#define pinlen 4

Atm::UserInterface::UserInterface(std::istream& in, std::ostream& out): istream(in), ostream(out) {}

Atm::UserInterface::~UserInterface() {}

char Atm::UserInterface::readSymbol() const
{
	std::string line;
	istream >> line;
	return line[0];
}

std::string Atm::UserInterface::read() const
{
	std::string res;
	std::getline(istream, res);
	return res;
}

void Atm::UserInterface::show(const std::string& s) const
{
	ostream << s.c_str();
}

void Atm::UserInterface::greeting() const
{
	std::string greeting = "Welcome to Polybank ATM, press ENTER to begin.\n";
	show(greeting);
}

void Atm::UserInterface::maintance() const
{
	std::ostringstream stream;
	stream << "Choose a command:\n";
	stream << "1. Balance\n";
	stream << "2. Withdraw cash\n";
	stream << "3. Deposit cash\n";
	stream << "4. Deposit cash to another bill\n";
	stream << "5. Perform transaction\n";
	stream << "6. Finish session\n\n";
	stream << "0. Turn off atm\n\n";
	stream << "Choose a command: ";
	show(stream.str());
}

void Atm::UserInterface::clear() const
{
	if (system(NULL)) {
		system("cls");
	} else {
		ostream << '\n';
	}
}
