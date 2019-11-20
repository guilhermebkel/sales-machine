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
  int preco = 99999, lote;
  std::string nome_comprador;
  Usuario* comprador;
  Show* show_escolhido = nullptr;
  Crianca* crianca = nullptr;
  
  for(Show* show : this->shows){
    if(show->get_id() == show_id){
      show_escolhido = show;
      break;
    }
  }

  if(show_escolhido == nullptr){
    throw InvalidIdException();
  }

  // Caso os ingressos estiverem esgotados
  if(show_escolhido->get_capacidades().size() == 0){
    throw NoTicketsException();
  }

  // Iteração para pegar o lote de menor valor
  for(int i=0; i<show_escolhido->get_precos().size(); i++){  
    if(show_escolhido->get_precos()[i] < preco){
      preco = show_escolhido->get_precos()[i] * quantidade;
      lote = i;
    }
  }

	for(Usuario *usuario : this->usuarios){
    if(usuario->get_id() == usuario_id){
      comprador = usuario;
			crianca = dynamic_cast<Crianca*>(usuario);
			break;
    }
  }

  if(crianca != nullptr){
		throw InsufficientPermissionException();
	}
  else if(comprador->get_saldo() < preco){
    throw NotEnoughFundsException();
  }
  else{
    comprador->set_saldo(preco);
    comprador->set_ingressos_comprados(quantidade);
    nome_comprador = comprador->get_nome();
  }

  // Caso o comprador quiser comprar mais ingressos do que existe
  if(show_escolhido->get_capacidades()[lote] < quantidade){
    throw NotEnoughTicketsException();
  }

  // Decrementa a capacidade do lote ja que um ingresso foi comprado
  show_escolhido->decrement_capacidade(lote, quantidade);

  // Aumenta a quantidade de ingressos que foram vendidos
  show_escolhido->set_ingressos_vendidos(quantidade);

  // Remove lote que ja esgotou
  if(show_escolhido->get_capacidades()[lote] == 0){
    show_escolhido->remove_lote(lote);
  }

  std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
  std::cout << "- Cliente: " << nome_comprador << std::endl;
  std::cout << "- Show: " << show_escolhido->get_nome() << std::endl;
  std::cout << "- Horario: " << show_escolhido->get_aberturaPortoes() << 'h' << std::endl;
  std::cout << "- Preco: R$" << preco << ",00" << std::endl;
}