# Documentação — Algoritmos de Busca em Grafos

## 1. Visão geral do programa

O programa implementa diferentes algoritmos de busca em grafos, utilizando como exemplo a localização de caminhos entre formigueiros. Cada vértice representa um formigueiro, enquanto as arestas representam as conexões existentes entre eles.

As conexões possuem pesos, que representam o custo de deslocamento entre dois vértices.

O objetivo dos algoritmos é encontrar um caminho entre um vértice de origem e um vértice de destino, utilizando diferentes estratégias de exploração.

Os algoritmos implementados são:

- **DFS (Depth-First Search):** busca em profundidade.
- **BFS (Breadth-First Search):** busca em largura.
- **Busca Gulosa (Greedy Best-First Search):** prioriza o vértice que aparenta estar mais próximo do destino.
- **A* (A-Star):** considera o custo percorrido e a estimativa do custo restante até o destino.

## 2. Estrutura de representação do grafo

O grafo é representado por uma lista de adjacências, implementada utilizando listas encadeadas.

A estrutura `No` armazena as informações de cada conexão:

- `dest`: identifica o vértice de destino da conexão.
- `peso`: representa o custo da conexão.
- `distRelativa`: campo previsto para armazenar uma estimativa de distância, mas que não é utilizado pelos algoritmos atuais.
- `prox`: aponta para o próximo elemento da lista.

A estrutura `grafo` mantém o vetor de listas de adjacências e a quantidade máxima de vértices (`Gmax`).

### Inicialização — `init()`

A função `init()` cria a estrutura do grafo, reserva espaço para suas listas de adjacências e inicializa cada posição como vazia.

Dessa forma, cada vértice começa sem conexões, permitindo que elas sejam adicionadas posteriormente.

### Inserção de conexões — `inserirAdj()`

A função `inserirAdj()` adiciona uma conexão entre dois vértices, registrando o peso correspondente.

A implementação representa um grafo não direcionado. Portanto, quando uma conexão é inserida entre os vértices A e B, também é registrada a conexão inversa entre B e A, utilizando o mesmo peso.

A função também verifica se os vértices informados são válidos e impede a inserção de uma conexão que já exista.

## 3. Busca em profundidade — DFS

**Função:** `dfs(Grafo g, int orig, int dest)`

A busca em profundidade explora um caminho até onde for possível antes de retornar e explorar outras possibilidades.

Para realizar esse processo, o algoritmo utiliza uma **pilha**, estrutura que segue o princípio LIFO (*Last In, First Out*), ou seja, o último elemento inserido é o primeiro a ser retirado.

### Funcionamento

1. Inicializa um vetor para controlar os vértices visitados.
2. Insere o vértice de origem na pilha.
3. Retira o último vértice inserido e percorre suas conexões.
4. Verifica se algum vizinho corresponde ao destino.
5. Caso o destino não seja encontrado, adiciona à pilha os vizinhos ainda não visitados.
6. Repete o processo até encontrar o destino ou esvaziar a pilha.

O controle de visitados impede que o algoritmo explore repetidamente os mesmos vértices, evitando ciclos desnecessários.

### Característica principal

A DFS prioriza a profundidade da exploração, não necessariamente o caminho mais curto ou de menor custo.

**Exemplo simplificado:** imagine que você está explorando um labirinto. Ao encontrar uma passagem, continua seguindo por ela até não conseguir avançar. Somente depois retorna para tentar outra passagem.

**Como simplificar a explicação:** basta dizer que a DFS utiliza uma pilha e procura avançar o máximo possível por um caminho antes de explorar alternativas.

## 4. Busca em largura — BFS

**Função:** `bfs(Grafo g, int orig, int dest)`

A busca em largura explora os vértices por níveis de proximidade em relação à origem.

Diferentemente da DFS, que prioriza a profundidade, a BFS verifica primeiro os vizinhos diretamente conectados à origem e, depois, os vizinhos desses vértices.

Para isso, utiliza uma **fila**, estrutura que segue o princípio FIFO (*First In, First Out*), ou seja, o primeiro elemento inserido é o primeiro a ser retirado.

### Funcionamento

1. Inicializa um vetor para controlar os vértices visitados.
2. Insere o vértice de origem na fila.
3. Retira o primeiro vértice da fila e percorre suas conexões.
4. Verifica se algum vizinho corresponde ao destino.
5. Caso não seja o destino, adiciona à fila os vizinhos ainda não visitados.
6. Repete o processo até encontrar o destino ou esvaziar a fila.

