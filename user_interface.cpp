#include "atm.h"
#define cardlen 16
#define pinlen 4

Atm::UserInterface::UserInterface(std::istream& in, std::ostream& out): istream(in), ostream(out) {}

Atm::UserInterface::~UserInterface() {}

char Atm::UserInterface::readSymbol() const
{
	return istream.get();
}

std::string Atm::UserInterface::read() const
{
	std::string res;
	std::getline(istream, res);
	return res;
}

bool Atm::UserInterface::isNumbers(const std::string& s)  const
{
	size_t len = s.length();
	for (size_t i = 0; i < len; ++i) {
		if (!isNumber(s[i])) return false;
	}
	return len > 0;
}

bool Atm::UserInterface::isNumber(char c) const
{
	int digit = c - '0';
	return digit <= 9 && digit >= 0;
}

void Atm::UserInterface::show(const std::string& s) const
{
	ostream << s.c_str();
}

void Atm::UserInterface::greeting() const
{
	std::string greeting = "Welcome to Polybank ATM, press ENTER for beginning.\n";
	show(greeting);
}

void Atm::UserInterface::maintance() const
{
	std::string maintance = "Choose command:\n1. Balance\n2. Withdraw cash\n3. Send money to another bill\n4. Put cash\n\n0. Finish session\n\ncommand: ";
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