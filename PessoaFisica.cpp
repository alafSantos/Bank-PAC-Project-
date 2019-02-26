#include "PessoaFisica.h"

PessoaFisica::PessoaFisica(std::string nome, CPF cpf, double salario)
:nome(nome), cpf(cpf), salario(salario), tipo(true), contaAtiva(false){}

std::string PessoaFisica::getId()const
{
  return this->cpf.getId();
}

bool PessoaFisica::getContaAtiva()
{
  return this->contaAtiva;
}

void PessoaFisica::setContaAtiva(bool on)
{
  this->contaAtiva = on;
}


bool PessoaFisica::getTipo()
{
  return this->tipo;
}

unsigned long int PessoaFisica::getIdentificacao()
{
  return this->cpf.getCPF();
}

double PessoaFisica::getSalario()
{
  return this->salario;
}

std::string PessoaFisica::getNome()const
{
  return this->nome;
}
