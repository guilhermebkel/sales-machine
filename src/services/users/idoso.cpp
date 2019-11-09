#include "users/idoso.h"

Idoso::Idoso(int id, std::string nome, int idade, float saldo):
	Adulto(id, nome, idade, saldo){
}

int Idoso::get_idade(){
	return _idade;
}

void Idoso::set_saldo(float quantia){
	this->_saldo -= quantia;
}