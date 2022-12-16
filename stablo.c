#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
#define EXIT_SUCCESS 0
#define EXIT_FAIL -1

struct stablo;
typedef struct stablo* pozicijaD;
typedef struct stablo
{
	char ime[MAX];
	pozicijaD child;
	pozicijaD sibling;
}Direktorij;

struct stog;
typedef struct stog* pozicijaS;
typedef struct stog {
	pozicijaD el;
	pozicijaS next;
}Stog;

pozicijaD md(char*, pozicijaD);  //make directory
int PrintMeni();
int push(pozicijaS, pozicijaD);
pozicijaD pop(pozicijaS);
int SortiraniUnos(pozicijaD, pozicijaS);
pozicijaD cd(char*, pozicijaD, pozicijaS);	//change directory
pozicijaD cd_tockatocka(pozicijaS, pozicijaD);			//cd..
pozicijaD dir(pozicijaD);
pozicijaD brisisve(pozicijaD);				// za izlaz

int main(void)
{
	char ime[MAX] = { 0 };
	char odabir[MAX] = { 0 };

	Direktorij root;
	root.child = NULL;
	root.sibling = NULL;
	strcpy(root.ime, "C:");


	Stog head;
	head.next = NULL;
	head.el = NULL;

	push(&head, &root);


	PrintMeni();
	do {
		scanf("%s", odabir);
		if (odabir == "md" || odabir == "MD")
		{
			//printf("unesite ime novog direktorija\n");
			scanf("%s", ime);
			pozicijaD novi = NULL;
			novi = md(ime, &root);
		}
		else if (odabir == "cd dir")
		{

		}
		else if (odabir == "dir" || odabir == "DIR")
		{
			pozicijaD trenutni = pop(&head);
			dir(trenutni);
		}
		else if (odabir == "exit" || odabir == "EXIT")
		{
			brisisve(&root);
		}
	} while (odabir != "exit");
	return 0;
}



pozicijaD md(char* ime_novog_dir, pozicijaD element)

{
	pozicijaD novi_dir;
	novi_dir = (pozicijaD)malloc(sizeof(Direktorij));
	strcpy(novi_dir->ime, ime_novog_dir);
	if (element->child == NULL)
	{
		element->child = novi_dir;
	}
	else
	{
		pozicijaD currChild = (pozicijaD)malloc(sizeof(Direktorij));
		currChild = element->child;

		while (currChild->sibling)
			currChild = currChild->sibling;
		currChild->sibling = novi_dir;
	}
	novi_dir->child = NULL;
	novi_dir->sibling = NULL;

	return element;
}

int PrintMeni()
{
	printf("\n * * * * * * * * * * * * * * * * * * * * *\n\t\tMENI\n Odaberite:\n");
	printf("\tmd  -> za dodavanje novog direktorija\n");
	printf("\tcd dir  -> za otvaranje odredenog direktorija\n");
	printf("\tcd..  -> za povratak u prethodni direktorij\n");
	printf("\tdir  -> pokazuje sav sadrzaj\n");
	printf("\texit  -> za izlaz\n");
	printf("___________________________________________________\n");

	return EXIT_SUCCESS;
}

int push(pozicijaS head, pozicijaD element)
{
	pozicijaS novi = (pozicijaS)malloc(sizeof(Stog));
	if (novi == NULL)
	{
		printf("greska pri alokaciji memorije\n");
		return EXIT_FAIL;
	}
	novi->next = head->next;
	head->next = novi;
	return  EXIT_SUCCESS;
}

pozicijaD pop(pozicijaS head)
{
	pozicijaS temp = head->next;

	if (head->next == NULL)
		return NULL;

	pozicijaD dir = temp->el;
	head->next = temp->next;
	free(temp);
	return dir;
}

pozicijaD cd(char* ime_poddir, pozicijaD element, pozicijaS head)
{
	pozicijaD temp = element->child;
	while (temp != NULL && strcmp(ime_poddir, temp->ime) != 0)
	{
		temp = temp->sibling;
	}
	if (temp == NULL)
	{
		printf("ne postoji direktorij s imenom %s", ime_poddir);
		return element;
	}
	else
	{
		pozicijaS novi = NULL;
		novi->el = element;
		novi->next = NULL;
		push(head, novi);
		return temp;
	}
}

pozicijaD cd_tockatocka(pozicijaS s, pozicijaD d)
{
	pozicijaD element = pop(s);
	if (element == NULL)
	{
		printf("nemate se kamo vratit\n");
		return d;
	}
	return element;
}

pozicijaD dir(pozicijaD glavni_dir)
{
	pozicijaD poddir = glavni_dir->child;
	if (poddir == NULL)
	{
		printf("prazan direktorij\n");
		return NULL;
	}
	else
	{
		while (poddir->sibling != NULL)
		{
			printf("%s\t", poddir->ime);
			poddir = poddir->sibling;
		}
		return NULL;
	}
}
pozicijaD brisisve(pozicijaD current)
{
	if (current == NULL)
		return NULL;
	brisisve(current->sibling);
	brisisve(current->child);
	free(current);
	return NULL;
}