#pragma warning (disable:4996)
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "Header.h"
/*/
char* Readline(FILE* ptr) {
	int len = 0;
	char t = fgetc(ptr);
	char* a = (char*)malloc(sizeof(char));
	if (a == NULL) return;
	while ((t != '\n') && (t != EOF)) {
		len += 1;
		char* p = (char*)realloc(a, len * sizeof(char));
		if (p == NULL) {
			printf("oioi");
			return;
		}
		a = p;
		a[len - 1] = t;
		t = fgetc(ptr);
	}
	len += 1;
	char* p = (char*)realloc(a, len * sizeof(char));
	if (p == NULL) {
		printf("oioi");
		return;
	}
	a = p;
	*(a + len - 1) = 0;
	if (*a == 0) {
		//printf("haha");
	}
	return a;
}

typedef struct string {
	char* stroka;
	int len;
	struct string* next;
} string;
string* init(char* str, int a) {
	struct string* lst;
	lst = (struct string*)malloc(sizeof(struct string));
	lst->len = a;
	lst->stroka = (char*)malloc(sizeof(char) * a);
	strcpy(lst->stroka, str);
	lst->next = NULL;
	return(lst);
}

//string* uzel(char* str, int a, string* ptr) {
//	string* smth = (string*)malloc(sizeof(string));
	//smth->stroka = (char*)malloc(sizeof(char) * a);
	//strcpy(smth->stroka, str);
//	smth->len = a;
	//smth->next = ptr;
	//return(smth);
//}

//struct string* addelem(string* lst, int number, char* stroka)

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
	//return(temp);
}

string* Read(char* filename) {
	FILE* ptr = fopen(filename, "r");
	if (ptr == NULL) {
		printf("Плохо");
		exit(1);
	}
	char* phj = (char*)malloc(sizeof(char)*100);
	char* fuck = NULL;
	fscanf(ptr, "%[^\n]\n", phj);
	//fuck = (char*)malloc(strlen(phj) * sizeof(char));
	//strcpy(fuck, phj);
	string* line = (string*)malloc(sizeof(string));
	line = init(phj, strlen(phj));
	printf("%d ass %s\n",strlen(phj), line->stroka);
	while ((fscanf(ptr, "%[^\n]\n", phj)) != EOF) {
		string* temp;
		temp = line;
		string* p = NULL;
		//if (!p) printf("so it's zero");
		//printf("dude wtf %s\n", line->stroka);
		int length = strlen(phj);
		int trigger = 0;
		while ((temp) && !(trigger)) {
			printf("\n%s\n", line->stroka);
			if (length <= (temp->len)) {
				if (!p) {
					printf("%d balls %s\n", length, phj);
					string* new =(string*)malloc(sizeof(string));
					if (!new) exit(1);
					new->len = line->len;
					new->stroka = (char*)malloc(sizeof(char) * line->len);
					printf("\nbefore strcpy %s\n", line->stroka);
					strcpy(new->stroka, line->stroka);
					new->next = line->next;
					line->len = length;
					line->stroka = (char*)realloc(line, sizeof(char) * length);
					strcpy(line->stroka, phj);
					line->next = new;
					trigger = 1;
				}
				else {
					printf("%d ass %s\n", length, phj);
					string* new =(string*) malloc(sizeof(string));
					new->len = length;
					new->stroka = (char*)malloc(sizeof(char) * length);
					strcpy(new->stroka, phj);
					new->next = temp;
					p->next = new;
					trigger = 1;
				}
			}
			else{
				printf("dick ");
				p = temp;
				printf("\n{%s}\n", temp->stroka);
				temp = temp->next;
			}
			//else if (temp == NULL) {
				//printf("fuck my balls %s\n", &phj);
				//string* new = malloc(sizeof(string));
				//new->len = length;
				//new->stroka = (char*)malloc(sizeof(char) * length);
				//new->stroka = phj;
				//p->next = new;
			//}
		}
		if (!trigger) {
			printf("fuck my balls %s\n", &phj);
			string* new =(string*) malloc(sizeof(string));
			new->len = length;
			new->stroka = (char*)malloc(sizeof(char) * length);
			strcpy(new->stroka, phj);
			p->next = new;
		}
	}

	fclose(ptr);
	return line;
}

void printit(string* lst) {
	int length = 0;
	string* temp = lst;
	while (temp) {
		length += 1;
		//printf("%s\n", temp->stroka);
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
	//	printf("test %s %s test\n", temp->stroka, line->stroka);
		while (temp && (strlen(strochka) >= (temp->len))) {
			p = temp;
		//	printf("works? %s\n", p->stroka);
			temp = temp->next;

			trigger = 1;
		}

		if (trigger) {
			//printf("truly works?2 %s\n", p->stroka);
			addelem(p, strlen(strochka), strochka);
		//	printf("holy shit%s %d\n holy fuck %s %d", temp->stroka, temp->len, p->next->stroka, p->next->len);

		}
		else {
			//printf("dude why\n");
			string* smth = koren(temp, strlen(strochka), strochka);
			//printf(" new koren %s %d\n", smth->stroka, smth->len);
			line = smth;
			
			//printf("new new koren %s %d\n", line->stroka, line->len);
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
/*/
int main(void) {
	char* cNameFile = "itjustworks.txt";
	FILE* ptr = fopen(cNameFile, "r");
	//string* line =(string*) malloc(sizeof(string));
	//Read(cNameFile, line);
	string* spisok;
	spisok = newRead(cNameFile);
	printit(spisok);
	int len = 0;
	while (len != -1) {
		printf("Vvedite dliny strok, kotorye hotite naiti. Dlya ostanovki vvedite -1\n");
		scanf("%d", &len);
		cert(spisok, len);
	}
	return 0;
}
