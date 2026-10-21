/**
 * @file Gerenciador_Emprestimo.hpp
 * @brief No arquivo Gerenciador_Emprestimo.hpp idealizamos a Classe Gerenciador_Empréstimo 
 * e os métodos relacionados o ato de pegar livros em bibliotecas.
 */
#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#include <chrono>
#include <map>
#include "Usuario.hpp"
#include "Livro.hpp"

/**
 * @struct Emprestimo
 * @brief Struct que armazena 
 */
struct Emprestimo{
    long long int id_emprestimo;///< O ID do empréstimo (único).
    Usuario* usuario = nullptr;
    Livro* livro = nullptr;
    std::chrono::system_clock::time_point data_Emprestimo; //< Data na qual o livro foi emprestado.
    std::chrono::system_clock::time_point data_Devolucao; //< É a data na qual o livro deveria para ser devolvido.
    std::chrono::system_clock::time_point data_Devolucao_Real; ///< É a data em que houve a real devolução do livro.
    bool ativo = true; ///< Indica se o empréstimo está em andamento ou não.
};

/**
 * @class Gerenciador_Emprestimo
 * @brief Classe que estabelece as formas de um usuario pegar/devolver/renovar livros emprestados.
 */
class Gerenciador_Emprestimo{
    private:
    long long int proximo_id_emprestimo; ///< Armazena o ID do próximo empréstimo

    /**
     * @brief Um map que armazena o id dos empréstimos.
     * Consultamos pelo id de qual empréstimo se trata e encontramos os dados de quem o fez e qual livro foi pego,
     * alem de sua respectiva data de devolução.
     */
    std::map<long long int, Emprestimo> emprestimos;

    public:
    /**
     * @brief Checa se o aluno está com penalizações atuais que possam impedir o empréstimo. 
     * @param usuario O usuário que entrou com o pedido de empréstimo/renovação.
     * @return A permissão ou a proibição do ato, a depender das penalizações do usuário.
     */
    static bool permitir_emprestimo(Usuario& usuario);

    /**
     * @brief Realiza o processo de empréstimo de um livro.
     * @param usuario O usuário que entrou com o pedido de empréstimo.
     * @param livro O livro que a ser emprestado.
     * @return Retorna o ID do novo empréstimo realizado.
     */
    static long long int pegar_livro_emprestado(Usuario& usuario, Livro& livro);

    // static long long int criar função que encontra um empréstimo e retorna o ID!

    /**
     * @brief Realiza o processo de renovação do empréstimo de um livro.
     * @param usuario O usuário que entrou com o pedido de renovação.
     * @param livro O livro que a ser renovado.
     */
    static void renovar_emprestimo(Usuario& usuario, Livro& livro);

    /**
     * @brief Permite a um aluno reservar um livro que não está em estoque.
     * @param usuario O usuario que desejar reservar o livro.
     * @param livro O livro a ser reservado.
     */
    static void reservar_livro(Usuario& usuario, Livro& livro);

    /**
     * @brief Checa se o livro está reservado previamente.
     * @param livro O livro cujo estado de reserva deve ser checado.
     * @return O estado do livro, se está reservado ou não.
     */
    static bool checar_reserva_livro(Usuario& usuario, Livro& livro);

    /**
     * @brief Checa se o livro está em estoque.
     * @param livro O livro cujo estoque é checado.
     * @return O estado do livro, se está em estoque ou não.
     */
    static bool checar_estoque_livro(Livro& livro);

    /**
     * @brief Registra a devolução do livro pelo aluno, mudando a quantidade de exemplares no estoque, e retirando-o da posse do aluno.
     * @param usuario Usuario que efetuou a devolução.
     * @param livro O livro que está sendo devolvido.
     */
    static void devolver_emprestimo(Usuario& usuario, Livro& livro);

    /**
     * @brief Calcula a data de devolução do exemplar a partir do dia em que foi efetuada uma renovação ou empréstimo.
     * @param usuario O usuario efetuando a renovação ou o empréstimo.
     * @param livro O livro que está sendo emprestado.
     * @param inicio O instante em que o empréstimo se deu.
     */
    static void calcular_data_devolucao(Usuario& usuario, Livro& livro);

    /**
     * @brief Checa se o empréstimo de um livro em posse de algum aluno está atrasado em relação ao prazo correto.
     * @param emprestimo Recebe o empréstimo em questão
     * @return Se está atrasado (true) ou não (false)
     * */
    static bool checar_atraso(const Emprestimo& emprestimo){
    
}
    /**
     * @brief Retorna o status do empréstimo de um livro em posse de algum aluno.
     * @param usuario O usuario que está com o livro.
     * @param livro O livro que está emprestado.
     * */
    static void status_emprestimo(Usuario& usuario, Livro& livro);

    /**
     * @brief Penaliza o aluno caso ele tenha devolvido o livro após a data de devolução. 
     * @param usuario O usuario com atraso na devolução
     */
    static void criar_penalizacao(Usuario& usuario);   
};

#endif