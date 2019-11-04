#include "mid/crianca.h"

Crianca::Crianca(int id, std::string nome, int idade, float saldo, Adulto* responsavel):
	Usuario(id, nome, idade, saldo){
		_responsavel = responsavel;
}

Adulto* Crianca::get_responsavel(){
	return _responsavel;
}

int Crianca::get_idade(){
	return _idade;
}

std::string Crianca::get_nome(){
	return _nome;
}

int Crianca::get_id(){
	return _id;
}

float Crianca::get_saldo(){
	return _saldo;
}