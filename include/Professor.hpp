#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "Funcionario.hpp"

class Professor : public Funcionario{
    public:
    
    Professor(int id, std::string siape, std::string nome, std::string senha);  
        
};
#endif