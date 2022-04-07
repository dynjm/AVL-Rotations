#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;
struct node{
    Node* lson;
    Node* rson;
    int BF;
    int d;
};

void initialize (Node **headptr, int data){
    Node * A;
    A = (Node*)malloc(sizeof(Node));
    A->lson = NULL;
    A->rson = NULL;
    A->BF = 0;
    A->d = data;
    *headptr = A;
}

void print (Node **ptr){
    Node * current;
    current = *ptr;
    if (current!=NULL){
        printf("-%d-", current->d);
        print (&(current->lson));
        print (&(current->rson));
    }
}


void rotate_right (Node **alpha, Node **beta){
    *beta = (*alpha)->lson;
    (*alpha)->lson =(*beta)->rson;
    (*beta)->rson = *alpha;
    (*alpha)->BF = 0;
    (*beta)->BF = 0;
}

void rotate_left (Node **alpha, Node **beta){
    *beta = (*alpha)->rson;
    (*alpha)->rson =(*beta)->lson;
    (*beta)->lson = *alpha;
    (*alpha)->BF = 0;
    (*beta)->BF = 0;
}

void rotate_left_right (Node **alpha, Node **p){
    Node * b;
    b = (*alpha)->lson;
    *p = b->rson;
    b->rson = (*p)->lson;
    (*p)->lson = b;
    (*alpha)->lson = (*p)->rson;
    (*p)->rson = *alpha;
    if ((*p)->BF==0){
        (*alpha)->BF = 0;
        b->BF = 0;
    } else if ((*p)->BF==1){
        (*alpha)->BF = 0;
        b->BF = -1;
    } else if ((*p)->BF==-1){
        (*alpha)->BF = 1;
        b->BF = 0;
    }
    (*p)->BF = 0;
}

void rotate_right_left (Node **alpha, Node **p){
    Node * b;
    b = (*alpha)->rson;
    *p = b->lson;
    b->lson = (*p)->rson;
    (*p)->rson = b;
    (*alpha)->rson = (*p)->lson;
    (*p)->lson = *alpha;
    if ((*p)->BF==0){
        (*alpha)->BF = 0;
        b->BF = 0;
    } else if ((*p)->BF==1){
        (*alpha)->BF = -1;
        b->BF = 0;
    } else if ((*p)->BF==-1){
        (*alpha)->BF = 0;
        b->BF = 1;
    }
    (*p)->BF = 0;
}


void insert (Node **headptr, int data){
    //search for place to insert new node
    Node *zeta, *tau, *v, *alpha, *phi, *beta;
    int w;
    
    alpha = *headptr;
    zeta = *headptr;
    while (1){
        if (zeta->d>data){ //new data is less
            tau = zeta->lson;
            if (tau==NULL){ //current node has no left son
                //insert at left
                v = (Node*)malloc(sizeof(Node)); //allocate memory for new node
                zeta->lson = v;
                break;
            }
        } else if (zeta->d<data) { //new data is more
            tau = zeta->rson;
            if (tau==NULL){ //no right son, insert at right
                v = (Node*)malloc(sizeof(Node)); //allocate memory for new node
                zeta->rson = v;
                break;
            }
        } else{ //equal, duplicate key
            return;
        }
        if (tau->BF!= 0){
            alpha = tau;
            phi = zeta;
        }
        //
            zeta = tau;
    }
        v->lson = NULL; //fill in new node fields
        v->rson = NULL;
        v->BF = 0;
        v->d = data;
    
    if (data<alpha->d){ //adjust balance factors
        zeta = alpha->lson;
        beta = alpha->lson;
    } else{
        zeta = alpha->rson;
        beta = alpha->rson;
    }
    while (zeta!=v){
        if (data<zeta->d){
            zeta->BF = -1;
            zeta = zeta->lson;
        } else{
            zeta->BF = 1;
            zeta = zeta->rson;
        }
    }
    if (data<alpha->d) {
        w=-1;
    } else{
        w=1;
    }
    
    if (alpha->BF==0){
        alpha->BF = w;
    } else if (alpha->BF==-w){
        alpha->BF = 0;
    } else if (alpha->BF==w){
        
        //rotateright or rotateleft
        if (beta->BF == w){
            
            //rotate right
            if (data<alpha->d){ rotate_right(&alpha, &beta);}
            else if (data>alpha->d){
                rotate_left(&alpha, &beta);
            }
            
            
        } else if (beta->BF == -w){
            if (data<alpha->d){
                rotate_left_right (&alpha, &beta);
            }
            else {
                rotate_right_left (&alpha, &beta);
            }
        }
        
        if (alpha==*headptr) {
            *headptr = beta;
        } else if (alpha==phi->lson){
            phi->lson = beta;
        } else if (alpha==phi->rson){
            phi->rson = beta;
        }
    }
}


int main () {
    int data;
    
    Node * head = NULL; //initialize head node
    scanf("%d", &data); //get first data
    initialize(&head, data); //initialize head node and put data there
    
    scanf("%d", &data);
    while (data!=0){
        print(&head);
        printf("\n");
        insert(&head, data); //insert data at new node at appropriate place
        scanf("%d", &data);
    }
    
    print(&head);
    
    return 0;
}