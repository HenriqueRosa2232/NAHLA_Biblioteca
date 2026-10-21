#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Acervo_Pessoas.hpp"
#include "Usuario.hpp"
#include "Aluno.hpp"
#include "Professor.hpp"
#include "Bibliotecario.hpp"

TEST_CASE("Testando o construtor e busca de usuarios no Acervo_Pessoas") {
    // Cria um Aluno de teste (ID 11, conforme a regra implementada no seu .cpp)
    Aluno alunoTeste("Alice Silva", "senha123", "alice123", 11);

    // Instancia o acervo passando o aluno pelo construtor
    Acervo_Pessoas acervo(alunoTeste);

    // 1. Valida se o aluno inserido via construtor é encontrado com sucesso buscando pelo login e ID correto (11)
    std::string loginBusca = "alice123";
    const Usuario* usuarioEncontrado = acervo.buscarUsuario(loginBusca, 11);
    
    REQUIRE(usuarioEncontrado != nullptr);
    CHECK(usuarioEncontrado->get_login() == "alice123");

    // 2. Tenta buscar um login inexistente ou ID incorreto (deve retornar nullptr)
    std::string loginFantasma = "usuario_inexistente";
    CHECK(acervo.buscarUsuario(loginFantasma, 11) == nullptr);
}

TEST_CASE("Testando insercao posterior e remocao de usuarios no Acervo_Pessoas") {
    // Cria um Professor (ID 12) e um Aluno (ID 11) para simular o acervo
    Professor profTeste("Pedro Henrique", "senha456", "Pedro_siap", 12);
    Aluno alunoCarlos("Carlos Eduardo", "senha789", "Carlos_mat", 11);

    // Inicializa o acervo com o professor
    Acervo_Pessoas acervo(profTeste);

    // Insere o aluno posteriormente usando o método inserirUsuario
    acervo.inserirUsuario(alunoCarlos);

    // 3. Remove o aluno existente pelo login ("Carlos_mat")
    CHECK(acervo.removerUsuarioPorLogin("Carlos_mat") == true);
    
    // 4. Tenta remover novamente um login que já foi deletado ou não existe
    CHECK(acervo.removerUsuarioPorLogin("Carlos_mat") == false);

    // 5. Garante que o professor continua cadastrado e intacto no acervo
    std::string loginProf = "Pedro_siap";
    const Usuario* usuarioRestante = acervo.buscarUsuario(loginProf, 12);
    REQUIRE(usuarioRestante != nullptr);
    CHECK(usuarioRestante->get_login() == "Pedro_siap");
}