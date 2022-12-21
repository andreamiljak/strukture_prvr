#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
#define EXIT_SUCCESS 0
#define ERROR -1


struct stablo;
typedef struct stablo* pozicija;
typedef struct stablo {
	int element;
	pozicija left;
	pozicija right;
}Stablo;

pozicija Unos(pozicija, pozicija);
pozicija Trazi(pozicija, int);
pozicija Brisi(pozicija, int);
pozicija TraziMin(pozicija);
pozicija TraziMax(pozicija);
int Inorder(pozicija);
int Preorder(pozicija p);
int Postorder(pozicija p);
int Orderlevel(pozicija p);
printMeni();

int main()
{
	
	
	
	pozicija root = NULL;
	pozicija temp = NULL;
	pozicija q = NULL;
	
	int choice;
	int element = 0;







	do {
		printf("Pick a number \n");
		printf("  1 - Insert Element\n");
		printf("  2 - Print In Order\n");
		printf("  3 - Print Pre Order\n");
		printf("  4 - Print Post Order\n");
		printf("  5 - Print Level Order\n");
		printf("  6 - Find Element\n");
		printf("  7 - Delete Element\n");
		printf("  0 - Exit\n");



		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Which element do you want to insert: ");
			scanf("%d", &element);
			q = (pozicija)malloc(sizeof(Stablo));
			q->left = NULL;
			q->right = NULL;
			q->element = element;
			root = Unos(root, q);

			break;
		case 2:
			Inorder(root);
			break;
		case 3:
			Preorder(root);
			break;
		case 4:
			Postorder(root);
			break;
		case 5:
			//Orderlevel(root);
			break;

		case 6:
			printf("Which element you want to find: ");
			scanf("%d", &element);
			temp = Trazi(root, element);
			if (!temp) {
				printf("Element not found!\n");
			}
			else {
				printf("Element found!\n");
			}
			break;
		case 7:
			printf("Which element you want to delete: ");
			scanf("%d", &element);

			root = Brisi(root, element);
			break;
		case 0:
			break;
		default:
			printf("Wrong input!\n");
		}


		

	} while (choice != 0);
	
	return EXIT_SUCCESS;
}

pozicija Unos(pozicija p, pozicija q)
{
	if (p == NULL)
		return q;
	if (p->element < q->element)
	{
		p->right = Unos(p->right, q);
	}
	else if (p->element > q->element)
	{
		p->left = Unos(p->left, q);
	}
	else {
		free(q);
	}
	return p;
}

pozicija Trazi(pozicija p, int el)
{
	if (p == NULL)
		return NULL;
	else if (el < p->element)
		p->left = Trazi(p->left, el);
	else if (el > p->element)
		p->right = Trazi(p->right, el);
	else
		return p;

}

pozicija Brisi(pozicija p, int el)
{
	if (p == NULL)
		return NULL;
	if (el < p->element)
		p->left = Brisi(p->left, el);
	else if (el > p->element)
		p->right = Brisi(p->right, el);
	else
	{
		if (p->left)
		{
			pozicija temp = TraziMax(p->left);
			p->element = temp->element;
			p->left = Brisi(p->left, temp->element);
		}

		else if (p->right)
		{
			pozicija temp = TraziMin(p->right);
			p->element = temp->element;
			p->right = Brisi(p->right, temp->element);
		}
		else
		{
			free(p);
			return NULL;
		}
	}
	return p;
}

pozicija TraziMin(pozicija p)
{
	if (p == NULL)
		return NULL;
	else if (p->left == NULL)
		return p;
	else
		return TraziMin(p->left);

}

pozicija TraziMax(pozicija p)
{
	if (p == NULL)
		return NULL;
	else if (p->right == NULL)
		return p;
	else
		return TraziMax(p->right);
}

int Inorder(pozicija p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		Inorder(p->left);
		printf("%d ", p->element);
		Inorder(p->right);
	}
	return EXIT_SUCCESS;
}


int Preorder(pozicija p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		printf("%d ", p->element);
		Preorder(p->left);
		Preorder(p->right);
		
	}
	return EXIT_SUCCESS;
}

int Postorder(pozicija p)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		Postorder(p->left);
		Postorder(p->right);
		printf("%d ", p->element);

	}
	return EXIT_SUCCESS;
}
