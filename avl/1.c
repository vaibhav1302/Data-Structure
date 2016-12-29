#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	struct node* left;
	struct node* right;
	int data;
	int height;
}node;
//function to find balancing factor of a node in AVL
int balance(node* root){
	if(root==NULL)
		return 0;
	int l, r;
	l= root->left==NULL?0:root->left->height;
	r= root->right==NULL?0:root->right->height;
	return (l-r);
}
//function to find height of a node
int height(node* root){
	if(root==NULL)
		return 0;
	else return root->height;
}
//function to find maximum of two integers
int max(int a, int b){
	return(a>=b?a:b);
}
//function to left rotate
void left_rotate(node** rptr){
	if(*rptr==NULL)
		return;
	node* tmp= *rptr;
	*rptr= (*rptr)->right;
	tmp->right= (*rptr)->left;
	(*rptr)->left= tmp;
	tmp->height= max(height(tmp->left), height(tmp->right));
	tmp= *rptr; 
	tmp->height= max(height(tmp->left), height(tmp->right)); 
}
//funciton to right rotate
void right_rotate(node** rptr){
	if(*rptr==NULL)
		return;
	node* tmp= *rptr;
	*rptr= (*rptr)->left;
	tmp->left= (*rptr)->right;
	(*rptr)->right= tmp;
	tmp->height= max(height(tmp->left), height(tmp->right));
	tmp= *rptr; 
	tmp->height= max(height(tmp->left), height(tmp->right)); 
}
//function to insert a node into AVL
void insert(node** rptr, int item){
	if(*rptr==NULL){
		*rptr= (node*)malloc(sizeof(node));
		(*rptr)->left= (*rptr)->right= NULL;
		(*rptr)->data= item;
		(*rptr)->height= 1;
		return;
	}
	else if((*rptr)->data > item)
		insert(&((*rptr)->left), item);
	else if((*rptr)->data < item)
		insert(&((*rptr)->right), item);
	else if((*rptr)->data == item)
		return;		
//balancing
	if(balance(*rptr)>1){
		if((*rptr)->left->data > item){
		//ll
			right_rotate(rptr);
		}
		if((*rptr)->left->data < item){
		//lr
			left_rotate(&((*rptr)->left));
			right_rotate(rptr);
		}
	}
	else if(balance(*rptr)<-1){
		if((*rptr)->right->data < item){
		//rr
			left_rotate(rptr);
		}
		if((*rptr)->left->data > item){
		//rl
			right_rotate(&((*rptr)->right));
			left_rotate(rptr);
		}
	}

}
//function to delete a node from AVL
void delete(node** rptr, int item){
	if(*rptr==NULL)
		return;
	else if((*rptr)->data > item)
		delete(&((*rptr)->left), item);
	else if((*rptr)->data < item)
		delete(&((*rptr)->right), item);
	else if((*rptr)->data == item){
		if((*rptr)->left==NULL && (*rptr)->right==NULL){
			free(*rptr);
			*rptr= NULL;
			return;
		}
		if((*rptr)->left!=NULL){
			node* ptr= (*rptr)->left;
			while(ptr->right!=NULL)
				ptr= ptr->right;
			(*rptr)->data= ptr->data;	
			delete(&((*rptr)->left), ptr->data);
		}	
		if((*rptr)->right!=NULL){
			node* ptr= (*rptr)->right;
			while(ptr->left!=NULL)
				ptr= ptr->left;
			(*rptr)->data= ptr->data;	
			delete(&((*rptr)->right), ptr->data);
		}	
	}
//balancing
	if(balance(*rptr)>1){
		if((*rptr)->left->data > item){
		//ll
			right_rotate(rptr);
		}
		if((*rptr)->left->data < item){
		//lr
			left_rotate(&((*rptr)->left));
			right_rotate(rptr);
		}
	}
	else if(balance(*rptr)<-1){
		if((*rptr)->right->data < item){
		//rr
			left_rotate(rptr);
		}
		if((*rptr)->left->data > item){
		//rl
			right_rotate(&((*rptr)->right));
			left_rotate(rptr);
		}
	}		
}

int main(){
return 0;
}
