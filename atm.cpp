#include "atm.h"
#include "server_access_layer.h"
#include "card_number.h"
#include "person.h"
#include "pin.h"

Atm::Atm(std::istream& in, std::ostream& out, Server& server): 
	_ui(in, out), _validator(), _serverAccessLayer(new ServerAccessLayer(server)), 
	_number(0), _pin(0), kAttempts(3), kTransactionLowBoundary(5.0), kTransactionHighBoundary(200000.0)
{
	// address initialization
	_address._country = "TestCountry";
	_address._city = "TestCity";
	_address._street = "TestStreet";
	_address._homeNumber = 1;
}

Atm::~Atm() 
{
	delete _serverAccessLayer;
	delete _number;
	delete _pin;
}

void Atm::run()
{
	_ui.clear();
	_ui.greeting();
	_getch();
	_ui.clear();

	_number = new CardNumber(readCardNumber());
	_pin = new Pin(readPin());

	bool credentials = _serverAccessLayer->checkCredentials(*_number, *_pin);
	size_t atmpts = kAttempts;
	while(!credentials) {
		if(atmpts-- > 0) {
			std::ostringstream stream;
			stream << "Incorrect pin or card number, try again. You have ";
			stream << atmpts << " attempts.";
			_ui.show(stream.str());
			delete _number;
			delete _pin;
			_number = new CardNumber(readCardNumber());
			_pin = new Pin(readPin());
			credentials = _serverAccessLayer->checkCredentials(*_number, *_pin);
		} else {
			_ui.show("Limit of attempts exhausted.");
			return;
		}
	}
	int command = -1;
	while(command!=QUIT) {
		_ui.clear();
		_ui.maintance();
		command = readCommand();
		_ui.clear();
		_ui.read(); // skip one line
		switch(command) {
			case BALANCE:
				balance();
				break;
			case WITHDRAW:
				withdraw();
				break;
			case DEPOSIT:
				deposit();
				break;
			case DEPOSIT_TO_ANOTHER_BILL:
				depositToAnotherBill();
				break;
			case TRANSACTION:
				transaction();
				break;
			default: // QUIT
				return;
		}
	}
}

void Atm::transaction() const
{
	CardNumber number = CardNumber(readCardNumber());
	Currency balance = _serverAccessLayer->balance(*_number, *_pin);
	if(balance.unit() == 0) {
		_ui.show("You cannot send money, your balance is empty.");
		_getch();
		return;
	}
	if(_serverAccessLayer->transact(*_number, *_pin, number, readAmountForTransaction(balance))) {
		_ui.clear();
		_ui.show("Transaction finished. Press ENTER to return to the menu.");
		_getch();
	} else {
		_ui.clear();
		_ui.show("Transaction failed. Press ENTER to return to the menu.");
		_getch();
	}
}

Currency Atm::readAmountForTransaction(const Currency& balance) const
{
	std::ostringstream stream;
	stream << "Type amount of money to send (more than 5.0)\n";
	stream << "amount: ";
	_ui.clear();
	_ui.show(stream.str());
	std::string curr = _ui.read();
	while(!isCurrencyNumbers(curr) || 
		atof(curr.c_str()) <= kTransactionLowBoundary || 
		atof(curr.c_str()) > kTransactionHighBoundary) {
		_ui.clear();
		_ui.show("Incorrect amount value! Press ENTER to repeat.");
		_getch();
		_ui.clear();
		_ui.show(stream.str());
		curr = _ui.read();
	}
	double value = atof(curr.c_str());
	int unit = static_cast<int>(value);
	int fraction = static_cast<int>((value - static_cast<double>(unit))*100);
	return Currency(unit,fraction);
}

void Atm::depositToAnotherBill() const
{
	if(_pockets.isFull() || _pockets.maxDeposit() == 0) {
		_ui.show("Sorry, but you cannot deposit money, try again later.");
		_getch();
		return;
	}
	CardNumber number = CardNumber(readCardNumber());
	Currency curr(readAmountForAtm(_pockets.maxDeposit()));
	if(_serverAccessLayer->transact(*_number,curr)) {
		_pockets.deposit(curr.unit());
		_ui.clear();
		_ui.show("Deposit finished. Press ENTER to return to the menu.");
		_getch();
	} else {
		_ui.clear();
		_ui.show("Deposit failed. Press ENTER to return to the menu.");
		_getch();
	}
}

