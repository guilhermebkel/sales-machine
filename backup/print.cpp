/*
std::cout << std::fixed << std::showpoint << std::setprecision(2);

std::cout << "\nNumero de usuarios:" << std::endl;
std::cout << "Criancas: " << criancas.size() << std::endl;
std::cout << "Adultos: " << adultos.size() + idosos.size() << std::endl;
std::cout << "Idosos: " << idosos.size() << std::endl;

std::cout << "\nIdade dos usuarios:" << std::endl;
int idadeMinima = 9999999, idadeMaxima = 0;
float idadeMedia = 0;
for (Crianca *crianca : criancas)
{
  idadeMedia += crianca->get_idade();
  if (crianca->get_idade() < idadeMinima)
  {
    idadeMinima = crianca->get_idade();
  }
  if (crianca->get_idade() > idadeMaxima)
  {
    idadeMaxima = crianca->get_idade();
  }
}
for (Adulto *adulto : adultos)
{
  idadeMedia += adulto->get_idade();
  if (adulto->get_idade() < idadeMinima)
  {
    idadeMinima = adulto->get_idade();
  }
  if (adulto->get_idade() > idadeMaxima)
  {
    idadeMaxima = adulto->get_idade();
  }
}
for (Idoso *idoso : idosos)
{
  idadeMedia += idoso->get_idade();
  if (idoso->get_idade() < idadeMinima)
  {
    idadeMinima = idoso->get_idade();
  }
  if (idoso->get_idade() > idadeMaxima)
  {
    idadeMaxima = idoso->get_idade();
  }
}
idadeMedia = idadeMedia / (criancas.size() + adultos.size() + idosos.size());
std::cout << "Minima: " << idadeMinima << std::endl;
std::cout << "Maxima: " << idadeMaxima << std::endl;
std::cout << "Media: " << idadeMedia << std::endl;

std::cout << "\nNumero de dependentes:" << std::endl;
int depentendes = 0, dependentesMinimo = 9999999, dependentesMaximo = 0;
float dependentesMedia = 0;
for (Adulto *adulto : adultos)
{
  dependentesMedia += adulto->get_dependentes().size();
  if (adulto->get_dependentes().size() < dependentesMinimo)
  {
    dependentesMinimo = adulto->get_dependentes().size();
  }
  if (adulto->get_dependentes().size() > dependentesMaximo)
  {
    dependentesMaximo = adulto->get_dependentes().size();
  }
}
for (Idoso *idoso : idosos)
{
  dependentesMedia += idoso->get_dependentes().size();
  if (idoso->get_dependentes().size() < dependentesMinimo)
  {
    dependentesMinimo = idoso->get_dependentes().size();
  }
  if (idoso->get_dependentes().size() > dependentesMaximo)
  {
    dependentesMaximo = idoso->get_dependentes().size();
  }
}
dependentesMedia = dependentesMedia / (adultos.size() + idosos.size());
std::cout << "Minimo: " << dependentesMinimo << std::endl;
std::cout << "Maximo: " << dependentesMaximo << std::endl;
std::cout << "Media: " << dependentesMedia << std::endl;

std::cout << "\nDependentes:";
for (Adulto *adulto : adultos)
{
  if (adulto->get_dependentes().size())
  {
    std::cout << std::endl
              << adulto->get_nome() << " (ID: " << adulto->get_id() << "): ";
    for (Crianca *crianca : adulto->get_dependentes())
    {
      std::cout << crianca->get_nome() << " (ID: " << crianca->get_id() << "), ";
    }
  }
}

std::cout << "\n\nNumero de eventos:" << std::endl;
std::cout << "Adultos:" << std::endl;
std::cout << " Boate: " << boates.size() << std::endl;
std::cout << " Show: " << shows.size() << std::endl;
std::cout << "Livres:" << std::endl;
std::cout << " Cinema: " << cinemas.size() << std::endl;
std::cout << "Infantis:" << std::endl;
std::cout << " Teatro de Fantoches: " << teatros.size() << std::endl;

std::cout << "\nNumero de eventos que o usuario possui:" << std::endl;
int numeroEventos = 0;
for (Adulto *adulto : adultos)
{
  for (Boate boate : boates)
  {
    if (boate.get_responsavel()->get_id() == adulto->get_id())
    {
      numeroEventos++;
    }
  }
  for (Cinema cinema : cinemas)
  {
    if (cinema.get_responsavel()->get_id() == adulto->get_id())
    {
      numeroEventos++;
    }
  }
  for (TeatroFantoche teatro : teatros)
  {
    if (teatro.get_responsavel()->get_id() == adulto->get_id())
    {
      numeroEventos++;
    }
  }
  for (Show show : shows)
  {
    if (show.get_responsavel()->get_id() == adulto->get_id())
    {
      numeroEventos++;
    }
  }
  if (numeroEventos)
  {
    std::cout << adulto->get_nome() << " (ID: " << adulto->get_id() << "): " << numeroEventos << std::endl;
    numeroEventos = 0;
  }
}
for (Idoso *idoso : idosos)
{
  for (Boate boate : boates)
  {
    if (boate.get_responsavel()->get_id() == idoso->get_id())
    {
      numeroEventos++;
    }
  }
  for (Cinema cinema : cinemas)
  {
    if (cinema.get_responsavel()->get_id() == idoso->get_id())
    {
      numeroEventos++;
    }
  }
  for (TeatroFantoche teatro : teatros)
  {
    if (teatro.get_responsavel()->get_id() == idoso->get_id())
    {
      numeroEventos++;
    }
  }
  for (Show show : shows)
  {
    if (show.get_responsavel()->get_id() == idoso->get_id())
    {
      numeroEventos++;
    }
  }
  if (numeroEventos)
  {
    std::cout << idoso->get_nome() << " (ID: " << idoso->get_id() << "): " << numeroEventos << std::endl;
    numeroEventos = 0;
  }
}

std::cout << "\nEvento com maior cota para idoso:" << std::endl;
int maiorCota = 0, idEventoMaiorCota;
std::string nomeEventoMaiorCota;
for (Boate boate : boates)
{
  if (boate.get_quotaIdoso() > maiorCota)
  {
    maiorCota = boate.get_quotaIdoso();
    idEventoMaiorCota = boate.get_id();
    nomeEventoMaiorCota = boate.get_nome();
  }
}
for (Show show : shows)
{
  if (show.get_quotaIdoso() > maiorCota)
  {
    maiorCota = show.get_quotaIdoso();
    idEventoMaiorCota = show.get_id();
    nomeEventoMaiorCota = show.get_nome();
  }
}
std::cout << nomeEventoMaiorCota << " (ID: " << idEventoMaiorCota << "): " << maiorCota << std::endl;

std::cout << "\nNumero de ingressos por preco:" << std::endl;
int ingresso50 = 0, ingresso100 = 0, ingresso150 = 0, ingresso250 = 0, ingresso300 = 0;
for (Boate boate : boates)
{
  contador = 0;
  for (int preco : boate.get_precos())
  {
    if (preco == 50)
    {
      ingresso50 += boate.get_capacidades()[contador];
    }
    else if (preco == 100)
    {
      ingresso100 += boate.get_capacidades()[contador];
    }
    else if (preco == 150)
    {
      ingresso150 += boate.get_capacidades()[contador];
    }
    else if (preco == 250)
    {
      ingresso250 += boate.get_capacidades()[contador];
    }
    else if (preco == 300)
    {
      ingresso300 += boate.get_capacidades()[contador];
    }
    contador++;
  }
}
for (Show show : shows)
{
  contador = 0;
  for (int preco : show.get_precos())
  {
    if (preco == 50)
    {
      ingresso50 += show.get_capacidades()[contador];
    }
    else if (preco == 100)
    {
      ingresso100 += show.get_capacidades()[contador];
    }
    else if (preco == 150)
    {
      ingresso150 += show.get_capacidades()[contador];
    }
    else if (preco == 250)
    {
      ingresso250 += show.get_capacidades()[contador];
    }
    else if (preco == 300)
    {
      ingresso300 += show.get_capacidades()[contador];
    }
    contador++;
  }
}
for (TeatroFantoche teatro : teatros)
{
  contador = 0;
  for (int preco : teatro.get_precos())
  {
    if (preco == 50)
    {
      ingresso50 += teatro.get_capacidades()[contador];
    }
    else if (preco == 100)
    {
      ingresso100 += teatro.get_capacidades()[contador];
    }
    else if (preco == 150)
    {
      ingresso150 += teatro.get_capacidades()[contador];
    }
    else if (preco == 250)
    {
      ingresso250 += teatro.get_capacidades()[contador];
    }
    else if (preco == 300)
    {
      ingresso300 += teatro.get_capacidades()[contador];
    }
    contador++;
  }
}
for (Cinema cinema : cinemas)
{
  contador = 0;
  for (int preco : cinema.get_precos())
  {
    if (preco == 50)
    {
      ingresso50 += cinema.get_capacidades()[contador];
    }
    else if (preco == 100)
    {
      ingresso100 += cinema.get_capacidades()[contador];
    }
    else if (preco == 150)
    {
      ingresso150 += cinema.get_capacidades()[contador];
    }
    else if (preco == 250)
    {
      ingresso250 += cinema.get_capacidades()[contador];
    }
    else if (preco == 300)
    {
      ingresso300 += cinema.get_capacidades()[contador];
    }
    contador++;
  }
}
std::cout << "R$50.00: " << ingresso50 << std::endl;
std::cout << "R$100.00: " << ingresso100 << std::endl;
std::cout << "R$150.00: " << ingresso150 << std::endl;
std::cout << "R$250.00: " << ingresso250 << std::endl;
std::cout << "R$300.00: " << ingresso300 << std::endl;

for (Crianca *crianca : criancas)
{
  delete crianca;
}
for (Adulto *adulto : adultos)
{
  delete adulto;
}
for (Idoso *idoso : idosos)
{
  delete idoso;
}
*/