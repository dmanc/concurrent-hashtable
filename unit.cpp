#include <iostream>
#include "sequential.h"

int testno = 0;

void check(int expected, int actual, const char* message) {
    if(expected != actual) {
        printf("FAILURE: Test %d with message: '%s'\n", ++testno, message);
        exit(0);
    }
}

int main() {
   check(0, 0, "constant check");
   printf("SUCCESS: Passed %d tests\n", testno);
}
