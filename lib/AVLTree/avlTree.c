#include "avlTree.h"

#include <stdlib.h>
#include <stdio.h>

/******************** PRIVATE **********************/

static int height(avl_node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return node->height;
}

static int max(int a, int b)
{
    int max_val;

    if (a > b)
    {
        max_val = a;
    }

    else
    {
        max_val = b;
    }

    return max_val;
}

static avl_node *newAvlNode(Record rec)
{
    avl_node *node = (avl_node *)malloc(sizeof(avl_node));

    node->record = rec;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

static avl_node *rotateRight(avl_node *node)
{
    avl_node *node_left = node->left;
    avl_node *sub_node_left = node_left->right;

    node_left->right = node;
    node->left = sub_node_left;

    node->height = max(height(node->left), height(node->right)) + 1;
    node_left->height = max(height(node_left->left), height(node_left->right)) + 1;

    return node_left;
}

static avl_node *rotateLeft(avl_node *node)
{
    avl_node *node_right = node->right;
    avl_node *sub_node_right = node_right->left;

    node_right->left = node;
    node->right = sub_node_right;

    node->height = max(height(node->left), height(node->right)) + 1;
    node_right->height = max(height(node_right->left), height(node_right->right)) + 1;

    return node_right;
}

static int nodeBalance(avl_node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return height(node->left) - height(node->right);
}

static avl_node *minValueNode(avl_node *node)
{
    avl_node *current = node;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

static void showInOrder(avl_node *root_node)
{
    if (root_node != NULL)
    {
        showInOrder(root_node->left);
        printf("\t%d-%d-%d : %dC\t", root_node->record.date.year, root_node->record.date.month, root_node->record.date.day, root_node->record.value);
        showInOrder(root_node->right);
    }
}

/******************** PUBLIC **********************/

void editNode(avl_node *root_node, Date date_to_edit, int new_temp)
{
    if (root_node == NULL)
    {
        return;
    }

    else if (dateIsEqual(root_node->record.date, date_to_edit))
    {
        root_node->record.value = new_temp;
    }

    else if (dateIsGreater(root_node->record.date, date_to_edit))
    {
        editNode(root_node->left, date_to_edit, new_temp);
    }

    else
    {
        editNode(root_node->right, date_to_edit, new_temp);
    }
}

int searchAVL(avl_node *root_node, Date date)
{
    if (root_node == NULL)
    {
        return 0;
    }

    else if (dateIsEqual(root_node->record.date, date))
    {
        return root_node->record.value;
    }

    else if (dateIsGreater(root_node->record.date, date))
    {
        return searchAVL(root_node->left, date);
    }

    else
    {
        return searchAVL(root_node->right, date);
    }
}

avl_node *insertNode(avl_node *node, Record rec)
{
    if (node == NULL)
    {
        return newAvlNode(rec);
    }

    if (dateIsGreater(node->record.date, rec.date)) // key < node key
    {
        node->left = insertNode(node->left, rec);
    }

    else if (dateIsGreater(rec.date, node->record.date))
    {
        node->right = insertNode(node->right, rec);
    }

    else // AVL should not have equal
    {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = nodeBalance(node);

    if (balance > 1 && dateIsGreater(node->left->record.date, rec.date))
    {
        return rotateRight(node);
    }

    if (balance < -1 && dateIsGreater(rec.date, node->right->record.date))
    {
        return rotateLeft(node);
    }

    if (balance > 1 && dateIsGreater(rec.date, node->left->record.date))
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && dateIsGreater(node->right->record.date, rec.date))
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

avl_node *deleteNode(avl_node *root_node, Date key)
{
    if (root_node == NULL)
    {
        return root_node;
    }

    if (dateIsGreater(root_node->record.date, key))
    {
        root_node->left = deleteNode(root_node->left, key);
    }

    else if (dateIsGreater(key, root_node->record.date))
    {
        root_node->right = deleteNode(root_node->right, key);
    }

    else
    {
        if ((root_node->left == NULL) || (root_node->right == NULL))
        {
            avl_node *temp;

            if (root_node->left)
            {
                temp = root_node->left;
            }

            else
            {
                temp = root_node->right;
            }

            if (temp == NULL)
            {
                temp = root_node;
                root_node = NULL;
            }

            else
            {
                *root_node = *temp;
            }

            free(temp);
        }

        else
        {
            avl_node *temp = minValueNode(root_node->right);

            root_node->record = temp->record;

            root_node->right = deleteNode(root_node->right, temp->record.date);
        }
    }

    if (root_node == NULL)
    {
        return root_node;
    }

    root_node->height = max(height(root_node->left), height(root_node->right)) + 1;

    int balance = nodeBalance(root_node);

    if (balance > 1 && nodeBalance(root_node->left) >= 0)
    {
        return rotateRight(root_node);
    }

    if (balance > 1 && nodeBalance(root_node->left) < 0)
    {
        root_node->left = rotateLeft(root_node->left);
        return rotateRight(root_node);
    }

    if (balance < -1 && nodeBalance(root_node->right) <= 0)
    {
        return rotateLeft(root_node);
    }

    if (balance < -1 && nodeBalance(root_node->right) > 0)
    {
        root_node->right = rotateRight(root_node->right);
        return rotateLeft(root_node);
    }

    return root_node;
}

void showPreOrder(avl_node *root_node)
{
    if (root_node != NULL)
    {
        printf("\t%d-%d-%d : %dC\t", root_node->record.date.day, root_node->record.date.month, root_node->record.date.year, root_node->record.value);
        showPreOrder(root_node->left);
        showPreOrder(root_node->right);
    }
}

void finalDisplay(avl_node *root_node)
{
    printf("\n-----------------------------------------\n");
    printf("| Date (YYYY-MM-DD) | Temperature (C) |\n");
    printf("-----------------------------------------\n");

    showInOrder(root_node);

    printf("-----------------------------------------\n\n");
}

avl_node *insertDataToAVL(avl_node *root_node, Record *rec, int num_of_records)
{
    for (int i = 0; i < num_of_records; i++)
    {
        root_node = insertNode(root_node, rec[i]);
    }

    return root_node;
}

/******************AVG TEMP BASED IMPLEMENTATION******************/

avl_node *insertTempNode(avl_node *node, Record rec)
{
    if (node == NULL)
    {
        return newAvlNode(rec);
    }

    if (rec.value < node->record.value) // key < node key
    {
        node->left = insertTempNode(node->left, rec);
    }

    else if (rec.value > node->record.value)
    {
        node->right = insertTempNode(node->right, rec);
    }

    else // AVL should not have equal
    {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = nodeBalance(node);

    if (balance > 1 && rec.value < node->left->record.value)
    {
        return rotateRight(node);
    }

    if (balance < -1 && rec.value > node->right->record.value)
    {
        return rotateLeft(node);
    }

    if (balance > 1 && rec.value < node->left->record.value)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && rec.value > node->right->record.value)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
avl_node *insertTempDataToAVL(avl_node *root_node, Record *rec, int num_of_records)
{
    for (int i = 0; i < num_of_records; i++)
    {
        root_node = insertTempNode(root_node, rec[i]);
    }

    return root_node;
}

/******************max & min functions*****************/

int findMinTemp(avl_node *root_node)
{

    if (root_node == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }

    while (root_node->left != NULL)
    {
        root_node = root_node->left;
    }

    return root_node->record.value;
}

int findMaxTemp(avl_node *root_node)
{

    if (root_node == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }

    while (root_node->right != NULL)
    {
        root_node = root_node->right;
    }

    return root_node->record.value;
}

void minDates(int min_temp, Record *rec, int recIndex){



    if (recIndex == 0)
    {
        return;
    }

    if (rec[recIndex - 1].value == min_temp)
    {
        printf("\t%d-%d-%d\t", rec[recIndex - 1].date.year, rec[recIndex - 1].date.month, rec[recIndex - 1].date.day);
    }

    minDates(min_temp, rec, recIndex - 1);

}

void maxDates(int max_temp,Record *rec, int recIndex)
{
    if (recIndex == 0)
    {
        return;
    }

    if (rec[recIndex - 1].value == max_temp)
    {
        printf("\t%d-%d-%d\t", rec[recIndex - 1].date.year, rec[recIndex - 1].date.month, rec[recIndex - 1].date.day);
    }

    maxDates(max_temp, rec, recIndex - 1);
}