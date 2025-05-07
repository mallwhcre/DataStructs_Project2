#include <stdlib.h>
#include <stdio.h>

#include "avlTree.h"
#include "fileParsing.h"

#define MAX_ENTRIES 50000
#define MAX_LINELEN 5000

typedef struct Date{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
}Date;

typedef struct Record
{
    char timestamp[24];
    int value;
    Date date;
} Record;



int main()
{

    test();

    return 0;
}