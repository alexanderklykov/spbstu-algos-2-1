#include<stdio.h>
#include<stdlib.h>

typedef struct ELEMENT{
	int data;
	struct ELEMENT* left, * right;
} ELEMENT;

ELEMENT* Node(long n, int* a, long* pi)

{
	if (n <= 0) return NULL;
	else	{
		long nl, nr; ELEMENT* q;
		nl = n / 2; /* число вершин в левом поддереве */ nr = n - nl - 1; /* число вершин в правом поддереве */ 
		q = (ELEMENT*)malloc(sizeof(ELEMENT));
		q->data = a[*pi]; (*pi)++;
		q->left = Node(nl, a, pi); q->right = Node(nr, a, pi); return q;
	}

}

/*рекурсивное удаление дерева */

/**q – указатель на корень дерева */

void Distruct(ELEMENT* q){
	if (q != NULL)	{
		Distruct(q->left);
		Distruct(q->right); free(q);
	}
}

/* печать бинарного дерева */ 
void Print(ELEMENT* q, long n){
	if (q != NULL)	{
		long i; Print(q->right, n + 5); for (i = 0; i < n; i++)
			printf(" "); printf("%d\n", q->data); Print(q->left, n + 5);
	}

}

int main()

{
	ELEMENT* root = NULL; long i;
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; i = 0;
	root = Node(10, a, &i); Print(root, 0); Distruct(root);
	return 0;
}
