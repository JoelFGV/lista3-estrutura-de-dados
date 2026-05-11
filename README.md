# Trabalho 3 - Sistema de Matchmaking para Jogos Online

## Descrição do projeto

Este projeto implementa um sistema simples de matchmaking para jogos online em C++, conforme proposto no Trabalho 3 da disciplina.

O sistema gerencia jogadores que estão aguardando para entrar em uma partida. Cada jogador possui um identificador único, um nome, um score que representa seu nível de habilidade e um timestamp que representa sua ordem de chegada na fila.

A principal finalidade do sistema é armazenar esses jogadores, ordená-los por nível de habilidade e formar grupos com jogadores de scores próximos. Para isso, o projeto utiliza algoritmos de ordenação implementados manualmente, sem o uso de funções prontas como `std::sort`.

O sistema permite:

- inserir jogadores na fila de espera;
- remover jogadores da fila pelo id;
- ordenar os jogadores por score usando insertion sort;
- ordenar os jogadores por score usando merge sort;
- formar grupos de jogadores com scores próximos;
- recuperar os jogadores atualmente na fila;
- exibir o estado atual da fila de espera;
- comparar o desempenho entre insertion sort e merge sort.

Cada jogador contém as seguintes informações:

- identificador único;
- nome;
- score;
- timestamp.

## Organização dos arquivos

O projeto está organizado nos seguintes arquivos:

- `main.cpp`
- `Matchmaking.hpp`
- `Matchmaking.cpp`
- `Player.hpp`
- `Player.cpp`

### Função de cada arquivo

- **main.cpp**: contém os testes que demonstram o funcionamento do sistema, incluindo inserção, remoção, ordenação, formação de grupos, recuperação de jogadores e teste de desempenho;
- **Player.hpp / Player.cpp**: definem e implementam a classe `Player`, responsável por representar um jogador aguardando partida;
- **Matchmaking.hpp / Matchmaking.cpp**: definem e implementam a classe `Matchmaking`, responsável por armazenar os jogadores, ordenar a fila, remover jogadores, formar grupos e imprimir o estado atual do sistema.

## Instruções de compilação

Para compilar o projeto, utilize o comando:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

## Instruções de execução

Após a compilação, execute o programa com:

```bash
./matchmaking
```

No Windows, a execução também pode ser feita com:

```bash
matchmaking.exe
```

## Organização interna dos dados

Internamente, o sistema foi implementado com estruturas manuais, sem uso de estruturas da STL como `vector`, `list`, `map`, `queue` ou `stack`.

### 1. Armazenamento dos jogadores

A classe `Matchmaking` mantém um array estático de jogadores com capacidade máxima definida pela constante:

```cpp
const int MAX_PLAYERS = 100000;
```

Além do array, a classe possui o atributo `size`, que representa a quantidade atual de jogadores armazenados na fila de espera.

De forma conceitual, a estrutura interna pode ser entendida como:

```cpp
Player players[MAX_PLAYERS];
int size;
```

Os jogadores são sempre inseridos no final do array. Por isso, após várias inserções, a fila não necessariamente está ordenada por score.

### 2. Representação dos jogadores

A classe `Player` representa cada jogador do sistema.

Cada objeto armazena:

- `id`: identificador único do jogador;
- `name`: nome do jogador;
- `score`: nível de habilidade do jogador;
- `timestamp`: ordem de chegada do jogador na fila.

A classe também possui métodos get para acessar essas informações:

- `getId()`;
- `getName()`;
- `getScore()`;
- `getTimestamp()`.

### 3. Funcionamento da inserção

No método `insert`, o sistema verifica se ainda existe espaço disponível no array.

Se houver espaço, o jogador é inserido na posição `size`, ou seja, no final da estrutura interna, e o valor de `size` é incrementado.

Caso o array já esteja cheio, o método retorna `false`.

De forma resumida:

- se houver espaço disponível, insere o jogador e retorna `true`;
- se não houver espaço disponível, não insere e retorna `false`.

### 4. Funcionamento da remoção

No método `removePlayer`, o sistema percorre o array procurando um jogador com o id informado.

Quando o jogador é encontrado, os elementos seguintes são deslocados uma posição para a esquerda, removendo o jogador da fila e mantendo o array compacto.

Se o jogador for encontrado e removido, o método retorna `true`.

Caso nenhum jogador com o id informado seja encontrado, o método retorna `false`.

### 5. Critério de ordenação

Os jogadores são ordenados seguindo dois critérios:

1. menor score primeiro;
2. em caso de empate no score, menor timestamp primeiro.

Esse critério é usado tanto no insertion sort quanto no merge sort.

Para evitar repetição de código, foi criada uma função auxiliar de comparação que verifica se um jogador deve vir antes de outro na ordenação.

Assim, se dois jogadores possuem o mesmo score, o jogador que chegou antes na fila, ou seja, com menor timestamp, aparece primeiro.

### 6. Ordenação com insertion sort

O método `sortByScoreInsertion` implementa manualmente o algoritmo insertion sort.

Esse algoritmo percorre o array a partir da segunda posição e insere cada jogador na posição correta entre os elementos anteriores já ordenados.

Durante esse processo, os jogadores maiores, de acordo com o critério de ordenação, são deslocados para a direita.

