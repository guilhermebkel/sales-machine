#ifndef MAQUINA_CINEMA_H
#define MAQUINA_CINEMA_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "eventos/evento.h"
#include "eventos/cinema.h"
#include "usuarios/usuario.h"

class MaquinaCinema {
  private:
    std::vector<Cinema*> filmes;
    std::vector<Usuario*> usuarios;

  public:
    MaquinaCinema(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
    void show_filmes();
    void show_horarios(int filme_id);
    void buy_ingresso(int filme_id, int horario_key, int usuario_id, int quantidade);
};

#endif