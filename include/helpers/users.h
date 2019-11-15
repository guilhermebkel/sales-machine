#include <iostream>
#include <fstream>
#include <vector>

#include "usuarios/usuario.h"
#include "usuarios/crianca.h"
#include "usuarios/adulto.h"
#include "usuarios/idoso.h"

std::vector<Usuario*> setup_usuarios(){
	std::ifstream usuariosDatabase("database/usuarios.csv");
	
	std::string usuarioId, usuarioTipo, usuarioNome, usuarioIdade, usuarioSaldo, usuarioResponsavel_id;
	
	std::vector<Crianca*> usuarioDependentes;
	Adulto* usuarioResponsavel;

	std::vector<Usuario*> usuarios;

	while(usuariosDatabase.good()){
		std::getline(usuariosDatabase, usuarioId, ',');
		std::getline(usuariosDatabase, usuarioTipo, ',');
		std::getline(usuariosDatabase, usuarioNome, ',');
		std::getline(usuariosDatabase, usuarioIdade, ',');

		// Verifica o tipo da linha atual
		// para decidir quando ler o último termo como '\n'
		// visto que a forma de leitura de criancas e adultos é diferente
		if(!usuarioTipo.compare("adulto")){
			std::getline(usuariosDatabase, usuarioSaldo, '\n');
			usuarios.push_back(new Adulto(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo)));
		}
		else if(!usuarioTipo.compare("idoso")){
			std::getline(usuariosDatabase, usuarioSaldo, '\n');
			usuarios.push_back(new Idoso(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo)));
		}
		else if(!usuarioTipo.compare("crianca")){
			std::getline(usuariosDatabase, usuarioSaldo, ',');
			std::getline(usuariosDatabase, usuarioResponsavel_id, '\n');

			// Associa o adulto respoonsavel com seu filho.
			for(Usuario* usuario : usuarios){
				Adulto* adulto = dynamic_cast<Adulto*>(usuario);
				Idoso* idoso = dynamic_cast<Idoso*>(usuario);

				// Caso for adulto
				if(adulto != nullptr && adulto->get_id() == std::stoi(usuarioResponsavel_id)){
					usuarioResponsavel = adulto;
					break;
				}
				// Caso for idoso
				else if(idoso != nullptr && idoso->get_id() == std::stoi(usuarioResponsavel_id)){
					usuarioResponsavel = idoso;
					break;
				}
			}

			usuarios.push_back(new Crianca(std::stoi(usuarioId), usuarioNome, std::stoi(usuarioIdade), std::stof(usuarioSaldo), usuarioResponsavel));
		}

		usuarioResponsavel = nullptr;
	}
	usuariosDatabase.close();

	// Faz as associações dos dependentes de cada adulto
	for(Usuario* usuario : usuarios){
		Adulto* adulto = dynamic_cast<Adulto*>(usuario);
		Idoso* idoso = dynamic_cast<Idoso*>(usuario);

		for(Usuario* usuario : usuarios){
			Crianca* crianca = dynamic_cast<Crianca*>(usuario);
			// Caso for adulto + crianca
			if(adulto != nullptr && crianca != nullptr && adulto->get_id() == crianca->get_responsavel()->get_id()){
				usuarioDependentes.push_back(crianca);
			}
			// Caso for idoso + crianca
			else if(idoso != nullptr && crianca != nullptr && idoso->get_id() == crianca->get_responsavel()->get_id()){
				usuarioDependentes.push_back(crianca);
			}
		}

		// Caso for adulto
		if(usuarioDependentes.size() && adulto != nullptr){
			adulto->set_dependentes(usuarioDependentes);
			usuarioDependentes.clear();
		}
		// Caso for idoso
		else if(usuarioDependentes.size() && idoso != nullptr){
			idoso->set_dependentes(usuarioDependentes);
			usuarioDependentes.clear();
		}
	}

	return usuarios;
}

void deallocate_usuarios(std::vector<Usuario*> usuarios){
	for (Usuario *usuario : usuarios){
		delete usuario;
	}
}