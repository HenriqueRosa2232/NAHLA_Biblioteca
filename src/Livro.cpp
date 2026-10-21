#include "Livro.hpp"
#include "Usuario.hpp"
#include <algorithm>

Livro::Livro(std::string titulo, std::string autor, std::string pais, std::string editora, int ano, std::string CDD, 
    std::string ISBN, int quantidade_exemplares_total): titulo(titulo), autor(autor), pais(pais), editora(editora), 
    ano(ano), CDD(CDD), ISBN(ISBN), quantidade_exemplares_total(quantidade_exemplares_total), 
    quantidade_disponivel(quantidade_exemplares_total), preco_unitario(0){}

std::string Livro::get_titulo() const{
    return titulo;
}

std::string Livro::get_autor() const{
    return autor;
}

std::string Livro::get_pais() const{
    return pais;
}

std::string Livro::get_editora() const{
    return editora;
}

int Livro::get_ano() const{
    return ano;
}

std::string Livro::get_CDD() const{
    return CDD;
}

std::string Livro::get_ISBN() const{
    return ISBN;
}

int Livro::get_quantidade_exemplares_total() const{
    return quantidade_exemplares_total;
}

void Livro::set_quantidade_exemplares_total(int nova_qtd){
    if(nova_qtd > 0){
        quantidade_exemplares_total = nova_qtd; 
    }
    //se for ==0, no qt acho a podemos informar la e perguntar se deseja remover o livro? ai chamaria a funcao do acervo, acho p 
    //remover ele, dando opcao de quer remover ou n la c mensagebox
}

int Livro::get_quantidade_disponivel() const{
    return quantidade_disponivel;
}

void Livro::set_quantidade_disponivel(int nova_qtd){
    if(nova_qtd > quantidade_exemplares_total || nova_qtd < 0){
        return; //alguma coisa la q deu erro p alterar a qtd!!
    }
    else{
        quantidade_disponivel = nova_qtd; 
    }
}

double Livro::get_preco_unitario() const{
    return preco_unitario;
}

void Livro::set_preco_unitario(double novo_preco){
    if(novo_preco > 0){ //acho q n tem livro d graça, ne? ;-;
        preco_unitario = novo_preco;
    }
    else{
        //teria q indicar erro, como e void n sei como ficaria no qt...
    }
}

void Livro::exibir_livro(){
    //n sei como ficaria no qt ainda, mas a ideia e "printar" tds as informacoes do livro
}

const std::vector<Usuario*>& Livro::get_lista_espera(){
    return lista_espera;
}

void Livro::adicionar_usuario_lista_espera(Usuario* usuario){
    if(usuario!=nullptr){
        lista_espera.push_back(usuario); //tem q ver se ja n esta na lista tbm
    }
    else{
        //tem q indicar erro, estudar logo sobre excecoes, serao muitas
    }
}

//usar iterador p acessar os  elementos do vetor, tem algoritmo d find ja, 
void Livro::remover_usuario_lista_espera(Usuario* usuario){
    auto it = std::find(lista_espera.begin(), lista_espera.end(), usuario);
    if(usuario!=nullptr && (it != lista_espera.end())){ //usuario tem q n ser nulo e tem q estar na lista, se o find n encontrar
        //ele retorna o ultimo elem dps do ultimo da lista(o end ali)
        lista_espera.erase(it); 
    }
    else{
        //tem q dar erro tbm ;-;
    }
}
