#include "hashtable.h"

class Sequential: public HashTable {
 public:
    uint32_t get(uint32_t key) {
        return 0;
    }

    void put(uint32_t key, uint32_t val) {
        return;
    }

    uint32_t del(uint32_t key) {
        return 0;
    }

    bool hasKey(uint32_t key) {
        return 0;
    }


};