O insertion sort é simples e funciona bem para entradas pequenas ou quase ordenadas, mas possui custo quadrático no pior caso.

Sua complexidade é:

```text
O(n²)
```

### 7. Ordenação com merge sort

O método `sortByScoreMerge` implementa manualmente o algoritmo merge sort.

Esse algoritmo utiliza recursão e a estratégia de divisão e conquista. O array é dividido em duas partes menores até que cada parte tenha apenas um elemento. Em seguida, as partes são combinadas novamente de forma ordenada.

A implementação utiliza dois métodos auxiliares:

- `mergeSort`, responsável pela divisão recursiva do array;
- `merge`, responsável por combinar duas partes já ordenadas.

Durante a etapa de combinação, arrays auxiliares são criados dinamicamente para armazenar temporariamente as metades esquerda e direita.

O merge sort possui desempenho mais eficiente para grandes quantidades de jogadores, pois sua complexidade no pior caso é:

```text
O(n log n)
```

### 8. Formação de grupos

O método `formGroup` tenta formar um grupo com `groupSize` jogadores, respeitando o limite máximo de diferença de score definido por `delta`.

O método assume que os jogadores já estão ordenados por score.

Um grupo é considerado válido quando:

```text
maior_score - menor_score <= delta
```

Como os jogadores estão ordenados, o sistema só precisa analisar blocos consecutivos de jogadores dentro do array. Para cada possível grupo, basta comparar o score do primeiro jogador do bloco com o score do último jogador do bloco.

Se a diferença for menor ou igual a `delta`, o grupo é formado.

Quando um grupo válido é encontrado:

1. um novo array dinâmico é criado com os jogadores do grupo;
2. o parâmetro `n` recebe o valor de `groupSize`;
3. os jogadores do grupo são removidos da fila de espera;
4. os demais jogadores são deslocados para manter o array compacto;
5. o método retorna o array com o grupo formado.

Caso nenhum grupo válido seja encontrado:

- o método retorna `nullptr`;
- o parâmetro `n` recebe `0`;
- nenhum jogador é removido da fila.

A memória retornada por `formGroup` deve ser liberada por quem chamou a função, utilizando:

```cpp
delete[] grupo;
```

### 9. Funcionamento do método `getWaitingPlayers`

O método `getWaitingPlayers` retorna uma cópia dos jogadores atualmente armazenados na fila de espera.

Para isso, ele cria um novo array dinâmico, copia os jogadores existentes e informa a quantidade de jogadores por meio do parâmetro `n`.

Se não houver jogadores na fila, o método retorna `nullptr` e define `n = 0`.

A memória retornada por esse método também deve ser liberada por quem chamou a função, utilizando:

```cpp
delete[] lista;
```

### 10. Funcionamento da exibição da fila

O método `printWaitingPlayers` imprime o estado atual da fila de espera.

A saída apresenta a seção:

```text
Waiting Players:
```

Em seguida, cada jogador é exibido no formato:

```text
[id | nome | score | timestamp]
```

Esse método é utilizado no `main.cpp` para demonstrar visualmente o funcionamento das operações implementadas.

## Testes implementados no `main.cpp`

O arquivo `main.cpp` contém uma sequência de testes para demonstrar as principais funcionalidades do sistema.

Os testes incluem:

- inserção de jogadores na fila de espera;
- remoção de jogador pelo id;
- ordenação da fila usando insertion sort;
- ordenação da fila usando merge sort;
- ordenação com empate de score, usando o timestamp como critério de desempate;
- tentativa de formação de grupo sem sucesso;
- formação de grupo bem-sucedida;
- recuperação dos jogadores restantes com `getWaitingPlayers`;
- impressão do estado atual da fila;
- comparação de desempenho entre merge sort e insertion sort com 10000 jogadores.

Para executar os testes, basta compilar e rodar o programa normalmente:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
./matchmaking
```

A saída do programa mostra cada etapa dos testes separada por títulos, facilitando a visualização do comportamento do sistema.

## Teste de desempenho

Além dos testes funcionais, o `main.cpp` também realiza um teste de desempenho com 10000 jogadores.

Nesse teste, são criados jogadores com scores gerados aleatoriamente. Em seguida, o programa mede o tempo de execução dos dois algoritmos de ordenação usando a biblioteca `<chrono>`.

A comparação é feita entre:

- `sortByScoreMerge`;
- `sortByScoreInsertion`.

O objetivo é observar, na prática, a diferença entre os custos computacionais esperados:

- insertion sort: `O(n²)`;
- merge sort: `O(n log n)`.

Como esperado, para uma quantidade maior de jogadores, o merge sort tende a apresentar desempenho melhor que o insertion sort.

## Observações sobre gerenciamento de memória

Alguns métodos retornam arrays alocados dinamicamente, como:

- `formGroup`;
- `getWaitingPlayers`.

Por isso, sempre que esses métodos retornarem um ponteiro diferente de `nullptr`, a memória deve ser liberada no código que chamou a função.

Exemplo:

```cpp
Player* grupo = matchmaking.formGroup(3, 100, &n);

if (grupo != nullptr) {
    // uso do grupo
    delete[] grupo;
}
```

Esse cuidado evita vazamentos de memória durante a execução do programa.
