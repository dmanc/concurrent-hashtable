#include "hashtable.h"

class Node {
  public:
    uint32_t key, value;
    Node* next;
    Node() {}
    Node(uint32_t K, uint32_t V): key(K), value(V){}
};

class Bucket {
  public:
    uint32_t size;
    Node *head;
    Bucket(): size(0), head(NULL) {}
    void add(int k, int v) {
        if(head == NULL) {
            head = new Node(k, v);
        } else {
            Node *node = new Node(k, v);
            node->next = head;
            head = node;
        }
        size++;
    }
};

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
