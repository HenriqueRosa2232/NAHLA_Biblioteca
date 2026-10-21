#include "doctest.h"

#include "Funcionario.hpp"
#include "Validador.hpp"

Funcionario funcionariow(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234");
Livro l0("titulow", "autorw", "paisw", "editoraw", 2021, "666.6", "9999999999999", 60);
Acervo_Livro acervo;

TEST_CASE("Testando criacao do Funcionario dependendo da validacao de seus dados"){
    SUBCASE("Dados validos, dever permitira criar o funcionario"){
        REQUIRE(Validador::validar_dados(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234") == true);

        Funcionario funcionario_teste(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234");
        CHECK(funcionario_teste.get_id() == 13);
        // CHECK(funcionario_teste.get_nome() == "funcionariox");  //preciso q usuario tenha um get nome p poder acessar ele
        CHECK(funcionario_teste.get_siape() == "1234567891234");
    }
    SUBCASE("Dados invalidos, deve retornar falso e n permitir criar o funcionario"){
        REQUIRE(Validador::validar_dados(5, "1234567891234", "1234567891234", "funcionariox", "1234567891234") == false);
    }
}

TEST_CASE("Testando os geters e seters de funcionario"){
    Funcionario f(13, "1234567891234", "1234567891234", "funcionariox", "1234567891234");
    SUBCASE("Testando getters"){
        CHECK(f.get_id() == 13);
        CHECK(f.get_login() == "1234567891234");
        CHECK(f.get_senha() == "1234567891234");
        // CHECK(f.get_nome() == "funcionariox"); //preciso d um get nome funcionario
        CHECK(f.get_siape() == "1234567891234");
        CHECK(f.is_penalizado() == false);
        CHECK(f.get_Lista_Livros_Usuario().empty() == true); //pq lista livros cmc vazia
        CHECK(f.get_pedidos_realizados().empty() == true); //cmc sem ter feito nenhum pedido
    }
    SUBCASE("Testando setters e se fizeram efeito"){
        f.set_senha("0000000000000");
        f.set_penalizado(true);
        
        CHECK(f.set_pedidos_realizados().empty() == true);
        CHECK(f.get_senha() == "0000000000000");
        CHECK(f.is_penalizado() == true);
    }
}

/*@preciso dessa qtd informada na validacao pq eu posso querer adicionar um livro q ja esta no acervo, so aumentar a qtd dele, 
tem q verificar se ja existe ent e aq so verifica se a qtd p compra e maior q 0 msm. lembrar d falar na tela p usuario q
a outra e qtd de livros q ja tem e essa e a q quer comprar */

TEST_CASE("Testando a criacao de uma SolicitacaoCompra apos validacao dos dados"){
    SUBCASE("Dados validos, deve permitir criar a solicitacao"){
        Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234");
        Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
        Validador::validar_dados(l1, 14, 20);
        int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 14, 20, funcionarioy.set_pedidos_realizados(), &funcionarioy);
        int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionarioy.get_pedidos_realizados());

        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].id_pedido == id_pedido);
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].quantidade == 20);
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].status == "Pendente");
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].preco_total == 14*20); 
    }
    SUBCASE("Dados invalidos, nao deve permitir criar solicitacao do pedido"){
        Livro l2("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
        Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234");
        REQUIRE(Validador::validar_dados(l2, 14, 0) == false);
    }
}


//int Funcionario::solicitar_compra_de_livros(Livro& livro, double preco_unitario, int qtd_livros_compra)
TEST_CASE("Testando metodo solicitar_compra_de_livros"){ //isso so sera chamado no programa se passar na verificacao la
    Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234");
    Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
    REQUIRE(Validador::validar_dados(l1, 14, 20) == true);
    //livro, qtd_livros_compra, id_pedido, preco_unitario
    //Livro& livro, double preco_unitario, int qtd_livros_compra
    int id_pedido = funcionarioy.solicitar_compra_de_livros(l1, 14, 20);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionarioy.get_pedidos_realizados());

    CHECK(funcionarioy.get_pedidos_realizados().size() > 0); //ver se add corretamente o livro na lista do funcionario
    CHECK(funcionarioy.get_pedidos_realizados()[indice_real].id_pedido == 1); //ver se o id recebeu valor certo d indice + 1
    CHECK(funcionarioy.get_pedidos_realizados()[indice_real].quantidade == 20);
    CHECK(funcionarioy.get_pedidos_realizados()[indice_real].status == "Pendente"); 
}

