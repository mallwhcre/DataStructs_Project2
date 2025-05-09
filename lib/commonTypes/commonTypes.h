#ifndef COMMON_TYPES_
#define COMMON_TYPES_

#include <stdbool.h>

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