/**
 * @file Aluno.hpp
 * @brief No arquivo Aluno.hpp idealizamos a Classe Aluno, que herda de Usuario.
 */
#ifndef ALUNO_H
#define ALUNO_H

#include "Usuario.hpp"
/**
 * @class Aluno
 * @brief Classe que representa um aluno.
 */
class Aluno : public Usuario {
    private:
        std::string matricula; ///< Matrícula do aluno
        bool pos_graduando; ///< Se é pós-graduante

    public:
        /**
         * @brief Construtor de Aluno, utilizando o construtor de Usuario
         * @param id O id referente a aluno
         * @param matricula A forma de login do aluno
         * @param senha A senha do aluno
         * @param nome O nome do aluno
         */
        Aluno(int id, std::string matricula, std::string senha, std::string nome, bool pos_graduando);

        /**
         * @brief Checa se o aluno é de pós graduação
         * @return Retorna se é aluno de pós graduação
         */
        bool is_pos_graduando();

        /**
         * @brief muda o status de graduação do aluno
         * @param pos_graduando status novo da graduação desse aluno
         */
        void set_pos_graduando(bool pos_graduando);

        int get_limite_dias() override; 

        int get_limite_obras() override;
};
#endif