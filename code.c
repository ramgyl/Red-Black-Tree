#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node* left;
    int value;
    struct node* parent;
    char color;
    struct node* right;
} node;

node* NewNode(){
    node *n = (node*)malloc(sizeof(node));
    return n;
}

node* CreateTree(){
    node* r;
    r = (node*)malloc(sizeof(node));
    r->color = 'b';
    r->left = NULL;
    r->right = NULL;
    r->parent = NULL;
    return r;
}

void CreateNil(node** a){
    node* left_nil = NewNode();
    node* right_nil = NewNode();
    left_nil = (node*)malloc(sizeof(node));
    right_nil = (node*)malloc(sizeof(node));
    (*a)->left = left_nil;
    left_nil->left = NULL;
    left_nil->right = NULL;
    left_nil->color = 'b';
    left_nil->parent = *a;
    (*a)->right = right_nil;
    right_nil->left = NULL;
    right_nil->right = NULL;
    right_nil->color = 'b';
    right_nil->parent = *a;
    return;
}

void BlackHeight(node* e){
    int count = 0;
    node* traverse = e;
    while(traverse!=NULL){
        if(traverse->color=='b'){
            count++;
        }
        traverse = traverse->left;
    }
    count--;
    printf("%d ", count);
    return;
}

void left_rotate(node **w, node **c){
    node *u = *w;
    node *temp;
    temp = u->right;
    u->right = temp->left;
    temp->left->parent = u;
    temp->parent = u->parent;
    if(u->parent==NULL){
        *c = temp;
    }
    else if(u==u->parent->left)
        u->parent->left = temp;
    else
        u->parent->right = temp;
    temp->left = u;
    u->parent = temp;
    return;
}
void right_rotate(node **w, node **c){
    node *u=*w;
    node* temp;
    temp = u->left;
    u->left = temp->right;
    temp->right->parent = u;
    temp->parent = u->parent;
    if(u->parent==NULL)
        *c = temp;
    else if(u->parent->right==u)
        u->parent->right = temp;
    else
        u->parent->left = temp;
    u->parent = temp;
    temp->right = u;
    return;
}

void MakeHealthy1(node** d, node** c){
    int flag1 = 1;
    while(flag1){
        if((*d)->parent==NULL){
            (*d)->color = 'b';
            flag1=0;
        }
        else if((*d)->parent->color=='b'){
            flag1=0;
        }
        else if((*d)->parent->parent==NULL){
            (*d)->parent->color = 'b';
            flag1 = 0;
        }
        else if((*d)->parent->parent->left->color=='r' && (*d)->parent->parent->right->color=='r'){
            (*d)->parent->parent->color = 'r';
            (*d)->parent->parent->left->color = 'b';
            (*d)->parent->parent->right->color = 'b';
            *d = (*d)->parent->parent;

        }
        else if((*d)->parent->parent->left->color!=(*d)->parent->parent->right->color && *d==(*d)->parent->right && (*d)->parent==(*d)->parent->parent->left){
            left_rotate(&((*d)->parent), c);
            *d = (*d)->left;
        }
        else if((*d)->parent->parent->left->color!=(*d)->parent->parent->right->color && *d==(*d)->parent->left && (*d)->parent==(*d)->parent->parent->right){
            right_rotate(&((*d)->parent), c);
            *d = (*d)->right;
        }
        else if((*d)->parent->parent->left->color!=(*d)->parent->parent->right->color && *d==(*d)->parent->left && (*d)->parent==(*d)->parent->parent->left){
            (*d)->parent->color = 'b';
            (*d)->parent->parent->color = 'r';
            right_rotate(&((*d)->parent->parent), c);
            flag1 = 0;
        }
        else if((*d)->parent->parent->left->color!=(*d)->parent->parent->right->color && *d==(*d)->parent->right && (*d)->parent==(*d)->parent->parent->right){
            (*d)->parent->color = 'b';
            (*d)->parent->parent->color = 'r';
            left_rotate(&((*d)->parent->parent), c);
            flag1 = 0;
        }
    }
    return;
}

void insert(int b, node** c){
    if((*c)->left==NULL && (*c)->right==NULL){
        (*c)->value = b;
        CreateNil(c);
    }
    else{
        node* d = *c;
        int is_present = 0;
        while((d->left!=NULL || d->right!=NULL) && !is_present){
            if(d->value==b){
                is_present = 1;
            }
            else{
                if(d->value < b){
                    d = d->right;
                }
                else{
                    d = d->left;
                }
            }
        }
        if(!is_present){
            d->value = b;
            d->color = 'r';
            CreateNil(&d);
            MakeHealthy1(&d, c);
        }
    }
    (*c)->color = 'b';
    BlackHeight(*c);
    return;
}

