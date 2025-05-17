#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hashTable.h"
#include "commonTypes.h"

#define TABLE_SIZE 50000


int hash(Record *rec, int *recIndex){

    int hashValue=0;

    int year=rec[*recIndex].date.year;
    int month=rec[*recIndex].date.month;
    int day=rec[*recIndex].date.day;

    char val[8];

    sprintf(val, "%d%d%d", year, month, day);

    for(int i=0; i<strlen(val); i++){
        hashValue += (int)val[i];
    }

    return hashValue % TABLE_SIZE;

}