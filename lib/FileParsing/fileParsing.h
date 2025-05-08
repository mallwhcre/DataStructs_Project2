#ifndef FILE_PARSING_
#define FILE_PARSING_

#include <stdlib.h>
#include <stdio.h>

#define MAX_ENTRIES 50000
#define MAX_LINELEN 5000

typedef struct Date
{
    int day;
    int month;
    int year;

} Date;

typedef struct Record
{
    char timestamp[24];
    int value;
    Date date;

} Record;

void readFile(Record *rec, FILE *f, int *recIndex);
int dayAvg(Record *rec, int *recIndex);     // calculates the average temp of a day
void splitDate(Record *rec, int *recIndex); // splits the dates

#endif