O vetor de visitados impede que um mesmo vértice seja inserido repetidamente na fila.

### Característica principal

A BFS explora primeiro os vértices mais próximos da origem em quantidade de arestas.

Em grafos não ponderados, ela garante a descoberta de um caminho com o menor número de arestas. Entretanto, como o grafo deste programa possui pesos, a BFS não garante encontrar o caminho de menor custo.

**Exemplo simplificado:** imagine que você está procurando uma pessoa em uma rede de contatos. Primeiro verifica seus contatos diretos, depois os contatos dos seus contatos e assim sucessivamente.

**Como simplificar a explicação:** destaque que a BFS utiliza uma fila e explora os vértices por camadas, começando pelos mais próximos da origem.

## 5. Busca Gulosa — Greedy Best-First Search

**Função:** `gulosa(Grafo g, int orig, int dest, int distanciasRel[])`

A busca gulosa utiliza uma heurística para decidir qual vértice deve ser explorado primeiro.

A heurística `h(n)` representa uma estimativa da distância entre determinado vértice e o destino.

O algoritmo prioriza o vértice que apresenta a menor estimativa de distância, tentando avançar em direção ao objetivo da maneira mais promissora.

### Funcionamento

1. Inicializa os vetores de controle da fronteira (`aberto`), dos vértices explorados (`fechados`) e dos predecessores (`pai`).
2. Insere a origem na fronteira.
3. Percorre os vértices disponíveis na fronteira e seleciona aquele que possui a menor heurística.
4. Verifica se o vértice selecionado é o destino.
5. Caso não seja, marca o vértice como explorado e adiciona seus vizinhos ainda não explorados à fronteira.
6. Repete o processo até encontrar o destino ou esgotar os candidatos.

A seleção é realizada considerando somente a heurística:

**f(n) = h(n)**

Nesse algoritmo, o custo real das conexões percorridas também é armazenado para que a função possa retornar o custo do caminho encontrado. Entretanto, esse custo não interfere na escolha do próximo vértice.

### Principais estruturas utilizadas

- `aberto[]`: indica os vértices disponíveis para exploração.
- `fechados[]`: indica os vértices que já foram explorados.
- `pai[]`: armazena o predecessor de cada vértice, permitindo reconstruir o caminho.
- `custoReal[]`: armazena o custo acumulado das conexões percorridas.
- `distanciasRel[]`: contém as estimativas heurísticas de cada vértice até o destino.

### Característica principal

A busca gulosa tenta chegar ao destino rapidamente, priorizando o que parece estar mais próximo dele.

Entretanto, como não considera o custo acumulado na seleção, pode encontrar um caminho mais caro do que outras alternativas disponíveis.

**Exemplo simplificado:** imagine que você deseja chegar a uma cidade e escolhe sempre a próxima cidade que parece estar mais próxima do destino, sem considerar quanto já gastou para chegar até ela.

**Como simplificar a explicação:** a busca gulosa escolhe sempre o vértice que parece estar mais próximo do destino, utilizando apenas a heurística.

## 6. Busca A* — A-Star

**Função:** `heuristica(Grafo g, int orig, int dest, int distanciasRel[])`

A busca A* utiliza uma combinação entre o custo real já percorrido e a estimativa do custo restante até o destino.

Diferentemente da busca gulosa, que considera somente a heurística, a A* avalia também quanto já foi gasto para alcançar determinado vértice.

Sua função de avaliação é:

**f(n) = g(n) + h(n)**

Em que:

- `g(n)`: custo real acumulado desde a origem até o vértice atual.
- `h(n)`: estimativa do custo restante até o destino.
- `f(n)`: custo estimado total do caminho passando pelo vértice avaliado.

### Funcionamento

1. Inicializa os vetores de controle da fronteira, dos vértices explorados e dos predecessores.
2. Define o custo da origem como zero e adiciona a origem à fronteira.
3. Percorre os vértices disponíveis e calcula `f(n)` para cada um.
4. Seleciona o vértice com o menor valor de `f(n)`.
5. Verifica se o vértice selecionado é o destino.
6. Caso não seja, percorre seus vizinhos e calcula o novo custo real para alcançar cada um.
7. Se encontrar um caminho com custo menor para determinado vizinho, atualiza seu custo, seu predecessor e sua posição lógica na fronteira.
8. Repete o processo até encontrar o destino ou esgotar os candidatos.

