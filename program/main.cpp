#include <iostream>
#include <stdlib.h>

#include "usuarios/usuario.h"
#include "eventos/evento.h"

#include "totem/totem.h"

#include "helpers/usuarios/setup.h"
#include "helpers/usuarios/list.h"
#include "helpers/eventos/setup.h"
#include "helpers/screen/clear.h"
#include "helpers/screen/status.h"

enum menu1 {CARREGA_USUARIOS_EVENTOS = 1, EXIBIR_USUARIOS, COMPRAR_INGRESSOS, SAIR };
enum menu2 {CINEMA = 1, SHOW, BOATE, FANTOCHE, CONCLUIR};

int main(){
	std::vector<Usuario*> usuarios;
	std::vector<Evento*> eventos;
	Usuario* usuario_logado = nullptr;
	int id_usuario_logado, id_evento, id_horario, quantidade_ingressos;

  int opcao_principal = 0;
  int opcao_eventos = 0;

	status("Sistema de vendas de ingressos iniciado...");

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

				status("Informações de eventos e usuários carregadas com sucesso...");
	      break;
      }
      case EXIBIR_USUARIOS: {
				clear();

        list_usuarios(usuarios);
				std::cout << std::endl << "=> Pressione ENTER para retornar ao menu principal...";
				std::cin.ignore();
				std::cin.get();

				status("Usuários listados com sucesso...");
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
					else{
						usuario_logado = nullptr;
					}
				}
        
				// Caso o usuario logado for inválido
				if(usuario_logado == nullptr){
					status("O usuário escolhido não existe...");
					break;
				}
        
				status("Usuário autenticado...");

				while(opcao_eventos != 5){
					std::cout << "- Você deseja comprar ingressos de qual evento? (Digite 5 para concluir)" << std::endl;
					std::cout << "1. Cinema" << std::endl;
					std::cout << "2. Show" << std::endl;
					std::cout << "3. Boate" << std::endl;
					std::cout << "4. Fantoche" << std::endl;
					std::cout << "5. Concluir" << std::endl;
					std::cout << "=> Opcao: ";

					std::cin >> opcao_eventos;

					switch(opcao_eventos) {
						case CINEMA: {
							try{
								Totem::boot_cinema(usuario_logado->get_id(), eventos, usuarios);
							}
							catch(std::exception &error){
								status(error.what());
							}
							break;
						}
						case SHOW: {
							try{
								Totem::boot_show(usuario_logado->get_id(), eventos, usuarios);
							}
							catch(std::exception &error){
								status(error.what());
							}
							break;
						}
						case BOATE: {
							try{
								Totem::boot_boate(usuario_logado->get_id(), eventos, usuarios);
							}
							catch(std::exception &error){
								status(error.what());
							}
							break;
						}
						case FANTOCHE: {
							try{
								Totem::boot_fantoche(usuario_logado->get_id(), eventos, usuarios);
							}
							catch(std::exception &error){
								status(error.what());
							}
							break;
						}
						case CONCLUIR: {
							clear();
							Totem::get_report(eventos, usuarios);
							std::cout << std::endl << "=> Pressione ENTER para retornar ao menu principal...";
							std::cin.ignore();
							std::cin.get();
							break;
						}
						default: {
							status("Opção inválida selecionada no menu de eventos...");
							break;
						}
					}
				}

				opcao_eventos = 0;
				status("Saida do menu de eventos efetuada com sucesso...");
				break;
      }
      case SAIR: {
				deallocate_usuarios(usuarios);
				deallocate_eventos(eventos);
        std::cout << std::endl << "=> Aplicação sendo finalizada..." << std::endl << std::endl;
				return 0;
      }
			default: {
				status("Opção inválida selecionada no menu principal...");
				break;
			}
    }
  }
}