#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "eventos/boate.h"
#include "eventos/show.h"
#include "eventos/cinema.h"
#include "eventos/teatro_fantoche.h"
#include "eventos/evento.h"

#include "usuarios/crianca.h"
#include "usuarios/adulto.h"
#include "usuarios/idoso.h"
#include "usuarios/usuario.h"

std::vector<Evento*> setup_eventos(std::vector<Usuario*> usuarios){
	std::string linha, termo;
	std::istringstream stream_string;
	int contador;
	
	std::string eventoId, eventoNome, eventoPublico, eventoTipo, eventoResponsavel_id, eventoNumTipos;
	int eventoHoraInicio, eventoHoraFim, eventoAberturaPortoes, eventoQuota_idoso, eventoDuracao;
	std::vector<int> eventoCapacidades, eventoPrecos, eventoHorariosInicio;
	std::vector<std::string> eventoArtistas;

	Usuario* eventoResponsavel = nullptr;

	std::vector<Evento*> eventos;

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
			// Salva as capacidades do evento
			if(contador < std::stoi(eventoNumTipos)*2 && (contador%2 == 0)){
				eventoCapacidades.push_back(std::stoi(termo));
			}
			// Salva os preços do eventos
			else if(contador < std::stoi(eventoNumTipos)*2 && (contador%2 != 0)){
				eventoPrecos.push_back(std::stoi(termo));
			}
			// Começa a salvar dados de acordo com o tipo do evento
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
					std::cout << contador << '-' << termo << '=' << std::stoi(eventoNumTipos) << std::endl;
					if(contador == std::stoi(eventoNumTipos)*2 + 1){
						eventoAberturaPortoes = std::stoi(termo);
					}
					else{
						eventoArtistas.push_back(termo);
					}
				}
				else if(eventoTipo == "boate"){
					if(contador%2 != 0){
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
		for(Usuario* usuario : usuarios){
			Adulto* adulto = dynamic_cast<Adulto*>(usuario);
			Idoso* idoso = dynamic_cast<Idoso*>(usuario);

			// Caso for adulto
			if(adulto != nullptr && adulto->get_id() == std::stoi(eventoResponsavel_id)){
				eventoResponsavel = adulto;
			}
			// Caso for idoso
			else if(idoso != nullptr && idoso->get_id() == std::stoi(eventoResponsavel_id)){
				eventoResponsavel = idoso;
			}
		}

		if(eventoTipo == "boate"){
			eventos.push_back(new Boate(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoQuota_idoso, eventoHoraInicio, eventoHoraFim));
		}
		else if(eventoTipo == "show"){
			eventos.push_back(new Show(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoQuota_idoso, eventoAberturaPortoes, eventoArtistas));
		}
		else if(eventoTipo == "cinema"){
			eventos.push_back(new Cinema(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoHorariosInicio, eventoDuracao));			
		}
		else if(eventoTipo == "fantoche"){
			eventos.push_back(new TeatroFantoche(std::stoi(eventoId), eventoNome, eventoResponsavel, eventoCapacidades, eventoPrecos, eventoHorariosInicio));
		}

		eventoCapacidades.clear();
		eventoPrecos.clear();
		eventoHorariosInicio.clear();
		eventoArtistas.clear();
		eventoResponsavel = nullptr;
		eventoQuota_idoso = 0;
	}
	eventosDatabase.close();

	return eventos;
}

void deallocate_eventos(std::vector<Evento*> eventos){
	for(Evento *evento : eventos){
		delete evento;
	}
}