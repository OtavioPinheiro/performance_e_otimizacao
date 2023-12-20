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
- Importante evitar o uso de `new` e `delete` em C++ por conta dos problemas que podem ocorrer, como por exemplo esquecer de usar o `delete` para limpar a memória alocada.
- Sempre que possível utilizar uma estrutura já existente para gerenciar a memória na *heap*.
- Para construir um objeto, alocando um espaço de memória na *heap*, sem precisar gerenciar a memória, usamos os **_Smart Pointers_**.
- Para usar os **_Smart Pointers_** precisamos incluir a biblioteca `memory`, logo `#include <memory>`.
- Exemplo de um ponteiro único: `std::unique_ptr<Usuario> usuario = std::make_unique<Usuario>(new Usuario("Teste"));`
- Não é possível fazer e nem passar uma copia de um `unique_ptr` para outro escopo. Mas é possível utilizar o endereço de memória (a referência) para uma função, então: `void ExibeNomeUsuario(std::unique_ptr<Usuario>& usuario)` é possível. Porém o mais comum é utilizar outra estrutura, o `shared_ptr`
- `shared_ptr` (se lê _Shared Pointers_), por tanto, são ponteiros inteligentes que usamos quando queremos compartilhar o ponteiro, usa-lo em outro escopo.
- `make_shared()` é usado para criar o ponteiro e não podemos usa-lo com a palavra `new`.
- Enquanto houver referências do ponteiro `shared_ptr`, o destrutor da classe na qual o ponteiro se refere (e.g. std::shared_ptr<Usuario> usuario = std::make_shared<Usuario>("Teste"); neste caso o ponteiro se refere a Usuario) não será chamado. Só será chamado quando todas as referências que apontam para a referida instância deixar de existir, ou seja, enquanto houver cópias da instancia.
- Para saber mais sobre _Smart Pointers_: [SMART POINTERS in C++](https://www.youtube.com/watch?v=UOB7-B2MfwA)
