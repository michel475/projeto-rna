#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 999999999

typedef struct no {
    int dest;
    int peso;
    int distRelativa;
    struct no *prox;
}No;

typedef struct grafo {
    No **adj;
    int Gmax;
} *Grafo;

Grafo init(int v) {
    Grafo g = (Grafo)malloc(sizeof(struct grafo));
    if(g != NULL) {
        g->adj = (No**)malloc(v * sizeof(struct no));
        g->Gmax = v;
        for(int i=0; i<v; i++) {
            g->adj[i] = (No*)malloc(sizeof(No));
            g->adj[i] = NULL;
        }
    }
    return g;
}

int inserirAdj(Grafo g, int orig, int dest, int peso) {
    if(g == NULL)
        return 0;
    if(orig >= g->Gmax || orig < 0 || dest >= g->Gmax || dest < 0)
        return 0;
    No *i = g->adj[orig];
    No *j = g->adj[dest];
    No *anti;
    No *antj;
    for(;i != NULL; i = i->prox) {
        if(i->dest == dest)
            return 0;
        anti = i;
    }

    for(; j != NULL; j = j->prox) {
        if(j->dest == orig)
            return 0;
        antj = j;
    }

    No *vizinhoOrig = (No*)malloc(sizeof(No));
    No *vizinhoDest = (No*)malloc(sizeof(No));

    if(vizinhoOrig == NULL || vizinhoDest == NULL)
        return 0;
    vizinhoOrig->dest = dest;
    vizinhoOrig->peso = peso;
    vizinhoOrig->prox = NULL;

    vizinhoDest->dest = orig;
    vizinhoDest->peso = peso;
    vizinhoDest->prox = NULL;
    if(g->adj[orig] == NULL)
    {
        g->adj[orig] = vizinhoOrig;
    }
    else {
        anti->prox = vizinhoOrig;
    }
    
    if(g->adj[dest] == NULL)
    {
        g->adj[dest] = vizinhoDest;
    }
    else{
        antj->prox = vizinhoDest;
    }

    return 1;

}

int dfs(Grafo g, int orig, int dest) {
    printf("=====DFS=====\n");
    printf("Busca em profundidade do formigueiro %d para o %d\n", orig, dest);
    if(g == NULL)
        return 0;
    if(orig >= g->Gmax || orig < 0 || dest >= g->Gmax || dest < 0)
        return 0;
    int pilha[g->Gmax], topo=0, visitados[g->Gmax];
    for(int i=0; i < g->Gmax; i++) {
        visitados[i] = 0;
    }
    visitados[orig] = 1;
    pilha[topo] = orig;
    topo++;
    while(topo > 0) {
        int visitado = pilha[--topo];
        printf("Explorando lista do %d\n", visitado);
        for(No *i = g->adj[visitado]; i != NULL; i = i->prox) {
            printf("Explorando %d\n", i->dest);
            if(i->dest == dest){
                printf("Destino encontrado!\n");
                printf("=============================\n");
                return 1;
            }
            else{
                if(visitados[i->dest] == 0) {
                    printf("Adicionando %d na pilha\n", i->dest);
                    visitados[i->dest] = 1;
                    pilha[topo++] = i->dest;
                }
            }
        }
        printf("Pilha de proximos formigueiros: "); //imprime a pilha que contém os próximos formigueiros a serem buscados
        for(int j=topo-1;j>=0;j--)
        	printf("%d ", pilha[j]);
        printf("\n\n");
		system("pause");
		system("cls");
    }
    return 0;
}

int bfs(Grafo g, int orig, int dest) {
    printf("=====BFS=====\n");
    printf("Busca em largura do formigueiro %d para o %d\n", orig, dest);
    if(g == NULL)
        return 0;
    if(orig >= g->Gmax || orig < 0 || dest >= g->Gmax || dest < 0)
        return 0;
    int fila[g->Gmax], inicio=0, fim=0, visitados[g->Gmax];
    for(int i = 0; i < g->Gmax; i++)
        visitados[i] = 0;
    visitados[orig] = 1; //adiciona a origem na lista de visitados
    fila[fim++] = orig;
    while(inicio != fim) {
        int visitado = fila[inicio];
        inicio = (inicio+1) % g->Gmax;
        printf("Explorando lista do %d\n", visitado);
        for(No *i = g->adj[visitado]; i != NULL; i = i->prox) {
            printf("Explorando %d\n", i->dest);
            if(i->dest == dest){
                printf("Destino encontrado!\n");
                printf("=============================\n");
                return 1;
            }
            else{
                if(visitados[i->dest] == 0) {
                    visitados[i->dest] = 1;
                    printf("Adicionando %d na fila\n", i->dest);
                    fila[fim] = i->dest;
                    fim = (fim+1) % g->Gmax;
                }
            }
        }
        printf("Fila de proximos formigueiros: "); //imprime a fila dos próximos formigueiros a serem buscados
        for(int j=inicio;j<fim;j++)
        	printf("%d ", fila[j]);
        printf("\n\n");
		system("pause");
		system("cls");
    }
    return 0;
}


