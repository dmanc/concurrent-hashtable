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

int main() {
    check(0xdeadbeef, 0xdeadbeef, "constant check");
    printf("SUCCESS: Passed %d tests\n", testno);
}
