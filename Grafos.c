///Pedro Henrique Macedo de Oliveira
///Matricula: 16-95531

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grafo
{
    int num;
    struct grafo *next;
    int peso;
} grafo;

typedef struct lista
{
    grafo *start;
} lista;

lista *cria_lista(int tamanho);

void list(lista listas[], int tamanho);

int adicionalist(lista *l, int vertices2);

int adicionapeso(lista *l, int pesos);

void imprimi_lista(lista *l);

lista *crialista();

void Largura(lista *l[], int tam, int inicio, int *visita, FILE *arquivo_log);

void busca_em_profundiade(lista *vet[], int tam, FILE *arquivo_log);

void busca(lista *l[], int tam, int first, int visited[], int cont, FILE *arquivo_log);

void dfs(lista *l[], int tam, int *visitados, int v, FILE *arquivo_log);

void topologica(lista *l[], int tam, int *visitados, FILE *arquivo_log);

void Prim(lista *l[], int tam, int outset, int *visitor);

void Kruskal(lista *l[], int tam, int outset, int *visitor);

int main()
{
    int i, arestas = 0, tam = 0, op;
    int value1, value2, value3;
    int valor1, valor2, valor3;
    char palavras[100];
    FILE *arquivo;
    FILE *arquivo_log;

    arquivo = fopen("dmxa0628.txt", "r");
    arquivo_log = fopen("Retorno.txt", "w");

    if (arquivo == NULL)
    {
        printf("ERRO ao ler");
    }

    if (arquivo_log == NULL)
    {
        printf("ERRO ao abrir");
    }

    while (tam == 0 || arestas == 0)
    {
        fscanf(arquivo, "%s", palavras);
        if (strcmp(palavras, "Nodes") == 0)
        {
            fscanf(arquivo, "%d", &tam);
        }
        if (strcmp(palavras, "Edges") == 0)
        {
            fscanf(arquivo, "%d", &arestas);
        }
    }

    lista *l[tam];

    for (i = 0; i < tam; i++)
    {
        l[i] = crialista();
    }

    while (fscanf(arquivo, "%s", palavras) != -1)
    {
        if (strcmp(palavras, "E") == 0)
        {
            fscanf(arquivo, "%d %d %d", &value1, &value2, &value3);
            fprintf(arquivo_log, "\n%d %d", value1, value2);
            adicionalist(l[value1 - 1], value2 - 1);
        }
        if (strcmp(palavras, "DD") == 0)
        {
            fscanf(arquivo, "%d %d %d", &valor1, &valor2, &valor3);
            fprintf(arquivo_log, "\n%d %d", valor1, valor2);
            adicionapeso(l[valor1 - 1], valor2);
        }
    }

    for (i = 0; i < tam; i++)
    {
        printf("\n%d ", i + 1);
        imprimi_lista(l[i]);
    }

    do
    {
        printf("\n");
        printf("\nInsira 1)Busca em largura 2)Busca em profundidade 3)Ordencao Topologica 4)Algoritmo de Prim 5)Algoritmo de Kruskal\n");
        scanf("%d", &op);

        int *visita = (int *)malloc(tam * sizeof(int));

        if (op == 1)
        {
            Largura(l, tam, 0, visita, arquivo_log);
        }
        else if (op == 2)
        {
            busca_em_profundiade(l, tam, arquivo_log);
        }
        else if (op == 3)
        {
            fprintf(arquivo_log, "\nOrdenacao Topologica\n");
            topologica(l, tam, visita, arquivo_log);
        }
        else if (op == 4)
        {
            printf("\nPrim\n");
            fprintf(arquivo_log, "\nPrim\n");
            Prim(l, tam, 0, visita);
            for (int i = 0; i < tam; i++)
            {
                printf("%d  ", visita[i]);
                fprintf(arquivo_log, "%d  ", visita[i]);
            }
        }
        else if (op == 5)
        {
            printf("\nKruskal\n");
            fprintf(arquivo_log, "\nKruskal\n");
            Kruskal(l, tam, 0, visita);
            for (int i = 0; i < tam; i++)
            {
                printf("%d  ", visita[i]);
                fprintf(arquivo_log, "%d  ", visita[i]);
            }
        }
    } while (op != 0);

    fclose(arquivo);
    fclose(arquivo_log);
}

lista *crialista() //Cria Lista!
{
    lista *l = (lista *)malloc(sizeof(lista));

    l->start = NULL;
    return l;
}

int adicionalist(lista *l, int vertices2)
{
    grafo *list = (grafo *)malloc(sizeof(grafo));

    list->num = vertices2;
    list->next = NULL;

    if (l->start == NULL)
    {
        l->start = list;
    }
    else
    {
        grafo *aux = l->start;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = list;
    }
    return 1;
}

int adicionapeso(lista *l, int pesos)
{
    if (l->start != NULL)
    {
        l->start->peso = pesos;
    }
    return 1;
}

void imprimi_lista(lista *l) //Imprimi lista no executavel!
{
    grafo *ola;

    ola = l->start;

    while (ola != NULL)
    {
        printf("-> %d ", ola->num + 1);
        ola = ola->next;
    }
    printf("-> /");
}

