#include "server_access_layer.h"

ServerAccessLayer::ServerAccessLayer(/*Server& server*/)
{

}

ServerAccessLayer::~ServerAccessLayer()
{

}

bool ServerAccessLayer::checkCredentials(const CardNumber& cardNumber, const Pin& pin)
{
	return true;// _server.check(cardNumber, pin);
}

Currency ServerAccessLayer::balance(const CardNumber& cn, const Pin& pin)
{
	return Currency(100,32); // _server.balance(cn, pin);
}

bool ServerAccessLayer::withdraw(const CardNumber& cn, const Pin& pin, const Currency& curr)
{
	return true; // _server.withdraw(cn,pin,curr);
}

bool ServerAccessLayer::deposit(const CardNumber& cn, const Pin& pin, const Currency& curr)
{
	return true; // _server.deposit(cn,pin,curr);
}

bool ServerAccessLayer::transact(const CardNumber& cn, const Currency& curr)
{
	return true; // _server.transact(cn,curr);
}

bool ServerAccessLayer::transact(const CardNumber& sender, const Pin& pin, const CardNumber& recipient, const Currency& curr)
{
	return true; // _server.transact(sender, pin, recipient, curr);
}

void encrypt(std::string& data)
{
	// will be implemented after basic functional
}
void decrypt(std::string& data)
{
	// will be implemented after basic functional
}