#ifndef NOT_ENOUGH_TICKETS_EXCEPTION_H
#define NOT_ENOUGH_TICKETS_EXCEPTION_H

#include <iostream>

class NotEnoughTicketsException: public std::exception {
	public:
		virtual const char* what() const noexcept {
			return "A quantidade de ingressos que voce deseja comprar nao esta disponivel!";
		}
};

#endif