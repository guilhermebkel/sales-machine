#include "eventos/boate.h"
#include "eventos/show.h"
#include "eventos/cinema.h"
#include "eventos/teatro_fantoche.h"
#include "eventos/evento.h"

#include "usuarios/crianca.h"
#include "usuarios/adulto.h"
#include "usuarios/idoso.h"
#include "usuarios/usuario.h"

std::vector<Crianca*> get_criancas(std::vector<Usuario*> usuarios){
	std::vector<Crianca*> criancas;

	for(Usuario* usuario: usuarios){
    Crianca* crianca = dynamic_cast<Crianca*>(usuario);

    if(crianca != nullptr){
      criancas.push_back(crianca);
    }
  }

	return criancas;
}

std::vector<Adulto*> get_adultos(std::vector<Usuario*> usuarios){
	std::vector<Adulto*> adultos;

	for(Usuario* usuario: usuarios){
    Adulto* adulto = dynamic_cast<Adulto*>(usuario);

    if(adulto != nullptr){
      adultos.push_back(adulto);
    }
  }

	return adultos;
}

std::vector<Idoso*> get_idosos(std::vector<Usuario*> usuarios){
	std::vector<Idoso*> idosos;

	for(Usuario* usuario: usuarios){
    Idoso* idoso = dynamic_cast<Idoso*>(usuario);

    if(idoso != nullptr){
      idosos.push_back(idoso);
    }
  }

	return idosos;
}

std::vector<TeatroFantoche*> get_teatros(std::vector<Evento*> eventos){
	std::vector<TeatroFantoche*> teatros;

	for(Evento* evento: eventos){
    TeatroFantoche* teatro = dynamic_cast<TeatroFantoche*>(evento);

    if(teatro != nullptr){
      teatros.push_back(teatro);
    }
  }

	return teatros;
}

std::vector<Cinema*> get_cinemas(std::vector<Evento*> eventos){
	std::vector<Cinema*> cinemas;

	for(Evento* evento: eventos){
    Cinema* cinema = dynamic_cast<Cinema*>(evento);

    if(cinema != nullptr){
      cinemas.push_back(cinema);
    }
  }

	return cinemas;
}

std::vector<Boate*> get_boates(std::vector<Evento*> eventos){
	std::vector<Boate*> boates;

	for(Evento* evento: eventos){
    Boate* boate = dynamic_cast<Boate*>(evento);

    if(boate != nullptr){
      boates.push_back(boate);
    }
  }

	return boates;
}

std::vector<Show*> get_shows(std::vector<Evento*> eventos){
	std::vector<Show*> shows;

	for(Evento* evento: eventos){
    Show* show = dynamic_cast<Show*>(evento);

    if(show != nullptr){
      shows.push_back(show);
    }
  }

	return shows;
}