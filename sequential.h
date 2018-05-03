#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include "hashtable.h"
#include <cstdio>

#define START_NUM_BUCKETS 16
#define RESIZE_FACTOR 0.75

class Node {
    public:
        uint32_t key, value;
        Node* next;
        Node(uint32_t K, uint32_t V): key(K), value(V), next(NULL){}
};

class Bucket {
    public:
        uint32_t size;
        Node *head;
        Bucket(): size(0), head(NULL) {}
        ~Bucket() {
            Node* head = this->head;
            while(head != NULL) {
                Node* next = head->next;
                head = next;
            }
        }

        bool hasKey(uint32_t k) {
            Node* head = this->head;
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
                head = new Node(k, v);
            } else {
                Node* node = new Node(k, v);
                node->next = head;
                head = node;
            }
            size++;
        }

        uint32_t get(uint32_t k) {
            Node* head = this->head;
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

class Sequential: public HashTable {
    private:
        uint32_t num_buckets;
        Bucket* buckets;
        bool toresize;
        //protected field entries

        double balanceFactor() {
            return (double) entries / (double) num_buckets;
        }

        Bucket* getBucketForKey(uint32_t key) {
            return buckets + (hash_(key) % num_buckets);
        }

        void resize() {
            //Save old buckets
            Bucket* old_buckets = buckets;
            uint32_t old_size = num_buckets;

            //Make new buckets with old size
            num_buckets *= 2;
            buckets = new Bucket[num_buckets];
            entries = 0;

            //Insert all old elements into new table
            for(uint32_t i = 0; i < old_size; i++) {
                Bucket* b = &old_buckets[i];
                Node* head = b->head;
                while(head != NULL) {
                    put(head->key, head->value);
                    head = head->next;
                }
            }
        }
    public:
        Sequential(bool toresize=true) : num_buckets(START_NUM_BUCKETS) {
            buckets = new Bucket[START_NUM_BUCKETS];
        }
        uint32_t get(uint32_t key) {
            Bucket* b = getBucketForKey(key);
            return b->get(key);
        }

        void put(uint32_t key, uint32_t val) {
            Bucket* b = getBucketForKey(key);
            b->add(key, val);

            entries++;

            if(balanceFactor() >= RESIZE_FACTOR) {
                resize();
            }


            return;
        }

        bool hasKey(uint32_t key) {
            Bucket* b = getBucketForKey(key);

            //return false if bucket empty
            if(b->size == 0) {
                return false;
            }

            return b->hasKey(key);
        }


};

#endif