void Largura(lista *l[], int tam, int inicio, int *visita, FILE *arquivo_log)
{

    int vertice, cont = 1, *fil, startfila = 0, endfila = 0;

    grafo *aux = (grafo *)malloc(sizeof(grafo));

    for (int i = 0; i < tam; i++)
    {
        visita[i] = 0;
    }

    fil = (int *)malloc(tam * sizeof(int));
    endfila++;
    fil[endfila] = inicio;
    visita[startfila] = cont;

    printf("\nBusca em Largura: ");
    fprintf(arquivo_log, "\n");
    fprintf(arquivo_log, "\nBusca em Largura: ");

    while (startfila != endfila)
    {
        startfila = (startfila + 1) % tam;
        vertice = fil[startfila];
        cont++;

        printf("%d  ", vertice + 1);
        fprintf(arquivo_log, "%d ", vertice + 1);

        aux = l[vertice]->start;

        while (aux != NULL)
        {
            if (!visita[aux->num])
            {
                endfila = (endfila + 1) % tam;
                fil[endfila] = aux->num;
                visita[aux->num] = cont;
            }
            aux = aux->next;
        }
    }
}

void busca_em_profundiade(lista *l[], int tam, FILE *arquivo_log)
{
    int visitados[tam];
    int cont = 1;
    for (int i = 0; i < tam; i++)
    {
        visitados[i] = 0;
    }
    printf("\nBusca de profundiadade: ");
    fprintf(arquivo_log, "\nBusca de profundiadade: ");
    busca(l, tam, 0, visitados, cont, arquivo_log);
}

void busca(lista *l[], int tam, int first, int visited[], int cont, FILE *arquivo_log)
{
    fprintf(arquivo_log, "%d ", first + 1);
    printf("%d  ", first + 1);
    grafo *aux = (grafo *)malloc(sizeof(grafo));
    visited[first] = cont;
    aux = l[first]->start;

    while (aux != NULL)
    {
        if (!visited[aux->num])
        {
            busca(l, tam, aux->num, visited, cont + 1, arquivo_log);
        }
        aux = aux->next;
    }
}

void dfs(lista *l[], int tam, int *visitados, int v, FILE *arquivo_log)
{
    grafo *aux;
    visitados[v] = 1;

    for (int i = 0; i < tam; i++)
    {
        for (aux = l[i]->start; aux != NULL; aux = aux->next)
        {
            if (!visitados)
            {
                dfs(l, tam, visitados, aux->num, arquivo_log);
            }
        }
    }
    fprintf(arquivo_log, "%d  ", v + 1);
    printf("%d  ", v + 1);
}

void topologica(lista *l[], int tam, int *visitados, FILE *arquivo_log)
{
    for (int i = 0; i < tam; i++)
    {
        visitados[i] = 0;
    }
    for (int i = 0; i < tam; i++)
    {
        dfs(l, tam, visitados, i, arquivo_log);
    }
}

void Prim(lista *l[], int tam, int outset, int *visitor)
{

    int i, destiny, first, smaller;

    for (i = 0; i < tam; i++)
    {
        visitor[i] = -1;
    }
    visitor[outset] = outset;

    grafo *aux;
    grafo *aux2;

    do
    {

        first = 1;
        for (i = 0; i < tam; i++)
        {

            aux = l[i]->start;
            if (visitor[i] != -1)
            {

                aux2 = aux;
                while (aux2 != NULL)
                {
                    if (visitor[aux2->num] == -1)
                    {
                        if (first)
                        {
                            smaller = aux2->peso;
                            outset = i;
                            destiny = aux2->num;
                            first = 0;
                        }
                        else
                        {
                            if (smaller > aux2->peso)
                            {
                                smaller = aux2->peso;
                                outset = i;
                                destiny = aux2->num;
                            }
                        }
                    }

                    aux2 = aux2->next;
                }
            }
        }
        if (first != 1)
        {
            visitor[destiny] = outset;
        }

    } while (first != 1);
}

void Kruskal(lista *l[], int tam, int outset, int *visitor)
{

    int i, destiny, first, smaller;

    int *arv = (int *)malloc(tam * sizeof(int));

    for (i = 0; i < tam; i++)
    {
        visitor[i] = -1;
        arv[i] = i;
    }

    visitor[outset] = outset;

    grafo *aux;
    grafo *aux2;

    while (1)
    {

        first = 1;
        for (i = 0; i < tam; i++)
        {

            aux = l[i]->start;
            aux2 = aux;
            while (aux2 != NULL)
            {

                if (visitor[aux2->num] == -1 && arv[i] != arv[aux2->num])
                {
                    if (first)
                    {
                        smaller = aux2->peso;
                        outset = i;
                        destiny = aux2->num;
                        first = 0;
                    }
                    else
                    {
                        if (smaller > aux2->peso)
                        {
                            smaller = aux2->peso;
                            outset = i;
                            destiny = aux2->num;
                        }
                    }
                }
                aux2 = aux2->next;
            }
        }

        if (first == 1)
        {
            break;
        }

        if (visitor[outset] == -1)
        {
            visitor[outset] = destiny;
        }
        else
            visitor[destiny] = outset;

        for (i = 0; i < tam; i++)
        {
            if (arv[i] == arv[destiny])
                arv[i] = arv[outset];
        }
    }
}