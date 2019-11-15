#ifndef NO_TICKETS_EXCEPTION_H
#define NO_TICKETS_EXCEPTION_H

#include <iostream>

class NoTicketsException: public std::exception {
	public:
		virtual const char* what() const noexcept {
			return "Os ingressos para esse evento estao esgotados!";
		}
};

#endif