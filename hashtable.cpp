#include <iostream>
#include "sequential.h"

int main() {
    std::cout << "Hello World\n";

    std::cout << "Basic bucket test" << "\n";
    Bucket b = Bucket();
    b.add(1, 4);
    b.add(2, 3);
    std::cout << b.size << "\n";
    Node* head = b.head;
    while(head != NULL) {
        std::cout << head->key << " " << head->value << "\n";        
        head = head->next;
    }
    return 0;
}
