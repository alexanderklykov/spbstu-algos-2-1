#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)
#define false 0
#define true 1
typedef struct partOfChain chain;
struct partOfChain {
    int roadTo;
    chain* next;
};
typedef struct grph head;
struct grph {
    _Bool used;
    chain* next;
};
int howManyVertex;//глобальная переменная
void Push(head* graph, int begin, int end) {//добавление эллемента
    chain* tmp = malloc(sizeof(chain));
    tmp->roadTo = end;
    tmp->next = NULL;
    if (!graph[begin].next) {
        graph[begin].next = tmp;
        return;
    }
    tmp->next = graph[begin].next;
    graph[begin].next = tmp;
    return;
}
//проверяем шаг
_Bool MakeStep(head* graph, int position, int deep) {
    chain* here;
    deep++;
    if (deep == howManyVertex) {
        printf("%i ", position + 1);
        return true;
    }
    here = graph[position].next;
    while (here) {
        if (!graph[here->roadTo].used) {

            graph[here->roadTo].used = true;
            if (MakeStep(graph, here->roadTo, deep)) {
                printf("%i ", position + 1);
                return true;
            }
        }
        here = here->next;
    }
    graph[position].used = false;
    return false;
}

_Bool FirstStep(head* graph) {//Делаем первый шаг

    int i = 0;
    while (i < howManyVertex) {
        if (graph[i].used != true && graph[i].next != NULL) {
            graph[i].used = true;
            if (MakeStep(graph, i, 0)) {
              
                return true;

            }
        }
        if (!graph[i].next) {
            break;
        }
        graph[i].used = false;
        i++;
    }
    printf("No way\n");
    return false;
}
void InitializationAndReadGraph(head* graph) {
    int from, to;
    for (int i = 0; i < howManyVertex; i++) { 
        graph[i].next = NULL;
        graph[i].used = false;
    }

    
    while (scanf("%i %i", &from, &to)) { //чтение из файла в граф
        Push(graph, from - 1, to - 1);
        Push(graph, to - 1, from - 1);
        //printf("%i %i\n", from, to);
        if (getchar() == EOF) {
            break;
        }
        //getch();
    }
    return;
}

void CleanGraph(head* graph) {
    for (int i = 0; i < howManyVertex; i++) {//освобождение памяти
        chain* here = graph[i].next;
        chain* nextch;
        while (here) {
            nextch = here->next;
            free(here);
            here = nextch;
        }
    }
}

int main(void) {
    FILE* fp;
    head* graph;

    fp = freopen("inlab4.txt", "r", stdin);
    scanf_s("%i", &howManyVertex);
    graph = malloc(howManyVertex * sizeof(head)); //создание графа
    InitializationAndReadGraph(graph);
    FirstStep(graph);
    CleanGraph(graph);
    free(graph);
    
    return 0;
}
