#ifndef PESSOAFISICA_H
#define PESSOAFISICA_H
#include "Pessoa.h"

class PessoaFisica : public Pessoa
{
  private:
    const std::string nome;
    const double salario;
    const CPF cpf;
    bool tipo;
    bool contaAtiva;

  public:
    PessoaFisica(std::string nome, CPF cpf, double salario);
    bool getTipo();
    bool getContaAtiva();
    void setContaAtiva(bool on);
    double getSalario();
    unsigned long int getIdentificacao();
    std::string getNome()const;
    std::string getId()const;
};

#endif
