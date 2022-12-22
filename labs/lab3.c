#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
struct node
{
    int vertex;
    struct node* next;
};
struct node* createNode(int);
struct Graph
{
    int numVertices;
    struct node** adjLists;
};
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
int main()
{
    struct Graph* graph = createGraph(6);
    FILE* fp;

    fp = freopen("in.txt", "r", stdin);
    int from=0, to=0;
    while (scanf("%i %i", &from, &to)) { //чтение элемента графа
        addEdge(graph, from, to);
        if (getchar() == EOF) {
            break;
        }
    }


    printGraph(graph);

    return 0;
}

/*Выделение памяти под эллемент графа*/
struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
/*создание графа*/
struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}
/*Добавление эллемента*/
void addEdge(struct Graph* graph, int src, int dest)
{
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
/*вывод графа*/
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 1; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
