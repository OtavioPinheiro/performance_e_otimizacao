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

## _Move semantics_ e _Move Constructor_
### Move semantics:
É uma característica introduzida no C++11 que permite a transferência eficiente de recursos de um objeto para outro, geralmente por meio de um movimento de "roubo" dos recursos, em vez de copiá-los. Isso é particularmente útil quando um objeto temporário é criado durante uma expressão, e em vez de copiar os dados, podemos simplesmente movê-los.

### Move Constructor:
É um construtor especial que permite a transferência eficiente de recursos entre objetos. Ele é invocado automaticamente quando um objeto é criado a partir de outro objeto.

**Exemplo:**
```c++
#include <iostream>
#include <vector>

class Exemplo {
public:
    // Move constructor
    Exemplo(Exemplo&& other) noexcept {
        std::cout << "Move Constuctor chamado!" << std::endl;
        // Realiza a transferência eficiente de recursos, por exemplo, move um vetor
        dados = std::move(other.dados);
    }

    // Outros construtores e métodos da classe...

private:
    std::vector<int> dados;
};

int main() {
    Exemplo obj1;
    // ...

    // Chama o move constructor ao criar obj2 a partir de obj1 usando std::move
    Exemplo obj2 = std::move(obj1);

    return 0;
}
```

Em outras palavras, _**Move semantics**_ é um conceito geral que se refere à capacidade de mover objetos de uma variável para outra sem copiar seus dados. _**Move constructor**_ é um tipo específico de construtor que é usado para mover objetos.

_**Move semantics**_ pode ser implementado usando uma variedade de métodos, incluindo _**move constructors**_, _**move assignment operators**_ e _**rvalue references**_. _**Move constructors**_ são uma maneira eficiente e segura de implementar _**move semantics**_.

### R-Values references:
É um tipo de referência que só pode ser usado para receber um valor temporário.

**Exemplo:**
```c++
int x = 10;

int&& r = x; // r é um rvalue reference para x
```

No código acima, a variável `x` é um _**L-Value**_, o que significa que ela pode ser usada para referenciar uma posição na memória. A variável `r` é um _**R-Value**_, o que significa que ela só pode ser usada para receber um valor temporário.

### Move assignment operators:
Um _**Move assignment operator**_ é um operador de atribuição que move o conteúdo de um objeto para outro objeto durante uma operação de atribuição, em vez de copiar o conteúdo. Ele é semelhante ao operador de atribuição tradicional, mas tem um operando adicional que é um _R-Value reference_.

**Exemplo:**
```c++
#include <iostream>
#include <vector>

class Exemplo {
public:
    // Construtor padrão
    Exemplo() : dados(nullptr) {}

    // Move constructor
    Exemplo(Exemplo&& other) noexcept {
        std::cout << "Construtor de Movimento chamado!" << std::endl;
        dados = std::move(other.dados);
    }

    // Move assignment operator
    Exemplo& operator=(Exemplo&& other) noexcept {
        std::cout << "Operador de Atribuição de Movimento chamado!" << std::endl;
        if (this != &other) {
            // Libera os recursos do objeto atual, se necessário
            dados.clear();
            // Atribui os recursos de 'other' ao objeto atual
            dados = std::move(other.dados);
        }
        return *this;
    }

    // Outros construtores e métodos da classe...

private:
    std::vector<int> dados;
};

int main() {
    // Criando objetos
    Exemplo obj1;
    Exemplo obj2;

    // Atribuindo um objeto ao outro usando o operador de atribuição de movimento
    obj2 = std::move(obj1);

    return 0;
}
```

Neste exemplo, o _**Move assignment operator**_ (operator=) é acionado quando `obj2` é atribuído a partir de `obj1` usando `std::move(obj1)`. O operador de atribuição de movimento (_Move assignment operator_) efetua a transferência eficiente de recursos, movendo o vetor de `obj1` para `obj2`. Esse operador é usado quando queremos transferir os recursos de um objeto temporário (ou explicitamente usando std::move) para outro objeto, evitando cópias desnecessárias.

Nesses cenários, a função `std::move` pode acabar movendo algo que não deveria ser movido. Para identificar se algo foi passado como _r-value_ ou _l-value_, podemos usar outra função no lugar de `std::move`. Essa função é a `std::forward`.

## std::move() e std::foward()
`std::forward` e `std::move` são duas funções-padrão do C++ que são usadas para controlar o tipo de referência que é passado para uma função, ambos utilizados no contexto de _**Move semantics**_ em C++.

