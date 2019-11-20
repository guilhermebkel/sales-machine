#ifndef CINEMA_H
#define CINEMA_H

#include <vector>

#include "eventos/evento.h"

class Cinema: public Evento {
	private:
		std::vector<int> _horarios;
		int _duracao;

	public:
		Cinema(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, std::vector<int> horarios, int duracao);
		std::vector<int> get_precos();
		std::vector<int> get_capacidades();
		Usuario* get_responsavel();
		int get_id();
		std::string get_nome();
		std::vector<int> get_horarios();
		int get_duracao();
		void decrement_capacidade(int lote, int quantidade);
		void remove_lote(int lote);
		void set_ingressos_vendidos(int quantidade);
		int get_ingressos_vendidos();
};

#endif