TEST_CASE("Testando metodo para gerar status pedido"){
    REQUIRE(Validador::validar_dados(l0, 10, 35) == true); //inverter a ordem dois ultimos parametros d td lugar q tiver assim!
    int id_pedido = funcionariow.solicitar_compra_de_livros(l0, 10, 35);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionariow.get_pedidos_realizados());

    CHECK(funcionariow.get_pedidos_realizados()[indice_real].status == "Pendente"); //ver se original ta pendente msm
    funcionariow.gerar_status_pedido(id_pedido);
    std::string status_gerado = funcionariow.get_pedidos_realizados().back().status;
    CHECK((status_gerado == "Aprovado" || status_gerado == "Recusado") == true);
    std::string motivo_recusado = funcionariow.get_pedidos_realizados().back().motivo_pedido_nao_concluido;
    if(status_gerado == "Recusado"){
        CHECK(!motivo_recusado.empty() == true);
    }
    else{
        CHECK(motivo_recusado.empty() == true);
    }

}

TEST_CASE("Testando metodo para atualizar status pedido"){
    REQUIRE(Validador::validar_dados(l0, 20, 10) == true);
    int id_pedido = funcionariow.solicitar_compra_de_livros(l0, 20, 10);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionariow.get_pedidos_realizados());
    funcionariow.gerar_status_pedido(id_pedido);

    funcionariow.atualizar_status_pedido(id_pedido, "Concluido");
    std::string status_pedido = funcionariow.consultar_status_solicitacao_livros(id_pedido);
    CHECK((status_pedido == "Concluido" || status_pedido == "Encerrado" || status_pedido == "Finalizado") == true);
    status_pedido = funcionariow.consultar_status_solicitacao_livros(id_pedido);
    std::string motivo_nao_concluido = funcionariow.get_pedidos_realizados()[indice_real].motivo_pedido_nao_concluido;
    if(status_pedido == "Encerrado"){
        CHECK(!motivo_nao_concluido.empty() == true);
    }
    else{
        CHECK(motivo_nao_concluido.empty() == true);
    }
}

TEST_CASE("Testando metodo consultar status solicitacao do pedido"){
    Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234");
    SUBCASE("Id valido"){
        int id_pedido = funcionariow.solicitar_compra_de_livros(l0, 20, 10);
        int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionariow.get_pedidos_realizados());

        
        std::string status_retornado = funcionariow.consultar_status_solicitacao_livros(id_pedido);
        CHECK(status_retornado == "Aprovado" || status_retornado == "Recusado");
        
    }
    SUBCASE("Id invalido"){
        int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(10, funcionariow.get_pedidos_realizados());

        CHECK(funcionariow.consultar_status_solicitacao_livros(10) == "-1");
    }
}



//isso vai p bibliotecario e vai chamar e o catalogar livro la! n o concluir pedido
// TEST_CASE("Testando metodo para catalogar livro, se pedido tiver sido concluido corratamente"){
//     int id_pedido =  ; //ja foi criado e ta pronto p concluir 
//     funcionariow.concluir_pedido(id, l0, acervo);
//     std::string status_final = funcionariow.get_pedidos_realizados().back().status;
//     CHECK(status_final == "Concluido" || status_final == "Encerrado");
//     if(status_final == "Encerrado"){
//         CHECK(!funcionariow.get_pedidos_realizados()[id-1].motivo_pedido_nao_concluido.empty() == true);
//     }
//     else{
//         CHECK(funcionariow.get_pedidos_realizados()[id-1].motivo_pedido_nao_concluido.empty() == true);
//     }
//     if(status_final == "Concluido"){
//         CHECK(acervo.getListaAcervoLivro().size() == 1);
//     }
// }