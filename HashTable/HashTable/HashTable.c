#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include "list.h"

#define UNUSED 0	// Anvands for att markera en ledig plats i Hashtabellen


/* Denna funktion tar en nyckel och returnerar ett hash-index
dvs ett index till arrayen som Šr Hashtabellen */
static int hash(Key key, int tablesize)
{
	return key % tablesize; // Ersatt med ett index
}

HashTable createHashTable(unsigned int size)
{
	int i;
	// Dessa tva rader ar bara till for att labskelettet ska kompilera. Ta bort dessa nar du skriver funktionen.

	HashTable htable;
	htable.size = size;
	htable.table = (struct node*)malloc(sizeof(struct node)*size);

	for (i = 0; i < size; i++) 
	{
		htable.table[i] = NULL;
	}

	return htable;

}

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet uppdateras */
void insertElement(HashTable* htable, const Key key, const Value value)
{ 
	int index = hash(key, htable->size);

	Data person;
	person.key = key;
	person.value = value;	//person måste skrivas över till table

	if (htable->table[index] != NULL)
	{
		addFirst(&htable->table[index], person);
	}
	else
	{
		addLast(&htable->table[index], person);
	}
	

	
	// Postcondition: det finns ett element for key i tabellen (anvand lookup() for att verifiera)
}

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key)
{
	int index = hash(key, htable->size);
	if (htable->table[index] != NULL)			//if (htable->table[index]->data.key != NULL)???
	{
		Data toRemove; 
		toRemove.key = key;
		removeElement(&htable->table[index], toRemove);
		htable->size = htable->size - 1;
	}

	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
}

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key)
{
	int index = hash(key, htable->size); //får det hashade värdet i retur.
	Data person;
	person.key = key;
	return search(htable->table[index], person);	//search är en funktion i list.c som rekursivt hittar rätt plats
	
}


/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable)
{
	int size = getSize(htable), index;

	for (index = 0; index < size; index++)
	{
		free((*htable).table[index]);		//frigör alla index som finns

	}
	htable->size = 0;
	// Postcondition: hashtabellen har storlek 0
}

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable)
{
    return htable->size; 
}

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable)
{
	int i;

	for (i = 0; i < htable->size; i++)
	{
		List person = htable->table[i];
		while (person != NULL)
		{
			printPerson(&person->data.value);
			printf("\n");
			person = person->next;
		}
		//skriver ut varje person i listan interaktivt istället för rekursivt
		//här ska funktionen kallas
	}
	// Tips: anvand printPerson() i Person.h for att skriva ut en person
}
