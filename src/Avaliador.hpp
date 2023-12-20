#ifndef TDD_AVALIADOR_HPP
#define TDD_AVALIADOR_HPP
#include "Leilao.hpp"
#include <vector>

class Avaliador
{
private:
    float maiorValor = INT_MIN;
    float menorValor = INT_MAX;
    std::vector<Lance> maiores3Lances;
    static bool ordenaLances(const Lance&, const Lance&);
public:
    Avaliador();
    void avalia(Leilao leilao);
    float recuperaMaiorValor() const;
    float recuperaMenorValor() const;
    std::vector<Lance> recupera3MaioresLances() const;
};


#endif //TDD_AVALIADOR_HPP
