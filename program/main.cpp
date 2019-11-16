#include <iostream>

#include "usuarios/usuario.h"
#include "eventos/evento.h"

#include "maquinas/maquina_fantoche.h"
#include "maquinas/maquina_cinema.h"
#include "maquinas/maquina_boate.h"

#include "helpers/usuarios/setup.h"
#include "helpers/eventos/setup.h"

int main(){
	std::vector<Usuario*> usuarios;
	std::vector<Evento*> eventos;

	usuarios = setup_usuarios();
	eventos = setup_eventos(usuarios);

	MaquinaFantoche maquina_fantoche(eventos, usuarios);
	MaquinaCinema maquina_cinema(eventos, usuarios);
	MaquinaBoate maquina_boate(eventos, usuarios);

	// [TESTE] - Máquina Fantoche:
	// maquina_fantoche.show_eventos();
	// maquina_fantoche.show_horarios(5);
	// maquina_fantoche.buy_ingresso(5, 1, 1, 150);
	
	// [TESTE] - Máquina Cinema:
	// maquina_cinema.show_filmes();
	// maquina_cinema.show_horarios(1);
	// maquina_cinema.buy_ingresso(1, 1, 1, 150);

	// [TESTE] - Máquina Boate:
	// maquina_boate.show_boates();
	// maquina_boate.buy_ingresso(4, 1, 2);
	
	// Desaloca todos os ponteiros dinâmicos utilizados
	deallocate_usuarios(usuarios);
	deallocate_eventos(eventos);

	return 0;
}