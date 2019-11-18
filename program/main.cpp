#include <iostream>

#include "usuarios/usuario.h"
#include "eventos/evento.h"

#include "maquinas/maquina_fantoche.h"
#include "maquinas/maquina_cinema.h"
#include "maquinas/maquina_boate.h"
#include "maquinas/maquina_show.h"

#include "helpers/usuarios/setup.h"
#include "helpers/usuarios/list.h"
#include "helpers/eventos/setup.h"

// int main(){
	

// 	// [TESTE] - Carregar usuários e eventos
	

// 	// [TESTE] - Listar todos os usuários
	

// 	MaquinaFantoche maquina_fantoche(eventos, usuarios);
// 	MaquinaCinema maquina_cinema(eventos, usuarios);
// 	MaquinaBoate maquina_boate(eventos, usuarios);
// 	MaquinaShow maquina_show(eventos, usuarios);

// 	// [TESTE] - Máquina Fantoche:
// 	// maquina_fantoche.show_teatros();
// 	// maquina_fantoche.show_horarios(5);
// 	// maquina_fantoche.buy_ingresso(5, 1, 1, 150);
	
// 	// [TESTE] - Máquina Cinema:
// 	// maquina_cinema.show_filmes();
// 	// maquina_cinema.show_horarios(1);
// 	// maquina_cinema.buy_ingresso(1, 1, 1, 150);

// 	// [TESTE] - Máquina Boate:
// 	// maquina_boate.show_boates();
// 	// maquina_boate.buy_ingresso(4, 1, 30);

// 	// [TESTE] - Máquina Show:
// 	// maquina_show.list_shows();
// 	// maquina_show.buy_ingresso(7, 2, 20);
	
// 	// Desaloca todos os ponteiros dinâmicos utilizados
	

// 	return 0;
// }

enum menu1 {CARREGA_USUARIOS_EVENTOS = 1, EXIBIR_USUARIOS, COMPRAR_INGRESSOS, SAIR };
enum menu2 {CINEMA = 1, SHOW, BOATE, FANTOCHE};

int main(){
	std::vector<Usuario*> usuarios;
	std::vector<Evento*> eventos;
	Usuario* usuario_logado = nullptr;
	int id_usuario_logado;

  int opcao1 = 0;
  int opcao2 = 0;

  while(opcao1 != 4) {
    std::cout << "SISTEMA DE VENDAS DE INGRESSO" << "\n\n";
    std::cout << "Favor escolher uma das opcoes abaixo:\n";

    std::cout << "1. Carregar usuarios e eventos\n";
    std::cout << "2. Exibir usuarios cadastrados\n";
    std::cout << "3. Comprar ingressos\n";
    std::cout << "4. Sair\n";
    std::cout << "Opcao: ";

    std::cin >> opcao1;

    switch(opcao1) {
			case CARREGA_USUARIOS_EVENTOS: {
        usuarios = setup_usuarios();
				eventos = setup_eventos(usuarios);
        std::cout << "\n=> Informações de eventos e usuários foram carregadas!\n\n";
	      break;
      }
      case EXIBIR_USUARIOS: {
        list_usuarios(usuarios);
	      break;
      }
      case COMPRAR_INGRESSOS:{
        std::cout << "\nOpcao 3 selecionada!\n\n";
        
        std::cout << "\nInsira o identificador do usuário: ";
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
					break;
				}
        
        std::cout << "Favor escolher uma das opcoes abaixo:\n";
        std::cout << "1. Cinema\n";
        std::cout << "2. Show\n";
        std::cout << "3. Boate\n";
        std::cout << "4. Fantoche\n";
        std::cout << "Opcao: ";

        std::cin >> opcao2;

        switch(opcao2) {
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
            std::cout << "Opcao Invalida!\n\n";
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