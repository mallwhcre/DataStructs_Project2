#include <stdlib.h>
#include <stdio.h>

#include "avlTree.h"
#include "fileParsing.h"

#define MAX_ENTRIES 50000
#define MAX_LINELEN 5000

int main()
{

    FILE *temps;
    temps = fopen("../testfiles/test2.txt", "r");

    int rec_index_temp = 0;

    if (temps == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    else
    {
        printf("File opened successfully\n");
    }
    Record rec[MAX_ENTRIES];

    readFile(rec, &rec_index_temp, temps);

    // for (int i = 0; i < rec_index_temp; i++)
    // {
    //     splitDate(rec, i);
    //     printf("%d/%d/%d\n", rec[i].date.day, rec[i].date.month, rec[i].date.year);
    // }

    // printf("Number of records: %d\n", rec_index_temp);
    // printf("First record: %s %d\n", rec[0].timestamp, rec[0].value);

    printf("The date is: %d/%d/%d\n", rec[0].date.day, rec[0].date.month, rec[0].date.year);

    for (int i = 0; i < rec_index_temp; i++)
    {
        printf("Record %d: %s = %d\n", i, rec[i].timestamp, rec[i].value);
    }
        
    printf("\n\n");

    avl_node *root_node = NULL;

    root_node = insertDataToAVL(root_node, rec, rec_index_temp);

    showPreOrder(root_node);

    Date date = {.day = 15, .month = 2, .year = 2014};
    // root_node = deleteNode(root_node, date);

    printf("\n\n");

    // showPreOrder(root_node);

    // int temp = searchAVL(root_node, date);

    // printf("Temperature is %d", temp);

    editNode(root_node, date, 69);

    showPreOrder(root_node);
    return 0;
}
