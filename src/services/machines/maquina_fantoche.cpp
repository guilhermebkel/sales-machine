#include "machines/maquina_fantoche.h"

#include "prettyprint.hpp"

MaquinaFantoche::MaquinaFantoche(std::vector<TeatroFantoche> evento_fantoche){
  this->evento_fantoche = evento_fantoche;
}

void MaquinaFantoche::show_eventos(){
  for(auto evento : this->evento_fantoche){
    std::cout << evento.get_id() << std::endl;
  }
}