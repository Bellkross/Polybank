#include "account.h"

Account::Account(const CardNumber& card, const Pin& pin, 
				const Currency& balance, const Person& owner):
	_card(card), _pin(pin), _balance(balance), _owner(owner), _occupied(false)
{}

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