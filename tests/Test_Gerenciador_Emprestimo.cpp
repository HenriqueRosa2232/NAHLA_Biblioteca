#ifndef TEST_EMPRESTIMO_H
#define TEST_EMPRESTIMO_H

#include "doctest.h"
#include "Gerenciador_Emprestimo.hpp"

TEST_CASE("Testando se usuario penalizado não pode pegar livros") {
    Usuario u(11, "2026000000", "senha", "Maria");
    u.set_penalizado(true);
    CHECK_FALSE(Gerenciador_Emprestimo::permitir_emprestimo(u));
}

TEST_CASE("Testando se é proibido o empréstimo de livros a usuários que já pegaram o máximo de livros") {
    Usuario u(11, "2026000000", "senha", "Maria");
    Usuario w(12, "2026000001", "senha", "João");
    Usuario z(13, "2026000002", "senha", "Lara");
    SUBCASE("Com id 10, limite de 7 livros") {
        SUBCASE("Quando o usuário de id 10 tem menos de 7 livros"){
            CHECK(Gerenciador_Emprestimo::permitir_emprestimo(u));
    
        }
        CHECK(Gerenciador_Emprestimo::permitir_emprestimo(u));
    }
    SUBCASE("com 7 livros nao pode mais") {
        u.get_Lista_Livros_Usuario().size() == 7;
        CHECK_FALSE(Gerenciador_Emprestimo::permitir_emprestimo(u));
    }
}
#endif