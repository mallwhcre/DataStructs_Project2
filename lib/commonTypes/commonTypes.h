#ifndef COMMON_TYPES_
#define COMMON_TYPES_

#include <stdbool.h>

#define dateIsEqual(date1, date2) ((date1).year == (date2).year && (date1).month == (date2).month && (date1).day == (date2).day)

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

typedef struct Node avl_node;

struct Node
{
    Record record;
    avl_node *left;
    avl_node *right;
    int height;
};

bool dateIsGreater(Date date1, Date date2);

#endif