#ifndef EVENTO_INFANTIL_H
#define EVENTO_INFANTIL_H

#include "events/evento.h"

class EventoInfantil: public Evento {
	public:
		EventoInfantil(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos):
			Evento(id, nome, responsavel, capacidades, precos){}

		virtual Usuario* get_responsavel() = 0;
};

#endif