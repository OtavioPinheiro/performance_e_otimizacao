#include <iostream>
#include <string>
#include <cstring>
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

int main2()
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

class String
{
private:
    char* data;
    size_t size;
public:
    String(const char* string)
    {
        std::cout << "String criada" << std::endl;
        size = strlen(string);
        data = new char[size];
        data[size] = 0;
        memcpy(data, string, size);
    }

    String(const String& outraString)
    {
        std::cout << "String copiada" << std::endl;
        size = strlen(outraString.data);
        data = new char[size];
        memcpy(data, outraString.data, size);
    }

    String(String&& outraString)
    {
        std::cout << "String movida" << std::endl;
        size = outraString.size;
        data = outraString.data;

        outraString.size = 0;
        outraString.data = nullptr;
    }

    ~String()
    {
        delete data;
    }
};

class User
{
private:
    String nome;
public:
    User(const String& string) : nome(string)
    {
    }

    User(String&& string) : nome((String&&) string)
    {
    }
};

int main()
{
    User("Nome");
    return 0;
}