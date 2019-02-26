#ifndef PESSOA_H
#define PESSOA_H
#include <string>
#include "CPF.h"
#include "CNPJ.h"

class Pessoa
{
public: //tentar protected depois
    virtual bool getTipo() = 0; //PF = true, PJ = false
    virtual bool getContaAtiva() = 0; //on = true, off = false
    virtual void setContaAtiva(bool on) = 0;
    virtual double getSalario() = 0;
    virtual unsigned long int getIdentificacao() = 0;
    virtual std::string getNome()const = 0;
    virtual std::string getId()const = 0;
};

#endif
