#pragma once

/*
* C++ program to Implement AVL Tree
https://gist.github.com/Harish-R/097688ac7f48bcbadfa5
*/
#include<iostream>
#include <algorithm>

#define pow2(n) (1 << (n))
using namespace std;

/*
* Node Declaration
*/
struct avl_node
{
	int data;
	struct avl_node *left;
	struct avl_node *right;
};

/*
* Class Declaration
*/
class avlTree
{
public:
	int height(avl_node *);
	int diff(avl_node *);
	avl_node *rr_rotation(avl_node *);
	avl_node *ll_rotation(avl_node *);
	avl_node *lr_rotation(avl_node *);
	avl_node *rl_rotation(avl_node *);
	avl_node* balance(avl_node *);
	avl_node* insert(avl_node *, int);
    int example(avl_node *root);
	void display(avl_node *, int);
	void inorder(avl_node *);
	void preorder(avl_node *);
	void postorder(avl_node *);
	avl_node* remove(avl_node* t, int x, bool* marker);
	avl_node* remove(avl_node* t, int x);
	void erase(avl_node* t);
	avl_node* findMin(avl_node*);
	avl_node* findMax(avl_node*);
    bool search(avl_node* t, int x);

//private:
    //avl_node *root;

};


/*
* Height of AVL Tree
*/
int avlTree::height(avl_node *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

/*
* Height Difference
*/
int avlTree::diff(avl_node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

/*
* Right- Right Rotation
*/
avl_node *avlTree::rr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}
/*
* Left- Left Rotation
*/
avl_node *avlTree::ll_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
* Left - Right Rotation
*/
avl_node *avlTree::lr_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

/*
* Right- Left Rotation
*/
avl_node *avlTree::rl_rotation(avl_node *parent)
{
	avl_node *temp;
	temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

/*
* Balancing AVL Tree
*/
avl_node *avlTree::balance(avl_node *temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}

/*
* Insert Element into the tree
*/
avl_node *avlTree::insert(avl_node *root, int value)
{
	if (root == NULL)
	{
		root = new avl_node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
		root = balance(root);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
		root = balance(root);
	}
	return root;
}

/*
* Display AVL Tree
*/
void avlTree::display(avl_node *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		for (i = 0; i < level; i++)
			cout << "        ";
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}

/*
* Inorder Traversal of AVL Tree
*/
void avlTree::inorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}
/*
* Preorder Traversal of AVL Tree
*/
void avlTree::preorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}
avl_node* avlTree::findMin(avl_node* t) {
	if (t == NULL) return NULL;
	else if (t->left == NULL) return t; // if element traverse on max left then return
	else return findMin(t->left); // or recursively traverse max left
}
avl_node* avlTree:: findMax(avl_node* t) {
	if (t == NULL) return NULL;
	else if (t->right == NULL) return t;
	else return findMax(t->right);
}
/*
* Postorder Traversal of AVL Tree
*/
void avlTree::postorder(avl_node *tree)
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	cout << tree->data << "  ";
}

avl_node* avlTree:: remove(avl_node* t, int x, bool *marker) {
    *marker = false;
	avl_node* temp;
	// element not found
	if (t == NULL) return NULL;
	// searching element
	else if (x < t->data) t->left = remove(t->left, x, marker);
	else if (x >t->data) t->right = remove(t->right, x, marker);

	// element found 
	// element has 2 children
	else if (t->left && t->right) {
		temp = findMin(t->right);
		t->data = temp->data;
		t->right = remove(t->right, t->data, marker);
	}
	// if element has 1 or 0 child
	else {
		temp = t;
		if (t->left == NULL) t = t->right;
		else if (t->right == NULL) t = t->left;
		delete temp;
        *marker = true;
	}
	if (t == NULL) return NULL;
	// check balanced)
	t = balance(t);
    return t;
}


avl_node* avlTree:: remove(avl_node* t, int x) {
	bool m;
	return remove(t, x, &m);
}


bool avlTree::search(avl_node* t, int x){
    bool res;
	// element not found
	if (t == NULL) res = false;
	// searching element
	else if (x < t->data) res = search(t->left, x);
	else if (x >t->data) res = search(t->right, x);
	// element found 
	else {
        res = true;
	}
    
    return res;
}

int avlTree::example(avl_node *root){
    if(root == NULL) return 0;
    return root->data;
}

void avlTree::erase(avl_node *root){
	if(root->left != nullptr) erase(root->left);
	if(root->right != nullptr) erase(root->right);

	delete root;
}