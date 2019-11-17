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
  bool success = false;

  std::cout << "==================" << std::endl;
  std::cout << "| ID |  Horario  |" << std::endl;
  std::cout << "------------------" << std::endl;
  for(TeatroFantoche* teatro : this->teatros){
    std::cout << std::left;
    if(teatro->get_id() == teatro_id){
      for(int i=0; i<teatro->get_horarios().size(); i++){
        std::cout << "| " << std::setw(2) << i << ' ';

        std::string horario = std::to_string(teatro->get_horarios()[i]) + 'h';

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
    // nao encontrou um teatro com o id escolhido
    throw InvalidIdException();
  }
}

void MaquinaFantoche::buy_ingresso(int teatro_id, int horario_key, int usuario_id, int quantidade){
  bool success = false;
  
  for(TeatroFantoche* teatro : this->teatros){
    std::cout << std::left;
    if(teatro->get_id() == teatro_id){
      int preco = 99999;
      int lote;
      std::string nomeUsuario;

      // Caso os ingressos estiverem esgotados
      if(teatro->get_capacidades().size() == 0){
        throw NoTicketsException();
      }

      for(int i=0; i<teatro->get_precos().size(); i++){
        if(teatro->get_capacidades()[i] == 0){
          // Remove lote que ja esgotou
          teatro->remove_lote(i);
        }    
        if(teatro->get_precos()[i] < preco && teatro->get_capacidades()[i] > 0){
          preco = teatro->get_precos()[i];
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
      if(teatro->get_capacidades()[lote] < quantidade){
        throw NotEnoughTicketsException();
      }

      // Decrementa a capacidade do lote ja que um ingresso foi comprado
      teatro->decrement_capacidade(lote, quantidade);

      int horario = teatro->get_horarios()[horario_key];

      std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
      std::cout << "- Cliente: " << nomeUsuario << std::endl;
      std::cout << "- Teatro: " << teatro->get_nome() << std::endl;
      std::cout << "- Horario: " << horario << 'h' << std::endl;
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