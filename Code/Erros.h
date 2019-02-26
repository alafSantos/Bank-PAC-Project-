#ifndef ERROS_H
#define ERROS_H
#include <stdexcept>
class Erros : public std::runtime_error
{
public:
	Erros(std::string erro):runtime_error(erro){}
};
#endif
