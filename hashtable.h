#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class HashTable {
 public:
    virtual uint32_t get(uint32_t) = 0;
    virtual void put(int) = 0;
    virtual uint32_t  del(uint32_t) = 0;
    virtual bool hasKey(uint32_t) = 0;

    uint32_t size() {
        return entries;
    }

    bool isEmpty() {
        return size() == 0;
    }

 protected:
    uint32_t entries;
};

// Knuth's Multiplicative Method
uint32_t hash(uint32_t v) {
    return v * UINT32_C(2654435761);
}

#endif
