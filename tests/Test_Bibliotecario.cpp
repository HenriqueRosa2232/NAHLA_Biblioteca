#include "doctest.h"

#include "Bibliotecario.hpp"
#include "Usuario.hpp"

TEST_CASE("Testando criacao do Bibliotecario dependendo da validacao de seus dados"){
    SUBCASE("Dados validos, dever permitira criar o bibliotecario"){
        REQUIRE(Validador::validar_dados(13, "1234567891234", "1234567891234", "bibliotecariox", "1234567891234") == true);

        Bibliotecario bibliotecario_teste(13, "1234567891234", "1234567891234", "bibliotecariox", "1234567891234");
        CHECK(bibliotecario_teste.get_id() == 13);
        // CHECK(funcionario_teste.get_nome() == "funcionariox");  //preciso q usuario tenha um get nome p poder acessar ele
        CHECK(bibliotecario_teste.get_siape() == "1234567891234");
    }
    SUBCASE("Dados invalidos, deve retornar falso e n permitir criar o bibliotecario"){
        REQUIRE(Validador::validar_dados(5, "1234567891234", "1234567891234", "funcionariox", "1234567891234") == false);
    }
}

TEST_CASE("Testando o metodo concluir pedido"){
    Bibliotecario bibliotecarioy(13, "1234567891234", "1234567891234", "bibliotecarioy", "1234567891234"); 
    Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
    Livro iniciar_acervo("livro teste", "autorx", "paisx", "editorax", 1999, "cddx", "1234567891233", 5); //tem q vir antes do outro q quero add
    Acervo_Livro acervo(iniciar_acervo);
    int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 14, 20, bibliotecarioy.set_pedidos_realizados(), &bibliotecarioy);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, bibliotecarioy.get_pedidos_realizados());

    SUBCASE("Status pedido foi aprovado e depois concluido"){
        bibliotecarioy.set_pedidos_realizados()[indice_real].status = "Aprovado";
        bibliotecarioy.atualizar_status_pedido(id_pedido, "Concluido");
        CHECK(bibliotecarioy.get_pedidos_realizados()[indice_real].status == "Concluido");
        bibliotecarioy.concluir_pedido(id_pedido, l1, acervo, bibliotecarioy.set_pedidos_realizados());
        CHECK(acervo.getListaAcervoLivro().size() == 2); 
    }
    SUBCASE("Status pedido aprovado e depois encerrado(nao concluiu)"){
        bibliotecarioy.set_pedidos_realizados()[indice_real].status = "Aprovado";
        bibliotecarioy.atualizar_status_pedido(id_pedido, "Encerrado");
        bibliotecarioy.concluir_pedido(id_pedido, l1, acervo, bibliotecarioy.set_pedidos_realizados());

        CHECK(bibliotecarioy.get_pedidos_realizados()[indice_real].status == "Encerrado");
        CHECK(bibliotecarioy.get_pedidos_realizados()[indice_real].motivo_pedido_nao_concluido.empty() == false);
        CHECK(acervo.getListaAcervoLivro().size() == 1);
    }
    SUBCASE("Status pedido recusado"){
        bibliotecarioy.set_pedidos_realizados()[indice_real].status = "Recusado";
        bibliotecarioy.atualizar_status_pedido(id_pedido, "Concluido"); 
        bibliotecarioy.concluir_pedido(id_pedido, l1, acervo, bibliotecarioy.set_pedidos_realizados());

        CHECK(bibliotecarioy.get_pedidos_realizados()[indice_real].status == "Finalizado");
        CHECK(bibliotecarioy.get_pedidos_realizados()[indice_real].motivo_pedido_recusado.empty() == false);
        CHECK(acervo.getListaAcervoLivro().size() == 1); //so o livro inical
    }
}

