#ifndef TDD_LEILAO_HPP
#define TDD_LEILAO_HPP
#include <vector>
#include <string>
#include <iostream>
#include "Lance.hpp"

class Leilao
{
private:
    std::vector<Lance> lances;
    std::string descricao;
public:
    Leilao(std::string descricao);
    const std::vector<Lance>& recuperaLances() const;
    void recebeLance(const Lance& lance);
};

#endif //TDD_LEILAO_HPP
