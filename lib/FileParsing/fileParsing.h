#ifndef FILE_PARSING_
#define FILE_PARSING_

#include <stdbool.h>
#include <stdio.h>
#include "commonTypes.h"


void readFile(Record *rec, int *recIndex, FILE *file);
int dayAvg(Record *rec, int recIndex);     // calculates the average temp of a day
void splitDate(Record *rec, int recIndex); // splits the date from the timestamp

#endif