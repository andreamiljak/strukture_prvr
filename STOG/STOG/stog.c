#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX (200)
#define ERROR (-1)
#define EXIT_SUCCESS (0)

typedef struct stog Stog;
typedef struct stog* pozicija;

struct stog {
	int element;
	pozicija next;
};

int readfromfile(char*, char*);
int push(pozicija, int);
int pop(pozicija);
int postfix(char*);


int main()
{
	char filename[MAX] = { 0 };
	char izraz[MAX] = { 0 };



	printf("upišite ime datoteke\n");
	scanf(" %s", filename);

	readfromfile(filename, izraz);
	printf("\n ucitani postfix: %s\n", izraz);
	printf("\n\n%d\n", postfix(izraz));

	}

int readfromfile(char* filename, char* izraz)
{
	
	FILE* fp = fopen(filename, "r");
	char buffer[MAX];
	if (!fp)
	{
		printf("greška pri otvaranju datoteke");
		return ERROR;
	}
	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		if (strcmp("\n", buffer) != 0)
			break;
	}
	strcpy(izraz, buffer);
	
	return EXIT_SUCCESS;
	
	
}

int push(pozicija head, int el)
{
	pozicija p = head;
	pozicija q = NULL;

	while (p->next != NULL) {
		p = p->next;
		q = p;
	}
	q = (pozicija)malloc(sizeof(Stog));
	
	
	q->element = el;
	q->next = p->next;
	p->next = q;
	
	return EXIT_SUCCESS;

}
int pop(pozicija head)
{
	pozicija p = head;
	pozicija temp = NULL;
	int el = 0;

	while (p->next->next != NULL) {
		p = p->next;
	}
	temp = p->next;
	el = temp->element;
	p->next = NULL;
	free(temp);

	return el;

}


int postfix(char* izraz)
{
	char t[] = "";
	int n = 0, b = 0;
	int rezultat = 0;
	int temp1 = 0, temp2 = 0;
	Stog head = { .element = 0, .next = NULL };
	pozicija p = &head;


	while (strlen(izraz) != 0) {
		b = sscanf(izraz, " %s %n", t, &n);
		if (b != 1) {
			printf("Neispravan postfix!\n");
			return ERROR;
		}
		izraz = izraz + n;

		if (strcmp(t, "+") == 0) {
			if (head.next == NULL || head.next->next == NULL) {
				printf("Neispravan postfix!\n");
				break;
			}
			temp1 = pop(&head);
			temp2 = pop(&head);
			push(&head, temp1 + temp2);
		}
		else if (strcmp(t, "-") == 0) {
			if (head.next == NULL || head.next->next == NULL) {
				printf("Neispravan postfix!\n");
				break;
			}
			temp1 = pop(&head);
			temp2 = pop(&head);
			push(&head, temp1 - temp2);
		}
		else if (strcmp(t, "*") == 0) {
			if (head.next == NULL || head.next->next == NULL) {
				printf("Neispravan postfix!\n");
				break;
			}
			temp1 = pop(&head);
			temp2 = pop(&head);
			push(&head, temp1 * temp2);
		}
		else {
			push(&head, atoi(t));
		}

		
	}

	if (head.next == NULL || head.next->next != NULL) {
		printf("Neispravan postfix!\n");
		return ERROR;
	}

	rezultat = pop(&head);
	return rezultat;
}
