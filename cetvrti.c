#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <malloc.h>
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

int UcitajPoli(pozicija, pozicija);
int StvoriPoli(int, int);
int Sortiraj(pozicija, pozicija);
int Unos(pozicija, pozicija);
int Brisi(pozicija);
int Ispis(pozicija);
int ZbrojPoli(pozicija, pozicija, pozicija);
int UmnozakPoli(pozicija, pozicija, pozicija);

int main(void)
{

	
	Polinom head1 = {
		.koef = 0,
		.eksp = 0,
		.next = NULL
	};
	Polinom head2 = {
		.koef = 0,
		.eksp = 0,
		.next = NULL
	};
	Polinom headZbroj = {
		.koef = 0,
		.eksp = 0,
		.next = NULL
	};
	Polinom headUmnozak = {
		.koef = 0,
		.eksp = 0,
		.next = NULL
	};
	
		
	
	//UcitajPoli(&head1, &head2);

	
	printf("prvi polinom:\n");
	Ispis(&head1);
	printf("drugi polinom:\n");
	Ispis(&head2);
	printf("zbroj polinoma:\n");
	Ispis(&headZbroj);
	printf("umnozak polinoma:\n");
	Ispis(&headUmnozak);					//free memoriju

	return EXIT_SUCCESS;
}

int UcitajPoli(pozicija head1, pozicija head2)
{
	int br_red = 1;
	pozicija prvi_pol = NULL;
	prvi_pol = (pozicija)malloc(sizeof(Polinom));
	pozicija drugi_pol = NULL;
	drugi_pol = (pozicija)malloc(sizeof(Polinom));			//provjeri malloca
	int c, e, n = 0;
	char buffer[MAX] = { 0 };
	char* p = buffer;
	FILE* fp = NULL;
	fp = fopen("polinom.txt", "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return ERROR;
	}

	while (!feof(fp))
	{

		fgets(p, MAX, fp);					//dva fgetsa

		while (strlen(p) > 0)
		{
			sscanf(p, "%d %d %n", &c, &e, &n);

			if (br_red == 1 && c != 0)
			{
				prvi_pol = StvoriPoli(c, e);
				Sortiraj(&head1, prvi_pol);
			}
			else if (br_red == 2 && c != 0)
			{
				drugi_pol = StvoriPoli(c, e);		
				Sortiraj(&head2, drugi_pol);
			}
			p =p + n;
		}

		if (br_red == 1)
		{
			Ispis(&head1);
			printf("\n");
		}
			
		
		else if (br_red == 2)
		{
			Ispis(&head2);
			printf("\n");
		}
			
		br_red++;						//ne treba brojač
	}
	return EXIT_SUCCESS;;
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


	while (prvi->next != NULL)						//ne ulazi nam u petlju popravi!!!
	{										//lista prazna nema head.nexta

		
		if (prvi->next != NULL && prvi->next->eksp == drugi->eksp)
		{
			n = prvi->next->koef + drugi->koef;
			if (n == 0)
				Brisi(prvi);
		}

		else if(drugi->eksp > prvi->next->eksp)
		{
			drugi->next = prvi->next;
			prvi->next = drugi;
		}
		prvi = prvi->next;
	}
		
	return EXIT_SUCCESS;

}

int Unos(pozicija p, pozicija novi)			//ovo pozovi negdi
{
	novi->next = p->next;
	p->next = novi;

	return EXIT_SUCCESS;
}

int Brisi(pozicija p)
{
	pozicija head = p;
	pozicija todel = NULL;

	todel = (pozicija)malloc(sizeof(Polinom));

	while (head->next != NULL)
	{
		if (head->next->koef == 0)
		{
			todel = head->next;
			head->next = todel->next;
			free(todel);
		}
		else
			head = head->next;

	}
	return EXIT_SUCCESS;
}

int Ispis(pozicija p)
{
	pozicija q = p->next;
	while (q != NULL)
	{
		printf("%dx^%d", q->koef, q->eksp);
		q = q->next;
	}
	return EXIT_SUCCESS;
}

int ZbrojPoli(pozicija p1, pozicija p2, pozicija s)
{
	pozicija temp = NULL;
	int n = 0;

	if (p1->eksp == p2->eksp)		//fali while petlja  jer mora proc dook jedan od njih nije nula
	{
		if (p1->koef + p2->koef == 0)
		{
			p1 = p1->next;
			p2 = p2->next;
		}
		else
		{
			n = p1->koef + p2->koef;
			temp = StvoriPoli(n, p1->eksp);
			Sortiraj(s, temp);
			p1 = p1->next;
			p2 = p2->next;

		}
	}
	else if (p1->eksp > p2->eksp)
	{
		n = p1->koef;
		temp = StvoriPoli(p1->koef, p1->eksp);
		Sortiraj(s, temp);
		p1 = p1->next;
	}
	else if (p1->eksp < p2->eksp)
	{
		n = p2->koef;
		temp = StvoriPoli(p2->koef, p2->eksp);
		Sortiraj(s, temp);
		p2 = p2->next;
	}
	return EXIT_SUCCESS;
}
int UmnozakPoli(pozicija p1, pozicija p2, pozicija u)
{
	pozicija temp = NULL;
	int k, e = 0;
	while (p1 != NULL)
	{
		while (p2 != NULL)
		{
			k = p1->koef * p2->koef;
			e = p1->eksp + p2->eksp;
			temp = StvoriPoli(k, e);
			Sortiraj(u, temp);

			p2 = p2->next;				//vrati p2 na pocetnu vrijednost
		}
		p1 = p1->next;
	}
	return EXIT_SUCCESS;
}
