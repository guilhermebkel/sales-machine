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
  int preco = 99999, lote;
  std::string nome_comprador;
  Usuario* comprador = nullptr;
  Boate* boate_selecionada = nullptr;
  Crianca* crianca = nullptr;
  
  for(Boate* boate : this->boates){
    if(boate->get_id() == boate_id){
      boate_selecionada = boate;
      break;
    }
  }

  if(boate_selecionada == nullptr){
    throw InvalidIdException();
  }

  // Caso os ingressos estiverem esgotados
  if(boate_selecionada->get_capacidades().size() == 0){
    throw NoTicketsException();
  }

  // Iteração para pegar o lote de menor valor
  for(int i=0; i<boate_selecionada->get_precos().size(); i++){ 
    if(boate_selecionada->get_precos()[i] < preco){
      preco = boate_selecionada->get_precos()[i] * quantidade;
      lote = i;
    }
  }

  for(Usuario *usuario : this->usuarios){
    if(usuario->get_id() == usuario_id){
      comprador = usuario;
      // Faz conversao do usuario para crianca, a fim de verificar
      // permissões abaixo
      crianca = dynamic_cast<Crianca*>(usuario);
      break;
    }
  }

  if(comprador == nullptr && crianca == nullptr){
    throw InvalidIdException();
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
  if(boate_selecionada->get_capacidades()[lote] < quantidade){
    throw NotEnoughTicketsException();
  }

  // Decrementa a capacidade do lote ja que um ingresso foi comprado
  boate_selecionada->decrement_capacidade(lote, quantidade);

  // Aumenta a quantidade de ingressos que foram vendidos
  boate_selecionada->set_ingressos_vendidos(quantidade);
 
  // Remove lote que ja esgotou
  if(boate_selecionada->get_capacidades()[lote] == 0){
    boate_selecionada->remove_lote(lote);
  }

  std::cout << "=> Compra efetuada com sucesso! Segue abaixo os detalhes:" << std::endl;
  std::cout << "- Cliente: " << nome_comprador << std::endl;
  std::cout << "- Boate: " << boate_selecionada->get_nome() << std::endl;
  std::cout << "- Horario: " << boate_selecionada->get_horaInicio() << 'h' << std::endl;
  std::cout << "- Preco: R$" << preco << ",00" << std::endl;
}