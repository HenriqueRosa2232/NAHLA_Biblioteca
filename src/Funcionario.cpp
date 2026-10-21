#include "Funcionario.hpp"
#include "cstdlib"
#include "ctime"
#include "Acervo_Livro.hpp"
#include "Gerenciador_Pedidos.hpp"
// #include <algorithm> //por enquanto deixa, n acho q de problema, mas deixa assim

Funcionario::Funcionario(int id, std::string login, std::string senha, std::string nome, std::string siape):
 Usuario(id,login,senha,nome), SIAPE(siape){
    std::srand(std::time(nullptr)); //para gerar valores aleatorios e decidir estado dos pedidos 
 }

std::string Funcionario::get_siape(){
    return SIAPE;
}

const std::vector<SolicitacaoCompra>& Funcionario::get_pedidos_realizados(){
    return pedidos_realizados;
}

std::vector<SolicitacaoCompra>& Funcionario::set_pedidos_realizados(){
    return pedidos_realizados;
}

std::string Funcionario::consultar_status_solicitacao_livros(const int id_pedido){
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, this->pedidos_realizados);
    if(indice_real == -1){
        return "-1";
    }
    return pedidos_realizados[indice_real].status;
}  

int Funcionario::solicitar_compra_de_livros(Livro& livro, double preco, int qtd_livros_compra){
    Gerenciador_Pedidos::solicitar_compra_de_livros(livro, preco, qtd_livros_compra, pedidos_realizados, this);
}

void Funcionario::gerar_status_pedido(const int id_pedido){
    Gerenciador_Pedidos::gerar_status_pedido(id_pedido, pedidos_realizados);
}

void Funcionario::atualizar_status_pedido(const int id_pedido, std::string novo_status){
    Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, novo_status, pedidos_realizados);
}
