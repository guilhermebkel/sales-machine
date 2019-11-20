#include "eventos/show.h"

Show::Show(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, int quota_idoso, int aberturaPortoes, std::vector<std::string> artistas):
	EventoAdulto(id, nome, responsavel, capacidades, precos, quota_idoso){
		_aberturaPortoes = aberturaPortoes;
		_artistas = artistas;
}

int Show::get_id(){
	return _id;
}

int Show::get_quotaIdoso(){
	return _quota_idoso;
}

std::string Show::get_nome(){
	return _nome;
}

std::vector<int> Show::get_precos(){
	return _precos;
}
		
std::vector<int> Show::get_capacidades(){
	return _capacidades;
}

Usuario* Show::get_responsavel(){
	return _responsavel;
}

int Show::get_aberturaPortoes(){
	return _aberturaPortoes;
}

std::vector<std::string> Show::get_artistas(){
	return _artistas;
}

void Show::decrement_capacidade(int lote, int quantidade){
	_capacidades[lote] -= quantidade;
}
	
void Show::remove_lote(int lote){
	_capacidades.erase(_capacidades.begin()+lote);
	_precos.erase(_precos.begin()+lote);
}

void Show::set_ingressos_vendidos(int quantidade){
	this->_ingressos_vendidos += quantidade;
}
		
int Show::get_ingressos_vendidos(){
	return this->_ingressos_vendidos;
}