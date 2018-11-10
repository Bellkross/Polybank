#ifndef SERVER_ACCESS_LAYER_H_
#define SERVER_ACCESS_LAYER_H_
#include <string>
#include "currency.h"
#include "card_number.h"
#include "pin.h"

class ServerAccessLayer 
{
public:
	//ServerAccessLayer(const Server&);
	ServerAccessLayer(); // make private after server appearing
	~ServerAccessLayer();
	bool checkCredentials(const CardNumber&, const Pin&);
	Currency balance(const CardNumber&, const Pin&);
	bool withdraw(const CardNumber&, const Pin&, const Currency&);
	bool deposit(const CardNumber&, const Pin&, const Currency&);
	bool transact(const CardNumber&, const Currency&);
	bool transact(const CardNumber&, const Pin&, const CardNumber&, const Currency&);

private:
	//const Server& _server;
	ServerAccessLayer(const ServerAccessLayer&);
	ServerAccessLayer& operator=(const ServerAccessLayer&);
};

void encrypt(std::string& data);
void decrypt(std::string& data);

#endif