#ifndef IDOSO_H
#define IDOSO_H

#include "mid/adulto.h"

class Idoso: public Adulto {
	public:
		Idoso(int id, std::string nome, int idade, float saldo, std::vector<Crianca*> dependentes);
		int get_idade();
};

#endif