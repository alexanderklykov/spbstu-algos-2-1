#pragma once
#pragma warning (disable:4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

typedef struct string {
	char* stroka;
	int len;
	struct string* next;
} string;
//структура строки, нужна дл€ составлени€ списка

char* Readline(FILE* ptr);
//функци€, считывающа€ строку
struct string* koren(string* prev, int a, char* strochka);
//функци€, замен€юща€ корень данного списка на новый
void addelem(string* lst, int number, char* stroka);
//функци€, добавл€юща€ в произвольное место в списке узел
void printit(string* lst);
//функци€, вывод€щ€€ список
string* newRead(char* filename);
//функци€, в которой создаЄтс€ и, по мере создани€, сортируетс€ список
void cert(string* lst, int length);
//функци€, вывод€щ€€ строки запрашиваемой длины из списка
