#ifndef IDOSO_H
#define IDOSO_H

#include "usuarios/adulto.h"

class Idoso: public Adulto {
	public:
		Idoso(int id, std::string nome, int idade, float saldo);
		int get_idade();
		void set_saldo(float quantia);
};

#endif