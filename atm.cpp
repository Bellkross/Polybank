#include "atm.h"
#include "server_access_layer.h"
#include "card_number.h"
#include "person.h"
#include "pin.h"
#include <sstream> 

const size_t Atm::attempts = 3;

Atm::Atm(std::istream& in, std::ostream& out): _ui(in, out), _validator(), _serverAccessLayer(new ServerAccessLayer()), _number(0), _pin(0)
{
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
#ifdef NDEBUG
	_ui.greeting();
	_getch();
	_ui.clear();
#endif // NDEBUG

#ifndef NDEBUG
	_number = new CardNumber("1234567890123456");
	_pin = new Pin("1234");
#endif // NDEBUG
#ifdef NDEBUG
	_number = new CardNumber(readCardNumber());
	_pin = new Pin(readPin());
#endif // NDEBUG

	bool credentials = _serverAccessLayer->checkCredentials(*_number, *_pin);
	size_t atmpts = attempts;
	while(!credentials) {
		if(atmpts-- > 0) {
			_ui.show(std::string("Incorrect pin or card number, try again. You have %d attempts.", atmpts));
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
		switch(command) {
			case BALANCE:
				balance();
				break;
			case WITHDRAW:
				break;
			case SEND:
				break;
			case PUT_CASH:
				break;
			default: // QUIT
				return;
				break;
		}
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
	_ui.show("Press ENTER to back to the menu.");
	_getch();
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

bool isCommand(const char c)
{
	int n = c - '0';
	return n >= 0 && n <= 4;
}
