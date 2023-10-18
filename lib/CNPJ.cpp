#include "CNPJ.h"

CNPJ::CNPJ(std::string cnpj):Cnpj(cnpj),cnpj(converteCNPJ(cnpj)){}

unsigned long int CNPJ::converteCNPJ(std::string dadosPessoais)
{
  std::string cnpj = dadosPessoais.substr(0,2) + dadosPessoais.substr(3,3)
                   + dadosPessoais.substr(7,3) + dadosPessoais.substr(11,4)
                   + dadosPessoais.substr(16,2);
  return stod(cnpj);
}

unsigned long int CNPJ::getCNPJ()const
{
  return this->cnpj;
}

std::string CNPJ::getId()const
{
  return this->Cnpj;
}
