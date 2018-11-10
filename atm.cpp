#include "atm.h"
#include "server_access_layer.h"

Atm::Atm(std::istream& in, std::ostream& out): _ui(in, out), _validator(), _serverAccessLayer(new ServerAccessLayer())
{
	_address._country = "TestCountry";
	_address._city = "TestCity";
	_address._street = "TestStreet";
	_address._homeNumber = 1;
}

Atm::~Atm() {}

void Atm::run() const
{
	_ui.greeting();
	_getch();
	_ui.clear();
	DigitSequence<4> dspin(pins);
	CardNumber cn(dscn);
	Pin pin(dspin);
	_serverAccessLayer->checkCredentials(cn, pin);
	// serverAccessLayer.connect(CardNumber);
	// check card and number with server
	_ui.maintance();
	int command = readCommand();
	_ui.clear();
	switch(command) {
		case BALANCE:
			break;
		case WITHDRAW:
			break;
		case SEND:
			break;
		case PUT_CASH:
			break;
		default: // QUIT
			break;
	}
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
	return c;
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
