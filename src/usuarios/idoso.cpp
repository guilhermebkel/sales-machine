#include "usuarios/idoso.h"

Idoso::Idoso(int id, std::string nome, int idade, float saldo):
	Adulto(id, nome, idade, saldo){
}

int Idoso::get_idade(){
	return _idade;
}

void Idoso::set_saldo(float quantia){
	this->_saldo -= quantia;
}

int Idoso::get_ingressos_comprados(){
	return _ingressos_comprados;
}

void Idoso::set_ingressos_comprados(int quantidade){
	this->_ingressos_comprados += quantidade;
}