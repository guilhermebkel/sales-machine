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
	this->get_capacidades()[lote] -= quantidade;
}
	
void Boate::remove_lote(int lote){
	this->get_capacidades().erase(this->get_capacidades().begin()+lote);
}