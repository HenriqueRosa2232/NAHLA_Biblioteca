#include "doctest.h"
#include "Gerenciador_Pedidos.hpp"

TEST_CASE("Testando obter indice pelo id"){
    //happy path
    SUBCASE("Indice valido"){
        int id_pedido_atual = Gerenciador_Pedidos::get_id_atual();
        int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido_atual, Gerenciador_Pedidos::get_pedidos_globais());
        CHECK(id_pedido_atual == indice_real); //qnd ta c indice 0 e ainda n tem elems no vetor d pedidos globais os 2 sao 0(iguais)
    }
    
    SUBCASE("Indice invalido"){//indice invalido
        int indice_duvidoso = Gerenciador_Pedidos::obter_indice_pelo_id(14, Gerenciador_Pedidos::get_pedidos_globais());
        CHECK(indice_duvidoso == -1);
    }
}

TEST_CASE("Testando os getters de Gerenciador de Pedidos"){
    CHECK(Gerenciador_Pedidos::get_id_atual() == 0);
    CHECK(Gerenciador_Pedidos::get_pedidos_globais().empty() == true);
    CHECK(Gerenciador_Pedidos::get_motivos_pedido_recusado().empty() == false);
    CHECK(Gerenciador_Pedidos::get_motivos_pedido_nao_concluido().empty() == false);
}

TEST_CASE("Testando metodo solicitar_compra_de_livros"){
    Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234"); 
    Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
    REQUIRE(Validador::validar_dados(l1, 14, 20) == true);
    int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 14, 20, funcionarioy.set_pedidos_realizados(), &funcionarioy);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionarioy.get_pedidos_realizados());

    SUBCASE("Todos dados validos"){
        CHECK(funcionarioy.get_pedidos_realizados().size() > 0); //ver se add corretamente o livro na lista do funcionario
        CHECK(Gerenciador_Pedidos::get_pedidos_globais()[indice_real].dono_pedido == &funcionarioy); 
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].id_pedido == 1);
        CHECK(Gerenciador_Pedidos::get_pedidos_globais()[indice_real].id_pedido == 1);
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].quantidade == 20);
        CHECK(Gerenciador_Pedidos::get_pedidos_globais()[indice_real].quantidade == 20);
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].status == "Pendente"); 
        CHECK(Gerenciador_Pedidos::get_pedidos_globais()[indice_real].status == "Pendente");
    }

    SUBCASE("Dono pedido invalido"){ //acho q n tem como testar se o vetor e valido, pq ele pd ser vazio no 1o caso la? 
        int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 17, 10, funcionarioy.set_pedidos_realizados(), nullptr);
        CHECK(id_pedido == -1);
    }
}

TEST_CASE("Testando metodo gerar status pedido"){
    Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234"); 
    Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
    int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 14, 20, funcionarioy.set_pedidos_realizados(), &funcionarioy);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionarioy.get_pedidos_realizados());

    SUBCASE("Id valido"){
        bool valido = Validador::is_id_pedido_valido(id_pedido, funcionarioy.get_pedidos_realizados());
        Gerenciador_Pedidos::gerar_status_pedido(id_pedido, funcionarioy.set_pedidos_realizados());
        std::string status = funcionarioy.get_pedidos_realizados()[indice_real].status;
        CHECK(status == "Aprovado" || status == "Recusado");

        //tentar chamar dnv p gerar status pedido
        Gerenciador_Pedidos::gerar_status_pedido(id_pedido, funcionarioy.set_pedidos_realizados());
        std::string tentativa_gerar_novo_status = funcionarioy.get_pedidos_realizados()[indice_real].status;
        CHECK(status == tentativa_gerar_novo_status);
    }
    SUBCASE("Id invalido"){
        size_t tamanho_antes = funcionarioy.get_pedidos_realizados().size();
        Gerenciador_Pedidos::gerar_status_pedido(18, funcionarioy.set_pedidos_realizados());
        size_t tamanho_depois = funcionarioy.get_pedidos_realizados().size();
        CHECK(tamanho_antes == tamanho_depois); //pq so retorna nada la e n gera pedido novo
    }
}

