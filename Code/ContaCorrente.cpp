#include "ContaCorrente.h"
#include<iostream>
ContaCorrente::ContaCorrente(Pessoa *cliente):cliente(cliente), tipo(false), saldo(0)
{
  if(cliente->getTipo())this->limiteDeCredito = 0.7*this->cliente->getSalario();
  else this->limiteDeCredito = 1.5*this->cliente->getSalario(); //salario do dono
}

std::string ContaCorrente::getId()const
{
  return this->cliente->getId();
}

void ContaCorrente::aumentaLimite()
{
  this->limiteDeCredito += this->limiteDeCredito*0.02;
}

void ContaCorrente::deposito(double valor)
{
  this->saldo+=valor;
}

void ContaCorrente::saque(double valor)
{
  this->saldo-=valor;
}

unsigned long int ContaCorrente::getIdentificacao()
{
  return this->cliente->getIdentificacao();
}

double ContaCorrente::getLimite()const
{
  return this->limiteDeCredito;
}

double ContaCorrente::getSaldo()
{
  return this->saldo;
}

bool ContaCorrente::getTipo()const
{
  return this->tipo;
} //CP = true, CC = false

bool ContaCorrente::getTipoCliente()
{
  return this->cliente->getTipo();
}

std::string ContaCorrente::getNomeCliente()
{
  return this->cliente->getNome();
}

double ContaCorrente::getSalarioDono()
{
  return this->cliente->getSalario();
}
