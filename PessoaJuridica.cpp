#include "PessoaJuridica.h"

PessoaJuridica::PessoaJuridica(std::string nome, CNPJ cnpj, PessoaFisica dono)
:nome(nome), cnpj(cnpj), dono(dono), tipo(false), contaAtiva(false){}

std::string PessoaJuridica::getId()const
{
  return this->cnpj.getId();
}

bool PessoaJuridica::getContaAtiva()
{
  return this->contaAtiva;
}

void PessoaJuridica::setContaAtiva(bool on)
{
  this->contaAtiva = on;
}

bool PessoaJuridica::getTipo()
{
  return this->tipo;
}

unsigned long int PessoaJuridica::getIdentificacao()
{
  return this->cnpj.getCNPJ();
}

double PessoaJuridica::getSalario() //salario do dono
{
  return this->dono.getSalario();
}

std::string PessoaJuridica::getNome()const
{
  return this->nome;
}
