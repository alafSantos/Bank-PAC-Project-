#include "Banco.h"
Banco::Banco(double saldoInicial):saldoDoBanco(saldoInicial), saldoInicial(saldoInicial), taxas(0), qtdCPs(0), qtdCCs(0),
qtdErrosMes(0), qtdMeses(0), qtdTransacoesMes(0), contasEncerradasMes(0), contasNovasMes(0), contador(0){}

void Banco::operator-(std::string doc) //sobrecarga do operador - para encerrar uma conta
{
  this->contasEncerradasMes++;
  unsigned long int id = 0;
  if(doc.size() == 14)
  {
    CPF identificacao(doc);
    id = identificacao.getCPF();
  }
  else
  {
    CNPJ identificacao(doc);
    id = identificacao.getCNPJ();
  }

  unsigned int j = 0;
  for(int i = 0; i < this->contas.size(); i++) if (this->contas[i]->getIdentificacao()== id) j = i;
  if (this->contas[j]->getSaldo() == 0)
  {
    if(this->contas[j]->getTipo()) this->qtdCPs--;
    else this->qtdCCs--;
    for(int h = 0; h < this->contas.size(); h++)
    {
      this->contasEncerradas.push_back(this->contas[j]);
      if(this->PFs[h].getIdentificacao() == this->contas[j]->getIdentificacao())this->PFs[h].setContaAtiva(false);
    }
  }
  else
  {
    this->contasEncerradasMes--;
    this->qtdErrosMes++;
    throw Erros("ERRO: não é permitido encerrar conta com saldo ou dívida");
  }
}

std::string Banco::verificaRico()
{
  unsigned int aux = 0, existe = 0;
  for(int i = 0; i < this->contas.size(); i++)
  {
    if(this->contas[i]->getSaldo() >= 0)
    {
      existe = 1;
      for(int k = 0; k < this->contas.size(); k++)
        if(this->contas[i]->getSaldo() < this->contas[k]->getSaldo())
          aux = k;
      }
  }
  if(existe == 1) return (this->contas[aux]->getNomeCliente());
  else return ("N/A");
}

std::string Banco::verificaDivida()
{
  double aux = 0, existe = 0;
  for(int i = 0; i < this->contas.size(); i++)
  {
    if(this->contas[i]->getSaldo() < 0)
    {
      existe = 1;
      for(int k = 1; k < this->contas.size(); k++)
        if(this->contas[i]->getSaldo() > this->contas[k]->getSaldo())
          aux = k;
    }
  }
  if(existe == 1) return (this->contas[aux]->getNomeCliente());
  else return ("N/A");
}

void Banco::encerrarMes(double rendimento_poupanca, double juros_credito_pf, double juros_credito_pj, double rendimento_banco)
{
  double rendimento = 0, dividas = 0, saldoMes = 0, dinheiroPoupanca = 0;
  for(int p = 0; p < this->contas.size(); p++)
  {
    saldoMes += this->contas[p]->getSaldo();
    if(this->contas[p]->getSaldo() < 0)
    {
      dividas += abs(this->contas[p]->getSaldo());
      if(this->contas[p]->getTipoCliente()) this->contas[p]->deposito((this->contas[p]->getSaldo()*(juros_credito_pf))*(-1));
      else this->contas[p]->deposito(-1*(this->contas[p]->getSaldo()*(juros_credito_pj)));
    }
    if(this->contas[p]->getTipo())
    {
      dinheiroPoupanca += this->contas[p]->getSaldo();
      rendimento += this->contas[p]->getSaldo()*rendimento_poupanca;
      this->contas[p]->deposito((rendimento_poupanca)*this->contas[p]->getSaldo());
    }
    else if(this->contas[p]->getSaldo() >= 0) this->contas[p]->aumentaLimite();

  }
  this->rendimentoRecebido.push_back(((this->saldoDoBanco+dinheiroPoupanca)*rendimento_banco));
  this->saldoDosClientes.push_back(saldoMes + rendimento);
  this->saldoDoBanco = this->saldoDoBanco + ((this->saldoDoBanco+dinheiroPoupanca)*rendimento_banco);
  this->saldoDoBanco -= rendimento;
  this->saldoDoBancoMes.push_back(this->saldoDoBanco);
  this->rendimentoPoupancaTotal.push_back(rendimento);
  this->taxasRecebidas.push_back(abs(this->taxas));
  this->dividasMes.push_back(dividas);
  this->contasAtivas.push_back(this->qtdCCs+this->qtdCPs);
  this->contasN.push_back(this->contasNovasMes);
  this->contasE.push_back(this->contasEncerradasMes);
  this->maisRico.push_back(verificaRico());
  this->maiorDivida.push_back(verificaDivida());
  this->qtdTransacoesTotal.push_back(this->qtdTransacoesMes);
  this->qtdErrosTotal.push_back(this->qtdErrosMes);
  this->qtdMeses++;
  this->contasNovasMes = 0;
  this->contasEncerradasMes = 0;
  this->qtdTransacoesMes = 0;
  this->qtdErrosMes = 0;
  this->taxas = 0;

  for(int p = 0; p < this->contas.size(); p++) if(this->contas[p]->getTipoCliente()) depositar(this->contas[p],this->contas[p]->getSalarioDono()); //somente PF tem esse deposito(salario)
}

