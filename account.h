#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <exception>

#include "person.h"
#include "currency.h"
#include "card_number.h"
#include "pin.h"

class Account
{
public:
	Account(const CardNumber& card, const Pin& pin, 
			const Currency& balance, const Person& owner);
	Account(const Account&);
	Account& operator=(const Account&);
	~Account();

	const	CardNumber& card() const;
			CardNumber& card();
	const	Pin& pin() const;
			Pin& pin();
	const	Currency& balance() const;
			Currency& balance();
	const	Person& owner() const;
			Person& owner();

	bool withdraw(const Currency& amount);
	bool deposit(const Currency& amount);
private:
	CardNumber _card;
	Pin _pin;
	Currency _balance;
	Person _owner;
	bool _occupied;

	void wait() const;
};

bool operator==(const Account&, const Account&);
bool operator!=(const Account&, const Account&);

bool operator<(const Account&, const Account&);
bool operator>(const Account&, const Account&);
bool operator<=(const Account&, const Account&);
bool operator>=(const Account&, const Account&);

#endif // ACCOUNT_H_