#include "eventos/boate.h"

Boate::Boate(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, int quota_idoso, int horaInicio, int horaFim):
	EventoAdulto(id, nome, responsavel, capacidades, precos, quota_idoso){
		_horaInicio = horaInicio;
		_horaFim = horaFim;
}

int Boate::get_id(){
	return _id;
}

int Boate::get_quotaIdoso(){
	return _quota_idoso;
}

std::string Boate::get_nome(){
	return _nome;
}

std::vector<int> Boate::get_precos(){
	return _precos;
}
		
std::vector<int> Boate::get_capacidades(){
	return _capacidades;
}

Usuario* Boate::get_responsavel(){
	return _responsavel;
}

int Boate::get_horaInicio(){
	return _horaInicio;
}

int Boate::get_horaFim(){
	return _horaFim;
}

void Boate::decrement_capacidade(int lote, int quantidade){
	_capacidades[lote] -= quantidade;
}
	
void Boate::remove_lote(int lote){
	_capacidades.erase(_capacidades.begin()+lote);
	_precos.erase(_precos.begin()+lote);
}

void Boate::set_ingressos_vendidos(int quantidade){
	this->_ingressos_vendidos += quantidade;
}
		
int Boate::get_ingressos_vendidos(){
	return this->_ingressos_vendidos;
}