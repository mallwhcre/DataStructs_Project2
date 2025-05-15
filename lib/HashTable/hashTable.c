#include <stdlib.h>
#include <stdio.h>

#include "commonTypes.h"

#define TABLE_SIZE 50000


int hash(Record *rec){

    int hashValue=0;

    int year=rec->date.year;
    int month=rec->date.month;
    int day=rec->date.day;

    char val[24];

    *val=itoa(year);
    *val += itoa(month);
    *val += itoa(day);

    for(int i=0; i<strlen(val); i++){
        hashValue += ASCII(val[i]);
    }

    return hashValue % TABLE_SIZE;

}