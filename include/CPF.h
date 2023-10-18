#ifndef CPF_H
#define CPF_H
#include<string>

class CPF
{
  private:
    const unsigned long int cpf;
    const std::string Cpf;
  public:
      CPF(std::string cpf);
	    unsigned long int converteCPF(std::string dadosPessoais);
      unsigned long int getCPF()const;
      std::string getId()const;
};

#endif
