#ifndef MAQUINA_BOATE_H
#define MAQUINA_BOATE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "eventos/evento.h"
#include "eventos/boate.h"
#include "usuarios/usuario.h"

class MaquinaBoate {
  private:
    std::vector<Boate*> boates;
    std::vector<Usuario*> usuarios;

  public:
    MaquinaBoate(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
    void show_boates();
    void show_horarios(int evento_id);
    void buy_ingresso(int evento_id, int usuario_id, int quantidade);
};

#endif