### Principais estruturas utilizadas

- `aberto[]`: identifica os vértices disponíveis para exploração.
- `fechados[]`: identifica os vértices já explorados.
- `pai[]`: armazena os predecessores para reconstruir o caminho.
- `gScore[]`: armazena o menor custo real conhecido da origem até cada vértice.
- `distanciasRel[]`: fornece a estimativa heurística até o destino.

Um detalhe importante é que a implementação permite reabrir um vértice quando encontra um caminho melhor para alcançá-lo. Isso evita manter uma solução anterior que já foi superada por outra de menor custo.

### Característica principal

A A* busca equilibrar o custo já percorrido com a estimativa do que ainda falta percorrer.

Quando utiliza uma heurística admissível, ou seja, que não superestima o custo restante, e arestas com pesos não negativos, a A* pode garantir a descoberta de um caminho de custo mínimo.

**Exemplo simplificado:** imagine que você deseja chegar a uma cidade e, a cada escolha, considera tanto o dinheiro que já gastou para chegar até determinada cidade quanto o custo estimado para chegar ao destino a partir dela.

**Como simplificar a explicação:** a A* escolhe o caminho considerando o que já foi gasto e o que ainda se estima gastar até o destino.

## 7. Reconstrução do caminho — `imprimeCaminho()`

**Função:** `imprimeCaminho(int pai[], int orig, int dest, int tamanho)`

Essa função auxilia as buscas gulosa e A* na apresentação do caminho encontrado.

Durante a execução dessas buscas, o vetor `pai[]` armazena o vértice anterior de cada vértice alcançado.

Quando o destino é encontrado, a função começa a percorrer esse vetor a partir do destino, recuperando os predecessores até chegar à origem.

Como essa recuperação ocorre no sentido inverso, os vértices são armazenados temporariamente em um vetor e depois impressos na ordem correta.

**Exemplo de saída:**

`0 -> 2 -> 3 -> 7`

A função permite visualizar o caminho percorrido, em vez de apresentar somente o custo final.

**Como simplificar a explicação:** ela utiliza os predecessores armazenados durante a busca para reconstruir e imprimir o caminho da origem até o destino.

## 8. Comparação entre os algoritmos

| Algoritmo | Estrutura principal | Critério de exploração |
|---|---|---|
| DFS | Pilha | Explora profundamente um caminho antes de retornar. |
| BFS | Fila | Explora os vértices por níveis de proximidade. |
| Gulosa | Fronteira de candidatos | Seleciona a menor heurística `h(n)`. |
| A* | Fronteira de candidatos | Seleciona o menor custo estimado `g(n) + h(n)`. |

### Diferença entre a busca gulosa e a A*

A principal diferença está na maneira como cada algoritmo escolhe o próximo vértice.

A busca gulosa considera apenas a estimativa de distância até o destino. Já a A* considera tanto o custo percorrido quanto a estimativa restante.

Por isso, a busca gulosa pode escolher um caminho aparentemente promissor, mas que acaba sendo mais caro. A A*, quando utiliza uma heurística admissível e respeita as condições necessárias, consegue garantir um caminho de custo mínimo.

## 9. Considerações sobre o funcionamento do programa

Alguns detalhes ajudam a interpretar corretamente os resultados:

- DFS e BFS retornam `1` quando encontram o destino e `0` quando não o encontram ou quando recebem entradas inválidas.
- A busca gulosa e a A* retornam o custo real do caminho encontrado, ou `-1` quando não encontram uma solução válida.
- A busca gulosa não garante o menor custo.
- A A* depende da qualidade da heurística para garantir a otimalidade.
- O vetor de heurísticas deve conter estimativas coerentes com o destino escolhido.
- A BFS e a DFS não utilizam os pesos das arestas para decidir qual vértice explorar.

**Observação sobre a implementação:** as buscas DFS e BFS identificam a existência de um caminho, mas não armazenam seus predecessores para imprimir a sequência completa. Já a gulosa e a A* possuem essa funcionalidade por meio do vetor `pai[]`.

Além disso, a implementação atual utiliza uma fila circular na BFS e uma estrutura de controle da fronteira baseada em vetores nas buscas heurísticas. Esses detalhes fazem parte da implementação e não alteram o conceito principal dos algoritmos.
