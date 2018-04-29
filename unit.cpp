#include <iostream>
#include "sequential.h"
#include "coarse.h"
#include "fine.h"
#include "stm.h"
#include <thread>
#include <stdio.h>
#include <cstdlib>
#include <vector>

using namespace std;

int testno = 0;

void check(uint32_t expected, uint32_t actual, const char* message) {
    testno++;
    if(expected != actual) {
        printf("FAILURE: Test %d with message: '%s'\n", 
                testno, message);
        exit(0);
    }
}


void check(bool expected, bool actual, const char* message) {
    testno++;
    if(expected != actual) {
        printf("FAILURE: Test %d with message: '%s'\n", 
                testno, message);
        exit(0);
    }
}


template <class tbl_type>
void runTableTests() {
    tbl_type tbl;

    //Test starting size
    check(tbl.size(), 0, "intial table size not 0");
    check(tbl.isEmpty(), true, "is empty initial");

    //Check key initally
    check(tbl.hasKey(0xa), false, "missing key");

    //Simple put and get
    tbl.put(0xa, 0xb);
    check(tbl.size(), 1, "size after 1 put");
    check(tbl.get(0xa), 0xb, "simple get");
    check(tbl.hasKey(0xa), true, "haskey for present key");
    check(tbl.isEmpty(), false, "is empty with 1 key");
    
    //Delete single element
    /*tbl.del(0xa);
    check(tbl.size(), 0, "size after delete");
    check(tbl.isEmpty(), true, "isEmpty after deleting");
    check(tbl.hasKey(0xa), false, "check missing key");
    */

    //Multiple element operations
    for(uint32_t i = 0; i < 100; i++) {
        //printf("Putting %d, %d\n", i+1, i+5);
        tbl.put(i + 1, i + 5);
        check(tbl.size(), i + 2, "size after every operation");
    }

    for(uint32_t i = 0; i < 100; i+=5) {
        check(tbl.get(i + 1), i + 5, "check multiple inserted keys");
    }

}

typedef vector<int>::iterator vec_iter;
template <class tbl_type>
void func(tbl_type& tbl, vector<int> vec, vec_iter begin, vec_iter end, int id, int workers) {
    //if(id == workers-1)
    //    end = vec.begin() + 1000;
    //printf("begin and end %d %d\n", *begin, *end);
    for(vec_iter cur = begin; cur != end; ++cur) {
        //printf("cur %d\n", *cur);
        tbl.put(*cur, *cur);
    }
}

template <class tbl_type>
void runConcTableTests() {
    //TODO
    tbl_type tbl;
    check(tbl.size(), 0, "intial table size not 0");
    check(tbl.isEmpty(), true, "is empty initial");

    int val = 10000;
    int workers = 16;
    int part = val / workers + 1;
    vector<thread> threads(workers);
    vector<int> values(val);

    for(int i = 0; i<val; i++)
        values[i] = i + 1;

    for(int w = 0; w<workers; w++) {
        int start = w*part;
        int end = (w+1)*part;
        if(end > val) end = val;
        threads[w] = thread(func<tbl_type>, std::ref(tbl), values, values.begin() + start, values.begin() + end, w, workers);
    }

    for(int w = 0; w<workers; w++)
        threads[w].join();
    check(tbl.size(), val, "table size is not 1000");
    check(tbl.isEmpty(), false, "table size is empty");

    int sum = 0;
    for(int i = 0; i<val; i++)
        sum += tbl.get(i+1);
    check(true, sum == val*(val+1)/2, "Insert and sum 10000 elements");
}

void runSeqUnitTests() {
    Bucket b;
    uint32_t keys[2] = {1, 4};
    uint32_t values[2] = {2, 3};
    b.add(1, 2);
    b.add(4, 3);
    check(b.size, 2, "seq bucket size");
    Node* head = b.head;

    int i = 0;
    while (head != NULL) {
        check(head->key, keys[1 - i], "check key in seq bucket node");
        check(head->value, values[1 - i], "check value in seq bucket node");
        head = head->next;
        i++;
    }
    check(head == NULL, true, "bucket linked list");

    Sequential tbl;
    int val = 1000;
    for(int i = 0; i<=val; i++) {
        tbl.put(i, i);
    }
    int sum = 0;
    for(int i = 0; i<=val; i++)
        sum += tbl.get(i);
    check(true, sum == val*(val+1)/2, "Insert and sum 1000 elements");
}

int main() {

    printf("Running unit tests on Sequential table...\n");
    runSeqUnitTests();

    printf("Running table tests on Sequential table...\n");
    runTableTests<Sequential>();

    printf("Running table tests on Coarse table...\n");
    runTableTests<Coarse>();
    printf("Running concurrent table tests on Coarse table...\n");
    runConcTableTests<Coarse>();

    /*
    printf("Running table tests on Fine table...\n");
    runTableTests<Fine>();
    printf("Running concurrent table tests on Fine table...\n");
    runConcTableTests<Fine>();
    */
    
    printf("Running table tests on STM table...\n");
    runTableTests<STM>();
    printf("Running concurrent table tests on STM table...\n");
    runConcTableTests<STM>();

    printf("SUCCESS: Passed %d tests\n", testno);
}
