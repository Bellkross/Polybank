#ifndef SERVER_H_
#define SERVER_H_

#include <string>

#include "storage.h"
#include "currency.h"
#include "card_number.h"
#include "pin.h"

class Server 
{
public:
	explicit Server(Storage&);
	~Server();

	std::string fetchAccountName(const CardNumber& card, const Pin& pin);
	bool checkCredentials(const CardNumber& card, const Pin& pin);
	Currency balance(const CardNumber& card, const Pin& pin);
	bool withdraw(const CardNumber& card, const Pin& pin, const Currency& amount);
	bool deposit(const CardNumber& card, const Pin& pin, const Currency& amount);
	bool transact(const CardNumber& recipientCard, const Currency& amount);
	bool transact(const CardNumber& senderCard, const Pin& senderPin, 
				const CardNumber& recipientCard, const Currency& amount);

private:
	Storage& _storage;

	/* Server is non-copiable */
	Server(const Server&);
	Server& operator=(const Server&);
};

#endif // SERVER_H_