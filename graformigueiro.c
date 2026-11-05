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
        if(distanciasRelativas[i] == 0 && i != dest) {
            distanciasRelativas[i]++;
        }
        printf("Distancia Relativa de %d para %d: %d\n", i, dest, distanciasRelativas[i]);
    }
    distanciasRelativas[dest] = 0;
}

int dfs(Grafo g, int orig, int dest) {
    printf("=====DFS=====\n");
    printf("Busca em profundidade do formigueiro %d para o %d\n", orig, dest);
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

int gulosa(Grafo g, int orig, int dest, int distanciasRel[]) {
    printf("=====GULOSA=====\n");
    printf("Busca gulosa do formigueiro %d para o %d\n", orig, dest);
    if(g == NULL)
        return 0;
    if(orig == dest)
        return 0;
    int pilha[g->Gmax], topo=0, visitados[g->Gmax];
    for(int i=0; i < g->Gmax; i++) {
        visitados[i] = 0;
    }
    visitados[orig] = 1;
    pilha[topo++] = orig;
    int custo=distanciasRel[orig], flag=0;
    while(!flag) {
        int visitado = pilha[--topo];
        int distancias[g->Gmax], indices[g->Gmax], k=0;
        printf("Explorando lista do %d\n", visitado);
        for(No *j = g->adj[visitado]; j != NULL; j = j->prox) {
            printf("Explorando %d\n", j->dest);
            if(!visitados[j->dest]) {
                indices[k] = j->dest;
                distancias[k] = distanciasRel[j->dest];
                k++;
            }
        }
        int menor = distancias[0], index = indices[0];
        if(index == dest) {
            flag = 1;
            printf("Destino encontrado!\n");
            printf("=============================\n");
        } else{
            for(int i=1; i<k; i++) {
                if(indices[i] == dest) {
                    flag = 1;
                    printf("Destino encontrado!\n");
                    printf("=============================\n");
                } else{
                    if(menor > distancias[i] && !visitados[indices[i]]) {
                        menor = distancias[i];
                        index = indices[i];
                    }
                }
            }
        }
        printf("Menor encontrado: %d\n", menor);
        printf("Adicionando %d na pilha\n", index);
        visitados[index] = 1;
        pilha[topo++] = index;
        custo += menor;
    }
    return custo;
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
    printf("=====HEURISTICA=====\n");
    printf("Busca heurística do formigueiro %d para o %d\n", orig, dest);
    if(g == NULL)
        return 0;
    if(orig == dest)
        return 0;
    int pilha[g->Gmax], topo=0, visitados[g->Gmax];
    for(int i = 0; i < g->Gmax; i++) {
        visitados[i] = 0;
    }
    visitados[orig] = 1;
    pilha[topo++] = orig;
    int custo = 0, flag=0;
    while(!flag) {
        int visitado = pilha[--topo];
        printf("Explorando lista do %d\n", visitado);
        int distanciasPonderadas[g->Gmax], indices[g->Gmax], k=0, pesos[g->Gmax];
        for(No *j = g->adj[visitado]; j != NULL; j = j->prox) {
            printf("Explorando %d\n", j->dest);
            if(!visitados[j->dest]) {
                distanciasPonderadas[k] = distanciasRel[j->dest] + j->peso;
                indices[k] = j->dest;
                pesos[k] = j->peso;
                k++;
            }
        }
        
        int menor = distanciasPonderadas[0], index=indices[0], peso=pesos[0];
        if(index == dest) {
            flag = 1;
        } else{
            printf("Buscando o menor....\n");
            for(int i=1; i<k && !flag; i++) {
                if(indices[i] == dest) {
                    flag = 1;
                    peso = pesos[i];
                    printf("Destino encontrado!\n");
                    printf("=============================\n");
                } else{
                    if(menor > distanciasPonderadas[i]) {
                        menor = distanciasPonderadas[i];
                        peso = pesos[i];
                        index = indices[i];
                    }
                }
            }
        }
        printf("Menor encontrado: %d\n", menor);
        printf("Peso a ser adicionado ao custo: %d\n", peso);
        printf("Adicionando %d na pilha\n", index);
        visitados[index] = 1;
        pilha[topo++] = index;
        custo += peso;
    }
    return custo;
}

void gerarOrigDest(Grafo g, int *orig, int *dest) {
    srand(time(NULL));
    *orig = rand()%g->Gmax;
    *dest = rand()%g->Gmax;
}

void gerarArestas();

int main()
{
    Grafo g = init(15);
    int origem = 0, destino = 7;
    //gerarOrigDest(g, &origem, &destino);
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


    //dfs(g, 0, 4);
    bfs(g, origem, destino);
    int distanciasRel[15] = {41, 51, 29, 16, 40, 56, 54, 0, 22, 34, 62, 93, 64, 49, 81};
    inserindoDistanciasRelativas(g, destino, distanciasRel);
    printf("Custo guloso: %d\n", gulosa(g, origem, destino, distanciasRel));
    printf("Custo heuristica: %d\n", heuristica(g, origem, destino, distanciasRel));
}
