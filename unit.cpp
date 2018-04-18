#include <iostream>
#include "sequential.h"
#include <stdio.h>
#include <cstdlib>

int testno = 0;

void check(int expected, int actual, const char* message) {
    testno++;
    if(expected != actual) {
        printf("FAILURE: Test %d with message: '%s'\n", testno, message);
        exit(0);
    }
}

template <class tbl_type>
void runTableTests() {
    tbl_type tbl;

    //Test starting size
    check(tbl.size(), 0, "intial table size not 0");
}

int main() {

    // get hashtable choice to test specific table from cmd line
    runTableTests<Sequential>(); 



    printf("SUCCESS: Passed %d tests\n", testno);
}
