#include <iostream>

#include "usuarios/usuario.h"
#include "eventos/evento.h"
#include "maquinas/maquina_fantoche.h"

#include "helpers/usuarios/setup.h"
#include "helpers/eventos/setup.h"

int main(){
	std::vector<Usuario*> usuarios;
	std::vector<Evento*> eventos;

	usuarios = setup_usuarios();
	eventos = setup_eventos(usuarios);

	MaquinaFantoche maquina(eventos, usuarios);
	// maquina.show_eventos();
	// maquina.show_horarios(5);
	maquina.buy_ingresso(5, 1, 1);
	
	// Desaloca todos os ponteiros dinâmicos utilizados
	deallocate_usuarios(usuarios);
	deallocate_eventos(eventos);

	return 0;
}