#ifndef BOATE_H
#define BOATE_H

#include "iostream"
#include "vector"

#include "eventos/evento_adulto.h"

class Boate: public EventoAdulto {
	private:
		int _horaInicio;
		int _horaFim;

	public:
		Boate(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, int quota_idoso, int horaInicio, int horaFim);
		int get_id();
		int get_quotaIdoso();
		std::string get_nome();
		std::vector<int> get_precos();
		std::vector<int> get_capacidades();
		Usuario* get_responsavel();
		void decrement_capacidade(int lote, int quantidade);
		void remove_lote(int lote);
		int get_horaInicio();
		int get_horaFim();
		void set_ingressos_vendidos(int quantidade);
		int get_ingressos_vendidos();
};

#endif