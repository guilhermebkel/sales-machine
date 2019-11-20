#ifndef EVENTO_H
#define EVENTO_H

#include "string"
#include "iostream"
#include "vector"

#include "usuarios/usuario.h"

class Evento {
	public:
		int _id;
		std::string _nome;
		Usuario* _responsavel;
		std::vector<int> _capacidades;
		std::vector<int> _precos;
		int _ingressos_vendidos = 0;

		Evento(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos):
			_id(id), _nome(nome), _responsavel(responsavel), _capacidades(capacidades), _precos(precos){}

		virtual int get_id() = 0;
		virtual std::string get_nome() = 0;
		virtual std::vector<int> get_precos() = 0;
		virtual std::vector<int> get_capacidades() = 0;
		virtual void set_ingressos_vendidos(int quantidade) = 0;
		virtual int get_ingressos_vendidos() = 0;
};

#endif