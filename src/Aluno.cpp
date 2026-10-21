#include "Aluno.hpp"

Aluno::Aluno(int id, std::string matricula, std::string senha, std::string nome, bool pos_graduando) :
    Usuario(id, matricula, senha, nome), pos_graduando(pos_graduando), matricula(matricula)
    {}

bool Aluno::is_pos_graduando(){
    return this -> pos_graduando;
}

void Aluno::set_pos_graduando(bool pos_graduando){
    this -> pos_graduando = pos_graduando;
}

int Aluno::get_limite_dias(){
    if (pos_graduando){
        return 28;
    }
    return 14;
}

int Aluno::get_limite_obras(){
    if (pos_graduando){
        return 7;
    }
    return 5;
}

