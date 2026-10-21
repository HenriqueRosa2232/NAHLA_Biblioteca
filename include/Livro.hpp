/**
 * @file Livro.hpp
 * @brief Implementação da classe que representa a entidade Livro
 */
#ifndef LIVRO_H
#define LIVRO_H
#include <string>
#include <vector>
#include "Usuario.hpp"

/**
 * @class Livro
 * @brief A classe Livro representa um livro do acervo, em que as suas informações são usadas para identificação e administração
 * da quantidade de exemplares daquela obra na biblioteca.
 */
class Livro{ 
    private:
        std::string titulo; ///< Título da obra 
        std::string autor; ///< Autor da obra
        std::string pais; ///< Pais de emissão do livro
        std::string editora; ///< Editora do livro
        std::string CDD; ///< CDD do livro(sistema de endereçamento do livro por assunto)
        std::string ISBN; ///< ISBN do livro(é identificador único de busca)
        int ano; ///< Ano de publicação do livro
        int quantidade_exemplares_total; ///< Quantidade total daquele exemplar
        int quantidade_disponivel; ///< Quantidade desse exemplar que estão disponíveis
        double preco_unitario; ///< Preço de um exemplar do livro
        std::vector <Usuario*> lista_espera; ///<Lista de espera para aquele livro

        
    public:
        /**
         * @brief Construtor de Livro
         * @param titulo titulo do livro
         * @param autor autor da obra
         * @param pais pais de origem da obra
         * @param editora editora que imprimiu o livro
         * @param ano ano de publicação do livro
         * @param CDD CDD do livro
         * @param ISBN ISBN do livro
         * @param quantidade_exemplares_total Quantidade total daquele exemplar
         */

         
        Livro(std::string titulo, std::string autor, std::string pais, std::string editora, int ano, std::string CDD, 
            std::string ISBN, int quantidade_exemplares_total);
        /**
         * @brief Obtem o titulo do livro
         * @return Retorna o titulo do livro
         */
        std::string get_titulo() const;
        /**
         * @brief Obtem o autor do livro
         * @return Retorna o autor do livro
         */
        std::string get_autor() const;
        /**
         * @brief Obtem o pais de origem do livro
         * @return retorna o pais do livro
         */
        std::string get_pais() const;
        /**
         * @brief Obtem a editora do livro
         * @return retorna a editora do livro
         */
        std::string get_editora() const;
        /**
         * @brief Obtem o ano de publicacao do livro
         * @return retorna o ano em que o livro foi publicado
         */
        int get_ano() const;
        /**
         * @brief Obtem o CDD do livro
         * @return retorna o CDD do livro
         */
        std::string get_CDD() const;
        /** 
         * @brief Obtem o ISBN do livro
         * @return retorna o ISBN do livro
         */
        std::string get_ISBN() const;
        /**
         * @brief Obtem a quantidade de exemplares daquele livro
         * @return retorna a quantidade de exemplares
         */
        int get_quantidade_exemplares_total() const;

        /**
         * @brief Alterar a quantidade de exemplares total
         * @param nova_qtd_total Nova quantidade total daquele livro
         */
        void set_quantidade_exemplares_total(int nova_qtd_total);

        /** 
         * @brief Obtem a quantidade de livros daquele exemplar que estao disponiveis
         * @return retorna a quantidade de exemplares disponiveis
         */

        int get_quantidade_disponivel() const;

        /**
         * @brief Altera a quantidade daquele exemplar que está disponível
         * @param nova_qtd Nova quantidade disponivel daquele exemplar
         */
        void set_quantidade_disponivel(int nova_qtd);

        /**
         * @brief Obtem o preço unitário daquele exemplar
         * @return retorna o preço do exemplar
         */
        double get_preco_unitario() const;


        /**
         * @brief Altera o preco unitario daquele livro
         * @param novo_preco Novo preco unitario do exemplar
         */
        void set_preco_unitario(double novo_preco);


        /**
         * @brief Imprime as informacoes do livro
         */
        void exibir_livro();

        /**  
         * @brief Metodo para obter a lista de espera daquele livro
         * @return retorna o vetor da lista de espera dos usuarios que desejam reservar esse livro 
         */
        const std::vector <Usuario*>& get_lista_espera();

        /** 
         * @brief Metodo para adicionar um usuario na lista de espera do livro
         */
        void adicionar_usuario_lista_espera(Usuario* usuario);

        /**
         * @brief Metodo para remover usuario da lista de espera 
         */
        void remover_usuario_lista_espera(Usuario* usuario);
        
};

#endif




// std::vector <Usuario*> lista_espera; aq tem q ser ponteiro pq vai fzr conversao d tipo entre os diferentes usuarios.
        //o & n daria certo pq precisa conseguir usar o polimorfismo(ponteiros so)