void MakeHealthy2(node** d, node** c){
    int flag2 = 1;
    while(flag2){
        if((*d)->parent==NULL){
            (*d)->color = 'b';
            flag2 = 0;
        }
        else if((*d)->color=='r'){
            (*d)->color = 'b';
            flag2 = 0;
        }
        else if(*d==(*d)->parent->left && (*d)->parent->color=='b' && (*d)->parent->right->color=='r'){
            (*d)->parent->color = 'r';
            (*d)->parent->right->color = 'b';
            left_rotate(&((*d)->parent), c);
        }
        else if((*d)==(*d)->parent->right && (*d)->parent->color=='b' && (*d)->parent->left->color=='r'){
            (*d)->parent->color = 'r';
            (*d)->parent->left->color = 'b';
            right_rotate(&((*d)->parent), c);
        }
        else if((*d)==(*d)->parent->left && (*d)->parent->color=='r' && (*d)->parent->right->color=='b'){
            (*d)->parent->color = 'b';
            (*d)->parent->right->color = 'r';
            flag2 = 0;
        }
        else if(*d==(*d)->parent->right && (*d)->parent->color=='r' && (*d)->parent->left->color=='b'){
            (*d)->parent->color = 'b';
            (*d)->parent->left->color = 'r';
            flag2 = 0;
        }
        else if(*d==(*d)->parent->left && (*d)->parent->color=='b' && (*d)->parent->right->color=='b' && (*d)->parent->right->left->color=='b' && (*d)->parent->right->right->color=='b'){
            (*d)->parent->right->color = 'r';
            *d = (*d)->parent;
        }
        else if(*d==(*d)->parent->right && (*d)->parent->color=='b' && (*d)->parent->left->color=='b' && (*d)->parent->left->left->color=='b' && (*d)->parent->left->right->color=='b'){
            (*d)->parent->left->color ='r';
            *d = (*d)->parent;
        }
        else if(*d==(*d)->parent->left && (*d)->parent->right->color=='b' && (*d)->parent->right->left->color=='r' && (*d)->parent->right->right->color=='b'){
            (*d)->parent->right->color = 'r';
            (*d)->parent->right->left->color = 'b';
            right_rotate(&((*d)->parent->right), c);
        }
        else if(*d==(*d)->parent->right && (*d)->parent->left->color=='b' && (*d)->parent->left->right->color=='r' && (*d)->parent->left->left->color=='b'){
            (*d)->parent->left->color = 'r';
            (*d)->parent->left->right->color = 'b';
            left_rotate(&((*d)->parent->left), c);
        }
        else if(*d==(*d)->parent->left && (*d)->parent->right->color=='b' && (*d)->parent->right->right->color=='r'){
            char temp_color = (*d)->parent->color;
            (*d)->parent->color = 'b';
            (*d)->parent->right->color = temp_color;
            (*d)->parent->right->right->color = 'b';
            left_rotate(&((*d)->parent), c);
            flag2 = 0;
        }
        else if((*d)==(*d)->parent->right && (*d)->parent->left->color=='b' && (*d)->parent->left->left->color=='r'){
            char temp_color = (*d)->parent->color;
            (*d)->parent->color = 'b';
            (*d)->parent->left->color = temp_color;
            (*d)->parent->left->left->color = 'b';
            right_rotate(&((*d)->parent), c);
            flag2 = 0;
        }
    }
    return;
}

void delete(int p, node** q1){
    node* q = *q1;
    node* x = q;
    int is_present = 0;
    while((x->left!=NULL || x->right!=NULL) && !is_present){
        if(x->value==p){
            is_present = 1;
        }
        else{
            if(x->value < p){
                x = x->right;
            }
            else{
                x = x->left;
            }
        }
    }
    if(is_present){
        if(x->right->left!=NULL || x->right->right!=NULL){
            node* y = x;
            y = x->right;
            while(y->left->left!=NULL || y->left->right!=NULL){
                y = y->left;
            }
            x->value = y->value;
            if(y==y->parent->left){
                y->parent->left = y->right;
            }
            else{
                y->parent->right = y->right;
            }
            y->right->parent = y->parent;
            if(y->color=='b'){
                y = y->right;
                MakeHealthy2(&y, &q);
            }
        }
        else{
            if(x==q){
                q = x->left;
                q->parent = NULL;
                q->color = 'b';
            }
            else{
                if(x==x->parent->left){
                    x->parent->left = x->left;
                }
                else{
                    x->parent->right = x->left;
                }
                x->left->parent = x->parent;
                if(x->color=='b'){
                    x = x->left;
                    MakeHealthy2(&x, &q);
                }
            }
        }
        q->color = 'b';
        *q1 = q;
        BlackHeight(q);
    }
    else{
        printf("-1 ");
    }
    return;
}

void search(int f, node* g){
    node* h = g;
    int is_present = 0;
    while((h->left!=NULL || h->right!=NULL) && !is_present){
        if(f==h->value){
            is_present = 1;
        }
        else{
            if(h->value < f){
                h = h->right;
            }
            else{
                h = h->left;
            }
        }
    }
    if(is_present){
        printf("%c,", h->color);
        BlackHeight(h);
    }
    else{
        printf("-1,-1 ");
    }
    return;
}

int main() {
    node* root;
    root = CreateTree();
    int n1, n2, n3;
    scanf("%d\n", &n1);
    for(int i=0; i<n1; i++){
        int m1;
        scanf("%d ", &m1);
        insert(m1, &root);
    }
    printf("\n");
    scanf("\n%d\n", &n2);
    for(int j=0; j<n2; j++){
        int m2;
        scanf("%d ", &m2);
        delete(m2, &root);
    }
    printf("\n");
    scanf("\n%d\n", &n3);
    for(int k=0; k<n3; k++){
        int m3;
        scanf("%d ", &m3);
        search(m3, root);
    }
    return 0;
}
