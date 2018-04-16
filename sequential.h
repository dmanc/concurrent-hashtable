#include "hashtable.h"

class Sequential: public HashTable {
 public:
    int get(int key) {
        return 0;
    }

    void put(int val) {
        return;
    }

    int del(int key) {
        return 0;
    }

    bool hasKey(int key) {
        return 0;
    }


};
