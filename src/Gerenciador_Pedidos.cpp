#include "Gerenciador_Pedidos.hpp"
// #include "Validador.hpp"

int Gerenciador_Pedidos::id_atual = 0;

//obs: isso so deve ser chamado dps de validar_id la
int Gerenciador_Pedidos::obter_indice_pelo_id(int id_pedido, const std::vector <SolicitacaoCompra>& pedidos_funcionario){
    bool pedido_existe = false;
    if(Validador::is_id_pedido_valido(id_pedido, pedidos_funcionario) == false){
        return -1; //tratar la q -1 e pq n existe o id pedido
    }
    
    for(size_t i; i < pedidos_funcionario.size(); i++){
        if(pedidos_funcionario[i].id_pedido == id_pedido){
            return static_cast<int>(i);
        }
    }
    return -1; 
}

//verificar se a solicitacaocompra e valida antes c o metodo do validador dela. Se chamar id valido aq vai dar pau pq n existe pedido ainda p comparar id!
int Gerenciador_Pedidos::solicitar_compra_de_livros(Livro& livro, double preco_unitario, int qtd_livros_compra, 
    std::vector<SolicitacaoCompra>& pedidos_funcionario, Funcionario* dono_pedido){
        if(dono_pedido == nullptr){
            return -1; //dono invalido, n deve criar o pedido e informar q n localizou dono ou algo tipo
        }
    Gerenciador_Pedidos::id_atual++; //cmc do 1 e aumenta conforme as instancias de solicitacaocompra

    SolicitacaoCompra novo_pedido(livro, qtd_livros_compra, id_atual, preco_unitario); 
    novo_pedido.dono_pedido = dono_pedido;
    //tem q conseguir verificar se criou td certo 
    // pedidos_realizados.push_back(novo_pedido); //adicionando ao vetor la 
   
    pedidos_globais.push_back(novo_pedido);
    pedidos_funcionario.push_back(novo_pedido);

    return id_atual; //pegar la no qt p facilitar e coloca numa variavel idpedido p chamar mais rapido
}

void Gerenciador_Pedidos::gerar_status_pedido(const int id_pedido, std::vector<SolicitacaoCompra>& pedidos_funcionario){
    if(Validador::is_id_pedido_valido(id_pedido, pedidos_funcionario) == false){ //pega do ultimo pq vai ter maior id ja q vetor smp add pelo final 
        return; //indicar erro la pq pedido n pertence a esse funcionario
    }

    int indice_real = obter_indice_pelo_id(id_pedido, pedidos_funcionario);

    if(pedidos_funcionario[indice_real].status != "Pendente"){
        return;
    }
   
    int opcao = (std::rand()%2) + 1; //vai retornar 1 ou 2  
    switch(opcao){
        case 1: { //aq vai ser "Aprovado"
            pedidos_globais[indice_real].status = "Aprovado"; //altera no vetor geral
            pedidos_funcionario[indice_real].status = "Aprovado"; //altera no vetor do funcionario
            break;
        }
        case 2: {
            pedidos_globais[indice_real].status = "Recusado";
            pedidos_funcionario[indice_real].status = "Recusado";
            break;
        }
    }
}

//c esse novo_status estando limitado, nos vamos decidir as opcoes p bibliotecario poder selecionar(la no qt!!)
//p chamar essa confere se o status pedido la esta "Aprovado ou recusado antes!!" la na hora d chamar msm, talvez
void Gerenciador_Pedidos::atualizar_status_pedido(const int id_pedido, std::string novo_status, std::vector<SolicitacaoCompra>& pedidos_funcionario){ //teria q chamar a d cima antes! (ai vira A/R)
    if(Validador::is_id_pedido_valido(id_pedido, pedidos_funcionario) == false){
        return; //tem q indicar erro
    }
   
    int indice_real = obter_indice_pelo_id(id_pedido, pedidos_funcionario);
    
    if(pedidos_funcionario[indice_real].status != "Aprovado" && pedidos_funcionario[indice_real].status != "Recusado"){
        return;
    }

    if(pedidos_funcionario[indice_real].status == "Aprovado"){ //o novo_status poderia ser "Concluido" ou "Encerrado"(encerrado seria se desse aprovado mas n chegasse o pedido)
        pedidos_globais[indice_real].status = novo_status;
        pedidos_funcionario[indice_real].status = novo_status;
    }
    else if(pedidos_funcionario[indice_real].status == "Recusado"){
        int opcao = (std::rand()%6); //se add mais desculpas, alterar aq! 
        pedidos_globais[indice_real].motivo_pedido_recusado = get_motivos_pedido_recusado()[opcao];
        pedidos_funcionario[indice_real].motivo_pedido_recusado = get_motivos_pedido_recusado()[opcao]; //enfia a desculpa nos pedidos ;)

        pedidos_globais[indice_real].status = "Finalizado";
        pedidos_funcionario[indice_real].status = "Finalizado"; //foi recusado, e ai agr finalizaria
        // pedidos_realizados[id_pedido-1].motivo_pedido_recusado = ; //teria q chamar algo p qt ler e armazenar aq
    }
}

