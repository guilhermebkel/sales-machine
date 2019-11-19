#include <iomanip>
#include <string>

#include "maquinas/maquina_fantoche.h"

#include "exceptions/no_tickets.h"
#include "exceptions/not_enough_funds.h"
#include "exceptions/not_enough_tickets.h"
#include "exceptions/invalid_id.h"

MaquinaFantoche::MaquinaFantoche(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
  for(Evento* evento: eventos){
    TeatroFantoche* teatro = dynamic_cast<TeatroFantoche*>(evento);

    if(teatro != nullptr){
      this->teatros.push_back(teatro);
    }
  }
  
  this->usuarios = usuarios;
}

void MaquinaFantoche::show_teatros(){
  std::cout << "=========================================================================" << std::endl;
  std::cout << "| ID |                   Nome                      |      Horarios      |" << std::endl;
  std::cout << "-------------------------------------------------------------------------" << std::endl;
  for(TeatroFantoche* teatro : this->teatros){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << teatro->get_id() << ' ';
    std::cout << "| " << std::setw(43) << teatro->get_nome() << " | ";

    std::string horarios;
    for(int i=0; i<teatro->get_horarios().size(); i++){
      horarios = horarios + std::to_string(teatro->get_horarios()[i]) + 'h';
      if(i != teatro->get_horarios().size()-1){
        // Caso não for o último horario do vector, adiciona uma vírgula no std::cout
        horarios = horarios + ", ";
      }
    }
    std::cout << std::setw(19) << horarios;
    std::cout << '|' << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
  }
}

void MaquinaFantoche::show_horarios(int teatro_id){
  TeatroFantoche* teatro_escolhido = nullptr;

  for(TeatroFantoche* teatro : this->teatros){
    if(teatro->get_id() == teatro_id){
      teatro_escolhido = teatro;
      break;
    }
  }

  if(teatro_escolhido == nullptr){
    throw InvalidIdException();
  }

  std::cout << "==================" << std::endl;
  std::cout << "| ID |  Horario  |" << std::endl;
  std::cout << "------------------" << std::endl;

  for(int i=0; i<teatro_escolhido->get_horarios().size(); i++){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << i << ' ';

    std::string horario = std::to_string(teatro_escolhido->get_horarios()[i]) + 'h';

    std::cout << "| " << std::setw(10) << horario;
    std::cout << '|' << std::endl;
    std::cout << "------------------" << std::endl;
  }
}

void MaquinaFantoche::buy_ingresso(int teatro_id, int horario_key, int usuario_id, int quantidade){
  int preco = 99999, lote;
  std::string nome_comprador;
  Usuario* comprador;
  TeatroFantoche* teatro_escolhido;
  
  for(TeatroFantoche* teatro : this->teatros){
    if(teatro->get_id() == teatro_id){
      teatro_escolhido = teatro;
      break;
    }
  }

  if(teatro_escolhido == nullptr){
    throw InvalidIdException();
  }

  // Caso os ingressos estiverem esgotados
  if(teatro_escolhido->get_capacidades().size() == 0){
    throw NoTicketsException();
  }

  // Iteração para pegar o lote de menor valor
  for(int i=0; i<teatro_escolhido->get_precos().size(); i++){   
    if(teatro_escolhido->get_precos()[i] < preco){
      preco = teatro_escolhido->get_precos()[i] * quantidade;
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
  if(teatro_escolhido->get_capacidades()[lote] < quantidade){
    throw NotEnoughTicketsException();
  }

  // Decrementa a capacidade do lote ja que um ingresso foi comprado
  teatro_escolhido->decrement_capacidade(lote, quantidade);

  // Remove lote que ja esgotou
  if(teatro_escolhido->get_capacidades()[lote] == 0){
    teatro_escolhido->remove_lote(lote);
  } 

  int horario = teatro_escolhido->get_horarios()[horario_key];

  std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
  std::cout << "- Cliente: " << nome_comprador << std::endl;
  std::cout << "- Teatro: " << teatro_escolhido->get_nome() << std::endl;
  std::cout << "- Horario: " << horario << 'h' << std::endl;
  std::cout << "- Preco: R$" << preco << ",00" << std::endl;
}