void Atm::deposit() const
{
	if(_pockets.isFull() || _pockets.maxDeposit() == 0) {
		_ui.show("Sorry, but you cannot deposit money, try again later.");
		_getch();
		return;
	}
	Currency curr(readAmountForAtm(_pockets.maxDeposit()));
	if(_serverAccessLayer->deposit(*_number,*_pin,curr)) {
		_pockets.deposit(curr.unit());
		_ui.clear();
		_ui.show("Deposit finished. Press ENTER to return to the menu.");
		_getch();
	} else {
		_ui.clear();
		_ui.show("Deposit failed. Press ENTER to return to the menu.");
		_getch();
	}
}

void Atm::withdraw() const
{
	if(_pockets.isEmpty() || _pockets.max() == 0) {
		_ui.show("Sorry, but you cannot withdraw money, try again later.");
		_getch();
		return;
	}
	Currency balance = _serverAccessLayer->balance(*_number, *_pin);
	Currency curr(readAmountForAtm(_pockets.max()));
	if(_serverAccessLayer->withdraw(*_number,*_pin,curr)) {
		_pockets.withdraw(curr.unit());
		_ui.clear();
		_ui.show("You can take your money. Press ENTER to return to the menu.");
		_getch();
	} else {
		_ui.clear();
		_ui.show("Operation failed. Press ENTER to return to the menu.");
		_getch();
	}
}

void Atm::balance() const
{
	Currency balance = _serverAccessLayer->balance(*_number, *_pin);
	std::string name = _serverAccessLayer->fetchAccountName(*_number, *_pin);
	std::ostringstream stream;
	stream << name << ", your balance: " << balance << " grn." << std::endl;
	_ui.clear();
	_ui.show(stream.str());
	_ui.show("Press ENTER to return to the menu.");
	_getch();
}

size_t Atm::readAmountForAtm(const size_t max) const
{
	std::ostringstream stream;
	stream << "Type amount of money that is divisible by 100 and no bigger than " << max << '\n';
	stream << "amount: ";
	int amount = -1;
	while(amount < 0) {
		_ui.clear();
		_ui.show(stream.str());
		try {
			amount = std::stoi(_ui.read());
		} catch (std::logic_error&) {
			_ui.clear();
			_ui.show("Incorrect amount value! Press ENTER to repeat.");
			amount = -1;
			_getch();
		}
		if(amount < 1 || amount > max || amount % 100 != 0) {
			_ui.clear();
			_ui.show("Incorrect amount value! Press ENTER to repeat.");
			amount = -1;
			_getch();
		}
	}
	return amount;
}

int Atm::readCommand() const
{
	char c = _ui.readSymbol();
	bool condition = isCommand(c);
	while (!condition) {
		_ui.clear();
		_ui.show("Invalid command. Repeat, please.");
		_getch();
		_ui.clear();
		_ui.maintance();
		c = _ui.readSymbol();
		condition = isCommand(c);
	}
	return c - '0';
}

std::string Atm::readCardNumber() const
{
	std::string number;
	bool condition = _validator.validateCardNumber(number);
	while (!condition) {
		_ui.show("print card number: ");
		number = _ui.read();
		condition = _validator.validateCardNumber(number);
		if (!condition) {
			_ui.clear();
			_ui.show("Invalid card number. Repeat, please.");
			_getch();
			_ui.clear();
		}
	}
	return number;
}

std::string Atm::readPin() const
{
	std::string pin;
	bool condition = _validator.validatePin(pin);
	while (!condition) {
		_ui.show("print pin: ");
		pin = _ui.read();
		condition = _validator.validatePin(pin);
		if (!condition) {
			_ui.clear();
			_ui.show("Incorrect pin. Repeat, please.");
			_getch();
			_ui.clear();
		}
	}
	return pin;
}

bool isCurrencyNumbers(const std::string& s)
{
	size_t len = s.length();
	if(len <= 0 || s[0] == '0') return false;
	size_t dot = 1;
	size_t numbersAfterPoint = 0;
	for (size_t i = 0; i < len; ++i) {
		if (s[i] == '.' && dot-- > 0) {
			continue;
		} else if(s[i] == '.' && dot <= 0) {
			return false;
		}
		if (!isNumber(s[i])) {
			return false;
		} else if (dot == 0 && ++numbersAfterPoint > 2) {
			return false;
		}
	}
	return true;
}

bool isNumbers(const std::string& s)
{
	size_t len = s.length();
	for (size_t i = 0; i < len; ++i) {
		if (!isNumber(s[i])) return false;
	}
	return len > 0;
}

bool isNumber(char c)
{
	int digit = c - '0';
	return digit <= 9 && digit >= 0;
}

bool isCommand(const char c)
{
	int n = c - '0';
	return n >= 0 && n <= 5;
}
