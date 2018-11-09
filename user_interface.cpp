#include "user_interface.h"
#define cardlen 16
#define pinlen 4

UserInterface::UserInterface(std::istream& in, std::ostream& out): istream(in), ostream(out) {}

UserInterface::~UserInterface() {}

std::string UserInterface::readCardNubmer() const
{
	clear();
	std::string number;
	bool condition = number.length() != cardlen && !isNumbers(number);
	while (condition) {
		show("print card number: ");
		number = read();
		condition = number.length() != cardlen && !isNumbers(number);
		if (!condition) {
			clear();
			show("Incorrect card number, print only digits between 0 and 9.");
			_getch();
		}
	}
	return number;
}

std::string UserInterface::readPin() const
{
	clear();
	std::string number;
	bool condition = number.length() != pinlen && !isNumbers(number);
	while (condition) {
		show("print pin: ");
		number = read();
		condition = number.length() != pinlen && !isNumbers(number);
		if (!condition) {
			clear();
			show("Incorrect pin, print only digits between 0 and 9.");
			_getch();
		}
	}
	return number;
}

std::string UserInterface::read() const
{
	std::string res;
	std::getline(istream, res);
	return res;
}

bool UserInterface::isNumbers(const std::string& s)  const
{
	for (size_t i = 0; i < s.length(); ++i) {
		if (!isNumber(s[i])) return false;
	}
	return true;
}

bool UserInterface::isNumber(char c) const
{
	int digit = c - '0';
	return digit <= 9 && digit >= 0;
}

void UserInterface::show(const std::string& s) const
{
	ostream << s.c_str();
}

void UserInterface::greeting() const
{
	std::string greeting = "\tWelcome to Polybank ATM!\nPlease insert any button for beginning.\n";
	show(greeting);
	_getch();
}

void UserInterface::clear() const
{
	if (system(NULL)) {
		system("cls");
	} else {
		ostream << '\n';
	}
}