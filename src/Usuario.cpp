#include "Usuario.hpp"

Usuario::Usuario(int id, std::string login, std::string senha, std::string nome) : 
    id(id), 
    login(login),
    senha(senha),
    nome(nome)
    {}

bool Usuario::set_penalizado(bool penalizado) {
    this -> penalizado = penalizado;
}

int Usuario::get_id(){
    return this -> id;
}

std::string Usuario::get_login(){
    return this -> login;
}

void Usuario::set_senha(std::string senha){
    this -> senha = senha;
}

std::string Usuario::get_senha(){
    return this -> senha;
}

std::string Usuario::get_nome(){
    return this -> nome;
}

const std::list<Livro>& Usuario::get_Lista_Livros_Usuario(){
    return this -> Livros_Usuario;
}

bool Usuario::is_penalizado(){
    return this -> penalizado;
}

void Usuario::inserir_livro(Livro& livro){
    Livros_Usuario.push_back(livro);
}

void Usuario::remover_livro(std::string ISBN){
    for (auto it = this->Livros_Usuario.begin(); it != this->Livros_Usuario.end(); it++)
    {
        if (it->get_ISBN() == ISBN)
        {
            this->Livros_Usuario.erase(it);
            break;
        }
   }
}

bool Usuario::is_ativo(){
    return this -> conta_ativa;
}

void Usuario::set_conta_ativa(bool ativo) {
    this -> conta_ativa = ativo;
}