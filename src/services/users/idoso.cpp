#include "users/idoso.h"

Idoso::Idoso(int id, std::string nome, int idade, float saldo, std::vector<Crianca*> dependentes):
	Adulto(id, nome, idade, saldo, dependentes){
}

int Idoso::get_idade(){
	return _idade;
}

void Idoso::set_saldo(float quantia){
	this->_saldo -= quantia;
}