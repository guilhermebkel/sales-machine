#include <iomanip>
#include <string>

#include "maquinas/maquina_cinema.h"

#include "exceptions/no_tickets.h"
#include "exceptions/not_enough_funds.h"
#include "exceptions/not_enough_tickets.h"
#include "exceptions/invalid_id.h"

MaquinaCinema::MaquinaCinema(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
	for(Evento* evento: eventos){
    Cinema* filme = dynamic_cast<Cinema*>(evento);

    if(filme != nullptr){
      this->filmes.push_back(filme);
    }
  }
	
  this->usuarios = usuarios;
}

void MaquinaCinema::show_filmes(){
  std::cout << "=====================================================================================" << std::endl;
  std::cout << "| ID |                   Nome                      |      Horarios      |  Duracao  |" << std::endl;
  std::cout << "-------------------------------------------------------------------------------------" << std::endl;
  for(Cinema* filme : this->filmes){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << filme->get_id() << ' ';
    std::cout << "| " << std::setw(43) << filme->get_nome() << " | ";

    std::string horarios;
    for(int i=0; i<filme->get_horarios().size(); i++){
      horarios = horarios + std::to_string(filme->get_horarios()[i]) + 'h';
      if(i != filme->get_horarios().size()-1){
        // Caso não for o último horario do vector, adiciona uma vírgula no std::cout
        horarios = horarios + ", ";
      }
    }
    std::cout << std::setw(19) << horarios;
    std::cout << "| ";

		std::string duracao;
		duracao = std::to_string(filme->get_duracao()) + 'h';
		std::cout << std::setw(10) << duracao << '|' << std::endl;
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
  }
}

void MaquinaCinema::show_horarios(int filme_id){
  bool success = false;

  std::cout << "==================" << std::endl;
  std::cout << "| ID |  Horario  |" << std::endl;
  std::cout << "------------------" << std::endl;
  for(Cinema* filme : this->filmes){
    std::cout << std::left;
    if(filme->get_id() == filme_id){
      for(int i=0; i<filme->get_horarios().size(); i++){
        std::cout << "| " << std::setw(2) << i << ' ';

        std::string horario = std::to_string(filme->get_horarios()[i]) + 'h';

        std::cout << "| " << std::setw(10) << horario;
        std::cout << '|' << std::endl;
        std::cout << "------------------" << std::endl;
      }
      success = true;
      break;
    }
  }

  if (!success) {
    // Caso a tag 'success' estiver como falsa, significa que 
    // nao encontrou um filme com o id escolhido
    throw InvalidIdException();
  }
}

void MaquinaCinema::buy_ingresso(int filme_id, int horario_key, int usuario_id, int quantidade){
  bool success = false;
  
  for(Cinema* filme : this->filmes){
    std::cout << std::left;
    if(filme->get_id() == filme_id){
      int preco = 99999;
      int lote;
      std::string nomeUsuario;

      for(int i=0; i<filme->get_precos().size(); i++){
        if(filme->get_capacidades()[i] == 0){
          // Remove lote que ja esgotou
          filme->remove_lote(i);
        } 
        // Caso os ingressos estiverem esgotados
        if(filme->get_capacidades().size() == 0){
          throw NoTicketsException();
        }
        
        if(filme->get_precos()[i] < preco && filme->get_capacidades()[i] > 0){
          preco = filme->get_precos()[i];
          lote = i;
        }
      }

			for(Usuario *usuario : this->usuarios){
        if(usuario->get_id() == usuario_id){
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
      if(filme->get_capacidades()[lote] < quantidade){
        throw NotEnoughTicketsException();
      }

      // Decrementa a capacidade do lote ja que um ingresso foi comprado
      filme->decrement_capacidade(lote, quantidade);

      int horario = filme->get_horarios()[horario_key];

      std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
      std::cout << "- Cliente: " << nomeUsuario << std::endl;
      std::cout << "- Filme: " << filme->get_nome() << std::endl;
      std::cout << "- Horario: " << horario << 'h' << std::endl;
      std::cout << "- Preco: R$" << preco << ",00" << std::endl;

      success = true;
      break;
    }
  }

  if (!success) {
    // Caso a tag 'success' estiver como falsa, significa que 
    // nao encontrou um evento com o id escolhido
    throw InvalidIdException();
  }
}