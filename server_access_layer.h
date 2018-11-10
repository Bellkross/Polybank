#ifndef SERVER_ACCESS_LAYER_H_
#define SERVER_ACCESS_LAYER_H_
#include <string>
#include "card_number.h"
#include "pin.h"

class ServerAccessLayer 
{
public:
	//ServerAccessLayer(const Server&);
	ServerAccessLayer();
	~ServerAccessLayer();
	bool checkCredentials(const CardNumber&, const Pin&);
	
private:
	//const Server& _server;
	ServerAccessLayer(const ServerAccessLayer&);
	ServerAccessLayer& operator=(const ServerAccessLayer&);
};

void encrypt(std::string& data);
void decrypt(std::string& data);

#endif