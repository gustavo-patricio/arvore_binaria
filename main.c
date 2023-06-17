#include <stdio.h>
#include "avl_binary_tree.h"
#include <stdlib.h>



int main()
{
    NO *root = make_tree();
    // root = creat_tree_by_txt(stdin);
    operation_tree_by_txt(stdin);
    // pre_order(root);
    all_delete(root);
    return 0;
}