void Banco::depositar(ContaBancaria *conta, double valor)
{
  if(conta->getSaldo() >= 0) conta->deposito(valor);
  else //CASO 2 - SALDO NEGATIVO
  {
    if(abs(conta->getSaldo()) > valor) //se a pessoa deve mais do que vai depositar
    {
      conta->deposito(valor);
      this->saldoDoBanco += valor;
      this->taxas += valor;
      throw Erros("AVISO: esse valor foi usado (total ou parcialmente) para pagar dívida de crédito rotativo");
    }
    else //se a pessoa deve uma quantia menor do que vai depositar
    {
      double diferenca = valor - conta->getSaldo();
      conta->deposito(valor); //o saldo da conta vai ficar positivo ou igual a zero
      this->saldoDoBanco += (valor - diferenca);
      this->taxas+=(valor - diferenca);
      throw Erros("AVISO: esse valor foi usado (total ou parcialmente) para pagar dívida de crédito rotativo");
    }
  }
}

void Banco::pegaDadosPessoais(std::string dados_cliente)
{
  this->dadosPessoais.push_back(dados_cliente);
}

void Banco::criaClientes()
{
  unsigned int j = 0, i = 0, k = 0; //sao contadores de posicao
  while(j < dadosPessoais.size())
  {
    if(dadosPessoais[j] == "PF")
    {
        CPF cpf(dadosPessoais[j+2]);
        this->PFs.emplace_back(dadosPessoais[j+1], cpf, stod(dadosPessoais[j+3])); //(nome, cpf, salario)
        i += 1; j += 4; continue;
    }
    else if(this->dadosPessoais[j] == "PJ")
    {
      for(int p = 0; p < PFs.size(); p++)
      {
        CPF cpf(dadosPessoais[j+3]);
        if(cpf.getCPF() == PFs[p].getIdentificacao()) //if parar achar o dono da empresa
        {
          CNPJ cnpj(this->dadosPessoais[j+2]);
          this->PJs.emplace_back(this->dadosPessoais[j+1], cnpj, PFs[p]); //(nome, cnpj, donoDaEmpresa)
          break;
        }
      }
      k += 1; j += 4; continue;
    }
    i++; j++; k++;
  }
}

