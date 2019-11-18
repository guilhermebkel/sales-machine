
#include <iostream>
#include <vector>
#include <iomanip>

#include "usuarios/usuario.h"

void list_usuarios(std::vector<Usuario*> usuarios){
	std::cout << "========================================================" << std::endl;
  std::cout << "| ID |            Nome             | Idade |   Saldo   |" << std::endl;
  std::cout << "--------------------------------------------------------" << std::endl;
  for(Usuario* usuario : usuarios){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << usuario->get_id() << ' ';
    std::cout << "| " << std::setw(27) << usuario->get_nome() << " | ";
    std::cout << std::setw(6) << usuario->get_idade() << "| ";
    std::cout << std::setw(10) << "R$" + std::to_string((int)usuario->get_saldo()) + ",00 " << '|' << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
  }
}