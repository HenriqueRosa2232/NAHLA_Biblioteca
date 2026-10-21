/**
 * @file Usuario.hpp
 * @brief Define o TAD Usuario
 */
#ifndef USUARIO_H
#define USUARIO_H

#include "Livro.hpp"
#include "Acervo_Livro.hpp"

#include <list>
#include <algorithm>

#include <iostream>

/**
 * @class Usuario
 * @brief Representa um usuário do sistema.
 */
class Usuario {
    private:
        std::list<Livro> Livros_Usuario;        ///< Lista de livros do usuário.
        int id;                                 ///< Identificador do usuário.
        std::string login;                      ///< Forma de acesso do usuário.
        std::string senha;                      ///< Senha do usuário.
        std::string nome;                       ///< Nome do usuário.
        bool penalizado = false;                ///< Indica se o usuário possui multa/foi penalizado, começa em false pois um usuario não pode ser instanciado já com uma penalização.
        bool conta_ativa = true;                ///< Indica se a conta está ou não ativa, se o usuario foi instanciado então tem que estar ativa em principio.

    public:
        /**
         * @brief Construtor de Usuario.
         * @param id Identificador do usuário.
         * @param login Login (forma de acesso) do usuário.
         * @param senha Senha do usuário.
         * @param nome Nome do usuário.
         */
        Usuario(int id, std::string login, std::string senha, std::string nome);

        /**
         * @brief Modifica o estado de penalização do usuário.
         * @param penalizado Novo estado de penalização.
         * @return O novo estado de penalização.
         */
        bool set_penalizado(bool penalizado);

        /**
         * @brief Obtém o login do usuário.
         * @return Login do usuário.
         */
        std::string get_login();

         /**
         * @brief Obtém o id de usuário
         * @return id do usuario.
         */

        int get_id();

        /**
         * @brief muda a senha do usuário.
         * @param senha nova senha do usuário
         */

        void set_senha(std::string senha);

        /**
         * @brief retorna a senha do usuário.
         * @return senha do usuário
         */

        std::string get_senha();

        /**
         * @brief Retorna o nome do usuário.
         * @return nome do usuário.
         */
        std::string get_nome();
        /**
         * @brief Obtém a a lista de livros do usuário.
         * @return lista de livros do usuario.
         */
        const std::list<Livro>& get_Lista_Livros_Usuario();

        /**
         * @brief Verifica se o usuário está penalizado.
         * @return true se o usuário estiver penalizado, false caso contrário.
         */
        bool is_penalizado();

        /**
         * @brief Insere um livro na lista de livros do usuario.
         * @param livro o livro que vai ser adicionado
         */
        void inserir_livro(Livro& livro);

        /**
         * @brief remove um livro na lista de livros do usuário através do seu ISBN.
         * @param livro o livro que vai ser retirado
         */
        void remover_livro(std::string ISBN);

        /**
         * @brief Verifica se a conta do usuário está ativa.
         * @return true se a conta está ativa, false caso contrário.
         */
        bool is_ativo();

        /**
         * @brief Muda o status ativo da conta.
         * @param ativo é o novo status
         */
        void set_conta_ativa(bool ativo);

        /**
         * @brief função virtual para definir o limite dias que o usuário pode possuir.
         * @return o limite de dias em inteiros.
         */
        virtual int get_limite_dias() = 0;

        /**
         * @brief função virtual para definir o limite de livros que o usuário pode possuir.
         * @return o limite de obras em inteiros.
         */
        virtual int get_limite_obras() = 0; //Isso muda a depender de quem é o usuario, por isso coloquei como virtual

};

#endif