void Banco::abrirConta(std::string tipoDeConta, std::string documento)
{
  this->qtdTransacoesMes++; //para o RELATORIO
  this->contasNovasMes++;  //para o RELATORIO
  if(tipoDeConta == "CP")
  {
    if(documento.size() == 14)  //verifica o tamanho da string, se for cpf tem 14 posicoes
    {
      CPF cPf(documento);
      for(int h = 0; h < this->PFs.size(); h++)
      {
        if(cPf.getCPF() == this->PFs[h].getIdentificacao())
        {
          if(this->PFs[h].getContaAtiva())
          {
            this->qtdErrosMes++;
            this->qtdTransacoesMes--;
            this->contasNovasMes--;
            throw Erros("ERRO: o cliente " + this->PFs[h].getId() + " não pode abrir mais contas"); //COMO RESOLVER ISSO?
          }
          else
          {
            this->PFs[h].setContaAtiva(true);
            this->qtdCPs++;
            this->contas.push_back(new ContaPoupanca(&PFs[h]));
            this->contas[this->contador]->deposito(this->PFs[h].getSalario());
            this->contador++;
            break;
          }
        }else continue;
      }
    }
    else
    {
      this->qtdErrosMes++;
      this->qtdTransacoesMes--;
      this->contasNovasMes--;
      throw Erros("ERRO: clientes PJ não podem abrir CP");
    }
  }

  else if(tipoDeConta == "CC")
  {
    if(documento.size() == 14)  //verifica o tamanho da string, se for cpf tem 14 posicoes
    {
      CPF cPf(documento);
      for(int h = 0; h < this->PFs.size(); h++)
      {
        if(cPf.getCPF() == this->PFs[h].getIdentificacao())
        {
          if(this->PFs[h].getContaAtiva())
          {
            this->qtdErrosMes++;
            this->qtdTransacoesMes--;
            this->contasNovasMes--;
            throw Erros("ERRO: o cliente " + this->PFs[h].getId() + "  não pode abrir mais contas"); //COMO RESOLVER ISSO?
          }
          else //se a Pessoa fisica nao possuir uma conta ativa
          {
            this->qtdCCs++;
            this->contas.push_back(new ContaCorrente(&PFs[h]));
            this->contas[this->contador]->deposito(this->PFs[h].getSalario());
            this->contador++;
            this->PFs[h].setContaAtiva(true);
            break;
          }
        }else continue;
      }
    }
    else
    {
      CNPJ cnPj(documento);
      for(int e = 0; e < this->PJs.size(); e++)
      {
        if(cnPj.getCNPJ() == this->PJs[e].getIdentificacao())
        {
          if(this->PJs[e].getContaAtiva())
          {
            this->qtdErrosMes++;
            this->qtdTransacoesMes--;
            this->contasNovasMes--;
            throw Erros("ERRO: o cliente " + this->PJs[e].getId() + "  não pode abrir mais contas");
          }
          else
          {
              this->qtdCCs++;
              this->contas.push_back(new ContaCorrente(&PJs[e]));
              this->contas[this->contador]->deposito(this->PJs[e].getSalario()*5);
              this->contador++;
              this->PJs[e].setContaAtiva(true);
              break;
          }
        }else continue;
      }
    }
  }
}

void Banco::sacar(std::string documento, double valor)
{
  this->qtdTransacoesMes++;
  unsigned long int id = 0;
  if(documento.size() == 14)
  {
    CPF identificacao(documento);
    id = identificacao.getCPF();
  }
  else
  {
    CNPJ identificacao(documento);
    id = identificacao.getCNPJ();
  }
  unsigned int a = 0;
  while(a < this->contas.size())
  {
    if(this->contas[a]->getIdentificacao() == id)
    {
        if(this->contas[a]->getSaldo() >= valor)
        {
          this->contas[a]->saque(valor); //saque
          break;
        }

        if(((-1)*(this->contas[a]->getSaldo())) + valor <= this->contas[a]->getLimite()) //CASO 1 (se ainda tiver credito para usar)
        {
          if(this->contas[a]->getSaldo() > 0) //se tiver algum saldo na conta
          {
            double saque = this->contas[a]->getSaldo();
            saque = abs(valor - saque); //calcula a diferenca entre oq o cliente tinha o quanto ele quer
            if(saque > this->saldoDoBanco) //se o banco nao tiver saldo suficiente
            {
              this->qtdTransacoesMes--;
              continue;
            }
            else
            {
              saque = this->contas[a]->getSaldo();
              this->contas[a]->saque(saque); //zerou a conta;
              saque = abs(valor - saque);
              if(saque <= this->contas[a]->getLimite())
              {
                this->contas[a]->saque(saque); //deixou o saldo negativo
                this->saldoDoBanco -= saque; //tira o dinheiro do credito rotativo do banco
                throw Erros("AVISO: esse saque usou o limite de crédito do cliente "  + this->contas[a]->getId());
              }else
              {
                this->qtdErrosMes++;
                this->qtdTransacoesMes--;
                throw Erros("ERRO: o cliente " + this->contas[a]->getId() + "  não possui saldo suficiente"); //COMO RESOLVER ISSO?
              }
            }
          }
          else //se a conta ta zerada ou com saldo negativo
          {
            if((this->contas[a]->getLimite()) >= abs(this->contas[a]->getSaldo() - valor))
            {
              if(this->saldoDoBanco >= valor)
              {
                this->contas[a]->saque(valor);
                this->saldoDoBanco -= valor; //tira o dinheiro do credito rotativo do banco
                throw Erros("AVISO: esse saque usou o limite de crédito do cliente " + this->contas[a]->getIdentificacao());
              }
              else
              {
                this->qtdErrosMes++;
                this->qtdTransacoesMes--;
                continue;
              }
            }else
            {
              this->qtdTransacoesMes--;
              this->qtdErrosMes++;
              throw Erros("ERRO: o cliente " + this->contas[a]->getId() + "  não possui saldo suficiente"); //COMO RESOLVER ISSO?
            }
          }
        }
        else //CASO 2
        {
          this->qtdErrosMes++;
          this->qtdTransacoesMes--;
          throw Erros("ERRO: o cliente " + this->contas[a]->getId() +"  não possui saldo suficiente");
        }
      }
    a++;
  }
}

