#ifndef STORAGE_H_
#define STORAGE_H_

#include <vector>
#include <algorithm>
#include <exception>

#include "account.h"
#include "card_number.h"

class Storage
{
public:
	Storage();
	~Storage();

	Account& account(const CardNumber&);
	bool hasAccount(const CardNumber&);
	void addAccount(Account&);

private:
	std::vector<Account> _accounts;
//	std::set<Account, bool (Account::*) (const Account&, const Account&)> _accounts;

	/* puts test elements into Storage */
	void init();
	std::vector<Account>::iterator Storage::findIterator(const CardNumber&);

	/* Storage is non-copiable */
	Storage(const Storage&);
	Storage& operator=(const Storage&);
};

#endif // STORAGE_H_