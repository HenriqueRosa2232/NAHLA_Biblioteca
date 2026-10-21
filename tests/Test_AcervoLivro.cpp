#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include "Acervo_Livro.hpp"
Livro livro(
    "Dom Casmurro",
    "Machado de Assis",
    "Brasil",
    "Garnier",
    1899,
    "869.93",
    "9788535910663",
    10);
TEST_CASE("Teste do construtor de Livro")
{

    Acervo_Livro acervo(livro);
    auto it = std::next(acervo.getListaAcervoLivro().begin(), 0);
    REQUIRE(it != acervo.getListaAcervoLivro().end()); // verifica se o it nao ta apontando para elemento inválido
    CHECK(it->second.get_titulo() == "Dom Casmurro");
    CHECK(it->second.get_autor() == "Machado de Assis");
    CHECK(it->second.get_pais() == "Brasil");
    CHECK(it->second.get_editora() == "Garnier");
    CHECK(it->second.get_ano() == 1899);
    CHECK(it->second.get_CDD() == "869.93");
    CHECK(it->second.get_ISBN() == "9788535910663");
    CHECK(it->second.get_quantidade_exemplares_total() == 10);
}
TEST_CASE("Teste do método RemoverLivro")
{

    Acervo_Livro acervo(livro);
    std::map<std::string, Livro>::const_iterator it = acervo.getListaAcervoLivro().begin();

    REQUIRE(acervo.getListaAcervoLivro().size() == 1);
    acervo.RemoverLivroAcervo(it->second.get_ISBN());
    CHECK(acervo.getListaAcervoLivro().empty());
}
TEST_CASE("Teste do método ExibirLista")
{
    Acervo_Livro acervo(livro);

    std::ostringstream captura;
    auto *saidaOriginal = std::cout.rdbuf(captura.rdbuf());

    acervo.ExibirListaAcervo();

    std::cout.rdbuf(saidaOriginal);

    CHECK(captura.str().find("Dom Casmurro") != std::string::npos);
    CHECK(captura.str().find("Machado de Assis") != std::string::npos);
}
TEST_CASE("Teste do método inserir livro")
{
    Livro livro2(
        "O Alienista",
        "Machado de Assis",
        "Brasil",
        "L&PM",
        1882,
        "869.93",
        "9788525421050",
        5);

    Acervo_Livro acervo(livro);
    acervo.InserirLivroAcervo(livro2);
    auto it = std::next(acervo.getListaAcervoLivro().begin(), 1);
    REQUIRE(it != acervo.getListaAcervoLivro().end()); // verifica se o it nao ta apontando para elemento inválido
    CHECK(it->second.get_titulo() == "O Alienista");
    CHECK(it->second.get_autor() == "Machado de Assis");
    CHECK(it->second.get_pais() == "Brasil");
    CHECK(it->second.get_editora() == "L&PM");
    CHECK(it->second.get_ano() == 1882);
    CHECK(it->second.get_CDD() == "869.93");
    CHECK(it->second.get_ISBN() == "9788525421050");
    CHECK(it->second.get_quantidade_exemplares_total() == 5);
}
TEST_CASE("Teste do método buscar livro")
{
    Acervo_Livro acervo(livro);
    auto it = acervo.BuscarLivro("9788535910663");
    CHECK(it->get_ISBN() == "9788535910663");
}