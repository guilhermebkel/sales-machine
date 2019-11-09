#ifndef MAQUINA_FANTOCHE_H
#define MAQUINA_FANTOCHE_H

#include <iostream>
#include <vector>

#include "events/teatro_fantoche.h"

class MaquinaFantoche {
  private:
    std::vector<TeatroFantoche*> eventos;
    int total_ingressos = 10;

  public:
    MaquinaFantoche(std::vector<TeatroFantoche*> evento);
    void show_eventos();
    void show_horarios(int evento_id);
    void buy_ingresso(int evento_id, int horario_key);
};

#endif