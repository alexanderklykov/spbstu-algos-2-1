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
//��������� ������, ����� ��� ����������� ������

char* Readline(FILE* ptr);
//�������, ����������� ������
struct string* koren(string* prev, int a, char* strochka);
//�������, ���������� ������ ������� ������ �� �����
void addelem(string* lst, int number, char* stroka);
//�������, ����������� � ������������ ����� � ������ ����
void printit(string* lst);
//�������, ��������� ������
string* newRead(char* filename);
//�������, � ������� �������� �, �� ���� ��������, ����������� ������
void cert(string* lst, int length);
//�������, ��������� ������ ������������� ����� �� ������
