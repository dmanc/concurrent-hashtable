#ifndef FINE_H
#define FINE_H

#include "hashtable.h"

#define START_NUM_BUCKETS_FINE 16
#define RESIZE_FACTOR_FINE 0.75

class Node_Fine {
    public:
        uint32_t key, value;
        Node_Fine* next;
        Node_Fine(uint32_t K, uint32_t V): key(K), value(V), next(NULL){}
};

class Bucket_Fine {
    public:
        uint32_t size;
        Node_Fine *head;
        Bucket_Fine(): size(0), head(NULL) {}
        ~Bucket_Fine() {
            Node_Fine* head = this->head;
            while(head != NULL) {
                Node_Fine* next = head->next;
                delete head;
                head = next;
            }
        }

        bool hasKey(uint32_t k) {
            Node_Fine* head = this->head;
            while(head != NULL) {
                if(head->key == k) {
                    return true;
                }

                head = head->next;
            }
            //Didn't find key
            return false;

        }

        void add(uint32_t k, uint32_t v) {
            if(head == NULL) {
                head = new Node_Fine(k, v);
            } else {
                Node_Fine* node = new Node_Fine(k, v);
                node->next = head;
                head = node;
            }
            size++;
        }

        uint32_t get(uint32_t k) {
            Node_Fine* head = this->head;
            while(head != NULL) {
                if(head->key == k) {
                    return head->value;
                }

                head = head->next;
            }
            //Didn't find key
            return 0xdeadbeef;
        }
};

class Fine : public HashTable {
    private:
        uint32_t num_buckets;
        Bucket_Fine* buckets;
        mutex* locks;
        //protected field entries

        double balanceFactor() {
            return (double) entries / (double) num_buckets;
        }

        Bucket_Fine* getBucketForKey(uint32_t key) {
            return buckets + (hash_(key) % num_buckets);
        }

        mutex* getLockForKey(uint32_t key) {
            return locks + (hash_(key) % START_NUM_BUCKETS_FINE);
        }

        void resize() {
            //TODO
            //Save old buckets
            Bucket_Fine* old_buckets = buckets;
            uint32_t old_size = num_buckets;

            //Make new buckets with old size
            num_buckets *= 2;
            buckets = new Bucket_Fine[num_buckets];
            entries = 0;

            //Insert all old elements into new table
            for(uint32_t i = 0; i < old_size; i++) {
                Bucket_Fine* b = &old_buckets[i];
                Node_Fine* head = b->head;
                while(head != NULL) {
                    put(head->key, head->value);
                    head = head->next;
                }
            }
            
            delete[] old_buckets;
        }
    public:
        Fine() : num_buckets(START_NUM_BUCKETS_FINE) {
            buckets = new Bucket_Fine[START_NUM_BUCKETS_FINE];
            locks= new mutex[START_NUM_BUCKETS_FINE];
        }
        uint32_t get(uint32_t key) {
            Bucket_Fine* b = getBucketForKey(key);
            return b->get(key);
        }

        void put(uint32_t key, uint32_t val) {
            //TODO
            Bucket_Fine* b = getBucketForKey(key);
            b->add(key, val);

            entries++;
            if(balanceFactor() >= RESIZE_FACTOR_FINE) {
                resize();
            }

            return;
        }

        bool hasKey(uint32_t key) {
            //TODO
            Bucket_Fine* b = getBucketForKey(key);

            //return false if bucket empty
            if(b->size == 0) {
                return false;
            }

            return b->hasKey(key);
        }


};

#endif