void Banco::depositar(std::string documento, double valor)
{
  this->qtdTransacoesMes++;
  unsigned long int id = 0;
  if(documento.size() == 14)
  {
    CPF identificacao(documento);
    id = identificacao.getCPF();
  }
  else
  {
    CNPJ identificacao(documento);
    id = identificacao.getCNPJ();
  }

  for(int a = 0; a < this->contas.size(); a++)
  {
    if(this->contas[a]->getIdentificacao() == id)
    {
      if(this->contas[a]->getSaldo() >= 0) //se a pessoa nao usou o credito rotativo
      {
        this->contas[a]->deposito(valor);
        break;
      }
      else //CASO 2 - SALDO NEGATIVO
      {
        if(abs(this->contas[a]->getSaldo()) > valor) //se a pessoa deve mais do que vai depositar
        {
          this->contas[a]->deposito(valor);
          this->saldoDoBanco += valor;
          this->taxas += valor;
          throw Erros("AVISO: esse valor foi usado (total ou parcialmente) para pagar dívida de crédito rotativo");
        }
        else //se a pessoa deve uma quantia menor do que vai depositar
        {
          double diferenca = valor - this->contas[a]->getSaldo();
          this->contas[a]->deposito(valor); //o saldo da conta vai ficar positivo ou igual a zero
          this->saldoDoBanco += (valor - diferenca);
          this->taxas+=(valor - diferenca);
          throw Erros("AVISO: esse valor foi usado (total ou parcialmente) para pagar dívida de crédito rotativo");
        }
      }
    }
  }
}

void Banco::transferir(std::string doc1, std::string doc2, double valor)
{
  this->qtdTransacoesMes++; //tem q ver isso depois

  unsigned long int id1 = 0, id2 = 0;
  if(doc1.size() == 14)
  {
    CPF identificacao(doc1);
    id1 = identificacao.getCPF();
  }
  else
  {
    CNPJ identificacao(doc1);
    id1 = identificacao.getCNPJ();
  }

  if(doc2.size() == 14)
  {
    CPF identificacao(doc2);
    id2 = identificacao.getCPF();
  }
  else
  {
    CNPJ identificacao(doc2);
    id2 = identificacao.getCNPJ();
  }

  unsigned int aux1 = 0, aux2 = 0;
  for(int i = 0; i < this->contas.size(); i++)
  {
      if(this->contas[i]->getIdentificacao() == id1) aux1 = i;
      else if(this->contas[i]->getIdentificacao() == id2) aux2 = i;
  }

  if(this->contas[aux1]->getSaldo() >= valor*1.01) //CASO 1
  {
     this->contas[aux1]->saque(valor*1.01);
     this->saldoDoBanco += valor*0.01;
     this->taxas += valor*0.01;
     depositar(doc2,valor);
  }else //CASO 2
  {
    this->qtdErrosMes++;
    this->qtdTransacoesMes--;
    throw Erros("ERRO: o cliente " + this->contas[aux1]->getId() + "  não possui saldo suficiente");
  }
}

