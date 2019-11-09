#ifndef ADULTO_H
#define ADULTO_H

#include <vector>

#include "users/usuario.h"
#include "users/crianca.h"

class Adulto: public Usuario {
	public:
		std::vector<Crianca*> _dependentes;

		Adulto(int id, std::string nome, int idade, float saldo, std::vector<Crianca*> dependentes);
		int get_id();
		void set_dependentes(std::vector<Crianca*> dependentes);
		int get_idade();
		std::string get_nome();
		std::vector<Crianca*> get_dependentes();
		float get_saldo();
};

#endif