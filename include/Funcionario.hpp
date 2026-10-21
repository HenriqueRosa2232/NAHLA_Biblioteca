/**
 * @file Funcionario.hpp
 * @brief Implementacao da classe Funcionario
 */
#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#include <vector>
#include "Usuario.hpp"
#include "Acervo_Livro.hpp"
#include "Usuario.hpp"
#include "Livro.hpp"
#include "Gerenciador_Pedidos.hpp"

/**
 * @class Funcionario
 * @brief representa um funcionairo do sistema
 */
class Funcionario: public Usuario{
    private: 
        std::string SIAPE; ///< SIAP do funcionário
        

    public:
        /**
         * @brief Construtor da classe funcionário
         * @param id Identificador do funcionário
         * @param login Forma de login do funcionário
         * @param senha Senha do funcionário
         * @param nome Nome do funcionário
         * @param siape SIAPE do funcionário
         */
        Funcionario(int id, std::string login, std::string senha, std::string nome, std::string siape);        

        /**
         * @brief Metodo para obter o SIAPE do funcionário
         * @return retorna o SIAPE do funcionário
         */
        std::string get_siape(); 

        /**
         * @brief Metodo para consultar o status do pedido para aquisição dos livros
         * @param id_pedido Id do pedido para confirmar seu status
         */
        std::string consultar_status_solicitacao_livros(const int id_pedido);  

        /**
         * @brief Metodo para os funcionarios fazerem pedidos para compra de livros
         * @return retorna o id do pedido gerado
         */
        int solicitar_compra_de_livros(Livro& livro, double preco, int qtd_livros_compra); //-> vai retornar o id do pedido AQ

        /**
         * @brief Metodo para os funcionarios gerarem o status do pedido(atualizar para aprovado ou recusado)
         */
        void gerar_status_pedido(const int id_pedido);

//void Gerenciador_Pedidos::atualizar_status_pedido(const int id_pedido, std::string novo_status, std::vector<SolicitacaoCompra>& pedidos_funcionario)
        void atualizar_status_pedido(const int id_pedido, std::string novo_status);

        /**
         * @brief Metodo para obter o vetor com os pedidos que foram realizados pelo funcionario
         * @return retorna o vetor de pedidos realizados
         */
        const std::vector<SolicitacaoCompra>& get_pedidos_realizados();

        /**
         * @brief Metodo para alterar o vetor de pedidos realizados do funcionario(adicionar algum pedido)
         */
        std::vector<SolicitacaoCompra>& set_pedidos_realizados(); //so preciso q n deja const p poder mexer nele onde precisa
        

    protected:
        std::vector<SolicitacaoCompra> pedidos_realizados; ///< Vetor que armazena os pedidos realizados pelo funcionário
};

#endif