#ifndef NOT_ENOUGH_FUNDS_EXCEPTION_H
#define NOT_ENOUGH_FUNDS_EXCEPTION_H

#include <iostream>

class NotEnoughFundsException: public std::exception {
	public:
		virtual const char* what() const noexcept {
			return "Voce nao possui saldo suficiente para realizar essa compra!";
		}
};

#endif