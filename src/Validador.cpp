#include "Validador.hpp"

std::string Validador::remover_espacos(std::string str){
    auto inicio = std::find_if_not(str.begin(), str.end(), [](unsigned char ch){return std::isspace(ch);});
    if(inicio == str.end()){
        return ""; //string ta vazia se cmc e termina msm lugar
    }
    auto fim = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char ch){std::isspace(ch);}).base();
    return std::string(inicio, fim); //junta em um string e envia ela d volta
}


bool Validador::is_texto_valido(const std::string& str){
    return !remover_espacos(str).empty();
}

//validador dados livro
bool Validador::validar_dados(std::string titulo, std::string autor, std::string pais, std::string editora, int ano, 
    std::string CDD, std::string ISBN, int quantidade_exemplares_total){ //n precisa indicar q e static aq, n sabia kk(deu erro)
    if(is_texto_valido(titulo)){
        return false;
    }
    else if(is_texto_valido(autor)){
        return false;
    }
    else if(is_texto_valido(pais)){
        return false;
    }
    else if(is_texto_valido(editora)){
        return false;
    }
    else if(ano < 0 || ano > 2026){
        return false;
    }
    else if(is_texto_valido(CDD)){ //tem tamanho fixo p verificar tbm ou n?
        return false;
    }
    else if(is_texto_valido(ISBN)){ //msm d cima, n sei, google falou q acho q livros antigos tem 10 e novos 13, mas n sei como tratar isso
        return false;
    }
    else if(quantidade_exemplares_total <= 0){ //acho q o livro q bibliotecario for adicionar no acervo tem q ter ao
// menos 1 exemplar ne
        return false;
    }
    return true; //passou em td? ent agr libera p chamar o construtor de livro e criar o objeto livro msm(no qt la)
}

//validar dados do funcionario
bool Validador::validar_dados(int id, std::string login, std::string senha, std::string nome, std::string siape){
    if(id!=12 && id!=13){ //p cada um especifico la acho q tem q conferir na propria classe, ou ent ja fixar o id direto pq
        return false; //vai ter q informar msm p usuario o q e cada um no id, ou ent o id pode contar talvez a qtd de usuarios do
    }                   //sistema, e cada um teria um proprio? ?
    else if(is_texto_valido(login)){
        return false;
    }
    else if(is_texto_valido(senha)){
        return false;
    }
    else if(is_texto_valido(nome)){
        return false;
    }
    else if(is_texto_valido(siape)){ //tem q verificar no banco d dados se ta la tbm ne ;-; n sei fzr
        return false;
    }
    return true; //pode criar o funcionario
}

//validadar dados de solicitacao compra
bool Validador::validar_dados(Livro& livro, double preco_unitario, int quantidade){ //, int idpedido(acho q n existe ainda, como valida, genio?)
    std::string titulo = livro.get_titulo();
    std::string autor = livro.get_autor();
    std::string pais = livro.get_pais();
    std::string editora = livro.get_editora();
    int ano = livro.get_ano();
    std::string CDD = livro.get_CDD();
    std::string ISBN = livro.get_ISBN();
    int quantidade_exemplares_total = livro.get_quantidade_exemplares_total();
    double preco_total;
    if(quantidade > 0 && preco_unitario > 0){
        livro.set_preco_unitario(preco_unitario); //vai alterar o preco unitario do livro
    }
    if(Validador::validar_dados(titulo, autor, pais, editora, ano, CDD, ISBN, quantidade_exemplares_total) == false){
        return false; //se o livro for falso, n sei se isso realmente precisa, pq p criar o livro la ja vou chamar o conferir 
        //dados livro antes msm
    }
    else if(quantidade <= 0){ //tem q pedir no minimo um livro ne ;-;
        return false;
    }
    // else if(idpedido < 0){ //@qnd chamar tem q passar pedidos_realizados.size(), n deixar p usuario pq vai errar
    //     return false;
    // }
    return true; //ai chama p poder criar pedido dps ;)
}

//passar isso p validador, ne ;)
bool Validador::is_id_pedido_valido(int id_pedido, const std::vector <SolicitacaoCompra>& pedidos_funcionario){
    bool pedido_existe = false;
    if(id_pedido > pedidos_funcionario.back().id_pedido){
        return false;
    }
    else{
        for(size_t i; i < pedidos_funcionario.size(); i++){
            if(id_pedido == pedidos_funcionario[i].id_pedido){ //percorre o vetor dos pedidos do funcionario e ve se existe la
                pedido_existe = true;
            }
        }
    }
    return pedido_existe;
}

