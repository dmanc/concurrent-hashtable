#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class HashTable {
 public:
    // get key for value
    virtual uint32_t get(uint32_t) = 0;

    // put (key, value) pair
    virtual void put(uint32_t, uint32_t) = 0;

    // delete entry for key
    virtual uint32_t  del(uint32_t) = 0;

    // check if has entry with key
    virtual bool hasKey(uint32_t) = 0;

    // return number of entries
    uint32_t size() {
        return entries;
    }

    // return is table is empty
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
