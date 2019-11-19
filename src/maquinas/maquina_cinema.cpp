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
  Cinema* filme_escolhido = nullptr;

  for(Cinema* filme : this->filmes){
    if(filme->get_id() == filme_id){
      filme_escolhido = filme;
      break;
    }
  }

  if(filme_escolhido == nullptr){
    throw InvalidIdException();
  }

  std::cout << "==================" << std::endl;
  std::cout << "| ID |  Horario  |" << std::endl;
  std::cout << "------------------" << std::endl;

  for(int i=0; i<filme_escolhido->get_horarios().size(); i++){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << i+1 << ' ';

    std::string horario = std::to_string(filme_escolhido->get_horarios()[i]) + 'h';

    std::cout << "| " << std::setw(10) << horario;
    std::cout << '|' << std::endl;
    std::cout << "------------------" << std::endl;
  }
}

void MaquinaCinema::buy_ingresso(int filme_id, int horario_key, int usuario_id, int quantidade){
  int preco = 99999, lote, horario;
  std::string nome_comprador;
  Usuario* comprador = nullptr;
  Cinema* filme_escolhido = nullptr;
  
  for(Cinema* filme : this->filmes){
    if(filme->get_id() == filme_id){
      filme_escolhido = filme;
      break;
    }
  }

  if(filme_escolhido == nullptr){
    throw InvalidIdException();
  }

  // Caso os ingressos estiverem esgotados
  if(filme_escolhido->get_capacidades().size() == 0){
    throw NoTicketsException();
  }

  // Iteração para pegar o lote de menor valor
  for(int i=0; i<filme_escolhido->get_precos().size(); i++){
    if(filme_escolhido->get_precos()[i] < preco){
      preco = filme_escolhido->get_precos()[i] * quantidade;
      lote = i;
    }
  }

	for(Usuario *usuario : this->usuarios){
    if(usuario->get_id() == usuario_id){
      comprador = usuario;
      break;
    }
  }

  if(comprador->get_saldo() < preco){
    throw NotEnoughFundsException();
  }
  else{
    comprador->set_saldo(preco);
    nome_comprador = comprador->get_nome();
  }

  // Caso o comprador quiser comprar mais ingressos do que existe
  if(filme_escolhido->get_capacidades()[lote] < quantidade){
    throw NotEnoughTicketsException();
  }

  // Decrementa a capacidade do lote ja que um ingresso foi comprado
  filme_escolhido->decrement_capacidade(lote, quantidade);

  // Remove lote que ja esgotou
  if(filme_escolhido->get_capacidades()[lote] == 0){
    filme_escolhido->remove_lote(lote);
  } 

  horario = filme_escolhido->get_horarios()[horario_key];
  if(!horario){
    throw InvalidIdException();
  }

  std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
  std::cout << "- Cliente: " << nome_comprador << std::endl;
  std::cout << "- Filme: " << filme_escolhido->get_nome() << std::endl;
  std::cout << "- Horario: " << horario << 'h' << std::endl;
  std::cout << "- Preco: R$" << preco << ",00" << std::endl;
}