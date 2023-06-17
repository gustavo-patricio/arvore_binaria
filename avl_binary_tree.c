#include <stdio.h>
#include "avl_binary_tree.h"
#include <stdlib.h>
#include <string.h>

/*retorna a altura maxima entre subarvore_esquerda ou subarvore direita*/
int max(int height_left, int height_right);
/*pega a altura de um no da arvore*/
int get_height(NO *node_tree);

/*rotação simples para a direita*/
NO *right_rotation(NO *node_not_balanced);
/*rotação simples para a esquerda*/
NO *left_rotation(NO *node_not_balanced);

NO *make_tree()
{
    return NULL;
}

NO *create_node(int info)
{
    NO *new = (NO *)malloc(sizeof(NO));
    if (new == NULL)
    {
        printf("unallocated memory");
        exit(1);
    }
    new->info = info;
    new->left = NULL;
    new->right = NULL;
    new->father = NULL;
    new->height = 0;

    return new;
}

void operation_tree_by_txt(void *file_in)
{
    FILE *file = (FILE *)file_in;
    NO *root = make_tree();
    int data;
    char operator[2];

    while (fscanf(file, "%s%d", operator, &data) != EOF)
    {
        switch (operator[0])
        {
        case '+':
            root = insert(root, data);
            printf("0\n");
            break;
        case '-':
            root = delete (root, data);
            printf("0\n");
            break;
        case '=':
            switch (data)
            {
                case 1:
                    printf("em ordem - ");
                    in_order(root);
                    printf("\n0\n");
                    break;
                case 2:
                    printf("pre ordem - ");
                    pre_order(root);
                    printf("\n0\n");
                    break;
                case 3:
                    printf("pos ordem - ");
                    last_order(root);
                    printf("\n0\n");
                default:
                    break;
            }
        default:
            break;
        }
    }
}

NO *creat_tree_by_txt(void *file_in)
{
    FILE *file = (FILE *)file_in;
    NO *root = make_tree();
    int data;

    while (fscanf(file_in, "%d", &data) != EOF)
    {
        root = insert(root, data);
        printf("0\n");
    }
    return root;
}

NO *left_rotation(NO *node_not_balanced)
{
    NO *y = node_not_balanced->right;
    NO *T2 = y->left;

    y->left = node_not_balanced;
    node_not_balanced->right = T2;

    node_not_balanced->height = 1 + max(get_height(node_not_balanced->left), get_height(node_not_balanced->right));
    y->height = 1 + max(get_height(y->left), get_height(y->right));
    return y;
}

NO *right_rotation(NO *node_not_balanced)
{
    NO *x = node_not_balanced->left;
    NO *T2 = x->right;

    x->right = node_not_balanced;
    node_not_balanced->left = T2;

    node_not_balanced->height = 1 + max(get_height(node_not_balanced->left), get_height(node_not_balanced->right));
    x->height = 1 + max(get_height(x->left), get_height(x->right));

    return x;
}

NO *insert(NO *root_node, int info)
{
    if (root_node == NULL)
    {
        root_node = create_node(info);
        return root_node;
    }
    else if (info == root_node->info)
    {
        printf("E\n");
        return root_node;
    }
    else if (info > root_node->info)
    {
        root_node->right = insert(root_node->right, info);
        root_node->right->father = root_node;
    }
    else
    {
        root_node->left = insert(root_node->left, info);
        root_node->left->father = root_node;
    }
    // altera a altura do nó
    root_node->height = (max(get_height(root_node->left), get_height(root_node->right)) + 1);

    // //Balanceamento

    int balancing_factor = root_node == NULL ? 0 : (get_height(root_node->left) - get_height(root_node->right));

    if (balancing_factor < -1 && info > root_node->right->info)
    {
        return left_rotation(root_node);
    }
    if (balancing_factor > 1 && info < root_node->left->info)
    {
        return right_rotation(root_node);
    }
    if (balancing_factor > 1 && info > root_node->left->info)
    {
        root_node->left = left_rotation(root_node->left);
        return right_rotation(root_node);
    }
    if (balancing_factor < -1 && info < root_node->right->info)
    {
        root_node->right = right_rotation(root_node->right);
        return left_rotation(root_node);
    }

    return root_node;
}
NO *delete(NO *root_node, int search_key)
{
    if(root_node == NULL)
    {
        printf("E\n");
        return root_node;
    }else{
        if (root_node->info == search_key)
        {
            if (!root_node->left && !root_node->right)
            {
                free(root_node);
                return NULL;
            }
            else if (root_node->right && !root_node->left)
            {
                NO *aux = root_node->right;
                free(root_node);
                return aux;
            }
            else if (root_node->left && !root_node->right)
            {
                NO *aux = root_node->left;
                free(root_node);
                return aux;
            }
            else
            {
                NO *subestituto = root_node->right;
                while (subestituto->left)
                {
                    subestituto = subestituto->left;
                }
                if (subestituto->father != NULL)
                {
                    subestituto->father->left = NULL;
                    subestituto->right = root_node->right;
                }
                subestituto->left = root_node->left;
                free(root_node);
                return subestituto;
            }
        }
        else if (search_key > root_node->info)
        {
            root_node->right = delete (root_node->right, search_key);
        }
        else
        {
            root_node->left = delete (root_node->left, search_key);
        }
        return root_node;
    }
}

NO *all_delete(NO *root_node)
{
    if (root_node == NULL)
        return NULL;
    all_delete(root_node->left);
    all_delete(root_node->right);
    free(root_node);
}

void pre_order(NO *root_node)
{
    if (root_node == NULL){
        return;
    }
    printf("%d ", root_node->info);
    pre_order(root_node->left);
    pre_order(root_node->right);
}

void in_order(NO *root_node)
{
    if (root_node == NULL){
        return;
    }
    pre_order(root_node->left);
    printf("%d ", root_node->info);
    pre_order(root_node->right);
}

void last_order(NO *root_node)
{
    if (root_node == NULL){
        return;
    }
    pre_order(root_node->left);
    printf("%d ", root_node->info);
    pre_order(root_node->right);
}

void table_nodes(NO *root_node)
{
    if (root_node == NULL)
        return;
    table_nodes(root_node->left);
    printf("value: %d\t height: %d no: %p\t esq: %p\tdir: %p\t\n", root_node->info, root_node->height, root_node, root_node->left, root_node->right);
    table_nodes(root_node->right);
}

int max(int height_left, int height_right)
{
    return height_left > height_right ? height_left : height_right;
}

int get_height(NO *node_tree)
{
    if (node_tree == NULL)
    {
        return -1;
    }
    return node_tree->height;
}
