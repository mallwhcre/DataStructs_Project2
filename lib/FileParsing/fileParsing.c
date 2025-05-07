#include "fileParsing.h"

#include <stdio.h>

/*int test()
{
    printf("test");
}*/

void readFile(Record *rec, FILE *f, int *recIndex)
{
    char line[MAX_LINELEN];

    while (fgets(line, sizeof(line), f) != NULL && *recIndex < MAX_ENTRIES)
    {
        char *current_pos = line; // pos in the line

        // find opening brace
        while (*current_pos && *current_pos != '{')
            current_pos++;
        current_pos++; // skip brace

        while (*current_pos && *current_pos != '}')
        {
            if (*current_pos == '\0' || *current_pos == '}')
                break;

            // timestamp
            char *openingQ = strchr(current_pos, '"');
            if (!openingQ)
                break;

            char *closingQ = strchr(openingQ + 1, '"');
            if (!closingQ)
                break;

            int sizeOf = closingQ - openingQ - 1;

            strncpy(rec[*recIndex].timestamp, openingQ + 1, sizeOf);

            rec[*recIndex].timestamp[sizeOf] = '\0'; // null terminate the timestamp

            // value
            char *colon = strchr(closingQ, ':');
            if (!colon)
                break;

            // Find value
            openingQ = strchr(colon, '"');
            if (!openingQ)
                break;

            closingQ = strchr(openingQ + 1, '"');
            if (!closingQ)
                break;

            sizeOf = closingQ - openingQ - 1;

            char temp[5]; // holds the value
            strncpy(temp, openingQ + 1, sizeOf);
            temp[sizeOf] = '\0';

            rec[*recIndex].value = atof(temp);

            // next pair
            current_pos = closingQ + 1;
            *recIndex += 1;

            if (*recIndex >= MAX_ENTRIES)
                break;
        }
    }

    fclose(f);
}

void dayAvg(Record *rec,int *recIndex){
    int i = 0;
    int sum = 0;
    int count = 0;
    int day = rec[0].date.day;
    int month = rec[0].date.month;
    int year = rec[0].date.year;

    for (i = 0; i < *recIndex; i++)
    {
        if (rec[i].date.day == day && rec[i].date.month == month && rec[i].date.year == year)
        {
            sum += rec[i].value;
            count++;
        }
        else
        {
            printf("Average for %02d/%02d/%04d: %.2f\n", day, month, year, (float)sum / count);
            day = rec[i].date.day;
            month = rec[i].date.month;
            year = rec[i].date.year;
            sum = rec[i].value;
            count = 1;
        }
    }

    if (count > 0)
    {
        printf("Average for %02d/%02d/%04d: %.2f\n", day, month, year, (float)sum / count);
    }
}
