#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    if(orig >= g->Gmax)
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

void inserindoDistanciasRelativas(Grafo g, int dest, int distanciasRelativas[]) {
    srand(time(NULL));
    for(int i=0; i<g->Gmax; i++) {
        distanciasRelativas[i] = rand()%100;
        printf("Distancia relativa de %d para %d: %d\n", i, dest, distanciasRelativas[i]);
    }
    distanciasRelativas[dest] = 0;
    printf("Distancia relativa destino para si mesmo: %d\n", distanciasRelativas[dest]);
}

int dfs(Grafo g, int orig, int dest) {
    if(g == NULL)
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
        printf("Explorando lista de adjacencias do %d\n", visitado);
        for(No *i = g->adj[visitado]; i != NULL; i = i->prox) {
            printf("Explorando %d\n", i->dest);
            if(i->dest == dest)
                return 1;
            else{
                if(visitados[i->dest] == 0) {
                    printf("i->dest %d\n", i->dest);
                    visitados[i->dest] = 1;
                    pilha[topo++] = i->dest;
                }
            }
        }
    }
    return 0;
}

int bfs(Grafo g, int orig, int dest) {
    if(g == NULL)
        return 0;
    int fila[g->Gmax], inicio=0, fim=0, visitados[g->Gmax];
    for(int i = 0; i < g->Gmax; i++)
        visitados[i] = 0;
    fila[fim++] = orig;
    while(inicio != fim) {
        int visitado = fila[inicio];
        inicio = (inicio+1) % g->Gmax;
        printf("Explorando lista do %d\n", visitado);
        for(No *i = g->adj[visitado]; i != NULL; i = i->prox) {
            printf("Explorando %d\n", i->dest);
            if(i->dest == dest)
                return 1;
            else{
                if(visitados[i->dest] == 0) {
                    visitados[i->dest] = 1;
                    fila[fim] = i->dest;
                    fim = (fim+1) % g->Gmax;
                }
            }
        }
    }
    return 0;
}

int gulosa(Grafo g, int orig, int dest, int distanciasRel[]) {
    if(g == NULL)
        return 0;
    if(orig == dest)
        return 1;
    int pilha[g->Gmax], topo=0, visitados[g->Gmax];
    for(int i=0; i < g->Gmax; i++) {
        visitados[i] = 0;
    }
    visitados[orig] = 1;
    pilha[topo++] = orig;
    int custo=distanciasRel[orig], flag=0;
    while(!flag) {
        int visitado = pilha[--topo];
        int menor = 100, indice = visitado;
        for(No *j = g->adj[visitado]; j != NULL; j = j->prox) {
            if(menor > distanciasRel[j->dest]) {
                menor = distanciasRel[j->dest];
                indice = j->dest;
            }
            if(j->dest == dest) {
                flag = 1;
            }
        }
        pilha[topo++] = indice;
        custo += menor;
    }
    return custo;
}

int main()
{
    Grafo g = init(5);
    printf("%d\n", inserirAdj(g, 0, 1, 6));
    printf("%d\n", inserirAdj(g, 0, 2, 6));
    printf("%d\n", inserirAdj(g, 0, 3, 6));
    printf("%d\n", inserirAdj(g, 1, 3, 4));
    printf("%d\n", inserirAdj(g, 3, 2, 3));
    printf("%d\n", inserirAdj(g, 2, 4, 7));
    printf("%d\n", inserirAdj(g, 1, 4, 5));
    printf("%d\n", inserirAdj(g, 3, 4, 5));
    //dfs(g, 0, 4);
    bfs(g, 0, 4);
    int distanciasRel[5];
    inserindoDistanciasRelativas(g, 4, distanciasRel);
    printf("Custo: %d\n", gulosa(g, 0, 4, distanciasRel));
}
