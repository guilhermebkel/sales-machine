#ifndef MAQUINA_SHOW_H
#define MAQUINA_SHOW_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "eventos/evento.h"
#include "eventos/show.h"
#include "usuarios/usuario.h"

class MaquinaShow {
  private:
    std::vector<Show*> shows;
    std::vector<Usuario*> usuarios;

  public:
    MaquinaShow(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
    void list_shows();
    void buy_ingresso(int show_id, int usuario_id, int quantidade);
};

#endif