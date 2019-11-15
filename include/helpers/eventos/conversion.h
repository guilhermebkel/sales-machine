#include "eventos/boate.h"
#include "eventos/show.h"
#include "eventos/cinema.h"
#include "eventos/teatro_fantoche.h"
#include "eventos/evento.h"

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