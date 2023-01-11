#pragma warning (disable:4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "Header.h"

char* Readline(FILE* ptr) {
	int len = 0;
	char t = fgetc(ptr);
	char* a = (char*)malloc(sizeof(char));
	if (a == NULL) return;
	while ((t != '\n') && (t != EOF)) {
		len += 1;
		char* p = (char*)realloc(a, len * sizeof(char));
		if (p == NULL) {
			return;
		}
		a = p;
		a[len - 1] = t;
		t = fgetc(ptr);
	}
	len += 1;
	char* p = (char*)realloc(a, len * sizeof(char));
	if (p == NULL) {
		return;
	}
	a = p;
	*(a + len - 1) = 0;
	if (*a == 0) {
	}
	return a;
}

struct string* koren(string* prev, int a, char* strochka) // а- значение первого узла
{
	struct string* lst;
	// выделение памяти под корень списка
	lst = (struct string*)malloc(sizeof(struct string));
	lst->stroka = strochka;
	lst->len = a;
	lst->next = prev;
	return(lst);
}

void addelem(string* lst, int number, char* stroka)
{
	struct string* temp, * p;
	temp = (struct string*)malloc(sizeof(string));
	p = lst->next; // сохранение указателя на следующий узел
	lst->next = temp; // предыдущий узел указывает на создаваемый
	temp->stroka = stroka;
	temp->len = number; // сохранение поля данных добавляемого узла
	temp->next = p; // созданный узел указывает на следующий элемент
}


void printit(string* lst) {
	int length = 0;
	string* temp = lst;
	while (temp) {
		length += 1;
		temp = temp->next;
	}
	temp = lst;
	for (int i = 0; i < length; i += 1) {
		if (i >= (length - 10)) printf("%s\n", temp->stroka);
		temp = temp->next;
	}
}

string* newRead(char* filename) {
	FILE* ptr = fopen(filename, "r");
	if (ptr == NULL) {
		printf("BAD");
		exit(1);
	}
	char* strochka = NULL;
	strochka = Readline(ptr);
	string* line = (string*)malloc(sizeof(string));
	line->stroka = strochka;
	line->len = strlen(strochka);
	line->next = NULL;
	while (*(strochka = Readline(ptr))) {
		int trigger = 0;
		string* p = NULL;
		string* temp = line;
		while (temp && (strlen(strochka) >= (temp->len))) {
			p = temp;
			temp = temp->next;

			trigger = 1;
		}

		if (trigger) {
			addelem(p, strlen(strochka), strochka);

		}
		else {
			string* smth = koren(temp, strlen(strochka), strochka);
			line = smth;

		}
	}
	return line;
}

void cert(string* lst, int length) {
	if (length != -1) {
		string* temp = lst;
		int trigger = 1;
		if (temp->len > length) trigger = 0;
		if (trigger) {
			while (temp && temp->len < length) {
				temp = temp->next;
			}
			if (temp && (temp->len == length)) {
				printf("stroki dannoy dliny:\n");
				while (temp && (temp->len == length)) {
					printf("%s\n", temp->stroka);
					temp = temp->next;
				}
			}
			else printf("net strok takoy dliny");
		}
		else {
			printf("net strok takoy dliny");
		}
	}
}
