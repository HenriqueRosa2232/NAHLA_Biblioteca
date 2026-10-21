#ifndef ACERVO_PESSOAS_HPP
#define ACERVO_PESSOAS_HPP

#include <string>
#include <vector>
#include "Professor.hpp" 
#include "Aluno.hpp"
#include "Bibliotecario.hpp"

/**
 * @file Acervo_Pessoas.hpp
 * @brief Definição da classe Acervo_Pessoas para gerenciamento de pessoas no sistema.
 */

/**
 * @class Acervo_Pessoas
 * @brief Gerencia uma coleção de usuários, permitindo inserção, busca por login, remoção e listagem.
 */
class Acervo_Pessoas {

private:
    static std::vector<Aluno> alunos;               ///< Armazena a lista de usuários cadastrados
    static std::vector<Bibliotecario> bibliotecarios; ///< Armazena a lista de bibliotecários cadastrados
    static std::vector<Professor> professores;        ///< Armazena a lista de professores cadastrados

public:
    /**
     * @brief Construtor da classe Acervo_Pessoas.
     * @param Usuario Referência para o usuário base a ser processado.
     */
    Acervo_Pessoas(Usuario &Usuario);

    /**
     * @brief Imprime as informações detalhadas de um aluno.
     * @param aluno Referência para o objeto Aluno.
     */
    void imprimirAluno(Aluno &aluno);

    /**
     * @brief Imprime as informações detalhadas de um professor.
     * @param professor Referência para o objeto Professor.
     */
    void imprimirProfessor(Professor &professor);

    /**
     * @brief Imprime as informações detalhadas de um bibliotecário.
     * @param bibliotecario Referência para o objeto Bibliotecario.
     */
    void imprimirBibliotecario(Bibliotecario &bibliotecario);

    /**
     * @brief Insere um novo usuário no acervo correspondente.
     * @param usuario Referência para o usuário a ser inserido.
     */
    void inserirUsuario(Usuario &usuario);

    /**
     * @brief Busca um usuário com base no login e no identificador.
     * @param login Referência para a string contendo o login do usuário.
     * @param id Identificador numérico do tipo de usuário.
     * @return const Usuario* Ponteiro constante para o usuário encontrado, ou nullptr.
     */
    const Usuario* buscarUsuario(std::string &login, int id);

    /**
     * @brief Remove um usuário do acervo com base no seu login.
     * @param login String contendo o login do usuário a ser removido.
     * @return bool Retorna true se a remoção for bem-sucedida, false caso contrário.
     */
    bool removerUsuarioPorLogin(std::string login);
    
};

#endif