#ifndef MAQUINA_FANTOCHE_H
#define MAQUINA_FANTOCHE_H

#include <iostream>
#include <vector>

#include "events/teatro_fantoche.h"
#include "users/adulto.h"
#include "users/crianca.h"
#include "users/idoso.h"

class MaquinaFantoche {
  private:
    std::vector<TeatroFantoche*> eventos;
    std::vector<Adulto*> adultos;
    std::vector<Crianca*> criancas;
    std::vector<Idoso*> idosos;
    int total_ingressos = 10;

  public:
    MaquinaFantoche(std::vector<TeatroFantoche*> eventos, std::vector<Adulto*> adultos, std::vector<Crianca*> criancas, std::vector<Idoso*> idosos);
    void show_eventos();
    void show_horarios(int evento_id);
    void buy_ingresso(int evento_id, int horario_key, int usuario_id);
};

#endif