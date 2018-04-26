#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include "hashtable.h"

#define START_NUM_BUCKETS 10
#define RESIZE_FACTOR 10
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
                delete head;
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

        double balanceFactor() {
            return (double) entries / (double) num_buckets;
        }

        Bucket* getBucketForKey(uint32_t key) {
            return buckets + (hash(key) % num_buckets);
        }

        void resize() {
            //Resize
            //TODO
        }
    public:
        Sequential() : num_buckets(START_NUM_BUCKETS) {
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
            if(balanceFactor() > RESIZE_FACTOR) {
                printf("I should resize\n");
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