void Banco::gerarRelatorio()
{
  double divida = 0; unsigned int PFdevendo = 0, PJdevendo = 0, limite = 0; int erros = 0;
  for(int i = 0; i < this->contas.size(); i++)
  {
    unsigned int k = 0; bool pula = false;
    while(k < this->contasEncerradas.size())
    {
      if(this->contasEncerradas[k]->getIdentificacao() == this->contas[i]->getIdentificacao())pula = true;
      k++;
    }
    if(pula)continue;


  	limite += this->contas[i]->getLimite();
    if(this->contas[i]->getSaldo() < 0)
    {
     divida += abs(this->contas[i]->getSaldo());
     if(this->contas[i]->getTipoCliente())PFdevendo++;
     else PJdevendo++;
    }
  }

  for(int g = 0; g < this->qtdErrosTotal.size(); g++) erros += this->qtdErrosTotal[g];

  std::ofstream relatorio_file;
  relatorio_file.open("outputFiles/report.txt");

  relatorio_file << "Quantidade de contas ativas: " << this->qtdCCs + this->qtdCPs << " (" << this->qtdCPs << " CP e " << this->qtdCCs << " CC)\n";
  if(this->saldoInicial <= this->saldoDoBanco) relatorio_file << "Saldo do banco: R$ " << std::fixed << std::setprecision(2) << this->saldoDoBanco << " (+ R$ " << this->saldoDoBanco - this->saldoInicial << ")\n";
  else relatorio_file << "Saldo do banco: R$ " << std::setprecision(2) << std::fixed <<  this->saldoDoBanco << " (- R$ " << -1*(this->saldoDoBanco - this->saldoInicial) << ")\n";
  relatorio_file << "Dívida dos clientes: R$ " << std::setprecision(2) << std::fixed <<  divida << " (" << PFdevendo << " PF e " << PJdevendo << " PJ)\n";
  relatorio_file << "Total disponibilizado em limite de credito: R$ " << std::setprecision(2) << std::fixed << limite - divida << "\n";
  relatorio_file << "Erros: " << erros << std::endl;
  for(int q = 0; q < this->qtdMeses; q++)
  {
    relatorio_file << "--------------------------------------------------\n";
    relatorio_file << "MÊS " << q + 1 << std::endl;
    relatorio_file << "Transações: " << this->qtdTransacoesTotal[q] << " efetuadas e " << this->qtdErrosTotal[q] << " com erro\n";
    relatorio_file << "Total de contas ativas: " << this->contasAtivas[q] << " (" << this->contasN[q] << " novas e " << this->contasE[q] << " encerradas)\n";
    relatorio_file << "Rendimento pago a CP: R$ " << std::setprecision(2) << std::fixed <<  this->rendimentoPoupancaTotal[q] << "\n";
    relatorio_file << "Rendimento recebido: R$ " << std::setprecision(2) << std::fixed <<  this->rendimentoRecebido[q] << "\n";
    relatorio_file << "Juros e taxas recebidas: R$ " << std::setprecision(2) << std::fixed << this->taxasRecebidas[q] << "\n";
    relatorio_file << "Dívida dos clientes: R$ " << std::setprecision(2) << std::fixed <<  this->dividasMes[q] << "\n";
    relatorio_file << "Saldo dos clientes: R$ " << std::setprecision(2) << std::fixed << this->saldoDosClientes[q] << "\n";
    relatorio_file << "Cliente mais rico: " << this->maisRico[q] << "\n";
    relatorio_file << "Cliente com maior dívida: " << this->maiorDivida[q] << "\n";
    relatorio_file << "Saldo do banco: R$ " << std::setprecision(2) << std::fixed << this->saldoDoBancoMes[q] << std::endl;
  }
  relatorio_file.close();
}
