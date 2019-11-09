#include <iomanip>
#include <string>

#include "machines/maquina_fantoche.h"

MaquinaFantoche::MaquinaFantoche(std::vector<TeatroFantoche> evento_fantoche){
  this->evento_fantoche = evento_fantoche;
}

void MaquinaFantoche::show_eventos(){
  std::cout << "=========================================================================" << std::endl;
  std::cout << "| ID |                   Nome                      |      Horarios      |" << std::endl;
  std::cout << "-------------------------------------------------------------------------" << std::endl;
  for(auto evento : this->evento_fantoche){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << evento.get_id() << ' ';
    std::cout << "| " << std::setw(43) << evento.get_nome() << " | ";

    std::string horarios;
    for(int i=0; i<evento.get_horarios().size(); i++){
      horarios = horarios + std::to_string(evento.get_horarios()[i]) + 'h';
      if(i != evento.get_horarios().size()-1){
        // Caso não for o último horario do vector, adiciona uma vírgula no std::cout
        horarios = horarios + ", ";
      }
    }
    std::cout << std::setw(19) << horarios;
    std::cout << '|' << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
  }
}