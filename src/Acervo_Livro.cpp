#include "Acervo_Livro.hpp"

Acervo_Livro::Acervo_Livro(Livro &livro)
{
    Acervo_Livro::ListaAcervoLivros.insert({livro.get_ISBN(), livro});
}

const std::map<std::string, Livro> &Acervo_Livro::getListaAcervoLivro() const
{
    return this->ListaAcervoLivros;
}
void Acervo_Livro::RemoverLivroAcervo(std::string ISBN)
{
    auto it = this->ListaAcervoLivros.find(ISBN);
    this->ListaAcervoLivros.erase(it);
}

void Acervo_Livro::InserirLivroAcervo(Livro &livro)
{
    this->ListaAcervoLivros.insert({livro.get_ISBN(), livro});
}

void Acervo_Livro::ExibirListaAcervo()
{

    // Ainda necessita ser verificado como será implementado com o qt
}

const Livro *Acervo_Livro::BuscarLivro(std::string ISBN) const
{
    auto it = this->ListaAcervoLivros.find(ISBN);
    if (it != this->ListaAcervoLivros.end())
    {
        return &(it->second);
    }
    return nullptr;
}