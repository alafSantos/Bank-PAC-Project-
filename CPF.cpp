#include"CPF.h"

CPF::CPF(std::string cpf):Cpf(cpf), cpf(converteCPF(cpf)){};

unsigned long int CPF::converteCPF(std::string dadosPessoais)
{
  std::string cpf = dadosPessoais.substr(0,3) + dadosPessoais.substr(4,3)
                  + dadosPessoais.substr(8,3) + dadosPessoais.substr(12,2);
  return stod(cpf);
}

unsigned long int CPF::getCPF()const
{
  return this->cpf;
}

std::string CPF::getId()const
{
  return this->Cpf;
}
