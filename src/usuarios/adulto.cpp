#include "usuarios/adulto.h"

Adulto::Adulto(int id, std::string nome, int idade, float saldo):
	Usuario(id, nome, idade, saldo){
}

int Adulto::get_id(){
	return _id;
}

void Adulto::set_dependentes(std::vector<Crianca*> dependentes){
	_dependentes = dependentes;
}

int Adulto::get_idade(){
	return _idade;
}

std::vector<Crianca*> Adulto::get_dependentes(){
	return _dependentes;
}

std::string Adulto::get_nome(){
	return _nome;
}

float Adulto::get_saldo(){
	return _saldo;
}

void Adulto::set_saldo(float quantia){
	this->_saldo -= quantia;
}