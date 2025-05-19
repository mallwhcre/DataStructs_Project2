#ifndef HASH_TABLE_
#define HASH_TABLE_

#include "commonTypes.h"

#define TABLE_SIZE 50024

typedef struct hashNode
{
    Record record;
    int hashValue;
    struct hashNode *next;

} hashNode;

typedef struct hashTable
{
    hashNode *buckets[TABLE_SIZE];

} hashTable;

int hash(Date date); // creates hash values for each rec

hashTable *createHashTable();
void insertRecord(hashTable *table, Record *rec, int *recIndex);
void dumpHashTable(hashTable *table);
void insertDataToHashTable(hashTable *table, Record *rec, int *recIndex);
int searchHash(hashTable *table, Date date_to_search);

#endif