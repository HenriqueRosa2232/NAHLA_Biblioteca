#ifndef VALIDADOR_H
#define VALIDADOR_H
#include "Acervo_Livro.hpp"
#include "Acervo_Pessoas.hpp"
#include "Gerenciador_Emprestimo.hpp"
#include "Funcionario.hpp"
#include "Usuario.hpp"
#include "Gerenciador_Pedidos.hpp"
#include <iostream>

/**
 * @file Validador
 * @brief Implementacao da classe validador, que contém metodos para validar as informações passadas
 */
class Validador
{
public:
    /**
     * @brief Metodo estatico para remover espacos do comeco e do final de uma string
     * @return retorna a string sem os espacos no inicio e no fim
     */
    static std::string remover_espacos(std::string str);

    /**
     * @brief Confere se o texto informado e valido(se apos remover os espacos do inicio e fim a string nao fica vazia)
     * @return retorna se aquele texto e valido ou nao
     */
    static bool is_texto_valido(const std::string &str);

    ////////////////////////////////////////////////////////////////////////////
    // TESTAR ESSSE AQ!!
    /**
     * @brief Metodo para verificar se o id do pedido e valido(esta no vetor do funcionario)
     * @param id_pedido id do pedido para verificar
     * @param pedidos_funcionario vetor de pedidos do funcionario
     * @return retorna se o id e valido ou nao
     */
    static bool is_id_pedido_valido(int id_pedido, const std::vector<SolicitacaoCompra> &pedidos_funcionario);

    /**
     * @brief Metodo estático de validação das informações para criação de um objeto livro
     * @param titulo Titulo do livro
     * @param autor Autor do livro
     * @param pais Pais do livro
     * @param editora Editora do livro
     * @param ano Ano de publicação do livro
     * @param CDD CDD do livro
     * @param ISBN ISBN do livro
     * @param quantidade_exemplares_total Quantidade de exemplares total
     * @return true ou false, dependendo se a validação foi bem sucedida ou não
     */
    static bool validar_dados(std::string titulo, std::string autor, std::string pais, std::string editora, int ano,
                              std::string CDD, std::string ISBN, int quantidade_exemplares_total);

    /**
     * @brief Metodo estático que valida os dados do funcionario(e das subclasses Bibliotecario e Professor)
     * @param id Id do funcionário
     * @param login Login do funcionário
     * @param senha Senha do funcionário
     * @param nome Nome do funcionário
     * @param siape SIAPE do funcionário
     * @return retorna se os dados são válidos ou não
     */
    static bool validar_dados(int id, std::string login, std::string senha, std::string nome, std::string siape);

    /**
     * @brief Metodo estatico que valida os dados da solicitacao compra para funcionario e seus derivados
     * @param livro livro que o funcionario deseja pedir
     * @param preco_unitario preco unitario do livro
     * @param quantidade quantidade de exemplares que deseja pedir
     */
    static bool validar_dados(Livro &livro, double preco_unitario, int quantidade); // int idpedido, * @param idpedido id do pedido do funcionario
};

#endif