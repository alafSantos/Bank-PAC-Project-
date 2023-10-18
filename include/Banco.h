#ifndef BANCO_H
#define BANCO_H
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include "ContaCorrente.h"
#include "ContaPoupanca.h"
#include "PessoaJuridica.h"
#include "Erros.h"

class Banco
{
private:
  std::vector <ContaBancaria*> contas;
  std::vector <ContaBancaria*> contasEncerradas;
  std::vector <PessoaFisica> PFs;
  std::vector <PessoaJuridica> PJs;
  std::vector <std::string> dadosPessoais;
  std::vector <std::string> maisRico;
  std::vector <std::string> maiorDivida;
  std::vector <unsigned int> qtdTransacoesTotal;
  std::vector <unsigned int> qtdErrosTotal;
  std::vector <unsigned int> contasN;
  std::vector <unsigned int> contasE;
  std::vector <unsigned int> contasAtivas;
  std::vector <double> saldoDoBancoMes;
  std::vector <double> saldoDosClientes;
  std::vector <double> dividasMes;
  std::vector <double> taxasRecebidas;
  std::vector <double> rendimentoPoupancaTotal;
  std::vector <double> rendimentoRecebido;

  double limiteCred;
  double taxas;
  double saldoDoBanco;
  const double saldoInicial;
  unsigned int qtdMeses;
  unsigned int qtdTransacoesMes;
  unsigned int qtdErrosMes;
  unsigned int qtdCPs;
  unsigned int qtdCCs;
  unsigned int contasNovasMes;
  unsigned int contasEncerradasMes;
  unsigned int contador;

 public:
   Banco(double saldoInicial);
   void pegaDadosPessoais(std::string dados_cliente);
   void abrirConta(std::string tipoDeConta, std::string documento);
   void criaClientes();
   void sacar(std::string documento, double valor);
   void depositar(std::string documento, double valor);
   void depositar(ContaBancaria *conta, double valor);
   void transferir(std::string doc1, std::string doc2, double valor);
   void encerrarMes(double rendimento_poupanca, double juros_credito_pf, double juros_credito_pj, double rendimento_banco);
   void operator-(std::string doc); //sobrecarga do operador -
   void gerarRelatorio();
   std::string verificaRico();
   std::string verificaDivida();
   void aumentaLimite();
};

#endif
