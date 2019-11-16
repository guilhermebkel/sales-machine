#ifndef MAQUINA_FANTOCHE_H
#define MAQUINA_FANTOCHE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "eventos/evento.h"
#include "eventos/teatro_fantoche.h"
#include "usuarios/usuario.h"

class MaquinaFantoche {
  private:
    std::vector<TeatroFantoche*> teatros;
    std::vector<Usuario*> usuarios;

  public:
    MaquinaFantoche(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios);
    void show_teatros();
    void show_horarios(int teatro_id);
    void buy_ingresso(int teatro_id, int horario_key, int usuario_id, int quantidade);
};

#endif