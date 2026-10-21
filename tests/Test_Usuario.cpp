#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Usuario.hpp"

class USUARIO_TESTE : public Usuario{
    public:
        USUARIO_TESTE(int id, std::string login, std::string senha, std::string nome) : Usuario(id, login, senha, nome) {}

        int get_limite_dias() override {
            return 1;
        }
        int get_limite_obras() override{
            return 4;
        }
};

TEST_CASE("Testando get's e set's de Usuario"){
    USUARIO_TESTE Usuario_teste(11, "176893214470", "ax45#", "Ana");

    SUBCASE("Testando Get's"){
        CHECK(Usuario_teste.get_id() == 11);
        CHECK(Usuario_teste.get_login() == "176893214470");
        CHECK(Usuario_teste.get_senha() == "ax45#");
        CHECK(Usuario_teste.get_nome() == "Ana");
        CHECK(Usuario_teste.is_ativo() == true);
        CHECK(Usuario_teste.is_penalizado() == false);
    }
    SUBCASE("Testando Set's"){
        Usuario_teste.set_senha("aaaaaa");
        Usuario_teste.set_penalizado(true);
        Usuario_teste.set_conta_ativa(false);

        CHECK(Usuario_teste.get_senha() == "aaaaaa");
        CHECK(Usuario_teste.is_penalizado() == true);
        CHECK(Usuario_teste.is_ativo() == false);
    }
}
TEST_CASE("inserir e remover livros da lista de Usuario"){

    Livro Livro_teste("tituloX", "autorX", "Venezuela", "editoraX", 2000 , "CDDrandom", "ISBNrandom", 1);
    USUARIO_TESTE Usuario_teste(11, "1000000000000", "senhaX", "nomeX");

    Usuario_teste.inserir_livro(Livro_teste);

    CHECK(Usuario_teste.get_Lista_Livros_Usuario().size() == 1);

    Usuario_teste.remover_livro(Livro_teste.get_ISBN());

    CHECK(Usuario_teste.get_Lista_Livros_Usuario().size() == 0);
}

