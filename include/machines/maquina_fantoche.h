#ifndef MAQUINA_FANTOCHE_H
#define MAQUINA_FANTOCHE_H

#include <iostream>
#include <vector>

#include "events/teatro_fantoche.h"

class MaquinaFantoche {
  private:
    std::vector<TeatroFantoche> evento_fantoche;
    int total_ingressos;

  public:
    MaquinaFantoche(std::vector<TeatroFantoche> evento_fantoche);
    void show_eventos();
    void show_horarios(int evento_id);
    void buy_ingresso(int evento_id, int horario_key);
};

#endif