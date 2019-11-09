#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "users/usuario.h"
#include "users/crianca.h"
#include "users/adulto.h"
#include "users/idoso.h"

#include "events/boate.h"
#include "events/show.h"
#include "events/cinema.h"
#include "events/teatro_fantoche.h"
#include "events/evento.h"

#include "machines/maquina_fantoche.h"

int main(){
	std::string linha, termo;
	std::istringstream stream_string;
	int contador;

	std::string usuarioId, usuarioTipo, usuarioNome, usuarioIdade, usuarioSaldo, usuarioResponsavel_id;
	std::vector<Crianca*> usuarioDependentes;
	Adulto* usuarioResponsavel = nullptr;

	std::string eventoId, eventoNome, eventoPublico, eventoTipo, eventoResponsavel_id, eventoNumTipos;
	int eventoHoraInicio, eventoHoraFim, eventoAberturaPortoes, eventoQuota_idoso, eventoDuracao;
	std::vector<int> eventoCapacidades, eventoPrecos, eventoHorariosInicio;
	std::vector<std::string> eventoArtistas;
	Usuario* eventoResponsavel = nullptr;

	std::vector<Crianca*> criancas;
	std::vector<Adulto*> adultos;
	std::vector<Idoso*> idosos;

	std::vector<Boate*> boates;
	std::vector<Show*> shows;
	std::vector<Cinema*> cinemas;
	std::vector<TeatroFantoche*> teatros;

	std::ifstream usuariosDatabase("database/usuarios.csv");

	while(usuariosDatabase.good()){
		
		std::getline(usuariosDatabase, usuarioId, ',');
		std::getline(usuariosDatabase, usuarioTipo, ',');
		std::getline(usuariosDatabase, usuarioNome, ',');
		std::getline(usuariosDatabase, usuarioIdade, ',');

		// Verifica o tipo da linha atual
		// para decidir quando ler o último termo como '\n'
		if(!usuarioTipo.compare("adulto")){
			std::getline(usuariosDatabase, usuarioSaldo, '\n');
			usuarioResponsavel_id = "NULL";

			adultos.push_back(new Adulto(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo), criancas));
		}
		else if(!usuarioTipo.compare("idoso")){
			std::getline(usuariosDatabase, usuarioSaldo, '\n');
			usuarioResponsavel_id = "NULL";

			idosos.push_back(new Idoso(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo), criancas));
		}
		else if(!usuarioTipo.compare("crianca")){
			std::getline(usuariosDatabase, usuarioSaldo, ',');
			std::getline(usuariosDatabase, usuarioResponsavel_id, '\n');

			// Associa o adulto respoonsavel com
			// seu filho.
			for(Adulto* adulto : adultos){
				if(adulto->get_id() == std::stoi(usuarioResponsavel_id)){
					usuarioResponsavel = adulto;
					break;
				}
			}
			for(Idoso* idoso : idosos){
				if(idoso->get_id() == std::stoi(usuarioResponsavel_id)){
					usuarioResponsavel = idoso;
					break;
				}
			}

			criancas.push_back(new Crianca(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo), usuarioResponsavel));
		}
		usuarioResponsavel = nullptr;
	}
	usuariosDatabase.close();

	// Faz as associações dos dependentes de cada adulto
	for(Adulto* adulto : adultos){
		for(Crianca* crianca : criancas){
			if(adulto->get_id() == crianca->get_responsavel()->get_id()){
				usuarioDependentes.push_back(crianca);
			}
		}
		if(usuarioDependentes.size()){
			adulto->set_dependentes(usuarioDependentes);
			usuarioDependentes.clear();
		}
	}
	for(Idoso* idoso : idosos){
		for(Crianca* crianca : criancas){
			if(idoso->get_id() == crianca->get_responsavel()->get_id()){
				usuarioDependentes.push_back(crianca);
			}
		}
		if(usuarioDependentes.size()){
			idoso->set_dependentes(usuarioDependentes);
			usuarioDependentes.clear();
		}
	}

	std::ifstream eventosDatabase("database/eventos.csv");

	while(eventosDatabase.good()){

		std::getline(eventosDatabase, eventoId, ',');
		std::getline(eventosDatabase, eventoPublico, ',');

		if(!eventoPublico.compare("cinema")){
			eventoTipo = eventoPublico;
		}
		else{
			std::getline(eventosDatabase, eventoTipo, ',');
		}

		std::getline(eventosDatabase, eventoNome, ',');
		std::getline(eventosDatabase, eventoResponsavel_id, ',');
		std::getline(eventosDatabase, eventoNumTipos, ',');

		std::getline(eventosDatabase, linha);
		stream_string = std::istringstream(linha);
		contador = 0;
		while(std::getline(stream_string, termo, ',')){
			if(contador < std::stoi(eventoNumTipos)*2 && (contador%2 == 0)){
				eventoCapacidades.push_back(std::stoi(termo));
			}
			else if(contador < std::stoi(eventoNumTipos)*2 && (contador%2 != 0)){
				eventoPrecos.push_back(std::stoi(termo));
			}
			else{
				if(contador == std::stoi(eventoNumTipos)*2 && eventoPublico == "adulto"){
					eventoQuota_idoso = std::stoi(termo);
				}
				else if(eventoTipo == "cinema"){
					if(std::stoi(termo) > 5){
						eventoHorariosInicio.push_back(std::stoi(termo));
					}
					else{
						eventoDuracao = std::stoi(termo);
					}
				}
				else if(eventoTipo == "fantoche"){
					eventoHorariosInicio.push_back(std::stoi(termo));
				}
				else if(eventoTipo == "show"){
					if(contador*2 + 2 == std::stoi(eventoNumTipos) + 2){
						eventoAberturaPortoes = std::stoi(termo);
					}
					else{
						eventoArtistas.push_back(termo);
					}
				}
				else if(eventoTipo == "boate"){
					if(contador*2 + 2 == std::stoi(eventoNumTipos) + 2){
						eventoHoraInicio = std::stoi(termo);
					}
					else{
						eventoHoraFim = std::stoi(termo);
					}
				}
		}
		contador++;
	}

		// Associa o responsável do evento com o evento em questão
		for(Adulto* adulto : adultos){
			if(adulto->get_id() == std::stoi(eventoResponsavel_id)){
				eventoResponsavel = adulto;
			}
		}
		for(Idoso* idoso : idosos){
			if(idoso->get_id() == std::stoi(eventoResponsavel_id)){
				eventoResponsavel = idoso;
			}
		}

		if(eventoTipo == "boate"){
			boates.push_back(new Boate(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoQuota_idoso, eventoHoraInicio, eventoHoraFim));
		}
		else if(eventoTipo == "show"){
			shows.push_back(new Show(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoQuota_idoso, eventoAberturaPortoes, eventoArtistas));
		}
		else if(eventoTipo == "cinema"){
			cinemas.push_back(new Cinema(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoHorariosInicio, eventoDuracao));			
		}
		else if(eventoTipo == "fantoche"){
			teatros.push_back(new TeatroFantoche(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoHorariosInicio));
		}

		eventoCapacidades.clear();
		eventoPrecos.clear();
		eventoHorariosInicio.clear();
		eventoArtistas.clear();
		eventoResponsavel = nullptr;
		eventoQuota_idoso = 0;
	}
	eventosDatabase.close();

	MaquinaFantoche maquina(teatros, adultos, criancas, idosos);
	// maquina.show_eventos();
	// maquina.show_horarios(5);
	maquina.buy_ingresso(5, 1, 1);
	
	// Desaloca todos os ponteiros dinâmicos utilizados
	for (Crianca *crianca : criancas){
		delete crianca;
	}
	for (Adulto *adulto : adultos){
		delete adulto;
	}
	for (Idoso *idoso : idosos){
		delete idoso;
	}
	for(Boate *boate : boates){
		delete boate;
	}
	for(Show *show : shows){
		delete show;
	}
	for(Cinema *cinema : cinemas){
		delete cinema;
	}
	for(TeatroFantoche *teatro : teatros){
		delete teatro;
	}

	return 0;
}