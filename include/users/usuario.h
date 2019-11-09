#ifndef USUARIO_H
#define USUARIO_H

#include "string"
#include "iostream"

class Usuario {
	public:
		int _id;
		std::string _nome;
		int _idade;
		float _saldo;

		Usuario(int id, std::string nome, int idade, float saldo):
			_id(id), _nome(nome), _idade(idade), _saldo(saldo){}

		virtual int get_id() = 0;
		virtual std::string get_nome() = 0;
		virtual int get_idade() = 0;
		virtual float get_saldo() = 0;
		virtual void set_saldo(float quantia) = 0;
};

#endif