#include <iostream>
#include <stdlib.h>

#include "usuarios/usuario.h"
#include "eventos/evento.h"

#include "maquinas/maquina_fantoche.h"
#include "maquinas/maquina_cinema.h"
#include "maquinas/maquina_boate.h"
#include "maquinas/maquina_show.h"

#include "helpers/usuarios/setup.h"
#include "helpers/usuarios/list.h"
#include "helpers/eventos/setup.h"

enum menu1 {CARREGA_USUARIOS_EVENTOS = 1, EXIBIR_USUARIOS, COMPRAR_INGRESSOS, SAIR };
enum menu2 {CINEMA = 1, SHOW, BOATE, FANTOCHE};

int main(){
	std::vector<Usuario*> usuarios;
	std::vector<Evento*> eventos;
	Usuario* usuario_logado = nullptr;
	int id_usuario_logado;

  int opcao_principal = 0;
  int opcao_eventos = 0;

	system("clear");
	std::cout << "=> SISTEMA DE VENDAS DE INGRESSO" << std::endl << std::endl;

  while(opcao_principal != 4) {
    std::cout << "- O que você deseja fazer?" << std::endl;

    std::cout << "1. Carregar usuarios e eventos" << std::endl;
    std::cout << "2. Exibir usuarios cadastrados" << std::endl;
    std::cout << "3. Comprar ingressos" << std::endl;
    std::cout << "4. Sair" << std::endl;
    std::cout << "=> Opcao: ";

    std::cin >> opcao_principal;

    switch(opcao_principal) {
			case CARREGA_USUARIOS_EVENTOS: {
        usuarios = setup_usuarios();
				eventos = setup_eventos(usuarios);
				system("clear");
        std::cout << "[ STATUS ] Informações de eventos e usuários carregadas com sucesso...\n\n";
	      break;
      }
      case EXIBIR_USUARIOS: {
				system("clear");
        list_usuarios(usuarios);
				std::cout << std::endl << "=> Pressione ENTER para retornar ao menu principal...";
				std::cin.ignore();
				std::cin.get();
				system("clear");
				std::cout << "[ STATUS ] Usuários listados com sucesso...\n\n";
	      break;
      }
      case COMPRAR_INGRESSOS:{
        std::cout << std::endl << "-> Insira o ID do usuário: ";
        std::cin >> id_usuario_logado;

        // Função que verifica se usuario existe
				for(Usuario* usuario : usuarios){
					if(usuario->get_id() == id_usuario_logado){
						usuario_logado = usuario;
						break;
					}
				}
        
				// Caso o usuario logado for inválido
				if(usuario_logado == nullptr){
					system("clear");
					std::cout << "[ STATUS ] O usuário escolhido não existe..." << std::endl << std::endl;
					break;
				}
        
				system("clear");
				std::cout << "[ STATUS ] Usuário autenticado..." << std::endl << std::endl;

        std::cout << "- Você deseja comprar ingressos de qual evento?" << std::endl;
        std::cout << "1. Cinema" << std::endl;
        std::cout << "2. Show" << std::endl;
        std::cout << "3. Boate" << std::endl;
        std::cout << "4. Fantoche" << std::endl;
        std::cout << "=> Opcao: ";

        std::cin >> opcao_eventos;

        switch(opcao_eventos) {
          case CINEMA: {
            std::cout << "\nCinema Selecionado!\n\n";
						break;
          }
          case SHOW: {
            std::cout << "\nShow Selecionado!\n\n";
						break;
          }
					case BOATE: {
						std::cout << "\nBoate Selecionado!\n\n";
						break;
          }
					case FANTOCHE: {
            std::cout << "\nFantoche Selecionado\n\n";
						break;
          }
					default: {
						system("clear");
						std::cout << "[ STATUS ] Opção inválida selecionada no menu de eventos..." << std::endl << std::endl;
						break;
          }
        }
					break;
      }
      case SAIR: {
				deallocate_usuarios(usuarios);
				deallocate_eventos(eventos);
        std::cout << "\n=> Aplicação sendo finalizada...\n\n";
				return 0;
      }
    }
  }
}

	// MaquinaFantoche maquina_fantoche(eventos, usuarios);
	// MaquinaCinema maquina_cinema(eventos, usuarios);
	// MaquinaBoate maquina_boate(eventos, usuarios);
	// MaquinaShow maquina_show(eventos, usuarios);

	// [TESTE] - Máquina Fantoche:
	// maquina_fantoche.show_teatros();
	// maquina_fantoche.show_horarios(5);
	// maquina_fantoche.buy_ingresso(5, 1, 1, 150);
	
	// [TESTE] - Máquina Cinema:
	// maquina_cinema.show_filmes();
	// maquina_cinema.show_horarios(1);
	// maquina_cinema.buy_ingresso(1, 1, 1, 150);

	// [TESTE] - Máquina Boate:
	// maquina_boate.show_boates();
	// maquina_boate.buy_ingresso(4, 1, 30);

	// [TESTE] - Máquina Show:
	// maquina_show.list_shows();
	// maquina_show.buy_ingresso(7, 2, 20);