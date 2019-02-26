#include"Entrada.h"

std::vector< std::vector <std::string> > ler_arquivo(std::string caminho)
{
  std::vector< std::vector <std::string> > dados_todos;
  std::ifstream arquivo(caminho);
  if (arquivo.is_open())
  {
    std::string conteudo_da_linha;
    while(getline(arquivo, conteudo_da_linha))
    {
      std::stringstream ss(conteudo_da_linha);
      std::vector <std::string> dados;
      std::string token;
      while(getline(ss, token, ';')) dados.push_back(token);
      dados_todos.push_back(dados);
    }
    arquivo.close();
  }
  return dados_todos;
}
