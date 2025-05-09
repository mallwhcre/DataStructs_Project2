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

static avl_node *insertNode(avl_node *node, Record rec)
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

/******************** PUBLIC **********************/

void showPreOrder(avl_node *root_node)
{
    if (root_node != NULL)
    {
        printf("\t%d/%d/%d\t", root_node->record.date.day, root_node->record.date.month, root_node->record.date.year);
        showPreOrder(root_node->left);
        showPreOrder(root_node->right);
    }
}

avl_node *insertDataToAVL(avl_node *root_node, Record *rec, int num_of_records)
{
    for (int i = 0; i < num_of_records; i++)
    {
        root_node = insertNode(root_node, rec[i]);
    }

    return root_node;
}
