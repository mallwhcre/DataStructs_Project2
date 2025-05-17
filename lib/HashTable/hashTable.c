#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashTable.h"
#include "commonTypes.h"

int hash(Record *rec, int *recIndex)
{

  int hashValue = 0;

  int year = rec[*recIndex].date.year;
  int month = rec[*recIndex].date.month;
  int day = rec[*recIndex].date.day;

  char val[8];

  sprintf(val, "%d%d%d", year, month, day);

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
  int hashValue = hash(rec, recIndex);
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