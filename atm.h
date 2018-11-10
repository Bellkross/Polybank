#ifndef ATM_H_
#define ATM_H_
#include <iostream>
#include <string>
#include <conio.h> // for getch
#include "validator.h"
#include "address.h"

class CardNumber;
class Pin;
class ServerAccessLayer;
class Atm 
{
	friend class Tester;
public:
	Atm(std::istream&, std::ostream&);
	~Atm();

	void run();

private:
	static const size_t attempts;

	class UserInterface
	{
	public:
		UserInterface(std::istream&, std::ostream&);
		~UserInterface();

		void greeting() const;
		void maintance() const;
		void clear() const; // Clear console. Works only in shell available systems.
		std::string read() const;
		char readSymbol() const;
		void show(const std::string&) const;

	private:
		std::istream& istream;
		std::ostream& ostream;

		bool isNumbers(const std::string&)  const;
		bool isNumber(char) const;
		// not implemented
		UserInterface();
		UserInterface(const UserInterface&);
		UserInterface& operator=(const UserInterface&);
	};
	enum Command 
	{
		QUIT=0,
		BALANCE=1,
		WITHDRAW=2,
		SEND=3,
		PUT_CASH=4
	};
	Address _address;
	UserInterface _ui;
	Validator _validator;
	ServerAccessLayer* _serverAccessLayer;
	CardNumber* _number;
	Pin* _pin;

	void balance() const;

	std::string readCardNumber() const;
	std::string readPin() const;
	int readCommand() const;
	// not implemented
	Atm();
	Atm(const Atm&);
	Atm& operator=(const Atm&);
};

bool isCommand(const char);
#endif // ATM_H_