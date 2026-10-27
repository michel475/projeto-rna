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
    No *i;
    No *j;
    No *anti;
    No *antj;
    for(i=g->adj[orig]; i != NULL; i = i->prox) {
        if(i->dest == dest)
            return 0;
        anti = i;
    }

    for(j=g->adj[dest]; j != NULL; j = j->prox) {
        if(j->dest == orig)
            return 0;
        antj = i;
    }

    No *vizinhoOrig = (No*)malloc(sizeof(No));
    No *vizinhoDest = (No*)malloc(sizeof(No));

    if(vizinhoOrig == NULL || vizinhoDest)
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

void inserindoDistanciasRelativas(Grafo g, int dest) {
    srand(time(NULL));
    int vertices[g->Gmax];
    for(int i=0; i<g->Gmax; i++) {
        vertices[i] = rand()%100;
        printf("%d\n", vertices[i]);
    }
    
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

/*int gulosa(Grafo g, int orig, int dest) {
    if(g == NULL)
        return 0;
    
}*/

int main()
{
    Grafo g = init(5);
    printf("%d\n", inserirAdj(g, 0, 1, 6));
    printf("%d\n", inserirAdj(g, 0, 3, 4));
    printf("%d\n", inserirAdj(g, 3, 4, 3));
    printf("%d\n", inserirAdj(g, 4, 1, 7));
    printf("%d\n", inserirAdj(g, 1, 2, 5));
    //dfs(g, 0, 4);
    bfs(g, 0, 5);
    inserindoDistanciasRelativas(g, 3);
}
