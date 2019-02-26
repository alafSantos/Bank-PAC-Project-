#ifndef PESSOAJURIDICA_H
#define PESSOAJURIDICA_H
#include"PessoaFisica.h"

class PessoaJuridica : public Pessoa
{
  private:
    const std::string nome;
    const CNPJ cnpj;
    PessoaFisica dono;
    bool tipo;
    bool contaAtiva;

  public:
    PessoaJuridica(std::string nome, CNPJ cnpj, PessoaFisica dono);
    bool getTipo();
    bool getContaAtiva();
    void setContaAtiva(bool on);
    double getSalario(); //salario do dono
    unsigned long int getIdentificacao();
    std::string getNome()const;
    std::string getId()const;
};
#endif
