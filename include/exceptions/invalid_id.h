#ifndef INVALID_ID_EXCEPTION_H
#define INVALID_ID_EXCEPTION_H

#include <iostream>

class InvalidIdException: public std::exception {
	public:
		virtual const char* what() const noexcept {
			return "A ID selecionada esta incorreta!";
		}
};

#endif