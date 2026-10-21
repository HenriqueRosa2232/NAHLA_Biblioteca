#include "Acervo_Pessoas.hpp"
#include "Usuario.hpp"
#include "Aluno.hpp"
#include "Professor.hpp"
#include "Bibliotecario.hpp"
#include <iostream>

Acervo_Pessoas::Acervo_Pessoas(Usuario &Usuario) {
    if (Usuario.get_id() == 13){
        Bibliotecario* b1 = (Bibliotecario*) &Usuario;
        bibliotecarios.push_back(*b1);
    

    } else if (Usuario.get_id() == 12){ 
        Professor* p1=(Professor*)& Usuario;
        professores.push_back(*p1);

    } else if (Usuario.get_id() ==11){
        Aluno* a1 = (Aluno*) &Usuario;
        alunos.push_back (*a1);
        
    }
    
}
void Acervo_Pessoas::inserirUsuario (Usuario& usuario){
    if (usuario.get_id() == 13) {
        bibliotecarios.emplace_back(usuario);
    } else if (usuario.get_id() == 11) { 
        alunos.emplace_back(usuario);
    } else if (usuario.get_id() == 12){
        professores.emplace_back(usuario);
    }
}


const Usuario* Acervo_Pessoas::buscarUsuario(std::string& login, int id) {
   if (id == 11) {
    for (auto& aluno : alunos) {
        if (aluno.get_login() == login) { 
            return &aluno;
        }
    }

   }
    if (id == 12) { 
        for (auto& professor : professores) {
        if (professor.get_login() == login) {
            return &professor;
    }
}

}
    if (id == 13) { 
        for (auto& bibliotecario : bibliotecarios) {
        if (bibliotecario.get_login() == login) {
            return &bibliotecario;
}
    }
}

}

bool Acervo_Pessoas::removerUsuarioPorLogin(std::string login) {
    for (auto it = alunos.begin(); it != alunos.end(); ++it) {
        if (it -> get_login() == login) {
            alunos.erase(it);
            return true;
        }
    }
    return false;
}


//Exibe na saída padrão a lista de todos os usuários cadastrados

void Acervo_Pessoas::imprimirAluno(Aluno & aluno) {
    std::cout << "Nome: " << aluno.get_nome()<< "\t" << 
    "Matricula: " << aluno.get_login() << "\t" 
    << (aluno.is_penalizado() ? "Penalizado": "Regular") <<std::endl;

    
} 




void Acervo_Pessoas::imprimirProfessor(Professor & professor) {
std::cout << "Nome: " << professor.get_nome()<< "\t" << 
    "SIAPE: " << professor.get_login() << "\t" 
    << (professor.is_penalizado() ? "Penalizado": "Regular") <<std::endl;
}



void Acervo_Pessoas::imprimirBibliotecario(Bibliotecario & bibliotecario) {
    std::cout << "Nome: " << bibliotecario.get_nome()<< "\t" << 
    "SIAPE: " << bibliotecario.get_login() << "\t" 
    << (bibliotecario.is_penalizado() ? "Penalizado": "Regular") <<std::endl;
}



    // //std::cout << "\n--- Registro de Usuários ---" << std::endl;
 
    // //if (alunos.empty()) {
    //     std::cout << "Nenhum aluno cadastrado." << std::endl;
    //     return;
    // }

    // if (bibliotecarios.empty()) {
    //     std::cout << "Nenhum bibliotecário cadastrado." << std::endl;
    //     return;
    // }

    // if (professores.empty()) {
    //     std::cout << "Nenhum professor cadastrado." << std::endl;
    //     return;
    // }

    // //for (const auto& usuario :usuario) {
    //    // Usuario temp = usuario;
    //     //std::cout << "ID (Tipo): " << temp.get_id() 
    //               //<< " | Login: " << temp.get_login() 
    //               //<< std::endl;
    // }
