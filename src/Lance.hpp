#ifndef TDD_LANCE_HPP
#define TDD_LANCE_HPP
#include "Usuario.hpp"
#include <string>

class Lance
{
private:
    Usuario usuario;
    float valor;
public:
    Lance(Usuario usuario, float valor);
    float recuperaValor() const;
    std::string recuperaNomeUsuario() const;
};

#endif //TDD_LANCE_HPP