//aq so chama se o status do pedido for aprovado, se tiver sido recusado anteriormente ele ja foi finalizado e ate ja
//adicionou motivo de ter sido recusado nele, se chamar essa aq vai encher a desculpa d pq n concluiu e vai ta errado
void Gerenciador_Pedidos::concluir_pedido(const int id_pedido, Livro& livro, Acervo_Livro& acervo, std::vector <SolicitacaoCompra>& pedidos_funcionario){
    if(Validador::is_id_pedido_valido(id_pedido, pedidos_funcionario) == false){ //pega do ultimo pq vai ter maior id ja q vetor smp add pelo final ;)
        return; //indicar erro la pq pedido n pertence a esse funcionario
    }

    int indice_real = obter_indice_pelo_id(id_pedido, pedidos_funcionario);
    

    const Livro *livro_existe = acervo.BuscarLivro(livro.get_ISBN());
    int qtd_pedida = pedidos_funcionario[indice_real].quantidade;
      
    if(pedidos_funcionario[indice_real].status == "Concluido"){ 
        if(livro_existe != nullptr){ //se tiver, remove e add dnv no acervo p conseguir alterar a qtd total e a disponivel 
            acervo.RemoverLivroAcervo(livro.get_ISBN());
            livro.set_quantidade_exemplares_total(livro.get_quantidade_exemplares_total()+qtd_pedida);
            livro.set_quantidade_disponivel(livro.get_quantidade_disponivel()+qtd_pedida); 
            acervo.InserirLivroAcervo(livro);
            return;
            //lembrar de desabilitar botao no qt qnd isso acontecer 
        }
        else{ //n tinha ainda no acervo
            livro.set_quantidade_exemplares_total(qtd_pedida); //n teria qtd anterior(livro n existia ainda no acervo)
            livro.set_quantidade_disponivel(qtd_pedida); //n tem nenhum disp, ja q n existia, mas add e eles ficam disponiveis
            acervo.InserirLivroAcervo(livro); 
            return;
        }
    }
    else if(pedidos_funcionario[indice_real].status != "Finalizado"){ //vai ser status encerrado aq
        int opcao = (std::rand()%5); //tem q exibir dps o motivo la no qt
        pedidos_globais[indice_real].motivo_pedido_nao_concluido = get_motivos_pedido_nao_concluido()[opcao];
        pedidos_funcionario[indice_real].motivo_pedido_nao_concluido = get_motivos_pedido_nao_concluido()[opcao]; //s public na struct ent n precisa d get p acessar dps tbm
        pedidos_funcionario[indice_real].status = "Encerrado"; //deu algm problema e n vai chegar os livros la, se quiser o motivo
        //tem q lembrar d desbilitar botao p usuario mexer nesse pedido dnv qnd for encerrado, vai poder so olhar o status e tals
    }
}

const std::vector <std::string> Gerenciador_Pedidos::motivos_pedido_recusado = {
    "Pedido fora do orcamento atual da biblioteca.", "Livro muito desatualizado.", "Livro nao esta mais no catalogo da editora.", 
    "Livro esgotado e nao passivel de reposicao.", "Livro nao cumpre os requisitos didaticos atuais.", 
    "O fornecedor selecionado nao emite nota fiscal para orgaos publicos."  
};

const std::vector <std::string> Gerenciador_Pedidos::motivos_pedido_nao_concluido = {
    "Pedido extraviado. Lamentamos, parece que seu pedido nao podera ser entregue, iremos restituir inteiramente o valor do pedido.",
    "Pedido destruido/inutilizavel. Sentimos muito ao informar que seu pedido nao sera concluido, pois houve um acidente na transportadora e este se encontra inutilizavel. O valor desembolsado sera devolvido em breve.",
    "Problema logistico na transportadora. Infelizmente, devido a problemas tecnicos nao poderemos entregar seu pedido, este tera seu valor integralmente devolvido em breve.",
    "Distancia de entrega muito longa. Nao conseguimos entregar o pedido para o endereco informado, o reembolso sera enviado logo.",
    "Greve ou paralizacao da transportadora. Informamos que a transportadora entrou em greve e nao tem previsao para retomada das atividades, iremos reembolsar o valor do seu pedido em breve."

};

const std::vector<std::string>& Gerenciador_Pedidos::get_motivos_pedido_recusado(){
    return motivos_pedido_recusado;
}

const std::vector<std::string>& Gerenciador_Pedidos::get_motivos_pedido_nao_concluido(){
    return motivos_pedido_nao_concluido;
}

const std::vector <SolicitacaoCompra>& Gerenciador_Pedidos::get_pedidos_globais(){
    return pedidos_globais;
}

const int Gerenciador_Pedidos::get_id_atual(){
    return id_atual;
}