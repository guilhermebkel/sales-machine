#include <iomanip>
#include <string>

#include "usuarios/crianca.h"

#include "maquinas/maquina_boate.h"

#include "exceptions/no_tickets.h"
#include "exceptions/not_enough_funds.h"
#include "exceptions/not_enough_tickets.h"
#include "exceptions/invalid_id.h"
#include "exceptions/insufficient_permission.h"

MaquinaBoate::MaquinaBoate(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
  for(Evento* evento: eventos){
    Boate* boate = dynamic_cast<Boate*>(evento);

    if(boate != nullptr){
      this->boates.push_back(boate);
    }
  }
  
  this->usuarios = usuarios;
}

void MaquinaBoate::show_boates(){
  std::cout << "=========================================================================" << std::endl;
  std::cout << "| ID |                   Nome                      |  Inicio  |   Fim   |" << std::endl;
  std::cout << "-------------------------------------------------------------------------" << std::endl;
  for(Boate* boate : this->boates){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << boate->get_id() << ' ';
    std::cout << "| " << std::setw(43) << boate->get_nome() << " | ";

    std::string inicio;
		std::string fim;
    
		inicio = std::to_string(boate->get_horaInicio()) + 'h';
		fim = std::to_string(boate->get_horaFim()) + 'h';

    std::cout << std::setw(9) << inicio;
    std::cout << "| " << std::setw(8) << fim << '|' << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
  }
}

void MaquinaBoate::buy_ingresso(int boate_id, int usuario_id, int quantidade){
  bool success = false;
  
  for(Boate* boate : this->boates){
    std::cout << std::left;
    if(boate->get_id() == boate_id){
      int preco = 99999;
      int lote;
      std::string nomeUsuario;

      for(int i=0; i<boate->get_precos().size(); i++){
        if(boate->get_capacidades()[i] == 0){
          // Remove lote que ja esgotou
          boate->remove_lote(i);
        } 
        // Caso os ingressos estiverem esgotados
        if(boate->get_capacidades().size() == 0){
          throw NoTicketsException();
        }
        
        if(boate->get_precos()[i] < preco && boate->get_capacidades()[i] > 0){
          preco = boate->get_precos()[i];
          lote = i;
        }
      }

			for(Usuario *usuario : this->usuarios){
        if(usuario->get_id() == usuario_id){
					Crianca* crianca = dynamic_cast<Crianca*>(usuario);
					if(crianca != nullptr){
						throw InsufficientPermissionException();
					}

          if(usuario->get_saldo() < preco){
            throw NotEnoughFundsException();
          }
          else{
            usuario->set_saldo(preco);
            nomeUsuario = usuario->get_nome();
          }
        }
      }

      // Caso o usuario quiser comprar mais ingressos do que existe
      if(boate->get_capacidades()[lote] < quantidade){
        throw NotEnoughTicketsException();
      }

      // Decrementa a capacidade do lote ja que um ingresso foi comprado
      boate->decrement_capacidade(lote, quantidade);

      std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
      std::cout << "- Cliente: " << nomeUsuario << std::endl;
      std::cout << "- Boate: " << boate->get_nome() << std::endl;
      std::cout << "- Horario: " << boate->get_horaInicio() << 'h' << std::endl;
      std::cout << "- Preco: R$" << preco << ",00" << std::endl;

      success = true;
      break;
    }
  }

  if (!success) {
    // Caso a tag 'success' estiver como falsa, significa que 
    // nao encontrou um teatro com o id escolhido
    throw InvalidIdException();
  }
}