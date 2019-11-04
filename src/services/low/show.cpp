#include "low/show.h"

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