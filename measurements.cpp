#include "Set_hash.cpp"
#include "Set_tree.cpp"
#include "Set_avl.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <random>
using namespace std;

std::mt19937 rng;
std::uniform_int_distribution<std::mt19937::result_type> distr;
int random_int()
{
    return distr(rng);
}
int *random_array(int size)
{
    int* res = new int[size];
    for (int i = 0; i < size; i++)
        res[i] = distr(rng);

    return res;
}

long diff(timespec start, timespec end)
{
    if ((end.tv_nsec-start.tv_nsec)<0)
    {
        return 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else 
    {
        return end.tv_nsec-start.tv_nsec;
    }
    return 0;
}


void measureHash()
{
    std::random_device dev;
    std::mt19937 rng_m(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr_m(-2147483647,2147483647);
    distr = distr_m;
    rng = rng_m;

    string path = "time_hashSet.txt";

    int iterations = 10;
    int minBusket = 200;
    int maxBusket = 20000;
    int busketStep = 20;
    int elementMlt = 2;
    int elementStep = 250;

    ofstream file(path);
    for (int iter = 0; iter <= iterations; iter++)
    {
        cout << iter << '\n';
        for (int b = minBusket; b <= maxBusket; b += busketStep)
        {
            Set_HashTable *s = new Set_HashTable(b);

            struct timespec begin, end;
            struct timespec begin_cpu, end_cpu;


            for (int e = 0; e < elementMlt * b; e += elementStep)
            {
                int *t = random_array(elementStep);
                // insert

                clock_gettime(CLOCK_REALTIME, &begin);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

                for (int i = 0; i < elementStep; i++)
                {
                    s->insert(t[i]);
                }

                clock_gettime(CLOCK_REALTIME, &end);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

                long insert = diff(begin, end);
                long insert_cpu = diff(begin_cpu, end_cpu);
                // contain (existing)

                clock_gettime(CLOCK_REALTIME, &begin);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

                for (int i = 0; i < elementStep; i++)
                {
                    s->contains(t[i]);
                }

                clock_gettime(CLOCK_REALTIME, &end);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

                long contains_0 = diff(begin, end);
                long contains_0_cpu = diff(begin_cpu, end_cpu);

                // remove (existing)

                clock_gettime(CLOCK_REALTIME, &begin);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

                for (int i = 0; i < elementStep; i++)
                {
                    s->remove(t[i]);
                }

                clock_gettime(CLOCK_REALTIME, &end);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

                long remove_0 = diff(begin, end);
                long remove_0_cpu = diff(begin_cpu, end_cpu);

                delete[] t;

                // contain (mean)

                t = random_array(elementStep);

                clock_gettime(CLOCK_REALTIME, &begin);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

                for (int i = 0; i < elementStep; i++)
                {
                    s->contains(t[i]);
                }

                clock_gettime(CLOCK_REALTIME, &end);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

                long contains_1 = diff(begin, end);
                long contains_1_cpu = diff(begin_cpu, end_cpu);

                // remove (existing)

                clock_gettime(CLOCK_REALTIME, &begin);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

                for (int i = 0; i < elementStep; i++)
                {
                    s->remove(t[i]);
                }

                clock_gettime(CLOCK_REALTIME, &end);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

                long remove_1 = diff(begin, end);
                long remove_1_cpu = diff(begin_cpu, end_cpu);

                delete[] t;



                //write data

                file << iter << ' ' << e << ' ' << b << ' ' << s->GetLoad() << ' ' << insert << ' ' << contains_0 << ' ' << contains_1 << ' ' << remove_0 << ' ' << remove_1 << ' ' <<
                                    insert_cpu << ' ' << contains_0_cpu << ' ' << contains_1_cpu << ' ' << remove_0_cpu << ' ' << remove_1_cpu << '\n'; 
    
                //restore count

                while(s->size < e+elementStep){
                    int r = random_int();
                    s->insert(r);
                }
            }
            delete s;
        }
    }
    file.close();
}


void measureAVL_random(){
    std::random_device dev;
    std::mt19937 rng_m(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr_m(-2147483647,2147483647);
    distr = distr_m;
    rng = rng_m;

    string path = "time_avl_random.txt";

    int iterations = 15;
    int minElements = 10;
    int elements = 50000;
    int averaging = 10;
    int step = 20;

    ofstream file(path);

    for (int iter = 0; iter < iterations; iter++){
        cout << iter << '\n';
        Set_AVLTree *s = new Set_AVLTree();
        for(int i = 0; i < minElements; i++)
            s->insert(random_int());
        struct timespec begin, end;
        struct timespec begin_cpu, end_cpu;

        for(int e = 0; e < elements; e += step){
            //insert

            int *t = random_array(averaging);

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->insert(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long insert = diff(begin, end);
            long insert_cpu = diff(begin_cpu, end_cpu);

            //contains
            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                bool re = s->contains(t[i]);
                if(!re) std::cout <<"hell\n";
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
            long contains = diff(begin, end);
            long contains_cpu = diff(begin_cpu, end_cpu);

            //remove

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->remove(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long remove = diff(begin, end);
            long remove_cpu = diff(begin_cpu, end_cpu);

            delete[] t;
            //Write
            file << iter << ' ' << e << ' ' << insert << ' ' << contains << ' ' << remove << ' ' <<
                    insert_cpu << ' ' << contains_cpu << ' ' << remove_cpu << ' ' << s->tree.height(s->ht) << '\n';

            //Restore count
            while (s->size < e + step){
                s->insert(random_int());
            }
        }
        delete s;
    }
    file.close();
}


void measureTree_random(){
    std::random_device dev;
    std::mt19937 rng_m(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr_m(-2147483647,2147483647);
    distr = distr_m;
    rng = rng_m;

    string path = "time_tree_random.txt";

    int iterations = 15;
    int minElements = 10;
    int elements = 50000;
    int averaging = 10;
    int step = 20;

    ofstream file(path);

    for (int iter = 0; iter < iterations; iter++){
        cout << iter << '\n';
        Set_Tree *s = new Set_Tree();
        for(int i = 0; i < minElements; i++)
            s->insert(random_int());
        struct timespec begin, end;
        struct timespec begin_cpu, end_cpu;

        for(int e = 0; e < elements; e += step){
            //insert

            int *t = random_array(averaging);

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->insert(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long insert = diff(begin, end);
            long insert_cpu = diff(begin_cpu, end_cpu);

            //contains
            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                bool re = s->contains(t[i]);
                if(!re) std::cout <<"hell\n";
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
            long contains = diff(begin, end);
            long contains_cpu = diff(begin_cpu, end_cpu);

            //remove

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->remove(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long remove = diff(begin, end);
            long remove_cpu = diff(begin_cpu, end_cpu);

            delete[] t;
            //Write
            file << iter << ' ' << e << ' ' << insert << ' ' << contains << ' ' << remove << ' ' <<
                    insert_cpu << ' ' << contains_cpu << ' ' << remove_cpu << ' ' << '\n';

            //Restore count
            while (s->size < e + step){
                s->insert(random_int());
            }
        }
        delete s;
    }
    file.close();
}


void measureAVL_sequential(){
    std::random_device dev;
    std::mt19937 rng_m(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr_m(-2147483647,2147483647);
    distr = distr_m;
    rng = rng_m;

    string path = "time_avl_sequential.txt";

    int iterations = 5;
    int minElements = 10;
    int elements = 50000;
    int averaging = 5;
    int step = 40;

    ofstream file(path);

    for (int iter = 0; iter < iterations; iter++){
        cout << iter << '\n';
        Set_AVLTree *s = new Set_AVLTree();
        for(int i = 0; i < minElements; i++)
            s->insert(s->size);
        struct timespec begin, end;
        struct timespec begin_cpu, end_cpu;

        for(int e = 0; e < elements; e += step){
            //insert

            int *t = random_array(averaging);

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->insert(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long insert = diff(begin, end);
            long insert_cpu = diff(begin_cpu, end_cpu);

            //contains
            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                bool re = s->contains(t[i]);
                if(!re) std::cout <<"hell\n";
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
            long contains = diff(begin, end);
            long contains_cpu = diff(begin_cpu, end_cpu);

            //remove

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->remove(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long remove = diff(begin, end);
            long remove_cpu = diff(begin_cpu, end_cpu);

            delete[] t;
            //Write
            file << iter << ' ' << e << ' ' << insert << ' ' << contains << ' ' << remove << ' ' <<
                    insert_cpu << ' ' << contains_cpu << ' ' << remove_cpu << ' ' << s->tree.height(s->ht) << '\n';

            //Restore count
            while (s->size < e + step){
                s->insert(s->size);
            }
        }
        delete s;
    }
    file.close();
}

void measureTree_sequential(){
    std::random_device dev;
    std::mt19937 rng_m(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distr_m(-2147483647,2147483647);
    distr = distr_m;
    rng = rng_m;

    string path = "time_tree_sequential.txt";

    int iterations = 5;
    int minElements = 10;
    int elements = 50000;
    int averaging = 5;
    int step = 40;

    ofstream file(path);

    for (int iter = 0; iter < iterations; iter++){
        cout << iter << '\n';
        Set_Tree *s = new Set_Tree();
        for(int i = 0; i < minElements; i++)
            s->insert(s->size);
        struct timespec begin, end;
        struct timespec begin_cpu, end_cpu;

        for(int e = 0; e < elements; e += step){
            //insert

            int *t = random_array(averaging);

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->insert(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long insert = diff(begin, end);
            long insert_cpu = diff(begin_cpu, end_cpu);

            //contains
            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                bool re = s->contains(t[i]);
                if(!re) std::cout <<"hell\n";
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);
            long contains = diff(begin, end);
            long contains_cpu = diff(begin_cpu, end_cpu);

            //remove

            clock_gettime(CLOCK_REALTIME, &begin);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_cpu);

            for (int i = 0; i < averaging; i++)
            {
                s->remove(t[i]);
            }

            clock_gettime(CLOCK_REALTIME, &end);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_cpu);

            long remove = diff(begin, end);
            long remove_cpu = diff(begin_cpu, end_cpu);

            delete[] t;
            //Write
            file << iter << ' ' << e << ' ' << insert << ' ' << contains << ' ' << remove << ' ' <<
                    insert_cpu << ' ' << contains_cpu << ' ' << remove_cpu << '\n';

            //Restore count
            while (s->size < e + step){
                s->insert(s->size);
            }
        }
        delete s;
    }
    file.close();
}