#ifndef INSUFFICIENT_PERMISSION_H
#define INSUFFICIENT_PERMISSION_H

#include <iostream>

class InsufficientPermissionException: public std::exception {
	public:
		virtual const char* what() const noexcept {
			return "O evento e' somente para adultos!";
		}
};

#endif