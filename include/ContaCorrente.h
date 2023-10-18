#ifndef CONTA_CORRENTE_H
#define CONTA_CORRENTE_H
#include "ContaBancaria.h"

class ContaCorrente : public ContaBancaria
{
  private:
    Pessoa *cliente;
    double saldo;
    double limiteDeCredito;
    const bool tipo;

  public:
    ContaCorrente(Pessoa *cliente);
    void deposito(double valor);
    void saque(double valor);
    unsigned long int getIdentificacao();
    double getLimite()const;
    double getSaldo();
    bool getTipo()const; //CP = true, CC = false
    bool getTipoCliente();
    std::string getNomeCliente();
    void aumentaLimite();
    double getSalarioDono();
    std::string getId()const;
};
#endif
