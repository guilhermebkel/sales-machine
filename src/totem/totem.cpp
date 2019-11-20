#include <iomanip>

#include "totem/totem.h"

std::set<int, unique_id> Totem::eventos_modificados;
std::set<int, unique_id> Totem::usuarios_modificados;

void Totem::boot_cinema(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;
	
	MaquinaCinema maquina_cinema(eventos, usuarios);
								
	system("clear");
	maquina_cinema.show_filmes();
	std::cout << std::endl << "=> Insira a ID do filme desejado: ";
	std::cin >> id_evento;

	system("clear");
	maquina_cinema.show_horarios(id_evento);
	std::cout << std::endl << "=> Insira a ID do horario desejado: ";
	std::cin >> id_horario;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	system("clear");
	maquina_cinema.buy_ingresso(id_evento, id_horario, usuario_id, quantidade_ingressos);
	std::cout << std::endl << "=> Pressione ENTER para retornar ao menu de eventos...";
	std::cin.ignore();
	std::cin.get();

	system("clear");
	std::cout << "[ STATUS ] Ingressos para cinema comprados com sucesso...\n\n";
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::boot_show(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;
	
	MaquinaShow maquina_show(eventos, usuarios);

	system("clear");
	maquina_show.list_shows();
	std::cout << std::endl << "=> Insira a ID do show desejado: ";
	std::cin >> id_evento;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	system("clear");
	maquina_show.buy_ingresso(id_evento, usuario_id, quantidade_ingressos);
	std::cout << std::endl << "=> Pressione ENTER para retornar ao menu de eventos...";
	std::cin.ignore();
	std::cin.get();

	system("clear");
	std::cout << "[ STATUS ] Ingressos para show comprados com sucesso...\n\n";
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::boot_boate(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;
								
	MaquinaBoate maquina_boate(eventos, usuarios);

	system("clear");
	maquina_boate.show_boates();;
	std::cout << std::endl << "=> Insira a ID da boate desejada: ";
	std::cin >> id_evento;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	system("clear");
	maquina_boate.buy_ingresso(id_evento, usuario_id, quantidade_ingressos);
	std::cout << std::endl << "=> Pressione ENTER para retornar ao menu de eventos...";
	std::cin.ignore();
	std::cin.get();

	system("clear");
	std::cout << "[ STATUS ] Ingressos para boate comprados com sucesso...\n\n";
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::boot_fantoche(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	int id_evento, id_horario, quantidade_ingressos;

	MaquinaFantoche maquina_fantoche(eventos, usuarios);

	system("clear");
	maquina_fantoche.show_teatros();
	std::cout << std::endl << "=> Insira a ID do teatro desejado: ";
	std::cin >> id_evento;

	system("clear");
	maquina_fantoche.show_horarios(id_evento);
	std::cout << std::endl << "=> Insira a ID do horario desejado: ";
	std::cin >> id_horario;
	std::cout << std::endl << "=> Quantos ingressos você deseja comprar? ";
	std::cin >> quantidade_ingressos;

	system("clear");
	maquina_fantoche.buy_ingresso(id_evento, id_horario, usuario_id, quantidade_ingressos);
	std::cout << std::endl << "=> Pressione ENTER para retornar ao menu de eventos...";
	std::cin.ignore();
	std::cin.get();

	system("clear");
	std::cout << "[ STATUS ] Ingressos para boate comprados com sucesso...\n\n";
	eventos_modificados.insert(id_evento);
	usuarios_modificados.insert(usuario_id);
}

void Totem::get_report(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	std::cout << "=============================================" << std::endl;
	std::cout << "|     USUARIOS QUE COMPRARAM INGRESSOS      |" << std::endl;
	std::cout << "=============================================" << std::endl;
	std::cout << "| ID |           Nome           | Ingressos |" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;

	for(int usuario_id : usuarios_modificados){
		for(Usuario* usuario : usuarios){
			if(usuario->get_id() == usuario_id){
				std::cout << "| " << std::setw(3) << usuario->get_id() << "| ";
				std::cout << std::setw(25) << usuario->get_nome() << "| ";
				std::cout << std::setw(10) << usuario->get_ingressos_comprados() << '|' << std::endl;
				std::cout << "---------------------------------------------" << std::endl;
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