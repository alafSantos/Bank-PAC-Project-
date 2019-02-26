#include "ContaPoupanca.h"

ContaPoupanca::ContaPoupanca(Pessoa *cliente):cliente(cliente), saldo(0), tipo(true), limiteDeCredito(0){}

std::string ContaPoupanca::getId()const
{
  return this->cliente->getId();
}

void ContaPoupanca::aumentaLimite()
{
  this->limiteDeCredito += this->limiteDeCredito*0.02;
}

void ContaPoupanca::deposito(double valor)
{
    this->saldo+=valor;
}

void ContaPoupanca::saque(double valor)
{
  this->saldo-=valor;
}

unsigned long int ContaPoupanca::getIdentificacao()
{
  return this->cliente->getIdentificacao();
}

double ContaPoupanca::getLimite()const
{
  return this->limiteDeCredito;
}

double ContaPoupanca::getSaldo()
{
  return this->saldo;
}

bool ContaPoupanca::getTipo()const
{
  return this->tipo;
} //CP = true, CC = false

bool ContaPoupanca::getTipoCliente()
{
  return this->cliente->getTipo();
}

std::string ContaPoupanca::getNomeCliente()
{
  return this->cliente->getNome();
}

double ContaPoupanca::getSalarioDono()
{
  return this->cliente->getSalario();
}
