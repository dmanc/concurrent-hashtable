#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class HashTable {
 public:
    virtual int get(int) = 0;
    virtual void put(int) = 0;
    virtual int del(int) = 0;
    virtual bool hasKey(int) = 0;

    int size() {
        return entries;
    }

    bool isEmpty() {
        return size() == 0;
    }

 protected:
    int entries;
};

#endif
