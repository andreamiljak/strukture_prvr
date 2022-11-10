#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define EXIT_SUCCESS 0
#define ERROR (-1)
#define MAX (1024)

struct poli;
typedef struct poli* pozicija;
typedef struct poli {
	int koef;
	int eksp;

	pozicija next;
}Polinom;

int StvoriPoli(int,int);
int Sortiraj(pozicija, pozicija);
int Unos(pozicija, pozicija);
int Brisi(pozicija);
int ZbrojPoli();

int main(void)
{
	Polinom head = {
		.koef = 0,
		.eksp = 0,
		.next=NULL
	};
	int c, e, n = 0;
	char buffer[MAX] = { 0 };
	char* p = buffer;

	pozicija z = NULL;
	z = (pozicija)malloc(sizeof(Polinom));
	
	FILE* fp = NULL;
	fp = fopen("polinom.txt", "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return ERROR;
	}

	while (!feof(fp))
	{
		
		fgets(p, MAX, fp);
		printf(p);
		printf("\n");
		while (strlen(p) > 0)
		{
			sscanf(p, "%d %d %n", &c, &e, &n);
			p += n;
			printf("%d %d \n", c, e);
			z=StvoriPoli(c, e);
			Sortiraj(&head, z);
		}
		
		n = 0;
	}
	
	return EXIT_SUCCESS;
}


int StvoriPoli(int k, int e)
{
	pozicija novi = NULL;
	novi = (pozicija)malloc(sizeof(Polinom));
	
	novi->koef = k;
	novi->eksp = e;
	novi->next = NULL;

	return novi;

}

int Sortiraj(pozicija p, pozicija novi)
{
	pozicija prvi = p;
	pozicija drugi = novi;
	int n = 0;


	while (prvi->next != NULL && prvi->next->eksp > drugi->eksp)
		prvi = prvi->next;

	if (prvi->next != NULL && prvi->next->eksp == drugi->eksp)
	{
		prvi->next->koef += drugi->koef;							
		n = prvi->next->koef;

		if (n == 0)
			Brisi(prvi);
	}

	else
	{
		Unos(prvi, drugi);
	}




		return EXIT_SUCCESS;

}

int Unos(pozicija p, pozicija novi)
{
	novi->next = p->next;
	p->next = novi;

	return EXIT_SUCCESS;


}

int Brisi(pozicija p)
{
	pozicija prvi = p;
	pozicija drugi = NULL;

	drugi = (pozicija)malloc(sizeof(Polinom));

	while (prvi->next != NULL)
	{
		if (prvi->next->koef == 0)
		{
			drugi = prvi->next;
			prvi->next = drugi->next;
			free(drugi);
		}
		else
			prvi = prvi->next;

	}
	return EXIT_SUCCESS;
}