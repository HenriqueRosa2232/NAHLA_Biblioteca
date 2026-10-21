// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Livro.hpp"
#include "Validador.hpp"

TEST_CASE("Testando criacao Livro dependendo da validacao dos dados"){
    SUBCASE("Dados validos, deve permitir a criacao do livro"){
        REQUIRE(Validador::validar_dados("titulox", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10) == true);
        
        Livro meu_livro("titulox", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10);
        CHECK(meu_livro.get_titulo() == "titulox"); //ver se dados ta correto msm dps d criar
        CHECK(meu_livro.get_ISBN() == "1234567891234");
    }

    SUBCASE("Dados invalidos, nao deve permitir a criacao do livro"){ //vai ser controlado por um if la
        REQUIRE(Validador::validar_dados("", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10) == false);
    }
}

TEST_CASE("Testando getters e setters da classe Livro"){
    Livro l("titulox", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10);
    SUBCASE("Testando os getters"){
        CHECK(l.get_titulo() == "titulox");
        CHECK(l.get_autor() == "autorx");
        CHECK(l.get_pais() == "paisx");
        CHECK(l.get_editora() == "editorax");
        CHECK(l.get_ano() == 1900);
        CHECK(l.get_CDD() == "625.4");
        CHECK(l.get_ISBN() == "1234567891234");
        CHECK(l.get_quantidade_exemplares_total() == 10);
        CHECK(l.get_quantidade_disponivel() == l.get_quantidade_exemplares_total()); //tem q ser iguais inicialmente
        CHECK(l.get_preco_unitario() == 0); //d inicio cmc c preco zero, so se setar dps muda algo
        CHECK(l.get_lista_espera().empty() == true);
    }
    
    SUBCASE("Testando os setters/alteradores e depois se as modificações foram feitas corretamente"){
        l.set_preco_unitario(50);
        l.set_quantidade_disponivel(5);
        l.set_quantidade_exemplares_total(12);
        //int id, std::string login, std::string senha, std::string nome
        Usuario usuario_teste(11, "2026888888", "2026888888", "usuariox");
        l.adicionar_usuario_lista_espera(&usuario_teste);
        CHECK(l.get_lista_espera().empty() == false); //conferir se adicionou o usuario la direito 
        l.remover_usuario_lista_espera(&usuario_teste);
        CHECK(l.get_lista_espera().empty() == true);

        CHECK(l.get_preco_unitario() == 50);
        CHECK(l.get_quantidade_disponivel() == 5);
        CHECK(l.get_quantidade_exemplares_total() == 12);
    }

    SUBCASE("Testando os setters com valores invalidos"){
        double valor_l = l.get_preco_unitario();
        l.set_preco_unitario(-2);
        CHECK(l.get_preco_unitario() == valor_l); //ver se n altera, na logica la e so falar q n mudou preco pq invalido ;)

        int qtd_total = l.get_quantidade_exemplares_total();
        l.set_quantidade_exemplares_total(0); //tem q ter pelo menos 1 livro p adicionar la
        CHECK(l.get_quantidade_exemplares_total() == qtd_total);

        int qtd_disponivel = l.get_quantidade_disponivel();
        l.set_quantidade_disponivel(100);
        CHECK(l.get_quantidade_disponivel() == qtd_disponivel);
        l.set_quantidade_disponivel(-6);
    }
}

//TEST_CASE("Exibir livro") //falta implementar ainda