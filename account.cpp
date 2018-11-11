/*****************************
 * Author: Polina Shlepakova *
 *****************************/

#include "account.h"

Account::Account(const CardNumber& card, const Pin& pin, 
				const Currency& balance, const Person& owner):
	_card(card), _pin(pin), _balance(balance), _owner(owner), _occupied(false)
{}

Account::Account(const Account& a): 
	_card(a.card()), _pin(a.pin()), _balance(a.balance()), _owner(a.owner()), _occupied(a._occupied)
{}

Account& Account::operator=(const Account&a )
{
	card() = a.card();
	pin() = a.pin();
	balance() = a.balance();
	owner() = a.owner();
	return *this;
}

Account::~Account() {}

const CardNumber& Account::card() const {return _card;}
CardNumber& Account::card() {return _card;}

const Pin& Account::pin() const {return _pin;}
Pin& Account::pin() {return _pin;}

const Currency& Account::balance() const {return _balance;}
Currency& Account::balance() {return _balance;}

const Person& Account::owner() const {return _owner;}
Person& Account::owner() {return _owner;}

bool Account::withdraw(const Currency& amount) 
{
	if (_occupied) {
		wait();
	}
	if (balance() < amount) {
		return false;
	}
	_occupied = true;
	balance() -= amount;
	_occupied = false;
	return true;
}

bool Account::deposit(const Currency& amount) 
{
	if (_occupied) {
		wait();
	}
	_occupied = true;
	balance() += amount;
	_occupied = false;
	return true;
}

void Account::wait() const 
{
	while (_occupied);
}

bool operator==(const Account& a1, const Account& a2) 
{
	return a1.card() == a2.card();
}

bool operator!=(const Account& a1, const Account& a2) {
	return !(a1 == a2);
}

bool operator<(const Account& a1, const Account& a2)
{
	return a1.card() < a2.card();
}

bool operator>(const Account& a1, const Account& a2)
{
	return a2 < a1;
}

bool operator<=(const Account& a1, const Account& a2)
{
	return a1 == a2 ? true : a1 < a2;
}

bool operator>=(const Account& a1, const Account& a2)
{
	return a2 <= a1;
}