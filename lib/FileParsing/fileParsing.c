#include "fileParsing.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 50000
#define MAX_LINELEN 5000

 void splitDate(Record *rec, int recIndex)
{
    char year[5];
    char month[3];
    char day[3];

    char *timestamp = rec[recIndex].timestamp;
    char *hyphen1 = strchr(timestamp, '-');

    if (hyphen1)
    {
        // Extract year (characters before first hyphen)
        int yearLen = hyphen1 - timestamp;
        if (yearLen > 0 && yearLen < 5)
        {
            strncpy(year, timestamp, yearLen);
            year[yearLen] = '\0';

            char *hyphen2 = strchr(hyphen1 + 1, '-');
            if (hyphen2)
            {
                // Extract month (between first and second hyphen)
                int monthLen = hyphen2 - (hyphen1 + 1);
                if (monthLen > 0 && monthLen < 3)
                {
                    strncpy(month, hyphen1 + 1, monthLen);
                    month[monthLen] = '\0';

                    char *tChar = strchr(hyphen2 + 1, 'T');
                    if (tChar)
                    {
                        // Extract day (between second hyphen and 'T')
                        int dayLen = tChar - (hyphen2 + 1);
                        if (dayLen > 0 && dayLen < 3)
                        {
                            strncpy(day, hyphen2 + 1, dayLen);
                            day[dayLen] = '\0';
                        }
                    }
                    else
                    {
                        // If no 'T' found, assume rest is day
                        strncpy(day, hyphen2 + 1, 2);
                        day[2] = '\0';
                    }
                }
            }
        }
    }

    rec[recIndex].date.day = atoi(day);
    rec[recIndex].date.month = atoi(month);
    rec[recIndex].date.year = atoi(year);
}

void readFile(Record *rec, int *recIndex, FILE *file)
{

    char line[MAX_LINELEN];
    Record rec_buffer[MAX_ENTRIES]; // to store the line each time
    int rec_buffer_index = 0;

    while (fgets(line, sizeof(line), file))
    {
        char *current_pos = line;
        current_pos++; // skip the brace
        int sum_of_line = 0;
        rec_buffer_index = 0;

        while (*current_pos != '}')
        {
            char *openingQ = strchr(current_pos, '"');
            char *closingQ = strchr(openingQ + 1, '"');
            int sizeOf = closingQ - openingQ - 1;
            strncpy(rec_buffer[rec_buffer_index].timestamp, openingQ + 1, sizeOf);
            rec_buffer[rec_buffer_index].timestamp[sizeOf] = '\0'; // null terminate the timestamp
            char *colon = strchr(closingQ, ':');

            openingQ = strchr(colon, '"');
            closingQ = strchr(openingQ + 1, '"');
            sizeOf = closingQ - openingQ - 1;

            char temp[5]; // holds the value
            strncpy(temp, openingQ + 1, sizeOf);
            temp[sizeOf] = '\0';

            rec_buffer[rec_buffer_index].value = atoi(temp);
            sum_of_line += rec_buffer[rec_buffer_index].value;

            current_pos = closingQ + 1;
            rec_buffer_index++;
        }

        rec[*recIndex] = rec_buffer[0];
        rec[*recIndex].value = sum_of_line / rec_buffer_index;
        splitDate(rec, *recIndex);

        // printf("Record %d: %s = %d\n", *recIndex, rec[*recIndex].timestamp, rec[*recIndex].value);

        *recIndex += 1;
    }

    fclose(file);
}

// Placeholder



int dayAvg(Record *rec, int recIndex)
{
    splitDate(rec, recIndex);

    int i = recIndex;

    int keyDay = rec[i].date.day;
    int keyMonth = rec[i].date.month;
    int keyYear = rec[i].date.year;

    int sum = 0;
    int count = 0;

    int sameDay = 1; // 1 if same day 0 if not

    while (sameDay && i < MAX_ENTRIES)
    {
        if (rec[i].date.day == keyDay && rec[i].date.month == keyMonth && rec[i].date.year == keyYear)
        {
            sum += rec[recIndex].value;
            count++;
        }
        else
        {
            sameDay = 0;
        }

        i++;
    }
    int avg = sum / count;

    return avg;
}
