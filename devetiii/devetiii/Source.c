
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct stablo;
typedef struct stablo* dite;
typedef struct stablo {
	int el;
	dite left;
	dite right;
}Stablo;



dite insert(dite, dite);
int inorder(dite);
dite novi(int);
int replace(dite);



int main()
{
	dite root = NULL;
	int i = 0;
	int niz[10];
	int max = 90;
	int min = 10;

	/*
	  root = insert(root, novi(2));
	  root = insert(root, novi(5));
	  root = insert(root, novi(7));
	  root = insert(root, novi(8));
	  root = insert(root, novi(11));
	  root = insert(root, novi(1));
	  root = insert(root, novi(4));
	  root = insert(root, novi(2));
	  root = insert(root, novi(3));
	  root = insert(root, novi(7));

	  inorder(root);

	  replace(root);
  */
	srand(time(0));

	for (i = 0; i < 10; i++)
	{
		niz[i] = rand() % (max - min + 1) + min;

		root = insert(root, novi(niz[i]));
	}
	inorder(root);

	replace(root);
	printf("\n");
	inorder(root);
	return 0;
}


dite insert(dite p, dite q)
{
	if (p == NULL)
		return q;
	if (q->el < p->el)
	{
		p->right = insert(p->right, q);
	}
	else if (p->el <= q->el)
	{
		p->left = insert(p->left, q);
	}
	else {
		free(q);
	}

	return p;
}
int inorder(dite p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		inorder(p->left);
		printf("%d ", p->el);
		inorder(p->right);
	}
	return 0;
}

dite novi(int element)
{
	dite q;
	q = (dite)malloc(sizeof(Stablo));

	q->el = element;
	q->left = NULL;
	q->right = NULL;

	//q = insert(p, q->el);
	return q;
}

int replace(dite p)
{
	if (p == NULL)
		return 0;
	int sum = p->el;
	p->el = replace(p->left) + replace(p->right);
	return (p->el + sum);
}