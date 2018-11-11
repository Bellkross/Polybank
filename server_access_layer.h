/****************************
 * Author: Vasylenko Kyrylo *
 ****************************/

#ifndef SERVER_ACCESS_LAYER_H_
#define SERVER_ACCESS_LAYER_H_
#include <string>
#include "currency.h"
#include "card_number.h"
#include "pin.h"

class Server;
class ServerAccessLayer 
{
public:
	explicit ServerAccessLayer(Server&);
	~ServerAccessLayer();

	std::string fetchAccountName(const CardNumber&, const Pin&);
	bool checkCredentials(const CardNumber&, const Pin&);
	Currency balance(const CardNumber&, const Pin&);
	bool withdraw(const CardNumber&, const Pin&, const Currency&);
	bool deposit(const CardNumber&, const Pin&, const Currency&);
	bool transact(const CardNumber&, const Currency&);
	bool transact(const CardNumber&, const Pin&, const CardNumber&, const Currency&);

private:
	Server& _server;
	ServerAccessLayer();
	ServerAccessLayer(const ServerAccessLayer&);
	ServerAccessLayer& operator=(const ServerAccessLayer&);
};

#endif