#include "storage.h"

Storage::Storage(): _accounts()
{
	init();
}

Storage::~Storage() {}

Account& Storage::account(const CardNumber& cn)
{
	std::vector<Account>::iterator it = findIterator(cn);
	if (it == _accounts.end()) {
		throw std::invalid_argument("Account is not in Storage");
	}
	return *it;
}

bool Storage::hasAccount(const CardNumber& cn)
{
	return findIterator(cn) != _accounts.end();
}

void Storage::addAccount(Account& a)
{
	if (hasAccount(a.card())) {
		return;
	}
	_accounts.push_back(a);
}

void Storage::init()
{
	Person polina;
	polina._surname = "Shlepakova";
	polina._name = "Polina";
	polina._patronymic = "Dmytrivna";
	Person kyryll;
	kyryll._surname = "Vasylenko";
	kyryll._name = "Kyryll";
	kyryll._patronymic = "Anatolevich";

	CardNumber pCard1("4900123411110000");
	CardNumber pCard2("4900123422221111");
	CardNumber kCard1("4900432177773333");
	CardNumber kCard2("4900432100005555");

	Pin pPin1("1234");
	Pin pPin2("1111");
	Pin kPin1("0000");
	Pin kPin2("0123");

	Currency pBalance1(20480, 64);
	Currency pBalance2(11000, 11);
	Currency kBalance1(200480);
	Currency kBalance2(10512, 55);

	addAccount(Account(pCard1, pPin1, pBalance1, polina));
	addAccount(Account(pCard2, pPin2, pBalance2, polina));
	addAccount(Account(kCard1, kPin1, kBalance1, kyryll));
	addAccount(Account(kCard2, kPin2, kBalance2, kyryll));
}

std::vector<Account>::iterator Storage::findIterator(const CardNumber& cn)
{
	Account a(cn, Pin("0000"), Currency(0), Person());
	return std::find(_accounts.begin(), _accounts.end(), a);
}