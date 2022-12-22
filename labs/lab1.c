#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node_t {
	char* word;
	struct node_t* next;
} node_t;

void ListPrint(node_t* list);
void ListDelete(node_t** list);
void Sorting(node_t** list, FILE* pfile);

int main() {
	FILE* pfile;
	node_t* list = NULL;

	pfile = fopen("input1.txt", "r");//Открытие файла
	if (pfile == NULL) {
		printf("file %s not open", "input1.txt");
		exit(EXIT_FAILURE);
	}

	Sorting(&list, pfile);
	fclose(pfile);//закрытие файла

	pfile = fopen("input2.txt", "r");//Открытие файла
	if (pfile == NULL) {
		printf("file %s not open", "input2.txt");
		exit(EXIT_FAILURE);
	}

	Sorting(&list, pfile);
	fclose(pfile);//закрытие файла


	ListPrint(list);//Вывод файла
	ListDelete(&list);//Удаление списка из памяти

	return 0;
}
/*чтение слова*/
char* GetWord(FILE* pfile) {
	int c;
	int count = 0;
	int memsize = BUFSIZ * sizeof(char);
	char* result = (char*) malloc(memsize);	
	char* tmp_alloc;

	if (result == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}

	c = fgetc(pfile);
	while (isspace(c))
		c = fgetc(pfile);

	while (!isspace(c) && c != EOF) {
		result[count++] = c;
		if (count >= memsize) {
			memsize += BUFSIZ * sizeof(char);
			tmp_alloc = (char*)realloc(result, memsize);
			if (tmp_alloc == NULL) {
				fprintf(stderr, "realloc error\n");
				exit(EXIT_FAILURE);
			}
			result = tmp_alloc;
		}
		c = fgetc(pfile);
	}

	memsize = (count + 1) * sizeof(char);
	tmp_alloc = (char*)realloc(result, memsize);
	if (tmp_alloc == NULL) {
		fprintf(stderr, "realloc error\n");
		exit(EXIT_FAILURE);
	}
	result = tmp_alloc;

	result[count] = '\0';
	return result;
}
/*длина строки*/
size_t StrLen(char* str) {
	size_t count = 0;
	while (str[count] != '\0')
		count++;
	return count;
}
/*Создание списка*/
node_t* ListCreate(char* word) {
	node_t* node = (node_t*)malloc(sizeof(node_t));
	if (node == NULL)
		return NULL;

	int len = (StrLen(word) + 1)*sizeof(char);
	node->word = (char*)malloc(len);
	if (node->word == NULL) {
		fprintf(stderr, "malloc error");
		exit(EXIT_FAILURE);
	}

	strcpy_s(node->word, len, word);
	node->next = NULL;
	return node;
}
/*Добавление эллемента*/
node_t* ListAddAfter(node_t* head, node_t* current, node_t* newnode) {
	if (head == NULL || current == NULL)
		return newnode;
	newnode->next = current->next;
	current->next = newnode;
	return head;
}

/*сравнение строк*/
int StringCompare(char* first, char* second) {
	int i;
	for (i = 0; first[i] != 0 && second[i] != 0; ++i) {
		if (tolower(first[i]) == tolower(second[i]))
			continue;
		if (tolower(first[i]) < tolower(second[i]))
			return -1;
		return 1;
	}

	if (first[i] == second[i])
		return 0;
	if (first[i])
		return 1;
	else
		return -1;
}
/*добавление эллемента и сортировка*/
node_t* ListAddSort(node_t* head, node_t* node) {
	node_t* prev = NULL;
	node_t* current = head;
	while (current && (StringCompare(current->word, node->word) != 1)) {
		prev = current;
		current = current->next;
	}

	if (current == head) {
		node->next = head;
		return node;
	}
	return ListAddAfter(head, prev, node);
}
/*Вывод списка*/
void ListPrint(node_t* list) {
	while (list) {
		printf("%s\n", list->word);
		list = list->next;
	}
}
/*Освобождение памяти*/
void ListDelete(node_t** list) {
	node_t* current;
	while (*list) {
		current = *list;
		*list = (*list)->next;
		free(current->word);
		free(current);
	}
}
/*Создание списка и сортировка*/
void Sorting(node_t** list, FILE* pfile) {
	char* word = GetWord(pfile);
	node_t* node;

	while (word[0] != '\0') {
		node = ListCreate(word);
		*list = ListAddSort(*list, node);

		free(word);
		word = GetWord(pfile);
	}
}
