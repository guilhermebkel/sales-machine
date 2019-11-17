#include "eventos/cinema.h"

Cinema::Cinema(int id, std::string nome, Usuario* responsavel, std::vector<int> capacidades, std::vector<int> precos, std::vector<int> horarios, int duracao):
	Evento(id, nome, responsavel, capacidades, precos){
		_horarios = horarios; 
		_duracao = duracao;
}

std::vector<int> Cinema::get_precos(){
	return _precos;
}
		
std::vector<int> Cinema::get_capacidades(){
	return _capacidades;
}

Usuario* Cinema::get_responsavel(){
	return _responsavel;
}

int Cinema::get_id(){
	return _id;
}

std::string Cinema::get_nome(){
	return _nome;
}

std::vector<int> Cinema::get_horarios(){
	return _horarios;
}

int Cinema::get_duracao(){
	return _duracao;
}

void Cinema::decrement_capacidade(int lote, int quantidade){
	_capacidades[lote] -= quantidade;
}
	
void Cinema::remove_lote(int lote){
	_capacidades.erase(_capacidades.begin()+lote);
	_precos.erase(_precos.begin()+lote);
}