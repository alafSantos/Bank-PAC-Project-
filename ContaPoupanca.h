#ifndef CONTA_POUPANCA_H
#define CONTA_POUPANCA_H
#include "ContaBancaria.h"

class ContaPoupanca : public ContaBancaria
{
  private:
    Pessoa *cliente;
    double saldo;
    double limiteDeCredito;
    const bool tipo;

  public:
    ContaPoupanca(Pessoa *cliente);
    void deposito(double valor);
    void saque(double valor);
    double getLimite()const;
    double getSaldo();
    unsigned long int getIdentificacao();
    bool getTipo()const; //CP = true, CC = false
    bool getTipoCliente(); //PF = true, PJ = false
    std::string getNomeCliente();
    void aumentaLimite();
    double getSalarioDono();
    std::string getId()const;
};

#endif
