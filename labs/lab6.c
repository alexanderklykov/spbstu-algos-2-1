include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define W 70
#define N 20
char TABLE[N][W];
typedef struct tree_t {
    int key;
    int number;
    bool visit;
    struct tree_t* leftChild;
    struct tree_t* rightChild;
    struct tree_t* myParent;
};
typedef struct tree_t tree;


void PrintTABLE(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < W; j++) {
            printf("%c", TABLE[i][j]);
        }
        printf("\n");
    }
}
void InitTABLE(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < W; j++) {
            TABLE[i][j] = ' ';
        }
    }
}

void PrintInTable(tree* t, int x, int y) {
    if (!t) {
        return;
    }
    if (t->leftChild) {
        PrintInTable(t->leftChild, x - (t->leftChild->number), y + 1);
    }
    TABLE[y][x] = t->key + '0';
    if (t->rightChild) {
        PrintInTable(t->rightChild, x + (t->rightChild->number), y + 1);
    }
}

void IncreaseNumber(tree* t) {
    while (t->number != -1) {
        t->number = t->number + 1; 
        t = t->myParent;
    }
    return;
}

tree* add(tree* t, int k)
{
    int flag = 0;
    tree* root = t;
    tree* child;
    if (t == NULL) {
        t = (tree*)malloc(sizeof(tree));
        t->key = k;
        t->leftChild = t->rightChild = t->myParent = NULL;
        t->number = -1;
        return t;
    }
    else
    {
        while (!flag) {
            if (t->leftChild == NULL) {
                child = (tree*)malloc(sizeof(tree));
                t->leftChild = child;
                child->myParent = t;
                child->key = k;
                child->visit = false;
                child->number = 1;
                child->leftChild = child->rightChild = NULL;
                IncreaseNumber(t);
                flag = 1;//Функция для увеличения поддеревьев
            }
            else if (t->rightChild == NULL) {
                child = (tree*)malloc(sizeof(tree));
                t->rightChild = child;
                child->myParent = t;
                child->key = k;
                child->number = 1;
                child->visit = false;
                child->leftChild = child->rightChild = NULL;
                IncreaseNumber(t);
                flag = 1;//Функция для увеличения поддеревьев
            }
            else if (t->leftChild->number > t->rightChild->number) {
                t = t->rightChild;
            }
            else {
                t = t->leftChild;
            }
        }
    }
    return root;
}
void DownNumber(tree* current) { //Я подхожу к корню текущего элемента, опуская их под деревья, когда беру элемент
    while (current->number != -1) {
        current->number = current->number - 1;
        current = current->myParent;
    }
}

tree* FindChildForChange(tree* current) {//Ищем крайний левый элемент для текущего
    while (current->leftChild != NULL) {
        current = current->leftChild;
    }
    current->myParent->leftChild = current->myParent->rightChild;//Я пишу правый элемент вместо левого, чтобы "поддерживать порядок".
    current->myParent->rightChild = NULL;
    DownNumber(current->myParent);
    return current;
}

tree* delete(tree* t, int k) {
    int compas = 0;
    if (t == NULL) {
        return t;
    }
    tree* root = t;
    tree* childForChange;
    int flag = 0;
    while (!flag) {
        if (t->key == k) {
            if (t->leftChild == NULL && t->rightChild == NULL) { //Лист или пустое дерево?
                if (t->number == -1) { //С деревом работа завершена
                    free(t);
                    return NULL;
                }
                DownNumber(t->myParent);
                if (t->myParent->leftChild != NULL && t->myParent->leftChild->key == k) {//Определение того, каким ребенком я являюсь в данный момент
                    t->myParent->leftChild = NULL;
                }
                else {
                    t->myParent->rightChild = NULL;
                }
            }
            else {
                //Случай, когда узел является корнем
                childForChange = FindChildForChange(t);//Найдите дочерний узел, который будет красивым
                if (t->number != -1) {
                    childForChange->myParent = t->myParent;//Вы не можете выбрасывать указатели, а просто измените номер и удалите этот дочерний элемент, но допустим, нам нужно изменить
                    if (t->myParent->leftChild != NULL && t->myParent->leftChild->key == k) {//Определение того, каким ребенком я являюсь в данный момент
                        t->myParent->leftChild = childForChange;
                    }
                    else {
                        t->myParent->rightChild = childForChange;
                    }
                }
                else {
                    root = childForChange;

                }
                childForChange->leftChild = t->leftChild;
                if (childForChange->leftChild) {
                    childForChange->leftChild->myParent = childForChange;
                }
                childForChange->rightChild = t->rightChild;
                if (childForChange->rightChild) {
                    childForChange->rightChild->myParent = childForChange;
                }
                childForChange->number = t->number;

            }
            free(t);
            return root;
        }
        else if (t->leftChild != NULL && t->leftChild->visit == 0 && (t->rightChild == NULL || t->rightChild->visit == 0)) {//поскольку мы всегда добавляем как можно больше влево
            t = t->leftChild;                                                                  //Затем производится эта проверка , так как при перемещении вправо
        }                                                                                    //Мы убираем левую, чтобы не оставлять никакого мусора
        else if (t->rightChild != NULL && t->rightChild->visit == 0) {                        //Вам нужен костыль на корню, потому что возникнет проблема с отсутствием элемента
            if (t->leftChild) {
                t->leftChild->visit = 0;
            }
            t = t->rightChild;
        }
        else {
            if (t->number == -1) { 
                printf("No element found\n");
                t->rightChild->visit = 0;
                return t;
            }
            t->visit = 1;
            if (t->leftChild) {
                t->leftChild->visit = 0;
            }
            if (t->rightChild) {
                t->rightChild->visit = 0;
            }
            t = t->myParent;
        }
    }

}

int main(void) {
    tree* myTree = NULL;
    int command = 0;
    int elem;
    InitTABLE();
    while (command != -1) {
        scanf("%i", &command);
        switch (command) {
        case 1:
            printf("add elem: ");
            scanf("%i", &elem);
            myTree = add(myTree, elem);
            PrintInTable(myTree, 35, 0);
            PrintTABLE();
            InitTABLE();
            break;
        case 2:
            printf("delete elem: ");
            scanf("%i", &elem);
            myTree = delete(myTree, elem);
            PrintInTable(myTree, 35, 0);
            PrintTABLE();
            InitTABLE();
            break;
        default:
            printf("unknow command\n");
            break;
        }
        //printf("%i\n", command);
    }
    getch();
    return 0;
}
