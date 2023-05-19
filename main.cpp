#include <iostream>
#include "Tests.cpp"
#include "measurements.cpp"
int main(){
    std::cout << "started\n";

    sandTest_hashTable();
    //measureTree_sequential();
    std::cout << "done\n";
    return 0;
}