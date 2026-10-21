#include "Bibliotecario.hpp"
#include "Emprestimo.hpp"

Bibliotecario::Bibliotecario(int id, std::string login, std::string senha, std::string nome, std::string siape): 
Funcionario(id,login,senha,nome,siape){}

void Bibliotecario::concluir_pedido(const int id_pedido, Livro& livro, Acervo_Livro& acervo, std::vector<SolicitacaoCompra>& pedidos_funcionairo){
    Gerenciador_Pedidos::concluir_pedido(id_pedido, livro, acervo, pedidos_funcionairo);
}


void Bibliotecario::catalogar_livro(int id_pedido, Acervo_Livro& acervo, Livro& livro, std::vector<SolicitacaoCompra>& pedidos_funcionario){
    int indice_real = Gerenciador_Pedidos::obter_indice_pelo_id(id_pedido, Gerenciador_Pedidos::get_pedidos_globais());
    if(Gerenciador_Pedidos::get_pedidos_globais()[indice_real].status != "Concluido"){
        return; //tem q indicar falha ao tentar catalogar o livro
    }
    
    std::vector <SolicitacaoCompra> vetor_do_funcionario = Gerenciador_Pedidos::get_pedidos_globais()[indice_real].dono_pedido->get_pedidos_realizados();
    concluir_pedido(id_pedido, livro, acervo, vetor_do_funcionario); //salva as mudancas nele bonitinho, ja altera qtd do acervo e ve se existe ;)
}

const Usuario* Bibliotecario::buscar_usuario_sistema(int id, const std::string login, std::string nome, Acervo_Pessoas& acervo_pessoas){
    const Usuario* usuario_existe = acervo_pessoas.buscarUsuarioPorLogin(login);
    if(usuario_existe == nullptr){
        return nullptr;
    }
    return usuario_existe;
}

void Bibliotecario::salvar_registro_livro(const Livro& livro){
    //banco d dados, n sei mexer
} 

const int Bibliotecario::consultar_estoque_livro(Livro& livro, Acervo_Livro& acervo){
    const Livro *livro_existe = acervo.BuscarLivro(livro.get_ISBN());
    if(livro_existe == nullptr){
        return -1; //tem q indicar erro la pq livro n tava no acervo e n pode consultar o estoque
    }
    return livro.get_quantidade_exemplares_total();
}

//OBSERVACAO SOBRE O EMPRESTIMO LIVRO
//se o emprestimo n for ser instanciavel e virar algo q possa ser armazenado, ent precisa q tds metodos sejam estatic se n 
//n da p usar eles, mas ja q precisa d guardar o emprestimo, melhor criar um construtor p ele, n? ai teria q ter alguns parametros,
//talvez: dono do emprestimo la, quantidade do livro emprestada(n sei se pd ser mais d um msm livro, se puder, ent tem q ter p devolver)
//
void Bibliotecario::devolver_emprestimo(Usuario& usuario, Livro& livro, Acervo_Livro& acervo, std::string estado_livro, Emprestimo& emprestimo){
    emprestimo.devolver_emprestimo(usuario, livro); //nesse devolver emprestimo tem q arrumar a qtd de livro disponiveis, 
    //devolver o livro p acervo tbm(alias, n tem um livros disponiveis gerais, ent talvez n precise, mas se for chamar o livro 
    //danificado la no emprestimo precisa d parametro p acervo tbm p conseguir remover o livro se estiver inutilizavel)
}

