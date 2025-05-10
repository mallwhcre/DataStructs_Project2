#include <stdlib.h>
#include <stdio.h>

#include "avlTree.h"
#include "fileParsing.h"

#define MAX_ENTRIES 50000
#define MAX_LINELEN 5000

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

    avl_node *root_node = NULL;

    root_node = insertDataToAVL(root_node, rec, rec_index_temp);

    // showPreOrder(root_node);
    ////////////////MENU/////////////////

    printf("SELECTION MENU:\n");

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

            if (searchAVL(root_node, date_to_edit) == 0)
            {
                printf("No record found for the given date.\n");
                break;
            }

            scanf("%d-%d-%d", &date_to_edit.year, &date_to_edit.month, &date_to_edit.day);
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

            if (searchAVL(root_node, date_to_delete) == 0)
            {
                printf("No record found for the given date.\n");
                break;
            }

            scanf("%d-%d-%d", &date_to_delete.year, &date_to_delete.month, &date_to_delete.day);

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
    return 0;
}
