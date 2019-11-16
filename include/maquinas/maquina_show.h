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
    std::vector<Show*> eventos;
    std::vector<Usuario*> usuarios;

  public:
    MaquinaShow(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
    void show_eventos();
    void show_horarios(int evento_id);
    void buy_ingresso(int evento_id, int horario_key, int usuario_id, int quantidade);
};

#endif