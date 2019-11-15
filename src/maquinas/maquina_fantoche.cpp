#include <iomanip>
#include <string>

#include "maquinas/maquina_fantoche.h"
#include "helpers/eventos/conversion.h"

MaquinaFantoche::MaquinaFantoche(std::vector<Evento*> eventos, std::vector<Usuario*> usuarios){
  this->eventos = get_teatros(eventos);
  this->usuarios = usuarios;
}

void MaquinaFantoche::show_eventos(){
  std::cout << "=========================================================================" << std::endl;
  std::cout << "| ID |                   Nome                      |      Horarios      |" << std::endl;
  std::cout << "-------------------------------------------------------------------------" << std::endl;
  for(auto evento : this->eventos){
    std::cout << std::left;
    std::cout << "| " << std::setw(2) << evento->get_id() << ' ';
    std::cout << "| " << std::setw(43) << evento->get_nome() << " | ";

    std::string horarios;
    for(int i=0; i<evento->get_horarios().size(); i++){
      horarios = horarios + std::to_string(evento->get_horarios()[i]) + 'h';
      if(i != evento->get_horarios().size()-1){
        // Caso não for o último horario do vector, adiciona uma vírgula no std::cout
        horarios = horarios + ", ";
      }
    }
    std::cout << std::setw(19) << horarios;
    std::cout << '|' << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
  }
}

void MaquinaFantoche::show_horarios(int evento_id){
  std::cout << "==================" << std::endl;
  std::cout << "| ID |  Horario  |" << std::endl;
  std::cout << "------------------" << std::endl;
  for(TeatroFantoche* evento : this->eventos){
    std::cout << std::left;
    if(evento->get_id() == evento_id){
      for(int i=0; i<evento->get_horarios().size(); i++){
        std::cout << "| " << std::setw(2) << i << ' ';

        std::string horario = std::to_string(evento->get_horarios()[i]) + 'h';

        std::cout << "| " << std::setw(10) << horario;
        std::cout << '|' << std::endl;
        std::cout << "------------------" << std::endl;
      }
      break;
    }
  }
}

void MaquinaFantoche::buy_ingresso(int evento_id, int horario_key, int usuario_id){
  for(TeatroFantoche* evento : this->eventos){
    std::cout << std::left;
    if(evento->get_id() == evento_id){
      int preco = 99999;
      int lote;
      std::string nomeUsuario;
      bool success;

      for(int i=0; i<evento->get_precos().size(); i++){
        if(evento->get_capacidades()[i] == 0){
          // Remove lote que ja esgotou
          evento->remove_lote(i);
        } 
        if(evento->get_capacidades().size() == 0){
          std::cout << "=> Infelizmente nao temos ingressos disponiveis para esse evento" << std::endl;
        } else if(evento->get_precos()[i] < preco && evento->get_capacidades()[i] > 0){
          preco = evento->get_precos()[i];
          lote = i;
        }
      }
      // Decrementa a capacidade do lote ja que um ingresso foi comprado
      evento->decrement_capacidade(lote, 1);

      for(Usuario *usuario : this->usuarios){
        if(usuario->get_id() == usuario_id){
          if(usuario->get_saldo() < preco){
            success = false;
          }
          else{
            success = true;
            usuario->set_saldo(preco);
            nomeUsuario = usuario->get_nome();
          }
        }
      }

      int horario = evento->get_horarios()[horario_key];

      if(success){
        std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
        std::cout << "- Cliente: " << nomeUsuario << std::endl;
        std::cout << "- Evento: " << evento->get_nome() << std::endl;
        std::cout << "- Horario: " << horario << 'h' << std::endl;
        std::cout << "- Preco: R$" << preco << ",00" << std::endl;
        evento->get_capacidades()[lote]--;
      }
      else{
        std::cout << "=> Seu saldo é insuficiente para realizar a compra do ingresso" << std::endl;
      }

      break;
    }
  }
}