TEST_CASE("Testando o metodo catalogar livro, ela so cataloga se a concluir pedido permitir(ja testada acima)"){
    Bibliotecario bibliotecarioy(13, "1234567891234", "1234567891234", "bibliotecarioy", "1234567891234"); 
    Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
    Livro iniciar_acervo("livro teste", "autorx", "paisx", "editorax", 1999, "111.1", "1234567891233", 5); //tem q vir antes do outro q quero add
    Acervo_Livro acervo(iniciar_acervo);
    int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 14, 20, bibliotecarioy.set_pedidos_realizados(), &bibliotecarioy);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, bibliotecarioy.get_pedidos_realizados());
    bibliotecarioy.set_pedidos_realizados()[indice_real].status = "Aprovado";
    bibliotecarioy.atualizar_status_pedido(id_pedido, "Concluido");
    bibliotecarioy.catalogar_livro(id_pedido, acervo, l1, bibliotecarioy.set_pedidos_realizados());
    CHECK(acervo.getListaAcervoLivro().size() == 2);
}

TEST_CASE("Teste conferir estoque do livro"){
    Livro iniciar_acervo("tituloy", "autory", "paisy", "editoray", 1900, "342.1", "1234567891234", 10);
    Acervo_Livro acervo(iniciar_acervo);
    Bibliotecario bibliotecarioy(13, "1234567891234", "1234567891234", "bibliotecarioy", "1234567891234");
    SUBCASE("O livro esta no acervo"){
        int qtd = bibliotecarioy.consultar_estoque_livro(iniciar_acervo, acervo);
        CHECK(qtd == iniciar_acervo.get_quantidade_exemplares_total());
    }
    SUBCASE("O livro nao esta no acervo"){
        Livro l1("titlox", "autorx", "paisx", "editorax", 1999, "832.6", "1234567891233", 5);
        int qtd = bibliotecarioy.consultar_estoque_livro(l1, acervo);
        CHECK(qtd == -1);
    }
}

TEST_CASE("Testando livro danificado"){
    Livro iniciar_acervo("tituloy", "autory", "paisy", "editoray", 1900, "342.1", "1234567891234", 10);
    Acervo_Livro acervo(iniciar_acervo);
    Usuario usuariox(10, "1234567891234", "1234", "usuariox");
    Bibliotecario bibliotecarioy(13, "1234567891234", "1234567891234", "bibliotecarioy", "1234567891234");
    SUBCASE("Livro Amassado"){
        CHECK(usuariox.is_penalizado() == false);
        bibliotecarioy.livro_danificado(iniciar_acervo, usuariox, acervo, "Amassado");
        CHECK(usuariox.is_penalizado() == true);
    }
    SUBCASE("Livro Molhado"){
        CHECK(usuariox.is_penalizado() == false);
        bibliotecarioy.livro_danificado(iniciar_acervo, usuariox, acervo, "Molhado");
        CHECK(usuariox.is_penalizado() == true);
    }
    SUBCASE("Livro Paginas faltando"){
        CHECK(usuariox.is_penalizado() == false);
        bibliotecarioy.livro_danificado(iniciar_acervo, usuariox, acervo, "Paginas faltando");
        CHECK(usuariox.is_penalizado() == true);
    }
    SUBCASE("Livro Inutilizavel"){
        CHECK(acervo.getListaAcervoLivro().size() == 1);
        CHECK(usuariox.is_penalizado() == false);
        CHECK(iniciar_acervo.get_quantidade_exemplares_total() == 10);
        CHECK(iniciar_acervo.get_quantidade_disponivel() == 10);
        bibliotecarioy.livro_danificado(iniciar_acervo, usuariox, acervo, "Inutilizavel");
        CHECK(usuariox.is_penalizado() == true);
        CHECK(iniciar_acervo.get_quantidade_exemplares_total() == 9);
        CHECK(iniciar_acervo.get_quantidade_disponivel() == 9);
        CHECK(acervo.getListaAcervoLivro().size() == 0); //removeu o livro do acervo
    }
}

// TEST_CASE("Testando buscar usuario sistema"){} //falta implementar tbm ;-;

// TEST_CASE("Testando salvar registro livro"){} //falta implementacao, precisa de banco d dados, se e q vamos usar ainda

// TEST_CASE("Testando devolver emprestimo"){} 

