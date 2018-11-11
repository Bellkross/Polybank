/*****************************
 * Author: Polina Shlepakova *
 *****************************/

#include "server.h"

#include <sstream>
#include <cassert>

Server::Server(Storage& storage): _storage(storage) {}

Server::~Server() {}

std::string Server::fetchAccountName(const CardNumber& card, const Pin& pin)
{
	assert(checkCredentials(card, pin));
	Account& a = _storage.account(card);
	Person ow = a.owner();
	std::ostringstream stream;
	stream << ow._surname << ' ' << ow._name << ' ' << ow._patronymic;
	return stream.str();
}

bool Server::checkCredentials(const CardNumber& card, const Pin& pin)
{
	try {
		Account& a = _storage.account(card);
		return a.pin() == pin;
	} catch (std::exception&) {
		return false;
	}
}

Currency Server::balance(const CardNumber& card, const Pin& pin)
{
	assert(checkCredentials(card, pin));
	Account& a = _storage.account(card);
	return a.balance();
}

bool Server::withdraw(const CardNumber& card, const Pin& pin, const Currency& amount)
{
	assert(checkCredentials(card, pin));
	Account& a = _storage.account(card);
	return a.withdraw(amount);
}

bool Server::deposit(const CardNumber& card, const Pin& pin, const Currency& amount)
{
	assert(checkCredentials(card, pin));
	Account& a = _storage.account(card);
	return a.deposit(amount);
}

bool Server::transact(const CardNumber& recipientCard, const Currency& amount)
{
	try {
		return _storage.account(recipientCard).deposit(amount);
	} catch (std::exception&) {
		return false;
	}
}

bool Server::transact(const CardNumber& senderCard, const Pin& senderPin, 
	const CardNumber& recipientCard, const Currency& amount)
{
	assert(checkCredentials(senderCard, senderPin));
	Account& as = _storage.account(senderCard);
	if (!as.withdraw(amount)) {
		return false;
	}
	return _storage.account(recipientCard).deposit(amount);
}
