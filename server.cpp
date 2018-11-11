#include "server.h"

#include <sstream>
#include <cassert>

Server::Server(Storage& storage): _storage(storage) {}

Server::~Server() {}

std::string Server::fetchAccountName(const CardNumber& card, const Pin& pin)
{
	Account& a = _storage.account(card);
	assert(a.pin() == pin);
	Person ow = a.owner();
	std::ostringstream stream;
	stream << ow._surname << ' ' << ow._name << ' ' << ow._patronymic;
	return stream.str();
}

bool Server::checkCredentials(const CardNumber& card, const Pin& pin)
{
	Account& a = _storage.account(card);
	return a.pin() == pin;
}

Currency Server::balance(const CardNumber& card, const Pin& pin)
{
	Account& a = _storage.account(card);
	assert(a.pin() == pin);
	return a.balance();
}

bool Server::withdraw(const CardNumber& card, const Pin& pin, const Currency& amount)
{
	Account& a = _storage.account(card);
	assert(a.pin() == pin);
	return a.withdraw(amount);
}

bool Server::deposit(const CardNumber& card, const Pin& pin, const Currency& amount)
{
	Account& a = _storage.account(card);
	assert(a.pin() == pin);
	return a.deposit(amount);
}

bool Server::transact(const CardNumber& recipientCard, const Currency& amount)
{
	return _storage.account(recipientCard).deposit(amount);
}

bool Server::transact(const CardNumber& senderCard, const Pin& senderPin, 
	const CardNumber& recipientCard, const Currency& amount)
{
	Account& as = _storage.account(senderCard);
	assert(as.pin() == senderPin);
	if (!as.withdraw(amount)) {
		return false;
	}
	return _storage.account(recipientCard).deposit(amount);
}
