#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dest;
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
    No *ant;
    for(i=g->adj[orig]; i != NULL; i = i->prox) {
        if(i->dest == dest)
            return 0;
        ant = i;
    }

    No *vizinho = (No*)malloc(sizeof(No));
    if(vizinho == NULL)
        return 0;
    vizinho->dest = dest;
    vizinho->prox = NULL;
    if(g->adj[orig] == NULL)
    {
        g->adj[orig] = vizinho;
    }
    else {
        ant->prox = vizinho;
    }

    return 1;

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
                    visitados[i->dest] = 1;
                    pilha[topo++] = i->dest;
                }
            }
        }
    }
    return 0;
}

int main()
{
    Grafo g = init(5);
    printf("%d\n", inserirAdj(g, 0, 1, 0));
    printf("%d\n", inserirAdj(g, 0, 3, 0));
    printf("%d\n", g->adj[0]->prox->dest);
}
