#ifndef AVL_TREE_
#define AVL_TREE_

#include "commonTypes.h"

void showPreOrder(avl_node *root_node);

avl_node *insertDataToAVL(avl_node *root_node, Record *rec, int num_of_records);
avl_node *deleteNode(avl_node *root_node, Date key);
avl_node *insertNode(avl_node *node, Record rec);
avl_node *insertTempDataToAVL(avl_node *root_node, Record *rec, int num_of_records);
avl_node *insertTempNode(avl_node *node, Record rec);

int findMinTemp(avl_node *root_node);
int findMaxTemp(avl_node *root_node);

void maxDates(int max_temp, Record *rec, int recIndex);
void minDates(int min_temp, Record *rec, int recIndex);


int searchAVL(avl_node *root_node, Date date);
void editNode(avl_node *root_node, Date date_to_edit, int new_temp);

void finalDisplay(avl_node *root_node);

#endif