#ifndef TOTEM_H
#define TOTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "eventos/evento.h"
#include "usuarios/usuario.h"

#include "maquinas/maquina_fantoche.h"
#include "maquinas/maquina_cinema.h"
#include "maquinas/maquina_boate.h"
#include "maquinas/maquina_show.h"

struct unique_id{
	bool operator()(const int id_1, const int id_2) const {
		return id_1 != id_2;
	}
};

class Totem {
	private:
		static std::set<int, unique_id> eventos_modificados;
		static std::set<int, unique_id> usuarios_modificados;

  public:	
		static void boot_cinema(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
		static void boot_show(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
		static void boot_boate(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
		static void boot_fantoche(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
		static void get_report(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
};

#endif