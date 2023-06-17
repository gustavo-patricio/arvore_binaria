#ifndef INCLUDED_AVL
#define INCLUDED_AVL

typedef struct avl_binary_tree
{
    int info;
    int height;
    struct avl_binary_tree *left;
    struct avl_binary_tree *right;
    struct avl_binary_tree *father;
}NO;


/*
inicia o nó raiz com valor NULL
start root node with NULL value*/
NO* make_tree();
/*cria um novo nó para ser inserido na arvore*/
NO* create_node(int info);
/*insere um valor na arvore*/
NO* insert(NO* root_node, int info);
/*cria uma arvore a partir de um txt formatado*/
NO* creat_tree_by_txt(void *file_in);
/*funcao que realiza as operaçoes */
void operation_tree_by_txt(void *file_in);
/*remove um valor da arvore*/
NO* delete(NO* root_node, int search_key);
/*deleta toda a arvore*/
NO* all_delete(NO* root_node);
/*percorre a arvore em pré ordem*/

/*expoe uma tabela de nós da arvore binaria*/
void table_nodes(NO *root_node);
/*percorre a arvore em pre ordem*/
void pre_order(NO* root_node);
/*percorre a arvore em ordem*/
void in_order(NO* root_node);
/*percorre a arvore em pos ordem*/
void last_order(NO* root_node);

int balancing_factor(NO *node_tree);



#endif
