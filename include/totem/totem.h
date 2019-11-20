#ifndef TOTEM_H
#define TOTEM_H

#include <iostream>
#include <string>
#include <vector>

#include "eventos/evento.h"
#include "usuarios/usuario.h"

#include "maquinas/maquina_fantoche.h"
#include "maquinas/maquina_cinema.h"
#include "maquinas/maquina_boate.h"
#include "maquinas/maquina_show.h"

class Totem {
  public:	
		static void boot_cinema(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
		static void boot_show(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
		static void boot_boate(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
		static void boot_fantoche(int usuario_id, std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
};

#endif