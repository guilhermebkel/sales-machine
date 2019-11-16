#ifndef SHOW_H
#define SHOW_H

#include "iostream"
#include "vector"
#include "string"

#include "eventos/evento_adulto.h"

class Show: public EventoAdulto {
	private:
		int _aberturaPortoes;
		std::vector<std::string> _artistas;

	public:
		Show(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, int quota_idoso, int aberturaPortoes, std::vector<std::string> artistas);
		int get_id();
		int get_quotaIdoso();
		std::string get_nome();
		std::vector<int> get_precos();
		std::vector<int> get_capacidades();
		Usuario* get_responsavel();
		int get_aberturaPortoes();
		std::vector<std::string> get_artistas();
		void decrement_capacidade(int lote, int quantidade);
		void remove_lote(int lote);
};

#endif