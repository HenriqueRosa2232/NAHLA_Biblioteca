#include "doctest.h"
#include "Validador.hpp"

TEST_CASE("Testando remover espacos"){
    CHECK(Validador::remover_espacos("              abc      ") == "abc"); //so remove os espacos das beiradas
    CHECK(Validador::remover_espacos("  r ec    ") == "r ec"); //pois espaco e um caractere valido
    CHECK(Validador::remover_espacos(" amaodbqdok    ") == "amaodbqdok");
}


TEST_CASE("Testando se o texto e valido"){
    CHECK(Validador::is_texto_valido("abcde") == true);
    CHECK(Validador::is_texto_valido("                     ") == false);
    CHECK(Validador::is_texto_valido("       aeiou ") == true); //o texto e valido se apos remover os espacos n ficar vazio
}

//tenho q alterar tds lugares q mexem c size como id pedido
TEST_CASE("Testando se metodo validacao do id pedido e valido"){
    SUBCASE("Id existe"){
        Funcionario funcionariox(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234");
        Livro l("titulox", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10);
        CHECK(Validador::validar_dados(l, 14, 20) == true); 

        int id_pedido = funcionariox.solicitar_compra_de_livros(l, 14, 20);
        std::vector <SolicitacaoCompra> pedidos_funcionario = funcionariox.get_pedidos_realizados();
        CHECK(Validador::is_id_pedido_valido(id_pedido, pedidos_funcionario) == true);
    }
    SUBCASE("Id nao existe"){
        Funcionario funcionariob(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234");
        Livro l("titulox", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10);
        CHECK(Validador::validar_dados(l, 14, 20) == true); 

        //se id e invalido qnd tenta acessar algo e n tem nada no vetor ainda
        CHECK(Validador::is_id_pedido_valido(0, funcionariob.get_pedidos_realizados()) == false); 

        //se n estiver vazio mas id ainda for invalido
        int id_pedido = funcionariob.solicitar_compra_de_livros(l, 20, 10);
        CHECK(Validador::is_id_pedido_valido(5, funcionariob.get_pedidos_realizados()) == false);
    }
}

TEST_CASE("Testando validacao do Livro"){
    SUBCASE("Dados validos"){
        //happy path la
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "Kenneth H. Rosen", "Estados Unidos", "McGraw-Hill", 2009,  "511.1", "9788580550055", 4) == true);
    }
    SUBCASE("Dados invalidos"){
    CHECK(Validador::validar_dados("", "Kenneth H. Rosen", "Estados Unidos", "McGraw-Hill", 2009,  "511.1", "9788580550055", 4) == false);
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "", "Estados Unidos", "McGraw-Hill", 2009,  "511.1", "9788580550055", 4) == false);
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "Kenneth H. Rosen", "", "McGraw-Hill", 2009,  "511.1", "9788580550055", 4) == false);
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "Kenneth H. Rosen", "Estados Unidos", "", 2009,  "511.1", "9788580550055", 4) == false);
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "Kenneth H. Rosen", "Estados Unidos", "McGraw-Hill", 2029,  "511.1", "9788580550055", 4) == false);
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "Kenneth H. Rosen", "Estados Unidos", "McGraw-Hill", 2009,  "", "9788580550055", 4) == false);
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "Kenneth H. Rosen", "Estados Unidos", "McGraw-Hill", 2009,  "511.1", "", 4) == false);
    CHECK(Validador::validar_dados("Matemática Discreta e suas Aplicações", "Kenneth H. Rosen", "Estados Unidos", "McGraw-Hill", 2007,  "511.1", "9788580550055", -2) == false);
    }
}

TEST_CASE("Testando validacao do Funcionario"){
    SUBCASE("Dados validos"){ //happy path 
        CHECK(Validador::validar_dados(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234") == true);
    }
    SUBCASE("Dados invalidos"){
        //10 ou 11 e de aluno, funcionario(professor ou bibliotecario n tem esse id, so 12 ou 13
        CHECK(Validador::validar_dados(10, "1234567891234", "1234567891234", "funcionariox", "1234567891234") == false);
        //algm dos outros campos q e string vazios ali
        CHECK(Validador::validar_dados(10 , "", "1234567891234", "funcionariox", "1234567891234") == false);
        CHECK(Validador::validar_dados(13, "1234567891234", "", "funcionariox", "1234567891234") == false);
        CHECK(Validador::validar_dados(13, "1234567891234", "1234567891234", "", "1234567891234") == false);
        CHECK(Validador::validar_dados(13, "1234567891234", "1234567891234", "funcionariox", "") == false);
    }
}

TEST_CASE("Testando validacao de dados dos pedidos para compra"){
    SUBCASE("Informacoes validas"){
        Funcionario funcionariox(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234");
        Livro l("titulox", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10);
        
        //se for manter o id p validar(acho q n tem como, qlqr coisa so chama o validar id dps, mas a classe n vai criar o id errado ao armazenar ele n)
        // CHECK(Validador::validar_dados(l, 14, funcionariox.get_pedidos_realizados().size()+1, 20) == true); 
        CHECK(Validador::validar_dados(l, 14, 20) == true); 
    }
    SUBCASE("Informacoes invalidas"){
        //no caso, esse get_pedidos realizados size tem q ser fixo no 3o parametro, o usuario n poderia mexer, 
        //nem seria uma opcao p ele alterar
        Funcionario funcionariox(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234");
        Livro l("", "autorx", "paisx", "editorax", 1900, "625.4", "1234567891234", 10);
        // CHECK(Validador::validar_dados(l, 14, funcionariox.get_pedidos_realizados().size()+1, 10) == false);
        CHECK(Validador::validar_dados(l, 14, 10) == false);
        // CHECK(Validador::validar_dados(l, -5, funcionariox.get_pedidos_realizados().size()+1, 600) == false);
        CHECK(Validador::validar_dados(l, -5, 600) == false);
        Livro l2("tituloz", "autorz", "paisz", "editoraz", 1984, "888.2", "1234567891234", 0);
        // CHECK(Validador::validar_dados(l2, 7, funcionariox.get_pedidos_realizados().size()+1, 0) == false); //n quero livro c 
        CHECK(Validador::validar_dados(l2, 7, 0) == false); //n quero livro c 0 n 
    }
}
