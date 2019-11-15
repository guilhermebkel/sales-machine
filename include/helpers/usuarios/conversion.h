#include "usuarios/crianca.h"
#include "usuarios/adulto.h"
#include "usuarios/idoso.h"
#include "usuarios/usuario.h"

std::vector<Crianca*> get_criancas(std::vector<Usuario*> usuarios){
	std::vector<Crianca*> criancas;

	for(Usuario* usuario: usuarios){
    Crianca* crianca = dynamic_cast<Crianca*>(usuario);

    if(crianca != nullptr){
      criancas.push_back(crianca);
    }
  }

	return criancas;
}

std::vector<Adulto*> get_adultos(std::vector<Usuario*> usuarios){
	std::vector<Adulto*> adultos;

	for(Usuario* usuario: usuarios){
    Adulto* adulto = dynamic_cast<Adulto*>(usuario);

    if(adulto != nullptr){
      adultos.push_back(adulto);
    }
  }

	return adultos;
}

std::vector<Idoso*> get_idosos(std::vector<Usuario*> usuarios){
	std::vector<Idoso*> idosos;

	for(Usuario* usuario: usuarios){
    Idoso* idoso = dynamic_cast<Idoso*>(usuario);

    if(idoso != nullptr){
      idosos.push_back(idoso);
    }
  }

	return idosos;
}