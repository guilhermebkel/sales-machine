#include <iostream>
#include <vector>

#include "usuarios/crianca.h"

Crianca* getDependente(int usuario_id, std::vector<Crianca*> criancas){
  Crianca* dependente = nullptr;

  for(Crianca *crianca : criancas){
    if(crianca->get_id() == usuario_id){
      dependente = crianca;
      break;
    }
  }

  return dependente;
}