void imprimeCaminho(int pai[], int orig, int dest, int tamanho) {
    int caminho[tamanho];
    int qtd = 0;
    int atual = dest;
    while (atual != -1 && qtd < tamanho) {
        caminho[qtd++] = atual;
        if (atual == orig)
            break;
        atual = pai[atual];
    }
    if (qtd == 0 || caminho[qtd - 1] != orig) {
        printf("Caminho nao encontrado.\n");
        return;
    }
    printf("Caminho encontrado: ");
    for (int i = qtd - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0)
            printf(" -> ");
    }
    printf("\n");
}


int gulosa(Grafo g, int orig, int dest, int distanciasRel[]) {
    printf("===== BUSCA GULOSA =====\n");
    printf("Busca gulosa do formigueiro %d para o %d\n", orig, dest);

    if (g == NULL || distanciasRel == NULL)
        return -1;

    if (orig < 0 || dest < 0 || orig >= g->Gmax || dest >= g->Gmax)
        return -1;

    if (orig == dest)
        return 0;

    int aberto[g->Gmax];
    int fechados[g->Gmax];
    int pai[g->Gmax];
    long long custoReal[g->Gmax];

    for (int i = 0; i < g->Gmax; i++) {
        aberto[i] = 0;
        fechados[i] = 0;
        pai[i] = -1;
        custoReal[i] = MAX;
    }

    aberto[orig] = 1;
    custoReal[orig] = 0;

    while (1) {
        int atual = -1;
        int menorHeuristica = INT_MAX;

        // Seleciona o vértice aberto com a menor heurística.
        for (int i = 0; i < g->Gmax; i++) {
            if (aberto[i] && !fechados[i]) {
                if (distanciasRel[i] < menorHeuristica) {
                    menorHeuristica = distanciasRel[i];
                    atual = i;
                }
            }
        }

        // Não existem mais vértices para explorar.
        if (atual == -1) {
            printf("Destino nao encontrado.\n");
            return -1;
        }

        printf("Explorando vertice %d (h = %d)\n",
               atual, distanciasRel[atual]);

        // O destino é encontrado quando é selecionado da fronteira.
        if (atual == dest) {
            printf("Destino encontrado!\n");
            imprimeCaminho(pai, orig, dest, g->Gmax);

            if (custoReal[dest] > INT_MAX)
                return -1;

            return (int)custoReal[dest];
        }

        aberto[atual] = 0;
        fechados[atual] = 1;

        // Adiciona os vizinhos à fronteira.
        for (No *j = g->adj[atual]; j != NULL; j = j->prox) {
            int vizinho = j->dest;

            if (vizinho < 0 || vizinho >= g->Gmax)
                continue;

            if (fechados[vizinho])
                continue;

            if (j->peso < 0)
                return -1;

            long long novoCusto = custoReal[atual] + j->peso;

            if (novoCusto < custoReal[vizinho]) {
                custoReal[vizinho] = novoCusto;
                pai[vizinho] = atual;
                aberto[vizinho] = 1;

                printf("Adicionando %d na fronteira (h = %d)\n",
                       vizinho, distanciasRel[vizinho]);
            }
        }

        printf("\n");
    }
}

void imprimePesos(Grafo g) {
    printf("=====IMPRIME-PESOS=====\n");
    if(g == NULL)
        return;
    for(int j=0; j<g->Gmax; j++) {
        printf("Lista de adjacencias do %d\n", j);
        for(No *i = g->adj[j]; i != NULL; i = i->prox) {
            printf("Peso da aresta: %d\n", i->peso);
        }
    }
    printf("FIM\n");
}

