#include "server_access_layer.h"
#include "server.h"

ServerAccessLayer::ServerAccessLayer(Server& server): _server(server)
{

}

ServerAccessLayer::~ServerAccessLayer()
{

}

std::string ServerAccessLayer::fetchAccountName(const CardNumber& cn, const Pin& pin)
{
	return _server.fetchAccountName(cn, pin);
}

bool ServerAccessLayer::checkCredentials(const CardNumber& cn, const Pin& pin)
{
	return _server.checkCredentials(cn, pin);
}

Currency ServerAccessLayer::balance(const CardNumber& cn, const Pin& pin)
{
	return _server.balance(cn, pin);
}

bool ServerAccessLayer::withdraw(const CardNumber& cn, const Pin& pin, const Currency& curr)
{
	return _server.withdraw(cn,pin,curr);
}

bool ServerAccessLayer::deposit(const CardNumber& cn, const Pin& pin, const Currency& curr)
{
	return _server.deposit(cn,pin,curr);
}

bool ServerAccessLayer::transact(const CardNumber& cn, const Currency& curr)
{
	return _server.transact(cn,curr);
}

bool ServerAccessLayer::transact(const CardNumber& sender, const Pin& pin, const CardNumber& recipient, const Currency& curr)
{
	return _server.transact(sender, pin, recipient, curr);
}