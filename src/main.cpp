#include "Banco.h"
#include "Entrada.h"

int main(int argc, char *argv[])
{
  std::vector < std::string > argumentos(argv, argv + argc);
  std::vector < std::vector<std::string> > clientes = ler_arquivo(argumentos[1]);
  std::vector < std::vector<std::string> > transacoes = ler_arquivo(argumentos[2]);
  std::vector <std::string> vetorTransacoes;
  for (auto transacao : transacoes) for (auto dados_transacao : transacao) vetorTransacoes.push_back(dados_transacao);
  if(vetorTransacoes[0] == "AbrirBanco")
  {
    if(stod(vetorTransacoes[1]) <= 0) std::cout << "ERRO: saldo inicial menor ou igual a zero\n";
    else
    {
      Banco banco(stod(vetorTransacoes[1]));
      for (auto cliente : clientes) for (auto dados_cliente : cliente) banco.pegaDadosPessoais(dados_cliente);
      banco.criaClientes(); //cria objetos de Pessoas dentro do banco
      unsigned int w = 2; //pula "AbrirBanco" e o saldo inicial do banco
      while(w < vetorTransacoes.size())
      {
        try{
            if(vetorTransacoes[w] == "AbrirConta") banco.abrirConta(vetorTransacoes[w+1], vetorTransacoes[w+2]);
            else if(vetorTransacoes[w] == "Sacar") banco.sacar(vetorTransacoes[w+1], stod(vetorTransacoes[w+2]));
            else if(vetorTransacoes[w] == "Depositar")banco.depositar(vetorTransacoes[w+1], stod(vetorTransacoes[w+2]));
            else if(vetorTransacoes[w] == "Transferir")banco.transferir(vetorTransacoes[w+1], vetorTransacoes[w+2], stod(vetorTransacoes[w+3]));
            else if(vetorTransacoes[w] == "EncerrarMes") banco.encerrarMes(stod(vetorTransacoes[w+1]), stod(vetorTransacoes[w+2]), stod(vetorTransacoes[w+3]), stod(vetorTransacoes[w+4]));
            else if(vetorTransacoes[w] == "EncerrarConta") banco - vetorTransacoes[w+1];
          } catch(std::runtime_error erro){ std::cerr << erro.what() << std::endl; }
        w++;
      }banco.gerarRelatorio();
    }
  }return 0;
}
