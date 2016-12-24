#include<stdlib.h>
#include<stdio.h>
//splay will not contain duplicates
//define structure
typedef struct node{
	struct node* left;
	struct node* right;
	int data;
}node;
//left and right rotate
void left_rotate(node** rptr){
	if(*rptr==NULL)
		return;
	node* tmp= *rptr;
	*rptr= tmp->right;
	tmp->right= (*rptr)->left;
	(*rptr)->left= tmp;
}
void right_rotate(node** rptr){
	if(*rptr==NULL)
		return;
	node* tmp= *rptr;
	*rptr= tmp->left;
	tmp->left= (*rptr)->right;
	(*rptr)->right= tmp;
}
//function to create a new node and return its pointer
node* create(int item){
	node* new= (node*)malloc(sizeof(node));
	new->left= new->right= NULL;
	new->data= item;
	return new;
}
//function to splay the given item, given that the item is present in the tree
void splay(node** rptr, int item, node* root){
	if(*rptr==NULL)
		return;
	else{
		if((*rptr)->data > item)
			splay(&((*rptr)->left), item, root);
		else if((*rptr)->data < item)
			splay(&((*rptr)->left), item, root);
		else if((*rptr)->data == item)
			return;
		if((*rptr)->data > item){
			if((*rptr)->left->data > item){//zig-zig
				right_rotate(rptr);
				right_rotate(rptr);
			}
			if((*rptr)->left->data < item){//zig-zag
				left_rotate(&((*rptr)->left));
				right_rotate(rptr);
			}
			else if(*rptr== root && (*rptr)->left->data==item)//zig
				right_rotate(rptr);
		}
		if((*rptr)->data < item){
			if((*rptr)->right->data < item){//zag-zag
				left_rotate(rptr);
				left_rotate(rptr);
			}
			if((*rptr)->right->data > item){//zag-zig
				right_rotate(&((*rptr)->right));
				left_rotate(rptr);
			}
			else if(*rptr== root && (*rptr)->right->data==item)//zag
				left_rotate(rptr);
		}
	}
}
//function to insert into a BST
void insert(node** rptr, int item){
	if(*rptr==NULL)
		*rptr= create(item);
	else if((*rptr)->data > item)
			insert(&((*rptr)->left), item);
	else if((*rptr)->data < item)
			insert(&((*rptr)->right), item);
}


int main(){
return 0;
}
