#ifndef STM_H
#define STM_H

#include "sequential.h"

using namespace std;

class STM: public HashTable {
    private:
        Sequential seq;
    public:
        STM() {}

        uint32_t get(uint32_t key) {
            __transaction_atomic {
                uint32_t val = seq.get(key);
                return val;
            }
        }

        void put(uint32_t key, uint32_t val) {
            __transaction_atomic {
                seq.put(key, val);
            }
        }

        bool hasKey(uint32_t key) {
            __transaction_atomic {
                bool result = seq.hasKey(key);
                return result;
            }
        }

        uint32_t size() {
            __transaction_atomic {
                uint32_t result = seq.size();
                return result;
            }
        }

        bool isEmpty() {
            __transaction_atomic {
                return seq.size() == 0;
            }
        }
};

#endif
