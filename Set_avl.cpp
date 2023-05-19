#pragma once

#include "AVLTree.cpp"

struct Set_AVLTree{
    Set_AVLTree();
    ~Set_AVLTree();
    
    int size = 0;

    bool is_empty();
    int example();
    bool contains(int key);
    void insert(int key);
    void remove(int key);
    void Display();
    //private:
        avlTree tree;
        avl_node* ht;
};



Set_AVLTree::Set_AVLTree(){
    ht = nullptr;
}

Set_AVLTree::~Set_AVLTree(){
    tree.erase(ht);
}


bool Set_AVLTree::is_empty(){
    return size == 0;
}

int Set_AVLTree::example(){
    return tree.example(ht);
}

bool Set_AVLTree::contains(int key){
    return tree.search(ht, key);
}

void Set_AVLTree::insert(int key){
    if (!contains(key)) {
        ht = tree.insert(ht,key);
        size++;
    }
}

void Set_AVLTree::remove(int key){
    bool removed = false;
    ht = tree.remove(ht, key, &removed);
    if(removed) size--;
}

void Set_AVLTree::Display(){
    tree.display(ht, 1);
}