//o devolver emprestimo do bibliotecario chama o de emprestimo, ai o de emprestimo tem q chamar o livro danificado, 
//la no devolver emprestimo tem q verificar se o livro esta na lista d livros do usuario ,da p pegar a lista assim: 
//std::list <Livro> lista_usuario = usuario.get_Lista_Livros_Usuario();
//colocar as opcoes de estado do livro como amassado, molhado, paginas faltando, inutilizavel, e aplicar penalidade d acordo c gravidade
void Bibliotecario::livro_danificado(Livro& livro, Usuario& usuario, Acervo_Livro& acervo, std::string estado_livro){ //passsar a lista d livros usuario tbm??
    std::string titulo = livro.get_titulo();
    std::string autor = livro.get_autor();
    std::string pais = livro.get_pais();
    std::string editora = livro.get_editora();
    int ano = livro.get_ano();
    std::string CDD = livro.get_CDD();
    std::string ISBN = livro.get_ISBN();
    int quantidade_exemplares_total = livro.get_quantidade_exemplares_total();
    double preco_total;
    if(Validador::is_texto_valido(estado_livro)){
        return; //indicar q o estado livro n esta valido
    }
    else if(Validador::validar_dados(titulo, autor, pais, editora, ano, CDD, ISBN, quantidade_exemplares_total) == false){
        return; //tem q indicar q dados livro tao invalidos
    }

    std::list <Livro> lista_usuario = usuario.get_Lista_Livros_Usuario();
    //talvez alguma forma d conferir se acervo ta valido tbm, mas n sei como ja q e instancia unica


    if(estado_livro == "Amassado"){
        usuario.set_penalizado(true); //aplica penalizacao, mas como q tira? 
        //definir qnt tempo
    }
    else if(estado_livro == "Molhado"){
        usuario.set_penalizado(true);
        //tempo maior q anterior um pouco, desleixo do krl
    }
    else if(estado_livro == "Paginas faltando"){
        usuario.set_penalizado(true);
        //um bom tempo, dependendo
    }
    else if(estado_livro == "Inutilizavel"){
        usuario.set_penalizado(true);
        const Livro* livro_existe = acervo.BuscarLivro(livro.get_ISBN());
        acervo.RemoverLivroAcervo(livro.get_ISBN());
        livro.set_quantidade_exemplares_total(livro.get_quantidade_exemplares_total()-1);
        livro.set_quantidade_disponivel(livro.get_quantidade_disponivel()-1); 
        acervo.InserirLivroAcervo(livro);
        //talvez remover o usuario da biblioteca? ja q ele fez eu remover um livro.. 
    }
}

/*
ESTOU PRECISANDO P CONSEGUIR FAZER O BIBLIOTECARIO/DUVIDAS :
-como ficaria a questao de remover a penalizacao do usuario?? talvez em emprestimo qnd usuario solicitar um emprestimo novo 
verificar a data d fim da penalizacao d uma vez? e se ja tiver passado da data, despenalizar o usuario, mas teria q ser mais no
cmc da funcao, antes daquela parte q verifica se usuario ta penalizado p permitir o emprestimo. talvez essa funcao possa retornar
o emprestimo q foi criado p esse usuario? p ficar salvo no vetor d emprestimos do usuario e talvez no vetor geral d emprestimos
tbm???. talvez p desfazer a penalizacao, em emprestimo, ja q tem aplicar penalizacao, poderia remover tbm?? ai chamaria o set 
penalizacao do usuario, trocando a penalizacao p false;?
-q o acervo de pessoas tenha um set(conjunto la q n permite copias tbm) c os Usuarios, um get p q eu possa acessar eles do 
bibliotecario tbm, e um set caso precise remover algm usuario, se este for expulso; 
-o bibliotecario so q devolve os emprestimos ne? o usuario so levaria o livro e o bibliotecario q confirma devolucao, p isso
, precisava q emprestimo tivesse construtor, p identificar o processo d emprestar msm, tendo algum atributo de dono do 
emprestimo, q poderia ser um ponteiro p usuario(p saber d qm seria o emprestimo), esses emprestimos tinham q ficar 
em usuario tbm de alguma forma, talvez c algm vetor, ai poderia alterar o status do emprestimo la(por meio da classe emprestimo, q 
receberia como parametro tbm o vetor de emprestimos do usuario, e talvez ter algm id p emprestimo p facilitar p encontrar dps?), 
e tbm teria q ter uma lista de emprestimos geral p bibliotecario conseguir conferir se o emprestimo existe antes de devolver. 
Esse vetor geral precisaria d ser static, pois seria algo da classe e n dependeria d instancia, se quiser, ao chamar o pedir 
emprestimo vc poderia acrescentar tbm ao id do emprestimo teria q ser usando id++(o id do emprestimo tbm seria estatico)
-
 */