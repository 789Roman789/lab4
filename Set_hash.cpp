#pragma once

#include "HashTable.cpp"

struct Set_HashTable{
    public:
        Set_HashTable();
        Set_HashTable(int busket);
        ~Set_HashTable();
        
        int size = 0;

        bool is_empty();
        int example();
        bool contains(int key);
        void insert(int key);
        void remove(int key);
        void Display();
        int GetLoad();

    private:
        HashTable* ht;
};


Set_HashTable::Set_HashTable(){
    ht = new HashTable(10);
}

Set_HashTable::Set_HashTable(int busket){
    ht = new HashTable(busket);
}


Set_HashTable::~Set_HashTable(){
    delete ht;
}


bool Set_HashTable::is_empty(){
    return size == 0;
}

int Set_HashTable::example(){
    return ht->Example();
}

bool Set_HashTable::contains(int key){
    return ht->Find(key);
}

void Set_HashTable::insert(int key){
    if (!contains(key)) {
        ht->Add(key);
        size++;
    }
}

void Set_HashTable::remove(int key){
    if (contains(key)) {
        ht->Del(key);
        size--;
    }
}

void Set_HashTable::Display(){
    ht->Display();
}

int Set_HashTable::GetLoad(){
    return ht->GetLoad();
}