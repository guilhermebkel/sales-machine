#include <iomanip>

#include "usuarios/adulto.h"

#include "totem/totem.h"

#include "helpers/usuarios/get_dependente.h"

#include "exceptions/invalid_id.h"

std::set<int, unique_id> Totem::eventos_modificados;
std::set<int, unique_id> Totem::usuarios_modificados;
//
// Adiciona import customizado de "helpers/screen/*"
// para evitar erro de dependência circular
void status(std::string message);
void press_enter();
void clear();

void Totem::boot_cinema(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;
	
	MaquinaCinema maquina_cinema(eventos, usuarios);
								
	clear();
	maquina_cinema.show_filmes();
	std::cout << std::endl << "=> Insira a ID do filme desejado: ";
	std::cin >> id_evento;

	clear();
	maquina_cinema.show_horarios(id_evento);
	std::cout << std::endl << "=> Insira a ID do horario desejado: ";
	std::cin >> id_horario;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	clear();
	maquina_cinema.buy_ingresso(id_evento, id_horario, usuario_id, quantidade_ingressos);
	press_enter();

	status("Ingressos para cinema comprados com sucesso...");
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::boot_show(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;
	
	MaquinaShow maquina_show(eventos, usuarios);

	clear();
	maquina_show.list_shows();
	std::cout << std::endl << "=> Insira a ID do show desejado: ";
	std::cin >> id_evento;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	clear();
	maquina_show.buy_ingresso(id_evento, usuario_id, quantidade_ingressos);
	press_enter();

	status("Ingressos para show comprados com sucesso...");
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::boot_boate(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;
								
	MaquinaBoate maquina_boate(eventos, usuarios);

	clear();
	maquina_boate.show_boates();;
	std::cout << std::endl << "=> Insira a ID da boate desejada: ";
	std::cin >> id_evento;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	clear();
	maquina_boate.buy_ingresso(id_evento, usuario_id, quantidade_ingressos);
	press_enter();

	status("Ingressos para boate comprados com sucesso...");
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::boot_fantoche(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;
	Adulto* adulto = nullptr;

	MaquinaFantoche maquina_fantoche(eventos, usuarios);

	clear();
	maquina_fantoche.show_teatros();
	std::cout << std::endl << "=> Insira a ID do teatro desejado: ";
	std::cin >> id_evento;

	clear();
	maquina_fantoche.show_horarios(id_evento);
	std::cout << std::endl << "=> Insira a ID do horario desejado: ";
	std::cin >> id_horario;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	// Verifica se o comprador é um adulto. Caso ele for, pede o ID
	// de seu usuario dependente
	for(Usuario *usuario : usuarios){
	  Adulto* adulto = dynamic_cast<Adulto*>(usuario);

    if(usuario->get_id() == usuario_id && adulto != nullptr){
			std::cout << std::endl << "=> Digite a ID do seu dependente: ";
			std::cin >> usuario_id;

			Crianca* comprador = getDependente(usuario_id, adulto->get_dependentes());
			if(comprador == nullptr){
				throw InvalidIdException();
			}
    }
  }

	clear();
	maquina_fantoche.buy_ingresso(id_evento, id_horario, usuario_id, quantidade_ingressos);
	press_enter();

	status("Ingressos para boate comprados com sucesso...");
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::get_report(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	std::cout << "=================================================================" << std::endl;
	std::cout << "|               USUARIOS QUE COMPRARAM INGRESSOS                |" << std::endl;
	std::cout << "=================================================================" << std::endl;
	std::cout << "| ID |                     Nome                     | Ingressos |" << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;

	for(int usuario_id : usuarios_modificados){
		for(Usuario* usuario : usuarios){
			if(usuario->get_id() == usuario_id){
				std::cout << "| " << std::setw(3) << usuario->get_id() << "| ";
				std::cout << std::setw(45) << usuario->get_nome() << "| ";
				std::cout << std::setw(10) << usuario->get_ingressos_comprados() << '|' << std::endl;
				std::cout << "-----------------------------------------------------------------" << std::endl;
			}
		}
	}

	std::cout << std::endl << std::endl;

	std::cout << "=================================================================" << std::endl;
	std::cout << "|                EVENTOS QUE VENDERAM INGRESSOS                 |" << std::endl;
	std::cout << "=================================================================" << std::endl;
	std::cout << "| ID |                     Nome                     | Ingressos |" << std::endl;
	std::cout << "-----------------------------------------------------------------" << std::endl;

	for(int evento_id : eventos_modificados){
		for(Evento* evento : eventos){
			if(evento->get_id() == evento_id){
				std::cout << "| " << std::setw(3) << evento->get_id() << "| ";
				std::cout << std::setw(45) << evento->get_nome() << "| ";
				std::cout << std::setw(10) << evento->get_ingressos_vendidos() << '|' << std::endl;
				std::cout << "-----------------------------------------------------------------" << std::endl;
			}
		}
	}
}