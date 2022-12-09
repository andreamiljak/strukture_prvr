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



	printf("upisite ime datoteke\n");
	scanf(" %s", filename);

	readfromfile(filename, izraz);
	printf("\n ucitani postfix: %s\n", izraz);
	printf("%d\n", postfix(izraz));

	getchar();
	getchar();

	return EXIT_SUCCESS;
}

int readfromfile(char* filename, char* izraz)
{

	FILE* fp = NULL;
	char buffer[MAX] = {0};

	fp = fopen(filename, "r");
	if (!fp)
	{
		printf("greska pri otvaranju datoteke");
		return ERROR;
	}
	fgets(izraz, MAX, fp);

	return EXIT_SUCCESS;


}

int push(pozicija head, int el)
{
	pozicija p = head;
	pozicija q = NULL;

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

	temp = head->next;
	el = temp->element;
	head->next = temp->next;
	free(temp);

	return el;
}


int postfix(char* izraz)
{
	int n = 0;
	int rezultat = 0;
	int temp1 = 0, temp2 = 0;
	Stog head;
	pozicija p = &head;

	head.next = NULL;
	head.element = 0;

	while (strlen(izraz) != 0) {
		int broj = 0;
		char operacija[2]= {0};
		int result = 0;
		result = sscanf(izraz, " %d %n", &broj, &n);
		if (result == 1) {
			push(&head, broj);
		}
		else {

			sscanf(izraz, "%s %n", operacija, &n);

			if (strcmp(operacija, "+") == 0) {
				/*if (head.next == NULL || head.next->next == NULL) {
				printf("Neispravan postfix!\n");
				break;
				}*/
				temp1 = pop(&head);
				temp2 = pop(&head);
				push(&head, temp1 + temp2);
			}
			else if (strcmp(operacija, "-") == 0) {
				/*if (head.next == NULL || head.next->next == NULL) {
				printf("Neispravan postfix!\n");
				break;
				}*/
				temp1 = pop(&head);
				temp2 = pop(&head);
				push(&head, temp1 - temp2);
			}
			else if (strcmp(operacija, "*") == 0) {
				/*if (head.next == NULL || head.next->next == NULL) {
				printf("Neispravan postfix!\n");
				break;
				}*/
				temp1 = pop(&head);
				temp2 = pop(&head);
				push(&head, temp1 * temp2);
			}
			else
			{
				printf("greska!\n");
				return ERROR;
			}

		}
		izraz += n;
	}

	/*if (head.next == NULL || head.next->next != NULL) {
	printf("Neispravan postfix!\n");
	return ERROR;
	}*/

	rezultat = pop(&head);
	return rezultat;
}

