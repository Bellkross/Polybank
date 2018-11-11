#include "atm.h"

Atm::Pockets::Pockets(): kLen(3), kCount(500), kMaxDepositCount(500*5), _capacity(0), _arr(new size_t[3])
{
	for(size_t i = 0; i < kLen; ++i) {
		_arr[i] = kCount;
	}
}

Atm::Pockets::~Pockets() {
	delete[] _arr;
}

bool Atm::Pockets::isEmpty() const {
	for(size_t i = 0; i < kLen; ++i) {
		if(_arr[i] > 0) return false;
	}
	return true;
}

bool Atm::Pockets::isFull() const {
	return _capacity >= kMaxDepositCount;
}

size_t Atm::Pockets::maxDeposit() const
{
	if(isFull() || _capacity >= kMaxDepositCount) return 0;
	return (kMaxDepositCount - _capacity)*banknote(0);
}

void Atm::Pockets::deposit(const size_t amount)
{
	size_t amnt = amount;
	while(amnt != 0 && maxDeposit() > 0 && amnt < maxDeposit()) {
		amnt -= banknote(0);
		++_capacity;
	}
}

size_t Atm::Pockets::max() const 
{
	if(isEmpty() || _arr[0] < 1) return 0;
	size_t a1 = _arr[0], a2 = _arr[1], a3 = _arr[2];
	if((a1 >= 1 && a2 >= 2) || a1 >= 5) {
		return sum(kLen);
	} else if (a1 < 5) {
		return sum(kLen-1);
	}
	return 0;
}

void Atm::Pockets::withdraw(const size_t amount) {
	size_t amnt = amount;
	while(amnt != 0 && max() > 0) {
		if(amnt >= banknote(2) && _arr[2] > 0) {
			amnt -= banknote(2);
			--_arr[2];
		}
		if(amnt >= banknote(1) && _arr[1] > 0) {
			amnt -= banknote(1);
			--_arr[1];
		}
		if(amnt >= banknote(0) && _arr[0] > 0) {
			amnt -= banknote(0);
			--_arr[0];
		}
	}
}

size_t Atm::Pockets::sum(const size_t hi) const
{
	size_t sum = 0;
	for(size_t i = 0; i < hi; ++i) {
		sum += _arr[i] * banknote(i);
	}
	return sum;
}

size_t Atm::Pockets::banknote(const size_t index) const
{
	switch(index) {
	case 0: return 100;
	case 1: return 200;
	case 2: return 500;
	default: throw std::invalid_argument("Incorrect banknote index");
	}
}