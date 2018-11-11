#ifndef ATM_H_
#define ATM_H_
#include <iostream>
#include <string>
#include <conio.h> // for getch
#include <sstream> 
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
	class Pockets
	{
		friend class Tester;
	public:
		Pockets();
		~Pockets();
		bool isFull() const;
		bool isEmpty() const;
		size_t max() const; // maximum amount of cash that Atm can fetch from pockets
		void withdraw(const size_t);
		size_t maxDeposit() const; // maximum amount of cash that Atm can put into pockets
		void deposit(const size_t);
	private:
		size_t* _arr; // (map) index - pocket size
		size_t _capacity; // pocket size for input
		const size_t kLen; // pockets count
		const size_t kCount; // count of banknotes in each pocket
		const size_t kMaxDepositCount; // max count of banknotes in each pocket

		size_t banknote(const size_t index) const; // returns banknote value by index (0 - 100), (1 - 200), (2 - 500)
		size_t sum(const size_t hi) const; // auxiliary method for max
	};
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
		DEPOSIT=3,
		DEPOSIT_TO_ANOTHER_BILL=4,
		TRANSACTION=5,
	};
	
	const size_t _attempts;

	mutable Pockets _pockets;
	Address _address;
	UserInterface _ui;
	Validator _validator;
	ServerAccessLayer* _serverAccessLayer;
	CardNumber* _number;
	Pin* _pin;

	void balance() const;
	void withdraw() const;
	void deposit() const;
	void depositToAnotherBill() const;

	size_t readAmountForAtm(const size_t) const;
	std::string readCardNumber() const;
	std::string readPin() const;
	int readCommand() const;

	// not implemented
	Atm();
	Atm(const Atm&);
	Atm& operator=(const Atm&);
};

bool isNumbers(const std::string&);
bool isNumber(char);
bool isCommand(const char);
#endif // ATM_H_