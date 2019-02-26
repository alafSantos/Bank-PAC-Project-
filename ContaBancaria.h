#ifndef CONTA_BANCARIA_H
#define CONTA_BANCARIA_H
#include "Pessoa.h"
class ContaBancaria
{
  public:
    virtual void deposito(double valor) = 0;
    virtual void saque(double valor) = 0;
    virtual unsigned long int getIdentificacao() = 0;
    virtual double getSaldo() = 0;
    virtual double getLimite()const = 0;
    virtual bool getTipo()const = 0; //CP = true, CC = false
    virtual bool getTipoCliente() = 0; //PF = true e PJ = false
    virtual std::string getNomeCliente() = 0;
    virtual void aumentaLimite() = 0;
    virtual double getSalarioDono() = 0;
    virtual std::string getId()const = 0;
};

#endif
