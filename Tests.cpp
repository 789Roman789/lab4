#include "Set_hash.cpp"
#include "Set_tree.cpp"
#include "Set_avl.cpp"
#include <iostream>

void sandTest_hashTable(){
    Set_HashTable s;

    while(true){
        int t;
        
        std::cout << "1 - insert\n";
        std::cout << "2 - remove\n";
        std::cout << "3 - contains\n";
        std::cout << "4 - is empty\n";
        std::cout << "5 - count\n";
        std::cout << "6 - display\n";
        
        std::cin >> t;
        std::cout << '\n';
        int v;
        switch (t)
        {
        case 1:
            std::cin >> v;
            s.insert(v);
            break;
        case 2:
            std::cin >> v;
            s.remove(v);
            break;
        case 3:
            std::cin >> v;
            std::cout << s.contains(v);
            break;
        case 4:
            std::cout << s.is_empty();
            break;
        case 5:
            std::cout << s.size;
            break;
        case 6:
            s.Display();
            break;
        default:
            std::cout << "wrong input \n";
            return;
            break;
        }

        std::cout << '\n' << '\n';
    }
}

void sandTest_AVL(){
    Set_AVLTree s;

    while(true){
        int t;
        
        std::cout << "1 - insert\n";
        std::cout << "2 - remove\n";
        std::cout << "3 - contains\n";
        std::cout << "4 - is empty\n";
        std::cout << "5 - count\n";
        std::cout << "6 - display\n";
        
        std::cin >> t;
        std::cout << '\n';
        int v;
        switch (t)
        {
        case 1:
            std::cin >> v;
            s.insert(v);
            break;
        case 2:
            std::cin >> v;
            s.remove(v);
            break;
        case 3:
            std::cin >> v;
            std::cout << s.contains(v);
            break;
        case 4:
            std::cout << s.is_empty();
            break;
        case 5:
            std::cout << s.size;
            break;
        case 6:
            s.Display();
            break;
        default:
            std::cout << "wrong input \n";
            return;
            break;
        }

        std::cout << '\n' << '\n';
    }
}

void sandTest_Tree(){
    Set_Tree s;

    while(true){
        int t;
        
        std::cout << "1 - insert\n";
        std::cout << "2 - remove\n";
        std::cout << "3 - contains\n";
        std::cout << "4 - is empty\n";
        std::cout << "5 - count\n";
        std::cout << "6 - display\n";
        
        std::cin >> t;
        std::cout << '\n';
        int v;
        switch (t)
        {
        case 1:
            std::cin >> v;
            s.insert(v);
            break;
        case 2:
            std::cin >> v;
            s.remove(v);
            break;
        case 3:
            std::cin >> v;
            std::cout << s.contains(v);
            break;
        case 4:
            std::cout << s.is_empty();
            break;
        case 5:
            std::cout << s.size;
            break;
        case 6:
            s.Display();
            break;
        default:
            std::cout << "wrong input \n";
            return;
            break;
        }

        std::cout << '\n' << '\n';
    }
}