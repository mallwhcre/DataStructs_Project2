#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashTable.h"
#include "commonTypes.h"

int hash(Date date)
{

  int hashValue = 0;
  char val[8];

  sprintf(val, "%d%d%d", date.year, date.month, date.day);

  for (int i = 0; i < strlen(val); i++)
  {
    hashValue += (int)val[i];
  }

  return hashValue % TABLE_SIZE;
}

hashTable *createHashTable()
{
  hashTable *table = (hashTable *)malloc(sizeof(hashTable));
  if (table == NULL)
  {
    printf("Memory allocation failed\n");
    return 0;
  }

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    table->buckets[i] = NULL;
  }

  return table;
}

void insertRecord(hashTable *table, Record *rec, int *recIndex)
{ 
  Date dateToHash = rec[*recIndex].date;
  int hashValue = hash(dateToHash);
  hashNode *newNode = (hashNode *)malloc(sizeof(hashNode));

  newNode->record = rec[*recIndex];
  newNode->hashValue = hashValue;
  newNode->next = table->buckets[hashValue];

  table->buckets[hashValue] = newNode;
}
void insertDataToHashTable(hashTable *table, Record *rec, int *recIndex)
{
  for (int i = 0; i < *recIndex; i++)
  {
    insertRecord(table, rec, &i);
  }
}
void dumpHashTable(hashTable *table)
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    hashNode *current = table->buckets[i];
    if (current != NULL)
    {
      printf("Bucket %d:\n", i);
      while (current != NULL)
      {
        printf("\t%d-%d-%d : %dC\n", current->record.date.year, current->record.date.month, current->record.date.day, current->record.value);
        current = current->next;
      }
    }
  }
}

int searchHash(hashTable *table,Date date_to_search)
{
  int hashValue = hash(date_to_search);
  hashNode *current = table->buckets[hashValue];
  
  while (current != NULL)
  {
    if (dateIsEqual(current->record.date, date_to_search))
    {
     return current->record.value;
    }
    current = current->next;
  }

  return 0;
}
void editHashNode(hashTable *table, Date date_to_edit, int newVal){

  int hashValue =hash(date_to_edit);
  hashNode *current= table->buckets[hashValue];

  while (current != NULL)
  {
    if (dateIsEqual(current -> record.date, date_to_edit))
    {
      current->record.value= newVal;
    }
    current=current->next;
  }

}

void deleteHashNode(hashTable *table, Date date_to_delete){
  int hashValue=hash(date_to_delete);
  hashNode *current=table->buckets[hashValue];
  hashNode *previous=NULL;

  while (current!=NULL){
    if (dateIsEqual(current->record.date, date_to_delete)){
       if (previous==NULL)
       {
        table->buckets[hashValue]=current->next; //if date is the head of the bucket point to the next bucket 
       }
       else {
        previous->next=current->next; //else link the previous node to the next node after the current 
       }

       free(current);

    }

    previous=current;
    current= current->next;
  }
}
