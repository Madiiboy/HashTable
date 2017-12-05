#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*Hjalpfunktion till add
  Allokerar minne for en ny nod
  om allokeringen lyckades initieras data samt pekare (pekare initieras till NULL).
  Den nya noden (eller NULL) returneras.*/
static struct node* createListNode(const Data data)
{

	List listNode = malloc(sizeof(struct node));
	if (listNode == NULL)
	{
		printf("Failed to allocate memory\n");
		return NULL;
	}
	listNode->data = data;
	listNode->next = NULL;

	return listNode;

    //Glom inte att testa sa att allokeringen lyckades innan du initierar noden
   
}

/*Returnera en tom lista - funktionen ar fardig*/
List createEmptyList(void)
{
    return NULL;
}


/*Ar listan tom?
  Returnerar 1 om den Šr tom, annars 0*/
int isEmpty(const List list)
{
	if (list == NULL)
	{
		return 1;
	}
	else
		return 0; 
}

/*Lagg till nod forst i listan
  Precondition: Det nya datat ligger forst i listan (testa med assert)?????????*/
void addFirst(List *list, const Data data)
{
	List newFirst = createListNode(data); //allokerar minne till en ny nod och returnerar den.
	if (*list == NULL)				  //om den misslyckas att allokera minne returnas null och detta skrivs ut
	{
		*list = newFirst;
		return;
	}

	else						//om listan är tom, dvs att head pekar på null skapas en ny nod. 
	{
		newFirst->next = *list;
		*list = newFirst;					//innehållet i head blir newFirst		
	}
	

	//assert(newFirst->data == data);
    //Anropa createListNode for att skapa den nya noden
    //Glom inte att testa att den nya noden faktiskt kunde skapas/tilldelas minne innan du fortsatter
    //Tank pa att listan kan vara tom nar en ny nod laggs till
}

/*Lagg till nod sist i listan
  Tips, nar du hittat ratt plats kan du anvanda funktionen addFirst for att lagga till*/
void addLast(List *list, const Data data)
{
	if (*list == NULL) {
		addFirst(list, data);
		return;
	}

	if ((*list)->next != NULL)       //rekursion tills den kommer fram till NULL
	{
		addLast(&(*list)->next, data);
	}
	else
	{
		addFirst(&(*list)->next, data);		//lägger till en nod
	}
}

/*Ta bort forsta noden i listan
  Precondition: listan ar inte tom (testa med assert)
  Noden ska lankas ur och minnet frigoras, resten av listan ska finnas kvar*/
void removeFirst(List *list)
{
	assert(*list != NULL);
    //Glom inte att frigora minnet for den nod som lankas ur listan.
	if (*list == NULL)
	{
		return;
	}
	List tempList = NULL;
	tempList = *list;
	*list = (*list)->next;
	free(tempList);
	//tempList = NULL;
    //Tank pa att listans huvud efter bortlankningen maste peka pa den nod som nu ar forst.
}

/*Ta bort sista noden i listan
  Precondition: listan ar inte tom (testa med assert)t*/
void removeLast(List *list)
{
	assert(*list != NULL);
	
	if (*list == NULL)
	{
		return;
	}

	if ((*list)->next == NULL)
	{
		free(*list);
		*list = NULL;
		return;
	}
	List toRemove = *list;
	while (toRemove->next->next != NULL)
	{
		toRemove = toRemove->next;
	}
	free(toRemove->next);
	toRemove->next = NULL;

	/*
	if ((*list)->next->next != NULL)
	{
		removeLast(&(*list)->next);
		
	}
	else
	{
		free((*list)->next);
		(*list)->next = NULL;
	}
	*/
    //Glom inte att frigora minnet for den nod som lankas ur listan.
    //Tank pa att den nod som nu ar sist inte pekar nagonstans, dess pekare maste nollstallas
}

/*Ta bort data ur listan (forsta forekomsten)
  Returnera 1 om datat finns, annars 0
  Tips, nar du hittar ratt nod kan du anvanda en av de ovanstaende funktionerna for att ta bort noden*/
int removeElement(List *list, const Data data)
{
	if ((*list)->data.key == data.key)
	{
		removeFirst(list);
		return 1;
	}
	if ((*list)->next == NULL)
	{
    return 0; //Ersatt med ratt returvarde
	}
	else
	{
		removeElement(&(*list)->next, data);
	}
	
}

/*Finns data i listan?
  Om datat finns returneras 1, annars 0
  Tank pa att listan kan vara tom*/
Value* search(const List list, const Data dataTwo)		
{
	List toFind = list;

	while (toFind != NULL)
	{				//the two data or not the same
		if (toFind->data.key == dataTwo.key) {
			return &toFind->data.value;
		}
		toFind = toFind->next;
	}

	return NULL; 

}

/*Returnera antalet noder i listan*/
int numberOfNodesInList(const List list)
{
	
	if (list == NULL) { 
		return 0;
	}
		return 1 + numberOfNodesInList(list->next);
}

/*Ta bort alla noder ur listan
  Glom inte att frigora minnet
  Postcondition: Listan ar tom, *list Šr NULL (testa med assert)*/
void clearList(List *list)
{

	if ((*list)->next != NULL)
	{
		 clearList(&(*list)->next);
	}
	
	free((*list)->next);
	*list = NULL;
	assert(*list == NULL);
    //Alla noder maste tas avallokeras en och en, det racker inte att endast frigora list.
}

/*Skriv ut listan
  Vid anropet kan man ange stdout som argument 2 for att skriva ut pŒ skarmen.
  Anvanda fprintf for att skriva ut.
  Den har typen av utskriftfunktion blir mer generell da man kan valja att skriva ut till skarmen eller till fil.*/
void printList(const List list, FILE *textfile)
{	
	if (list != NULL)
	{
		fprintf(textfile, "\n%d", list->data);
		printList(list->next, textfile);
    }

}

/*Returnera forsta datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getFirstElement(const List list)			
{
	assert(list != NULL);

	if (list != NULL)
		return list->data;

}

/*Returnera sista datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getLastElement(const List list)						//ej klar
{
	assert(list != NULL);

	if (list->next != NULL)
		getLastElement(list->next);
	else
		return list->data;


    
}
