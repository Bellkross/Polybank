#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_
#include <iostream>
#include <string>
#include <conio.h> // for getch

class UserInterface
{
	friend class Tester;
public:
	UserInterface(std::istream&, std::ostream&);
	~UserInterface();

	std::string readCardNubmer() const;
	std::string readPin() const;

	void greeting() const;
	void clear() const; // Clear console. Works only in shell available systems.
private:
	std::istream& istream;
	std::ostream& ostream;

	std::string read() const;
	void show(const std::string&) const;
	bool isNumbers(const std::string&)  const;
	bool isNumber(char)  const;
	// not implemented
	UserInterface();
	UserInterface(const UserInterface&);
	UserInterface& operator=(const UserInterface&);
};

#endif // USER_INTERFACE_H_