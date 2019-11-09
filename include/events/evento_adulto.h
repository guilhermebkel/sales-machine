#ifndef EVENTO_ADULTO_H
#define EVENTO_ADULTO_H

#include "events/evento.h"

class EventoAdulto: public Evento {
	public:
		int _quota_idoso;

		EventoAdulto(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, int quota_idoso):
			Evento(id, nome, responsavel, capacidades, precos), 
			_quota_idoso(quota_idoso){}
		
		virtual int get_quotaIdoso() = 0;
};

#endif