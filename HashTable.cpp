#pragma once

#include <vector>
#include <list>
#include <iostream>

using namespace std;

class HashTable{
public:
    HashTable(int bs);
    HashTable(void);
    ~HashTable(); 
    void Add(int str);
    bool Find(int key);
    void Del(int key);
    int Example();
    size_t Hash(int str);
    void Erase();
    void Display();
    int GetLoad();
private:
    list<int>* arr;
    int buskets = 10;
};

HashTable::HashTable(int bs) 
{
    buskets = bs;
    arr = new list<int>[buskets];
}
HashTable::HashTable() 
{
    arr = new list<int>[buskets];
}
HashTable::~HashTable(){
    delete[] arr;
}
size_t HashTable::Hash(int v)
{
    size_t res = 0;
    int pt = 1;
    int *lv = &v;
    for(int i = 0; i < sizeof(int); i++){
        res += pt * lv[i];
        res %= buskets;
    }

    return res;
    //unsigned int t = *(unsigned )int *)&v;
    //return t % buskets;
}
void HashTable::Add(int str)
{
    size_t tmp = Hash(str);   
    arr[tmp].push_front(str);
}
bool HashTable::Find(int key)
{
    size_t tmp = Hash(key);
    for (auto& i : arr[tmp])
    {
        if (i == key) return true;
    }
    return false;
}
int HashTable::Example(){
    for(int i = 0; i < buskets; i++){
        if(!arr[i].empty()) return arr[i].front();
    }
    return 0;
}
void HashTable::Del(int key)
{
    size_t tmp = Hash(key);
    for (auto i = arr[tmp].begin();
        i != arr[tmp].end(); ++i)
    {
        if (*i == key) 
        {
            arr[tmp].erase(i);
            return;
        }
    }
}

int HashTable::GetLoad(){
    int load = 0;
    for(int i = 0; i < buskets; i++){
        if(!arr[i].empty()) load++;
    }
    return load;
}
void HashTable::Erase(){
    delete[] arr;
    arr = new list<int>[buskets];
}
void HashTable::Display(){
    for(int i  = 0; i < buskets; i++){
        if (arr[i].size()>0){
            for (auto j = arr[i].begin(); j != arr[i].end(); ++j){
                cout << *j << ' ';
            }
            cout << '\n';
        }
    }
}