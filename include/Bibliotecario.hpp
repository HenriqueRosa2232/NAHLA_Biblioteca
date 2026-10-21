/**
 * @file Bibliotecario.hpp
 * @brief Implementacao da classe Bibliotecario, que herda de funcionário.
 */
#ifndef BIBLIOTECARIO_H
#define BIBLIOTECARIO_H
#include "Funcionario.hpp"
#include "Acervo_Livro.hpp"
#include <iostream>

/**
 * @class Bibliotecario
 * @brief Representa um bibliotecário do sistema
 */
class Bibliotecario: public Funcionario{
    public:
        /**
         * @brief Metodo construtor de bibliotecário
         * @param nome Nome do bibliotecário
         * @param id Identificador do bibliotecário
         * @param login Forma de login do bibliotecário
         * @param senha Senha do bibliotecário
         * @param siape SIAPE do bibliotecário
         */
        Bibliotecario(int id, std::string login, std::string senha, std::string nome, std::string siape);  

        /**
         * @brief Método para buscar usuário no sistema de acordo com seus dados
         * @param id Identificador do usuário
         * @param login Login(forma de acesso) do usuário
         * @param nome Nome do usuário
         * @param acervo_pessoas Acervo de pessoas(usuarios do sistema)
         * @return retorna um ponteiro p usuário, se tiver encontrado, se nao tiver deve retornar nullptr 
         */
        const Usuario* buscar_usuario_sistema(int id, const std::string login, std::string nome, Acervo_Pessoas& acervo_pessoas);


        /**
         * @brief Metodo para concluir o pedido de algum usuario(podendo ser so proprio bibliotecario ou de algum outro funcionario)
         * @param id_pedido id do pedido
         * @param livro livro que foi pedido
         * @param acervo acervi de livros
         * @param pedidos_funcionario o vetor de pedidos do funcionario que fez o pedido
         */
        void concluir_pedido(const int id_pedido, Livro& livro, Acervo_Livro& acervo, std::vector<SolicitacaoCompra>& pedidos_funcionairo);

        /**
         * @brief Adicionar livros ao acervo da biblioteca
         * @param acervo Acervo de todos os livros da biblioteca
         * @param livro Livro que deseja catalogar
         */
        void catalogar_livro(int id_pedido, Acervo_Livro& acervo, Livro& livro, std::vector <SolicitacaoCompra>& pedidos_funcionario); 
        
        /**
         * @brief Método que salva o livro adicionado no banco de dados
         * @param livro Livro que foi catalogado
         */
        void salvar_registro_livro(const Livro& livro);

        /**
         * @brief Consulta o estoque do livro
         * @param livro Livro que deseja conferir a quantidade em estoque
         * @return retorna a quantidade daquele livro no acervo
         */
        const int consultar_estoque_livro(Livro& livro, Acervo_Livro& acervo); 

        /**
         * @brief O bibliotecario, após uma devolução ser feita, pode conferir o estado do livro após o empréstimo e 
         * decidir se determinado livro está em condições de ser usado ou não, podendo removê-lo do acervo se estiver 
         * inutilizável e aplicar uma penalidade ao usuário, que ficará alguns dias(ou semanas) sem poder pegar outro livro.
         * @param livro Livro que foi danificado
         * @param usuario Usuario que danificou o livro
         * @param acervo Acervo de livros, caso precise removê-lo por estar inutilizável 
         */
        void livro_danificado(Livro& livro, Usuario& usuario, Acervo_Livro& acervo);

        /**
         * @brief Metodo para devolver emprestimo
         * @param usuario usuario que devolveu o emprestimo
         * @param livro livro que ele devolveu
         * @param acervo acervo de livros(para remover livro, caso necessario)
         * @param estado_livro estado do livro(molhado, rasgado, amassado, inutilizavel)
         * @param emprestimo emprestimo em que isto aconteceu
         */
        void devolver_emprestimo(Usuario& usuario, Livro& livro, Acervo_Livro& acervo, std::string estado_livro, Emprestimo& emprestimo);

        /**
         * @brief Metodo para indicar se o livro que estava emprestado foi danificado
         * @param livro livro que foi danificado
         * @param usuario usuario que danificou o livro
         * @param acervo acervo de livros(para remover o exemplar emprestado, se estiver inutilizavel)
         * @param estado_livro estado do livro 
         */
        void livro_danificado(Livro& livro, Usuario& usuario, Acervo_Livro& acervo, std::string estado_livro);
};


#endif