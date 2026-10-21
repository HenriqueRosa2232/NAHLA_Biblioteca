#include "Gerenciador_Emprestimo.hpp"
#include <chrono>
#include <map>

long long int Gerenciador_Emprestimo::proximo_id = 1;

std::map<long long int, Emprestimo> Gerenciador_Emprestimo::emprestimos;

bool Gerenciador_Emprestimo::permitir_emprestimo(Usuario& usuario){ //obs:retirada do parametro livro
    if (usuario.is_penalizado()){
        return false;
    }else{
        if((usuario.get_id() == 10) && (usuario.get_Lista_Livros_Usuario().size() < 7)){
            return true;
        }else if((usuario.get_id() >= 11) && (usuario.get_id() <= 13) && (usuario.get_Lista_Livros_Usuario().size() < 5)){
            return true;
        }else{
            return false;
        }
    }
}
long long int Gerenciador_Emprestimo::pegar_livro_emprestado(Usuario& usuario, Livro& livro){
    if(Gerenciador_Emprestimo::permitir_emprestimo(usuario) && (checar_estoque_livro(livro))){
       usuario.inserir_livro(livro);

       livro.set_quantidade_disponivel(livro.get_quantidade_disponivel() - 1);

       std::cout << "Empréstimo efetuado com sucesso!" << std::endl;
    }else{
        std::cout << "Não foi possível realizar o empréstimo." << std::endl;
    }
}

//bool deseja_entrar_lista_espera(Usuario& usuario, Livro& livro){}

void Gerenciador_Emprestimo::reservar_livro(Usuario& usuario, Livro& livro){
    if(Gerenciador_Emprestimo::permitir_emprestimo(usuario) && !(checar_estoque_livro(livro))){
        livro.adicionar_usuario_lista_espera(&usuario);

        std::cout << "Reserva efetuada com sucesso!" << std::endl;
    }else{
        std::cout << "Erro ao efetuar empréstimo, cheque se você cumpre todas as condições necessárias" << std::endl;
    }
}

bool Gerenciador_Emprestimo:: checar_reserva_livro(Usuario& usuario, Livro& livro){
    if (livro.get_lista_espera().size() == 0){
        return true;
    }else{
        reservar_livro(usuario, livro);
    }
}

bool Gerenciador_Emprestimo::checar_estoque_livro(Livro& livro){
    if(livro.get_quantidade_disponivel() > 0){
        return true;
    }else{
        return false;
    }
}

void Gerenciador_Emprestimo::devolver_emprestimo(Usuario& usuario, Livro& livro){
    usuario.remover_livro(livro);
    livro.set_quantidade_disponivel(livro.get_quantidade_disponivel() + 1);

    if(checar_atraso(usuario, livro)){
        criar_penalizacao(usuario);
        std::cout << "Livro devolvido com sucesso! Foi identificado um atraso, e sua devida penalização foi criada." << std::endl;
    }else{
        std::cout << "Livro devolvido. Usuário em situação regular." << std::endl;
    }
    
}

void Gerenciador_Emprestimo::calcular_data_devolucao(Usuario& usuario, Livro& livro){
    
}

bool Gerenciador_Emprestimo::checar_atraso(const Emprestimo& emprestimo){

}

void Gerenciador_Emprestimo::status_emprestimo(Usuario& usuario, Livro& livro){
    /*se o livro estiver na fila do aluno: printar Livro ainda em empréstimo
    se o livro não estiver na fila do aluno: printar Livro devolvido
    */
}

void Gerenciador_Emprestimo::criar_penalizacao(Usuario& usuario){
    usuario.set_penalizado(true);
}
