#include <iostream>
#include "sequential.h"
#include <stdio.h>
#include <cstdlib>

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
}

int main() {

    runSeqUnitTests();

    // get hashtable choice to test specific table from cmd line
    runTableTests<Sequential>(); 


    printf("SUCCESS: Passed %d tests\n", testno);
}
