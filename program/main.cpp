#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "users/usuario.h"
#include "users/crianca.h"
#include "users/adulto.h"
#include "users/idoso.h"

#include "events/boate.h"
#include "events/show.h"
#include "events/cinema.h"
#include "events/teatro_fantoche.h"

#include "machines/maquina_fantoche.h"

int main(){
	std::string linha, termo;
	std::istringstream stream_string;
	int contador;

	std::string usuarioId, usuarioTipo, usuarioNome, usuarioIdade, usuarioSaldo, usuarioResponsavel_id;
	std::vector<Crianca*> usuarioDependentes;
	Adulto* usuarioResponsavel = nullptr;

	std::string eventoId, eventoNome, eventoPublico, eventoTipo, eventoResponsavel_id, eventoNumTipos;
	int eventoCapacidade, eventoPreco, eventoHoraInicio, eventoHoraFim, eventoAberturaPortoes, eventoHorario, eventoQuota_idoso, eventoDuracao;
	std::vector<int> eventoCapacidades, eventoPrecos, eventoHorariosInicio;
	std::vector<std::string> eventoArtistas;
	Usuario* eventoResponsavel = nullptr;

	std::vector<Crianca*> criancas;
	std::vector<Adulto*> adultos;
	std::vector<Idoso*> idosos;

	std::vector<Boate> boates;
	std::vector<Show> shows;
	std::vector<Cinema> cinemas;
	std::vector<TeatroFantoche> teatros;

	std::ifstream usuarios("database/usuarios.csv");

	while(usuarios.good()){
		
		std::getline(usuarios, usuarioId, ',');
		std::getline(usuarios, usuarioTipo, ',');
		std::getline(usuarios, usuarioNome, ',');
		std::getline(usuarios, usuarioIdade, ',');

		// Verifica o tipo da linha atual
		// para decidir quando ler o último termo como '\n'
		if(!usuarioTipo.compare("adulto")){
			std::getline(usuarios, usuarioSaldo, '\n');
			usuarioResponsavel_id = "NULL";

			adultos.push_back(new Adulto(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo), criancas));
		}
		else if(!usuarioTipo.compare("idoso")){
			std::getline(usuarios, usuarioSaldo, '\n');
			usuarioResponsavel_id = "NULL";

			idosos.push_back(new Idoso(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo), criancas));
		}
		else if(!usuarioTipo.compare("crianca")){
			std::getline(usuarios, usuarioSaldo, ',');
			std::getline(usuarios, usuarioResponsavel_id, '\n');

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
	usuarios.close();

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

	std::ifstream eventos("database/eventos.csv");

	while(eventos.good()){

		std::getline(eventos, eventoId, ',');
		std::getline(eventos, eventoPublico, ',');

		if(!eventoPublico.compare("cinema")){
			eventoTipo = eventoPublico;
		}
		else{
			std::getline(eventos, eventoTipo, ',');
		}

		std::getline(eventos, eventoNome, ',');
		std::getline(eventos, eventoResponsavel_id, ',');
		std::getline(eventos, eventoNumTipos, ',');

		std::getline(eventos, linha);
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
			boates.push_back(Boate(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoQuota_idoso, eventoHoraInicio, eventoHoraFim));
		}
		else if(eventoTipo == "show"){
			shows.push_back(Show(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoQuota_idoso, eventoAberturaPortoes, eventoArtistas));
		}
		else if(eventoTipo == "cinema"){
			cinemas.push_back(Cinema(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoHorariosInicio, eventoDuracao));			
		}
		else if(eventoTipo == "fantoche"){
			teatros.push_back(TeatroFantoche(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoHorariosInicio));
		}

		eventoCapacidades.clear();
		eventoPrecos.clear();
		eventoHorariosInicio.clear();
		eventoArtistas.clear();
		eventoResponsavel = nullptr;
		eventoQuota_idoso = 0;
	}
	eventos.close();

	MaquinaFantoche maquina(teatros);

	maquina.show_eventos();

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

	return 0;
}