#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

#define ERROR (-1)
#define MAX (50)
#define EXIT_SUCCESS (0)



struct osoba;
typedef struct osoba* ljud;
typedef struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int godina;
	ljud next;
} Osoba;

ljud Stvori(char* , char*, int);
void UnosP(ljud head, ljud p);
void Ispis(head->next);


int main(void)
{
	Osoba head;
	//ljud head = NULL;
	ljud p = NULL;
	int odabir = 0;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int godina = 0;
	
	printf("zelite li unjeti ime na pocetak liste?\nda-> 1\n ne->2\n");
	scanf("%d", &odabir);
	while (odabir == 1)
	{
		printf("IME: ");
		scanf("%s", ime);
		printf("\nPREZIME: ");
		scanf("%s", prezime);
		printf("\nGODINA: ");
		scanf("%d", &godina);
		p = Stvori(ime, prezime, godina);

		printf("zelite li unjeti ime na pocetak liste?\nda-> 1\n ne->2\n");
		scanf("%d", &odabir);
		
	}
	UnosP(&head, p);
	Ispis(&head);

	return EXIT_SUCCESS;
}

ljud Stvori(char* ime, char*prezime, int godina) {
	ljud p = NULL;
	p = (ljud)malloc(sizeof(Osoba));
	if (!p)
	{
		printf("alokacija je neuspjesna :( \n");
		return NULL;

	}
	strcpy(p->ime,ime);
	strcpy(p->prezime, prezime);
	p->godina=godina;
	return p;
}

void UnosP(ljud head, ljud p)
{
	p->next = head->next;
	head->next = p;
}

void Ispis(ljud x)
{
	/*ljud p = NULL;
	ljud q = NULL;
	p = head->next;

	while (p != NULL) {
		q = p->next;
		printf("%s\t %s\t %d\n", p->ime,p->prezime,p->godina);
		p = q;
	}*/
	while (x != NULL)
	{
		printf("%s %s %d", x->ime, x->prezime, x->godina);
		x = x->next;
	}

	
}