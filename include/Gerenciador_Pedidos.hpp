#ifndef GERENCIADOR_PEDIDOS_H
#define GERENCIADOR_PEDIDOS_H
/**
 * @file Gerenciador_Pedidos
 * @brief implementacao da classe gerenciadora de pedidos
 */

#include "Livro.hpp"
#include "Validador.hpp"

/**
 * @struct SolicitacaoCompra
 * @brief representa um pedido de aquisição de livros para adicionar ao acervo da biblioteca
 */
struct SolicitacaoCompra{ 
    int id_pedido; ///< Id da solicitação
    Livro livro; ///< Qual livro deseja solicitar a compra
    // std::string ISBN_livro; ///< ISBN do livro(para identificá-lo)
    int quantidade; ///< Quantidade do livro que foi solicitada a compra
    double preco_total; ///< Preco total do pedido
    std::string status; ///< Status do pedido
    std::string motivo_pedido_recusado; ///< Motivo de o pedido ter sido recusado
    std::string motivo_pedido_nao_concluido; ///< Motivo de o pedido nao ter sido concluido
    Funcionario *dono_pedido = nullptr;

/**
 * @brief Construtor de solicitacao compra
 */
SolicitacaoCompra(Livro& livro, int quantidade, int idpedido, double preco_unidade): //@fzr esse id pedido mandado ser o size+1 d pedidosrealizados la
id_pedido(idpedido), livro(livro), quantidade(quantidade), preco_total(quantidade*preco_unidade), 
    status("Pendente"){};
};


/**
 * @class Gerenciador_Pedidos
 * @brief Contém métodos estáticos para gerenciar os pedidos de solicitação de livros dos funcionarios(bibliotecario e professor)
 */
class Gerenciador_Pedidos{
    private:
        static std::vector<SolicitacaoCompra> pedidos_globais; ///< Vetor que armazena todos os pedidos da biblioteca
        static int id_atual; ///< Id dos pedidos(conta as solicitacoes compra e e o id do pedido)
        static const std::vector <std::string> motivos_pedido_recusado; ///< Vetor que armazena motivos de o pedido ter sido recusado
        static const std::vector <std::string> motivos_pedido_nao_concluido; ///< Motivos de o pedido nao ter sido concluído
    public:
        /**
         * @brief Metodo para solicitar a compra de livros
         * @param livro Livro que deseja comprar
         * @param preco Qual o preco individual do livro
         * @param qtd_livros_compra Quantidade que deseja comprar do livro
         * @param pedidos_funcionario Vetor de pedidos do funcionario que fez a solicitacao
         * @return irá retornar o id do pedido
         */
        static int solicitar_compra_de_livros(Livro& livro, double preco, int qtd_livros_compra, std::vector <SolicitacaoCompra>& pedidos_funcionario, Funcionario* dono_pedido);

        /**
         * @brief Metodo p gerar o status do pedido, simulando uma pessoa externa controlando o status do pedido como aprovado/recusado
         * @param id_pedido id do pedido para gerar o status dele;
         * @param pedidos_funcionario Vetor de pedidos do funcionario que fez a soliitacao
         */
        static void gerar_status_pedido(const int id_pedido, std::vector<SolicitacaoCompra>& pedidos_funcionario);

        /**
         * @brief Metodo para atualizar o status do pedido
         * @param id_pedido id do pedido que deseja alterar o status
         * @param novo_status novo status do pedido 
         * @param pedidos_funcionario vetor de pedidos do funcionario
         */
        static void atualizar_status_pedido(const int id_pedido,std::string novo_status, std::vector<SolicitacaoCompra>& pedidos_funcionario);

        /**
         * @brief Metodo para concluir pedido
         * @param id_pedido id do pedido para concluir
         * @param livro livro que foi solicitado na compra
         * @param acervo acervo de livros para poder adicionar o livro, caso seja dado como concluido o pedido 
         * @param pedidos_funcionario vetor de pedidos do funcionario
         */
        static void concluir_pedido(const int id_pedido, Livro& livro, Acervo_Livro& acervo, std::vector<SolicitacaoCompra>& pedidos_funcionairo);

        /**
         * @brief Obter o indice de acordo com o id
         * @return retorna o indice correto para utilizacao
         */
        static int Gerenciador_Pedidos::obter_indice_pelo_id(int id_pedido, const std::vector <SolicitacaoCompra>& pedidos_funcionario);

        /**
         * @brief Get do vetor de motivos pelo qual pedido pode ter sido recusado
         * @return retorna o vetor de motivos
         */
        static const std::vector<std::string>& get_motivos_pedido_recusado();

        /**
         * @brief Get do vetor de motivos pelo qual podido pode nao ter sido concluido
         * @return retorna o vetor com os motivos
         */
        static const std::vector<std::string>& get_motivos_pedido_nao_concluido();

        
        /**
         * @brief Get do vetor de pedidos globais
         * @return retorna o vetor de pedidos globais
         */
        static const std::vector <SolicitacaoCompra>& get_pedidos_globais();

        /**
         * @brief Get do id atual do vetor de pedidos globais
         * @return retorna o id do pedido global atual
         */
        static const int get_id_atual();

};


#endif