int heuristica(Grafo g, int orig, int dest, int distanciasRel[]) {
    printf("===== BUSCA A* =====\n");
    printf("Busca heuristica do formigueiro %d para o %d\n", orig, dest);
    if (g == NULL || distanciasRel == NULL)
        return -1;
    if (orig < 0 || dest < 0 || orig >= g->Gmax || dest >= g->Gmax)
        return -1;
    if (orig == dest)
        return 0;
    int aberto[g->Gmax];
    int fechados[g->Gmax];
    int pai[g->Gmax];
    long long gScore[g->Gmax];
    for (int i = 0; i < g->Gmax; i++) {
        aberto[i] = 0;
        fechados[i] = 0;
        pai[i] = -1;
        gScore[i] = MAX;
    }
    // Custo real da origem até ela mesma.
    gScore[orig] = 0;
    aberto[orig] = 1;
    while (1) {
        int atual = -1;
        long long menorF = MAX;
        // Escolhe o vértice com menor custo
        for (int i = 0; i < g->Gmax; i++) {
            if (aberto[i] && !fechados[i]) {
                long long f = gScore[i] + distanciasRel[i];
                if (f < menorF) {
                    menorF = f;
                    atual = i;
                }
            }
        }

        // Não existem mais vértices para explorar.
        if (atual == -1) {
            printf("Destino nao encontrado.\n");
            return -1;
        }

        printf("Explorando vertice %d\n", atual);
        printf("g(n) = %lld | h(n) = %d | f(n) = %lld\n",
               gScore[atual],
               distanciasRel[atual],
               menorF);

        // O destino é encontrado quando é selecionado da fronteira.
        if (atual == dest) {
            printf("Destino encontrado!\n");
            imprimeCaminho(pai, orig, dest, g->Gmax);

            if (gScore[dest] > INT_MAX)
                return -1;

            return (int)gScore[dest];
        }

        aberto[atual] = 0;
        fechados[atual] = 1;

        // Avalia os vizinhos do vértice atual.
        for (No *j = g->adj[atual]; j != NULL; j = j->prox) {
            int vizinho = j->dest;

            if (vizinho < 0 || vizinho >= g->Gmax)
                continue;

            if (j->peso < 0)
                return -1;

            // g(novo) = g(atual) + custo da aresta.
            long long novoG = gScore[atual] + j->peso;

            // Atualiza somente quando encontra um caminho melhor.
            if (novoG < gScore[vizinho]) {
                gScore[vizinho] = novoG;
                pai[vizinho] = atual;

                // Reabre o vértice se um caminho melhor for encontrado.
                fechados[vizinho] = 0;
                aberto[vizinho] = 1;

                long long novoF = novoG + distanciasRel[vizinho];

                printf("Atualizando vertice %d:\n", vizinho);
                printf("g(n) = %lld | h(n) = %d | f(n) = %lld\n",
                       novoG,
                       distanciasRel[vizinho],
                       novoF);
            }
        }

        printf("\n");
    }
}

void gerarOrigDest(Grafo g, int *orig, int *dest) {
    srand(time(NULL));
    do{
        *orig = rand()%g->Gmax;
        *dest = rand()%g->Gmax;
    }while(*orig == *dest);
}

int main()
{
    Grafo g = init(15);
    int origem, destino;
    gerarOrigDest(g, &origem, &destino);
    printf("Origem: %d\nDestino: %d\n", origem, destino);
    inserirAdj(g, 0, 1, 10);
    inserirAdj(g, 0, 2, 12);
    inserirAdj(g, 0, 5, 15);
    inserirAdj(g, 0, 9, 15);
    inserirAdj(g, 1, 4, 11);
    inserirAdj(g, 1, 6, 14);
    inserirAdj(g, 2, 3, 13);
    inserirAdj(g, 2, 13, 20);
    inserirAdj(g, 3, 7, 16);
    inserirAdj(g, 3, 9, 18);
    inserirAdj(g, 4, 8, 18);
    inserirAdj(g, 5, 6, 17);
    inserirAdj(g, 5, 14, 25);
    inserirAdj(g, 6, 9, 20);
    inserirAdj(g, 7, 8, 22);
    inserirAdj(g, 8, 9, 25);
    inserirAdj(g, 9, 10, 28);
    inserirAdj(g, 9, 12, 30);
    inserirAdj(g, 9, 13, 32);
    inserirAdj(g, 10, 11, 35);
    inserirAdj(g, 11, 5, 37);
    inserirAdj(g, 11, 14, 38);
    inserirAdj(g, 12, 14, 39);
    inserirAdj(g, 13, 14, 41);

    bfs(g, origem, destino);
    int distanciasRel[15] = {41, 51, 29, 16, 40, 56, 54, 33, 22, 34, 62, 93, 64, 49, 81};
    distanciasRel[destino] = 0;
    printf("Custo guloso: %d\n", gulosa(g, origem, destino, distanciasRel));
    printf("Custo heuristica: %d\n", heuristica(g, origem, destino, distanciasRel));
}
