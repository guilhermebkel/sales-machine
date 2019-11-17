#include "eventos/teatro_fantoche.h"

TeatroFantoche::TeatroFantoche(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, std::vector<int> horarios):
	EventoInfantil(id, nome, responsavel, capacidades, precos){
		_horarios = horarios;
}

std::vector<int> TeatroFantoche::get_precos(){
	return _precos;
}
		
std::vector<int> TeatroFantoche::get_capacidades(){
	return _capacidades;
}

Usuario* TeatroFantoche::get_responsavel(){
	return _responsavel;
}

int TeatroFantoche::get_id(){
	return _id;
}

std::string TeatroFantoche::get_nome(){
	return _nome;
}

std::vector<int> TeatroFantoche::get_horarios(){
	return _horarios;
}

void TeatroFantoche::decrement_capacidade(int lote, int quantidade){
	_capacidades[lote] -= quantidade;
}
	
void TeatroFantoche::remove_lote(int lote){
	_capacidades.erase(_capacidades.begin()+lote);
	_precos.erase(_precos.begin()+lote);
}