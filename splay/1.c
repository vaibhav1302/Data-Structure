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
//function to insert into a splay
void insert_splay(node** rptr, int item){
	insert(rptr, item);
	splay(rptr, item, *rptr);
}
//function to delete from a BST and return pointer to the ancestor of the leaf deleted
node* del(node** rptr, int item){
	node* tmp;
	if(*rptr==NULL)
		return NULL;	
	else if((*rptr)->data > item)
		tmp=del(&((*rptr)->left), item);
	else if((*rptr)->data < item)
		tmp=del(&((*rptr)->right), item);
	else if((*rptr)->data == item){
		if((*rptr)->left==NULL && (*rptr)->right==NULL){
			free(*rptr);
			*rptr= NULL;
			return NULL;
		}
		if((*rptr)->left!=NULL){
			tmp= (*rptr)->left;
			while(tmp->right!=NULL)
				tmp= tmp->right;
			(*rptr)->data= tmp->data;
			tmp= del(&((*rptr)->left), (*rptr)->data);
		}
		if((*rptr)->right!=NULL){
			tmp= (*rptr)->right;
			while(tmp->left!=NULL)
				tmp= tmp->left;
			(*rptr)->data= tmp->data;
			tmp= del(&((*rptr)->right), (*rptr)->data);
		}		
	}
	if(tmp==NULL)
		return (*rptr);
	else
		return tmp;
		
}
//function to delete from a splay
void delete_splay(node** rptr, int item){
	node* tmp= del(rptr, item);
	if(tmp!=NULL)
		splay(rptr, tmp->data, *rptr);	
}
//function to search for an element in a BST and return pointer to it if found and pointer to ancestor if not found
node* search(node* root, int item){
	node* tmp;
	if(root==NULL)
		return NULL;
	else if(root->data==item)
		return root;
	else if(root->data > item)
		tmp= search(root->left, item);
	else if(root->data < item)
		tmp= search(root->right, item);
	
	if(tmp==NULL)
		return root;
	else
		return tmp;
}
//function to search for an element in splay and bring it to root if found else bring last accessed node to top
void search_splay(node** rptr, int item){
	if(*rptr==NULL)
		return;
	else{
		node* tmp= search(*rptr, item);
		if(tmp!=NULL)
			splay(rptr, tmp->data, *rptr);
	}
}

int main(){
return 0;
}
