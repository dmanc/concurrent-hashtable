#ifndef COARSE_H
#define COARSE_H

#include "sequential.h"
#include <mutex>

using namespace std;

class Coarse: public HashTable {
    private:
        Sequential seq;
        mutex lock;
    public:
        Coarse(bool toresize = true) : seq(toresize) {}
        
        uint32_t get(uint32_t key) {
            lock_guard<mutex> lock_g(lock);
            uint32_t val = seq.get(key);
            return val;
        }

        void put(uint32_t key, uint32_t val) {
            lock_guard<mutex> lock_g(lock);
            seq.put(key, val);
        }

        bool hasKey(uint32_t key) {
            lock_guard<mutex> lock_g(lock);
            bool result = seq.hasKey(key);
            return result;
        }

        uint32_t size() {
            lock_guard<mutex> lock_g(lock);
            uint32_t result = seq.size();
            return result;
        }

        bool isEmpty() {
            lock_guard<mutex> lock_g(lock);
            return seq.size() == 0;
        }
};

#endif
