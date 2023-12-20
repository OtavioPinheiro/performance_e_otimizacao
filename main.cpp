#include <iostream>
#include <string>
#include "Usuario.hpp"
#include <memory>

void* operator new(size_t bytes)
{
    std::cout << "Alocando " << bytes << " bytes" << std::endl;
    return malloc(bytes);
}

void ExibeNome(std::string_view nome)
{
    std::cout << nome << std::endl;
}

void ExibeNomeUsuario(const std::shared_ptr<Usuario>& usuario)
{
    std::cout << usuario->recuperaNome() << std::endl;
}

int main()
{
    std::cout << "------------------------------------------" << std::endl;
    std::string casal = "Fulano Siclano Beltrano da Silva & Fulana Siclana Beltrana da Silva";
    std::string_view meuNome(casal.c_str(), casal.find('&') - 1);
    std::string_view nomeEsposa(casal.c_str() + casal.find('&') + 2);

    ExibeNome(meuNome);
    ExibeNome(nomeEsposa);
    ExibeNome("Um nome qualquer sem estar na heap");

    std::shared_ptr<Usuario> usuario = std::make_shared<Usuario>("Teste");
    ExibeNomeUsuario(usuario);

    return 0;
}
