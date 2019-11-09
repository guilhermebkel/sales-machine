#ifndef CRIANCA_H
#define CRIANCA_H

#include "users/usuario.h"

class Adulto;

class Crianca: public Usuario {
	private:
		Adulto* _responsavel;

	public:
		Crianca(int id, std::string nome, int idade, float saldo, Adulto* responsavel);
		Adulto* get_responsavel();
		int get_idade();
		std::string get_nome();
		int get_id();
		float get_saldo();
		void set_saldo(float quantia);
		void set_responsavel(Adulto* responsavel);
};

#endif