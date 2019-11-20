#ifndef TEATRO_FANTOCHE_H
#define TEATRO_FANTOCHE_H

#include "iostream"
#include "vector"

#include "eventos/evento_infantil.h"

class TeatroFantoche: public EventoInfantil {
	private:
		std::vector<int> _horarios;
	
	public:
		TeatroFantoche(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, std::vector<int> horarios);
		std::vector<int> get_precos();
		std::vector<int> get_capacidades();
		Usuario* get_responsavel();
		int get_id();
		std::string get_nome();
		std::vector<int> get_horarios();
		void decrement_capacidade(int lote, int quantidade);
		void remove_lote(int lote);
		void set_ingressos_vendidos(int quantidade);
		int get_ingressos_vendidos();
};

#endif