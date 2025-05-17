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

    char val[24];

    *val=itoa(year);
    *val += itoa(month);
    *val += itoa(day);

    for(int i=0; i<strlen(val); i++){
        hashValue += ASCII(val[i]);
    }

    return hashValue % TABLE_SIZE;

}