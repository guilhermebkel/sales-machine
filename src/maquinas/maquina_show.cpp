#include <iomanip>
#include <string>

#include "usuarios/crianca.h"

#include "maquinas/maquina_show.h"

#include "exceptions/no_tickets.h"
#include "exceptions/not_enough_funds.h"
#include "exceptions/not_enough_tickets.h"
#include "exceptions/invalid_id.h"
#include "exceptions/insufficient_permission.h"

MaquinaShow::MaquinaShow(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
  for(Evento* evento: eventos){
    Show* show = dynamic_cast<Show*>(evento);

    if(show != nullptr){
      this->shows.push_back(show);
    }
  }
  
  this->usuarios = usuarios;
}

void MaquinaShow::list_shows(){
  std::cout << "==================================================================================================" << std::endl;
  std::cout << "| ID |               Nome                | Abertura |                  Artistas                  |" << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;
  for(Show* show : this->shows){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << show->get_id() << ' ';
    std::cout << "| " << std::setw(33) << show->get_nome() << " | ";

    std::string abertura;
    abertura = std::to_string(show->get_aberturaPortoes()) + 'h';
    std::cout << std::setw(9) << abertura;
	
		std::string artistas;
		for(int i=0; i<show->get_artistas().size(); i++){
			artistas = artistas + show->get_artistas()[i];
      if(i != show->get_artistas().size()-1){
        // Caso não for o último artista do vector, adiciona uma vírgula no std::cout
        artistas = artistas + ", ";
      }
		}

    std::cout << "| " << std::setw(43) << artistas << "|" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------" << std::endl;
  }
}

void MaquinaShow::buy_ingresso(int show_id, int usuario_id, int quantidade){
  bool success = false;
  
  for(Show* show : this->shows){
    std::cout << std::left;
    if(show->get_id() == show_id){
      int preco = 99999;
      int lote;
      std::string nomeUsuario;

      for(int i=0; i<show->get_precos().size(); i++){
        if(show->get_capacidades()[i] == 0){
          // Remove lote que ja esgotou
          show->remove_lote(i);
        } 
        // Caso os ingressos estiverem esgotados
        if(show->get_capacidades().size() == 0){
          throw NoTicketsException();
        }
        
        if(show->get_precos()[i] < preco && show->get_capacidades()[i] > 0){
          preco = show->get_precos()[i];
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
      if(show->get_capacidades()[lote] < quantidade){
        throw NotEnoughTicketsException();
      }

      // Decrementa a capacidade do lote ja que um ingresso foi comprado
      show->decrement_capacidade(lote, quantidade);

      std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
      std::cout << "- Cliente: " << nomeUsuario << std::endl;
      std::cout << "- Show: " << show->get_nome() << std::endl;
      std::cout << "- Horario: " << show->get_aberturaPortoes() << 'h' << std::endl;
      std::cout << "- Preco: R$" << preco << ",00" << std::endl;

      success = true;
      break;
    }
  }

  if (!success) {
    // Caso a tag 'success' estiver como falsa, significa que 
    // nao encontrou um show com o id escolhido
    throw InvalidIdException();
  }
}