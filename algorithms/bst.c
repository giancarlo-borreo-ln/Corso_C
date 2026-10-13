#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *left, *right;
};
/* Add a new node if root is NULL returns the new root
 * (the first inserted node) otherwise it just returns
 * the root passedb y the user in input
 * */
struct node *add(struct node *root, int val){
    struct node *saved_root = root;
    struct node *new = malloc(sizeof(*new)); 
    // We don't check for malloc() failures since this is 
    // a trivial example.
    
    new -> left = new -> right = NULL;
    new -> val = val;
    if(root == NULL) return new;

    while(1){
        if(val >= root -> val){
            if(root -> right == NULL) {
                root -> right = new;
                return saved_root;
            }   
            root = root -> right;
        }else{
            if(root -> left == NULL){
                root -> left = new;
                return saved_root;
            } 
            root = root -> left;
        }
    }
}

void print_sorted(struct node *root){
    if(root == NULL) return;
    print_sorted(root->left);
    printf("%d\n", root ->val);
    print_sorted(root->right);
}

void free_tree(struct node *root){
    if(root == NULL) return;

    free_tree(root -> right);
    free_tree(root -> left);

    free(root);
}

int main(void){
    struct node *root = NULL;

    root = add(root, 10);
    root = add(root, 5);
    root = add(root, 20);
    root = add(root, 100);
    root = add(root, 40);
    root = add(root, 33);
    print_sorted(root);
    free_tree(root);
    return 0;
}
