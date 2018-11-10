#include "server_access_layer.h"

ServerAccessLayer::ServerAccessLayer(/*Server& server*/)
{

}

ServerAccessLayer::~ServerAccessLayer()
{

}

bool ServerAccessLayer::checkCredentials(const CardNumber& cardNumber, const Pin& pin)
{
	return true;/*_server.check(cardNumber, pin);*/
}

void encrypt(std::string& data)
{
	// will be implemented after basic functional
}
void decrypt(std::string& data)
{
	// will be implemented after basic functional
}