A principal diferença entre `std::move` e `std::forward` é que `std::move` sempre força a passagem de um _R-Value reference_, enquanto `std::forward` mantém o tipo de referência original. Ou seja, utilize o `std::move` quando você quer explicitamente transformar um objeto em um _R-Value_ para permitir a movimentação eficiente de recursos. Use `std::forward` em _template functions_ (funções de modelo), geralmente, quando você deseja preservar a categoria de valor do argumento ao encaminhá-lo de maneira genérica.

**Exemplo de** `std::move()`:
```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2 = {7, 7, 7, 7, 7};

    std::cout << "Antes do std::move:\n";
    std::cout << "vec1: ";
    for (int i : vec1) std::cout << i << ' ';
    std::cout << "\nvec2: ";
    for (int i : vec2) std::cout << i << ' ';

    // Usa std::move para mover os elementos de vec1 para vec2
    std::move(vec1.begin(), vec1.begin() + 4, vec2.begin() + 1);

    std::cout << "\n\nDepois do std::move:\n";
    std::cout << "vec1: ";
    for (int i : vec1) std::cout << i << ' ';
    std::cout << "\nvec2: ";
    for (int i : vec2) std::cout << i << ' ';

    return 0;
}
```

Neste código, usamos `std::move` para mover os primeiros quatro elementos de `vec1` para `vec2`, começando na segunda posição de `vec2`. Depois de executar `std::move`, os elementos movidos não são mais acessíveis através de `vec1`, mas agora estão em `vec2`.

**Exemplo de** `std::forward()`:
```c++
#include <iostream>

// Função interna que aceita lvalue e rvalue
void inner(int& x) {
    std::cout << "lvalue\n";
}
void inner(int&& x) {
    std::cout << "rvalue\n";
}

// Função externa que encaminha os argumentos para a função interna
template <typename T>
void outer(T&& t) {
    inner(std::forward<T>(t));
}

int main() {
    int x = 10;

    outer(x);  // x é um lvalue
    outer(10); // 10 é um rvalue
}
```

Neste código, a função `outer` aceita tanto _L-Values_ quanto _R-Values_. Dentro de `outer`, usamos `std::forward` para encaminhar o argumento para a função `inner` mantendo o tipo do valor original. Assim, se você passar um _L-Value_ para `outer`, o `std::forward` garantirá que o _L-Value_ seja passado para `inner`. Da mesma forma, se você passar um _R-Value_ para `outer`, o `std::forward` garantirá que o _R-Value_ seja passado para `inner`.

**Para saber mais:**
- [Forwarding references](https://en.cppreference.com/w/cpp/language/reference#Forwarding_references)
- [std::forward](https://en.cppreference.com/w/cpp/utility/forward)

## Rules of 0, 3 and 5
Existem algumas regras quando falamos de gestão de recursos em C++. Regra de 0, 3 e 5.

### Regra do 0 (_Rule of 0_)
A "_Rule of 0_" sugere que, sempre que possível, evite implementar manualmente o **_copy constructor_**, **_copy assignment_**, **_move constructor_**, **_move assignment_** em uma classe. <u>Deixe que o compilador gere automaticamente esses membros especiais</u>, **a menos que você precise de um comportamento específico**.

## Regra do 3 (_Rule of 3_)
A "_Rule of 3_" diz que, se você precisar implementar um dos três membros especiais (_copy constructor_, _copy assignment_ e destrutor), provavelmente precisará implementar todos os três para garantir um comportamento consistente.

## Regra do 5 (_Rule of 5_)
A "_Rule of 5_" estende a "_Rule of 3_" para incluir os dois novos membros especiais introduzidos no C++11: _**move constructor**_ e _**move assignment**_. Se você precisar implementar um desses cinco membros especiais, provavelmente precisará implementar todos os cinco para garantir um comportamento consistente.

**Referências**
- [The rule of three/five/zero](https://en.cppreference.com/w/cpp/language/rule_of_three)
- [Back to Basics: Move Semantics (part 1 of 2) - Klaus Iglberger - CppCon 2019](https://www.youtube.com/watch?v=St0MNEU5b0o)
- [Back to Basics: Move Semantics (part 2 of 2) - Klaus Iglberger - CppCon 2019](https://www.youtube.com/watch?v=pIzaZbKUw2s)
- [Back to Basics: RAII and the Rule of Zero - Arthur O'Dwyer - CppCon 2019](https://www.youtube.com/watch?v=7Qgd9B1KuMQ)