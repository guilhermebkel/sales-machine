#include <iostream>

void press_enter(){
  std::cout << std::endl << "=> Pressione ENTER para retornar...";
	std::cin.ignore();
	std::cin.get();
}