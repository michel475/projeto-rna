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
        printf("Distancia relativa de %d para %d: %d\n", i, dest, distanciasRelativas[i]);
    }
    distanciasRelativas[dest] = 0;
    printf("Distancia relativa destino para si mesmo: %d\n", distanciasRelativas[dest]);
}

int dfs(Grafo g, int orig, int dest) {
    printf("=====DFS=====\n");
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
    printf("=====BFS=====\n");
    printf("Busca em largura do %d para o %d\n", orig, dest);
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
            if(i->dest == dest){
                printf("Destino encontrado!\n");
                printf("=============================\n");
                return 1;
            }
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
    printf("=====GULOSA=====\n");
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
        int distancias[g->Gmax], indices[g->Gmax], k=0;
        for(No *j = g->adj[visitado]; j != NULL; j = j->prox) {
            if(!visitados[j->dest]) {
                indices[k] = j->dest;
                distancias[k] = distanciasRel[j->dest];
                k++;
            }
            printf("Dist %d : %d\n", j->dest, distanciasRel[j->dest]);
        }
        int menor = distancias[0], index = 0;
        for(int i=0; i<k; i++) {
            if(indices[i] == dest) {
                flag = 1;
            } else{
                if(menor > distancias[i] && !visitados[indices[i]]) {
                    menor = distancias[i];
                    index = i;
                }
            }
        }
        if(!flag) {
            printf("Escolhido: %d\n", indices[index]);
            printf("Custo no escolhido: %d\n", menor);
            pilha[topo++] = indices[index];
            visitados[indices[index]] = 1;
            custo += menor;
        }
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
    if(g == NULL)
        return 0;
    if(orig == dest)
        return 1;
    int pilha[g->Gmax], topo=0, visitados[g->Gmax];
    for(int i = 0; i < g->Gmax; i++) {
        visitados[i] = 0;
    }
    visitados[orig] = 1;
    pilha[topo++] = orig;
    int custo = 0, flag=0, ant, custoAnt;
    while(!flag) {
        int visitado = pilha[--topo];
        printf("Visitando lista de adjacencias do : %d\n", visitado);
        int distanciasPonderadas[g->Gmax], indices[g->Gmax], k=0, pesos[g->Gmax];
        int elegiveis = 0;
        for(No *j = g->adj[visitado]; j != NULL; j = j->prox) {
            if(!visitados[j->dest]) {
                distanciasPonderadas[k] = distanciasRel[j->dest] + j->peso;
                indices[k] = j->dest;
                pesos[k] = j->peso;
                k++;
                printf("%d adicionado ao vetor distanciasPonderadas\n", j->dest);
                printf("Peso: %d\n", j->peso);
                elegiveis = 1;
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
        visitados[index] = 1;
        if(!elegiveis) {
            pilha[topo++] = ant;
            custo -= custoAnt;
            continue;
        }
        ant = visitado;
        custoAnt = peso;
        pilha[topo++] = index;
        custo += peso;
    }
    return custo;
}

/*int gerarAdjacencias(Grafo g, int orig, int dest) {
    if(g == NULL)
        return 0;
    if(orig == dest)
        return 1;
    if(orig >= g->Gmax || dest >= g->Gmax)
        return 0;
    for(int i=0; i<g->Gmax; i++) {
        
    }
}*/

void gerarOrigDest(Grafo g, int *orig, int *dest) {
    srand(time(NULL));
    *orig = rand()%g->Gmax;
    *dest = rand()%g->Gmax;
}

void gerarArestas();

int main()
{
    Grafo g = init(15);
    int origem = 1, destino = 4;
    gerarOrigDest(g, &origem, &destino);
    printf("Origem: %d\nDestino: %d\n", origem, destino);
    inserirAdj(g, 0, 1, 10);
    inserirAdj(g, 0, 2, 12);
    inserirAdj(g, 0, 5, 15);
    inserirAdj(g, 1, 4, 11);
    inserirAdj(g, 1, 6, 14);
    inserirAdj(g, 2, 3, 13);
    inserirAdj(g, 3, 7, 16);
    inserirAdj(g, 4, 8, 18);
    inserirAdj(g, 5, 6, 17);
    inserirAdj(g, 6, 9, 20);
    inserirAdj(g, 7, 8, 22);
    inserirAdj(g, 8, 9, 25);
    inserirAdj(g, 9, 10, 28);
    inserirAdj(g, 9, 12, 30);
    inserirAdj(g, 9, 13, 32);
    inserirAdj(g, 10, 11, 35);
    inserirAdj(g, 12, 14, 36);
    inserirAdj(g, 13, 14, 38);

    /*printf("Formigueiros criados: \n");
    printf("             0\n");
    printf("            / \\ \n");
    printf("           /   \\ \n");
    printf("          /     \\ \n");
    printf("         4-------1\n");
    printf("         |\\    / |\n");
    printf("         | \\  /  |\n");
    printf("          \\  2  /\n");
    printf("           \\   /\n");
    printf("            \\ /\n");
    printf("             3\n");*/
    /*
                   0
                  / \
                 /   \
                /     \
               4 ---- 1
                \ / \
                 3 - 2
    */


    //dfs(g, 0, 4);
    bfs(g, origem, destino);
    int distanciasRel[15];
    inserindoDistanciasRelativas(g, destino, distanciasRel);
    printf("Custo guloso: %d\n", gulosa(g, origem, destino, distanciasRel));
    printf("Custo heuristica: %d\n", heuristica(g, origem, destino, distanciasRel));
}
