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

## Copy Constructor
- _Copy Constructor_ ou Construtor de cópia é quando criamos um objeto a partir de outro. E.g. `Objeto(const Objeto&);`. Na implementação devemos copiar todos os valores de um objeto para outro, e.g. `Objeto::Objeto(const Objeto& objetoCopia) : valor1(objetoCopia.valor1), valor2(objetoCopia.valor2), ... {...}`
- Para impedir a cópia do construtor devemos fazer: `Objeto(const Objeto&) = delete`.
- Por padrão o Copy Constructor é definido da seguinte maneira `Objeto(const Objeto&) = default`.
- O cenário ideal é nunca precisar criar diretamente o _Copy Constructor_. Pela _Rule of zero_:
  - Zero _Copy Constructor_
  - Zero _Move Construtor_
  - Nenhum operador de atribuição
- O ideal é ter nossas propriedades contendo valores que já são gerenciados, que são autogerenciados e que não precisamos fazer a gestão.
- Os cenários onde precisaremos fazer a reescrita de algumas funções e classes é quando buscamos atingir uma maior performance (desempenho). O caso mais famoso a ser citado é da empresa de jogo EA que reecreveu classes como `vector`, `map`, `array`.
- Precisamos de _Copy Constructor_ para cenários de baixo nível, quando estamos manipulando ponteiros diretamente e alocando memória. Porém, nesses cenários é possível que haja o _undefined behavior_ (comportamento indefinido ou inesperado). Normalmente isso pode ocorrer quando temos duas instâncias de um objeto apontando para o mesmo endereço de memória, quando o operador `delete` for chamado para a primeira instância, o endereço de memória será liberado, porém, ao chamar novamente o operador `delete` para a segunda instância, o operador irá tentar liberar o mesmo endereço de memória que já foi liberado anteriormente pela primeira instância, isso irá ocasionar o _undefined behavior_, que pode ser uma invasão de memória, ou pode ocasionar um erro.
- Para saber mais [Copying and Copy Constructors in C++](https://www.youtube.com/watch?v=BvR1Pgzzr38)

## Tipos de valores
**_L-values_**: É tudo aquilo que conseguimos atribuir um endereço de memória. Pode-se entender também que L-values é tudo aquilo que é possível atribuir valores, ou, ainda, aquilo que está, imediatamente, à esquerda do simbolo de atribuição `=`, portanto, toda variável é um _L-value_.

**Exemplo:**
```c++
int& RecuperaNumero()
{
    static int valor = 10;
    return valor;
}

int main()
{
    RecuperaNumero() = 5;
    
    return 0;
}
```

**_R-values_**: De forma similar, _R-values_ é tudo aquilo que não podemos atribuir um endereço de memória. Normalmente os R-values ficam imediatamente à direita do sinal de atribuição `=`, também são conhecidos como valores temporários.

**Exemplo 01**:
```c++
int main()
{
    int valor = 10;
    
    return 0;
}
```

No exemplo anterior `valor` é um _L-value_ e `10` é um _R-value_.

**Exemplo 02-01**:
```c++
void ExibeValor(Valor& valor)
{
    std::cout << valor.retornaValor() << std::endl;
}
    
int main()
{
    ExibeValor(Valor(10));
}
```

**Exemplo 02-02**:
```c++
void ExibeValor(const Valor& valor)
{
    std::cout << valor.retornaValor() << std::endl;
}
    
int main()
{
    ExibeValor(Valor(10));
}
```

**Exemplo 02-03**:
```c++
void ExibeValor(const Valor&& valor)
{
    std::cout << valor.retornaValor() << std::endl;
}
    
int main()
{
    ExibeValor(Valor(10));
}
```

No **Exemplo 02-01** temos uma função que recebe por parâmetro uma referência de `Valor` para poder exibir o valor armazenado. Ao chamar a função e passar `Valor(10)` como parâmetro, nesse caso, teremos um problema, pois a função esperava um _L-value_ e foi passado um _R-value_, ou seja, um valor temporário. Mas o **Exemplo 02-02** mostra que é possível fazer com <u>a função aceite o valor temporário se marcarmos o parâmetro como</u> `const`, desta forma estamos especificando que o valor não sofrerá nenhuma alteração. Outra forma de passar um valor temporário para uma função é definir que a função receberá um valor temporário e, para isso, usamos o simbolo `&&`, assim como mostrado no **Exemplo 02-03**. 
A vantagem de se utilizar os _R-values_ é que não é necessário fazer uma cópia dos dados, podemos simplesmente movê-los.