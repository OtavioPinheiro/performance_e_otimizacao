#ifndef TDD_USUARIO_HPP
#define TDD_USUARIO_HPP
#include <string>

class Usuario
{
private:
    std::string nome;
public:
    Usuario(std::string);
    std::string recuperaNome() const;
    std::string recuperaPrimeiroNome() const;
};

#endif //TDD_USUARIO_HPP
