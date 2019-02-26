#ifndef CNPJ_H
#define CNPJ_H
#include <ostream>
#include <string>

class CNPJ
{
  private:
    const unsigned long int cnpj;
    const std::string Cnpj;
  public:
    CNPJ(std::string cnpj);
    unsigned long int converteCNPJ(std::string dadosPessoais);
    unsigned long int getCNPJ()const;
    std::string getId()const;
};

#endif
