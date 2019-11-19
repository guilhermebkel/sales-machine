#include "totem/totem.h"

void Totem::initialize(std::string tipo_evento, int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	if(tipo_evento == "cinema"){
		boot_cinema(usuario_id, eventos, usuarios);
	}
	else if(tipo_evento == "show"){
		boot_show(usuario_id, eventos, usuarios);
	}
	else if(tipo_evento == "boate"){
		boot_boate(usuario_id, eventos, usuarios);
	}
	else if(tipo_evento == "fantoche"){
		boot_fantoche(usuario_id, eventos, usuarios);
	}
}

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
	std::cout << "[ STATUS ] Ingressos para cinema comprados com sucesso...\n\n";
}