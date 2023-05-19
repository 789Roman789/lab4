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
struct node
{
	int data;
	struct node *left;
	struct node *right;
};

/*
* Class Declaration
*/
class Tree
{
public:
	int height(node *);
	int diff(node *);
	node* insert(node *, int);
    int example(node *root);
	void display(node *, int);
	void inorder(node *);
	void preorder(node *);
	void postorder(node *);
	node* remove(node* t, int x, bool* marker);
	node* remove(node* t, int x);
	void erase(node* t);
	node* findMin(node*);
	node* findMax(node*);
    bool search(node* t, int x);

//private:
    //avl_node *root;

};


/*
* Height of AVL Tree
*/
int Tree::height(node *temp)
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
int Tree::diff(node *temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

/*
* Insert Element into the tree
*/
node *Tree::insert(node *root, int value)
{
	if (root == NULL)
	{
		root = new node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
	}
	return root;
}

/*
* Display AVL Tree
*/
void Tree::display(node *ptr, int level)
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
void Tree::inorder(node *tree)
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
void Tree::preorder(node *tree)
{
	if (tree == NULL)
		return;
	cout << tree->data << "  ";
	preorder(tree->left);
	preorder(tree->right);

}
node* Tree::findMin(node* t) {
	if (t == NULL) return NULL;
	else if (t->left == NULL) return t; // if element traverse on max left then return
	else return findMin(t->left); // or recursively traverse max left
}
node* Tree:: findMax(node* t) {
	if (t == NULL) return NULL;
	else if (t->right == NULL) return t;
	else return findMax(t->right);
}
/*
* Postorder Traversal of AVL Tree
*/
void Tree::postorder(node *tree)
{
	if (tree == NULL)
		return;
	postorder(tree->left);
	postorder(tree->right);
	cout << tree->data << "  ";
}

node* Tree:: remove(node* t, int x, bool *marker) {
    *marker = false;
	node* temp;
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
    return t;
}


node* Tree:: remove(node* t, int x) {
	bool m;
	return remove(t, x, &m);
}


bool Tree::search(node* t, int x){
    node* temp;
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

int Tree::example(node *root){
    if(root == NULL) return 0;
    return root->data;
}

void Tree::erase(node *root){
	if(root->left != nullptr) erase(root->left);
	if(root->right != nullptr) erase(root->right);

	delete root;
}