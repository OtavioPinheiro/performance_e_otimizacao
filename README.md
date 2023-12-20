# Performance e Otimização em C++
Curso com o objetivo de apresentar algumas técnicas de otimização na linguagem C++.

## Otimizando strings
- Primeiro entendemos o quanto de memória uma string pode ocupar na heap e para isso utilizamos da função `malloc`.
- Vimos que strings são ponteiros de char `char*` e é constante `const`, pois, por via de regra, strings são imutáveis, armazenadas em lugares de somente leitura. Logo, caso não for manipular a string, use `const char*` na declaração da string em questão.
- A classe `std::string` permite a malipulação das strings. Porém, caso a string for pequena o suficiente, sendo seguro armazenar na *stack*, a classe string irá armazenar a memória necessária na *stack* e não na *heap*. Esse processo é conhecido como SSO (*Small String Optimization*).
- Vimos que uma string para ser considerada pequena depende da arquitetura do sistema e do compilador que é utilizado pela IDE. Ou seja, precisamos saber a plataforma que estamos trabalhando para saber como fazer a otimização.
- A classe `string_view` é ideal para trabalharmos com a visualização de uma `string`, podendo visualizar a *string* toda ou parte dela. Exemplo: `std::string_view nome(casal.c_str(), casal.find('&') - 1)`
- Podemos usar uma função que recebe uma `string_view` e essa função pode tanto receber `string_view` como, também, um ponteiro de caracteres `char*`, tudo isso sem alocar memória na *heap*.

## Smart pointers (Ponteiros inteligentes)
