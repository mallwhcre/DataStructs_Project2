#include <stdlib.h>
#include <stdio.h>

#include "avlTree.h"
#include "fileParsing.h"
#include "hashTable.h"

#define MAX_ENTRIES 50000
#define MAX_LINELEN 5000

void hashMenu(Record *rec, int rec_index_temp);

void avlMenu(Record *rec, int rec_index_temp);
static void dateTree(Record *rec, int rec_index_temp);
static void tempTree(Record *rec, int rec_index_temp);

int main()
{

    FILE *temps;
    temps = fopen("../testfiles/tempm.txt", "r");

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


    for (int i = 0; i < rec_index_temp; i++)
    {
        splitDate(rec, i);
    }

    printf("\n\n");

    printf("CHOOSE A DATA STRUCTURE:\n");
    printf("1. AVL Tree\n");
    printf("2. Hash Table\n");
    printf("3. Exit\n");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:

        avlMenu(rec, rec_index_temp);
        break;
    case 2:

        hashMenu(rec, rec_index_temp);
        break;
    case 3:

        printf("Exiting the program.\n");
        break;
    default:

        printf("Invalid choice, please try again.\n");
        break;
    }
    return 0;
}

void avlMenu(Record *rec, int rec_index_temp)
{
    printf("SELECTION MENU:\n");
    printf("1. Date based Tree Options\n");
    printf("2. Temperature based Tree Options\n");
    printf("3. Exit\n");

    int choice;

    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        dateTree(rec, rec_index_temp);
        break;
    case 2:
        tempTree(rec, rec_index_temp);
        break;
    case 3:
        printf("Exiting the program.\n");
        break;
    default:
        printf("Invalid choice, please try again.\n");
        break;
    }
}

static void dateTree(Record *rec, int rec_index_temp)
{

    avl_node *root_node = NULL;

    root_node = insertDataToAVL(root_node, rec, rec_index_temp);

    printf("TREE SORTED BY DATES MENU:\n");

    int exit = 0;

    while (exit != 1)
    {
        printf("1. Show Tree \n");
        printf("2. Look for Date \n");
        printf("3. Modify Average on a certain date\n");
        printf("4. Delete record form a certain date\n");
        printf("5. Exit\n");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            finalDisplay(root_node);
            printf("Tree displayed successfully.\n");
            break;
        case 2:
            printf("Enter the date to search (yyyy-mm-dd): ");

            Date date_to_search;

            scanf("%d-%d-%d", &date_to_search.year, &date_to_search.month, &date_to_search.day);

            searchAVL(root_node, date_to_search);

            if (searchAVL(root_node, date_to_search) == 0)
            {
                printf("No record found for the given date.\n");

                break;
            }

            printf("Record found: %d/%d/%d : %d\n", date_to_search.day, date_to_search.month, date_to_search.year, searchAVL(root_node, date_to_search));

            break;

        case 3:
            printf("Enter the date to modify (yyyy-mm-dd): ");

            Date date_to_edit;

            scanf("%d-%d-%d", &date_to_edit.year, &date_to_edit.month, &date_to_edit.day);

            while (searchAVL(root_node, date_to_edit) == 0)
            {
                printf("No record found for the given date.\n");
                printf("Please enter a valid date to modify (yyyy-mm-dd): ");

                scanf("%d-%d-%d", &date_to_edit.year, &date_to_edit.month, &date_to_edit.day);

                break;
            }
            printf("Old record: %d/%d/%d : %d\n", date_to_edit.day, date_to_edit.month, date_to_edit.year, searchAVL(root_node, date_to_edit));

            printf("Enter the new temperature average: ");

            int new_temp;
            scanf("%d", &new_temp);

            editNode(root_node, date_to_edit, new_temp);
            printf("Record modified successfully.\n");

            printf("New record: %d/%d/%d : %d\n", date_to_edit.day, date_to_edit.month, date_to_edit.year, searchAVL(root_node, date_to_edit));

            break;
        case 4:
            printf("Enter the date to delete (yyyy-mm-dd): ");

            Date date_to_delete;

            scanf("%d-%d-%d", &date_to_delete.year, &date_to_delete.month, &date_to_delete.day);

            while (searchAVL(root_node, date_to_delete) == 0)
            {
                printf("No record found for the given date.\n");
                printf("Please enter a valid date to delete (yyyy-mm-dd): ");

                scanf("%d-%d-%d", &date_to_delete.year, &date_to_delete.month, &date_to_delete.day);

                break;
            }

            printf("Record to be deleted: %d/%d/%d : %dC\n", date_to_delete.day, date_to_delete.month, date_to_delete.year, searchAVL(root_node, date_to_delete));

            root_node = deleteNode(root_node, date_to_delete);

            printf("Record deleted successfully.\n");

            break;
        case 5:

            printf("Exiting the program.\n");
            exit = 1;

            break;
        default:

            printf("Invalid choice, please try again.\n");
            break;
        }
    }
}

static void tempTree(Record *rec, int rec_index_temp)
{

    avl_node *root_node = NULL;
    root_node = insertTempDataToAVL(root_node, rec, rec_index_temp);

    printf("TREE SORTED BY TEMPS MENU:\n");

    int exit = 0;
    while (exit != 1)
    {
        printf("1. Show Tree \n");
        printf("2. Display days with Max Temperature: \n");
        printf("3. Display days with Min Temperature: \n");
        printf("4. Exit \n");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            finalDisplay(root_node);
            printf("Tree displayed successfully.\n");

            break;
        case 2:

            printf("Max temperature: %d\n", findMaxTemp(root_node));

            printf("Days with max temperature: ");

            maxDates(findMaxTemp(root_node), rec, rec_index_temp);
            printf("\n");

            break;
        case 3:

            printf("Min temperature: %d\n", findMinTemp(root_node));

            printf("Days with min temperature: ");

            minDates(findMinTemp(root_node), rec, rec_index_temp);
            printf("\n");

            break;
        case 4:
            printf("Exiting the program.\n");
            exit = 1;
            break;
        default:
            printf("Invalid choice, please try again.\n");
            break;
        }
    }
}

void hashMenu(Record *rec, int rec_index_temp)
{
    hashTable *table = NULL;
    table = createHashTable();
    insertDataToHashTable(table, rec, &rec_index_temp);


    printf("Hash Table Menu:\n");
    printf("1. Search for average temp of a certain date\n");
    printf("2. Modify average on a certain date\n");
    printf("3. Delete Record of certain date\n");
    printf("4. Display Hash Table\n");
    printf("5. Exit\n");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
       printf("Enter the date to search (yyyy-mm-dd): ");

            Date date_to_search;

            scanf("%d-%d-%d", &date_to_search.year, &date_to_search.month, &date_to_search.day);

            searchHash(table, date_to_search);

            if (searchHash(table, date_to_search) == 0)
            {
                printf("No record found for the given date.\n");

                break;
            }

            printf("Record found: %d/%d/%d : %dC\n", date_to_search.day, date_to_search.month, date_to_search.year,searchHash(table,date_to_search));

            break;
    case 2:
        printf("Modification of record is not implemented yet.\n");

        // Modify record logic
        break;
    case 3:
        printf("Deletion of record is not implemented yet.\n");

        // Delete record logics
        break;
    case 4:
        dumpHashTable(table);
        break;
    case 5:
        printf("Exiting the program.\n");
        break;
    default:
        printf("Invalid choice, please try again.\n");
        break;
    }
}
