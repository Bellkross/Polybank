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
	std::string maintance = "Choose a command:\n1. Balance\n2. Withdraw cash\n3. Deposit cash\n4. Perform transaction\n\n0. Finish session\n\ncommand: ";
	show(maintance);
}

void Atm::UserInterface::clear() const
{
	if (system(NULL)) {
		system("cls");
	} else {
		ostream << '\n';
	}
}
