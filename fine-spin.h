#ifndef FINE_SPIN_H
#define FINE_SPIN_H

#include <atomic>
#include "fine.h"

#define START_NUM_BUCKETS_FINE 16
#define RESIZE_FACTOR_FINE 0.75

class spin {
    private:
        atomic<bool> taken;
    public:
        spin() {
            taken = false;
        }
        void lock() {
            while(taken.exchange(true));
        }
        void unlock() {
            taken = false;
        }
};

class FineSpin : public HashTable {
    private:
        uint32_t num_buckets;
        Bucket_Fine* buckets;
        spin* locks;
        mutex resize_lock;
        atomic<uint32_t> entries_at;

        //protected field entries

        double balanceFactor() {
            return (double) entries_at / (double) num_buckets;
        }

        Bucket_Fine* getBucketForKey(uint32_t key) {
            return buckets + (hash_(key) % num_buckets);
        }

        spin* getLockForKey(uint32_t key) {
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
            entries_at = 0;

            //Insert all old elements into new table
            for(uint32_t i = 0; i < old_size; i++) {
                Bucket_Fine* b = &old_buckets[i];
                Node_Fine* head = b->head;
                while(head != NULL) {
                    put_free(head->key, head->value);
                    head = head->next;
                }
            }
            
            //delete[] old_buckets;
        }
    public:
        FineSpin() : num_buckets(START_NUM_BUCKETS_FINE) {
            buckets = new Bucket_Fine[START_NUM_BUCKETS_FINE];
            locks = new spin[START_NUM_BUCKETS_FINE];
            entries_at = 0;
        }
        uint32_t get(uint32_t key) {
            spin* bucket_lock = getLockForKey(key);
            lock_guard<spin> lock_g(*bucket_lock);
            Bucket_Fine* b = getBucketForKey(key);
            return b->get(key);
        }

        void put(uint32_t key, uint32_t val) {
            //TODO
            spin* bucket_lock = getLockForKey(key);
            bucket_lock->lock();
            Bucket_Fine* b = getBucketForKey(key);
            b->add(key, val);
            bucket_lock->unlock();

            entries_at++;


            //Only one thread should resize
            if(resize_lock.try_lock()) {
                if(balanceFactor() >= RESIZE_FACTOR_FINE) {
                    //Acquire all locks
                    for(int i = 0; i < START_NUM_BUCKETS_FINE; i++) {
                        locks[i].lock();
                    }
                    resize();
                    //Free all locks
                    for(int i = 0; i < START_NUM_BUCKETS_FINE; i++) {
                        locks[i].unlock();
                    }
                }
                resize_lock.unlock();
            }

            return;
        }

        //Puts without a lock, helper for resizing
        void put_free(uint32_t key, uint32_t val) {
            //TODO
            Bucket_Fine* b = getBucketForKey(key);
            b->add(key, val);
            entries_at++;
            return;
        }


        bool hasKey(uint32_t key) {

            spin* bucket_lock = getLockForKey(key);
            lock_guard<spin> lock_g(*bucket_lock);
            Bucket_Fine* b = getBucketForKey(key);

            //return false if bucket empty
            if(b->size == 0) {
                return false;
            }

            return b->hasKey(key);
        }

        uint32_t size() {
            return entries_at;
        }

        bool isEmpty() {
            return FineSpin::size() == 0;
        }


};

#endif