TEST_CASE("Testando metodo atualizar status pedido"){
    Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234"); 
    Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
    int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 14, 20, funcionarioy.set_pedidos_realizados(), &funcionarioy);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionarioy.get_pedidos_realizados());
    bool valido = Validador::is_id_pedido_valido(id_pedido, funcionarioy.get_pedidos_realizados());
    Gerenciador_Pedidos::gerar_status_pedido(id_pedido, funcionarioy.set_pedidos_realizados());
    std::string status_gerado = funcionarioy.get_pedidos_realizados()[indice_real].status;

    SUBCASE("Id valido"){
        if(status_gerado == "Aprovado"){
            //funcionou e pedido tinha sido aprovado antes
            Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Concluido", funcionarioy.set_pedidos_realizados());
            std::string status = funcionarioy.get_pedidos_realizados()[indice_real].status;
            CHECK(status == "Concluido" || status == "Encerrado");

            //tentar chamar dnv p atualizar status
            if(status == "Concluido"){ //retornou nada la
                Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Encerrado", funcionarioy.set_pedidos_realizados());
                std::string tentativa_gerar_novo_status = funcionarioy.get_pedidos_realizados()[indice_real].status;
                CHECK(status == tentativa_gerar_novo_status);
            }
            else{//quer dizer q foi encerrado(so essas opcoes)
                CHECK(funcionarioy.get_pedidos_realizados()[indice_real].motivo_pedido_nao_concluido.empty() == false);
                Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Concluido", funcionarioy.set_pedidos_realizados());
                std::string tentativa_gerar_novo_status = funcionarioy.get_pedidos_realizados()[indice_real].status;
                CHECK(status == tentativa_gerar_novo_status);
            }
        }
        else{//vai ter sido recusado
            Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Concluido", funcionarioy.set_pedidos_realizados());
            //vai dar finalizado pq se tiver sido recusado vc n altera nada no novo status
            CHECK(funcionarioy.get_pedidos_realizados()[indice_real].status == "Finalizado");
            CHECK(funcionarioy.get_pedidos_realizados()[indice_real].motivo_pedido_recusado.empty() == false);
            //se tiver sido recusado vai sortear uma desculpa esfarrapada la p colocar no pedido do funcionario
        }
    }

    SUBCASE("Id invalido"){ 
        size_t tamanho_antes = funcionarioy.get_pedidos_realizados().size();
        Gerenciador_Pedidos::atualizar_status_pedido(10, "Encerrado", funcionarioy.set_pedidos_realizados());
        size_t tamanho_depois = funcionarioy.get_pedidos_realizados().size();
    }
}

TEST_CASE("Testando metodo concluir pedido"){
    Funcionario funcionarioy(13, "1234567891234", "1234567891234", "funcionarioy", "1234567891234"); 
    Livro l1("tituloy", "autory", "paisy", "editoray", 1900, "666.6", "1234567891234", 10);
    Livro iniciar_acervo("livro teste", "autorx", "paisx", "editorax", 1999, "cddx", "1234567891233", 5); //tem q vir antes do outro q quero add
    Acervo_Livro acervo(iniciar_acervo);
    int id_pedido = Gerenciador_Pedidos::solicitar_compra_de_livros(l1, 14, 20, funcionarioy.set_pedidos_realizados(), &funcionarioy);
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, funcionarioy.get_pedidos_realizados());
    bool valido = Validador::is_id_pedido_valido(id_pedido, funcionarioy.get_pedidos_realizados());
    // Gerenciador_Pedidos::gerar_status_pedido(id_pedido, funcionarioy.set_pedidos_realizados());
    SUBCASE("Status pedido foi aprovado e depois concluido"){
        //forcar ser aprovado
        funcionarioy.set_pedidos_realizados()[indice_real].status = "Aprovado";
        //forcar q concluiu
        Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Concluido", funcionarioy.set_pedidos_realizados());
        // Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Concluido", funcionarioy.set_pedidos_realizados());
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].status == "Concluido");
        Gerenciador_Pedidos::concluir_pedido(id_pedido, l1, acervo, funcionarioy.set_pedidos_realizados());
        CHECK(acervo.getListaAcervoLivro().size() == 2); //deve ter 2 elems la(o q coloquei p criar o acervo e o q pediu p add la)
        
    }
    SUBCASE("Status pedido foi aprovado e depois encerraram"){
        funcionarioy.set_pedidos_realizados()[indice_real].status = "Aprovado";
        Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Encerrado", funcionarioy.set_pedidos_realizados());

        Gerenciador_Pedidos::concluir_pedido(id_pedido, l1, acervo, funcionarioy.set_pedidos_realizados());

        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].status == "Encerrado");
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].motivo_pedido_nao_concluido.empty() == false);
        CHECK(acervo.getListaAcervoLivro().size() == 1);
    }
    SUBCASE("Status pedido foi recusado, deve apenas alterar para finalizar"){
        funcionarioy.set_pedidos_realizados()[indice_real].status = "Recusado";
        //msm se tentar passar estado novo se tiver recusado n aceita
        Gerenciador_Pedidos::atualizar_status_pedido(id_pedido, "Concluido", funcionarioy.set_pedidos_realizados()); 
        Gerenciador_Pedidos::concluir_pedido(id_pedido, l1, acervo, funcionarioy.set_pedidos_realizados());

        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].status == "Finalizado");
        CHECK(funcionarioy.get_pedidos_realizados()[indice_real].motivo_pedido_recusado.empty() == false);
        CHECK(acervo.getListaAcervoLivro().size() == 1); //so o livro inical
    }
}