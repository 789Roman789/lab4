#pragma once

#include "Tree.cpp"

struct Set_Tree{
    Set_Tree();
    ~Set_Tree();
    
    int size = 0;

    bool is_empty();
    int example();
    bool contains(int key);
    void insert(int key);
    void remove(int key);
    void Display();

    private:
        node* ht;
        Tree tree;
};



Set_Tree::Set_Tree(){
    ht = nullptr;
}

Set_Tree::~Set_Tree(){
    tree.erase(ht);
}


bool Set_Tree::is_empty(){
    return size == 0;
}

int Set_Tree::example(){
    return tree.example(ht);
}

bool Set_Tree::contains(int key){
    return tree.search(ht, key);
}

void Set_Tree::insert(int key){
    if (!contains(key)) {
        ht = tree.insert(ht,key);
        size++;
    }
}

void Set_Tree::remove(int key){
    bool removed = false;
    ht = tree.remove(ht, key, &removed);
    if(removed) size--;
}

void Set_Tree::Display(){
    tree.display(ht, 1);
}