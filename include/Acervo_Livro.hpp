#ifndef ACERVO_LIVRO_H
#define ACERVO_LIVRO_H
#include <string>
#include <iostream>
#include <map>
#include "Gerenciador_Emprestimo.hpp"
#include "Livro.hpp"

/**
 * @class Acervo_Livro
 * @brief Esta é uma classe responsável por representar o conjunto de livros da biblioteca como um todo.
 *
 */
class Acervo_Livro
{
private:
    /** @brief Lista com a forma map do tipo livro responsável por armazenar todos os livros do acervo*/
    std::map<std::string, Livro> ListaAcervoLivros;

public:
    /** @brief Função get para acesso da Lista com forma map de AcervoLivros **/
    /** @return Retorna uma cópia da lista para visualização **/
    const std::map<std::string, Livro> &getListaAcervoLivro() const;

    /** @brief Construtor de AcervoLivros para inicialização */
    /** @param Livro Parâmetro do tipo Livro para inicializar o construtor da classe */
    Acervo_Livro(Livro &Livro);

    /** @brief Método para remover um livro da lista */
    /** @param livro Parâmetro para indicação de qual livro deseja remover através do ISBN */
    void RemoverLivroAcervo(std::string ISBN);
    /** @brief Método para exibir todos os livros do acervo */
    void ExibirListaAcervo();
    /** @brief Método utilizado para inserir um novo livro para a Lista do Acervo. */
    /** @param livro Parâmetro utilizando um objeto livro desejado a ser incrementado ao acervo */
    void InserirLivroAcervo(Livro &Livro);
    /** @brief Método para buscar um livro dentro do acervo através do seu ISBN */
    /** @param ISBN Parâmetro informado durante a chamada da função */
    /** @return Retorna o objeto do tipo livro contido na lista correspondente ao ISBN informado */
    const Livro *BuscarLivro(std::string ISBN) const;
};
#endif