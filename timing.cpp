#include <assert.h>
#include <chrono>
#include "coarse.h"
#include <cstdlib>
#include "fine.h"
#include <getopt.h>
#include <iostream>
#include <map>
#include "sequential.h"
//#include "stm.h"
#include <thread>
#include <type_traits>
#include <vector>

using namespace std;
vector<thread> threads;
vector<uint32_t> values;

bool isWrite(double probability) {
    if(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) < probability)
        return true;
    return false;
}

// Performs the reads/writes one a hashtable with a given R/W ratio
typedef std::vector<uint32_t>::iterator vec_iter;
template <class tbl_type>
void operation(tbl_type& tbl, vec_iter begin, vec_iter end, double probability, double* time) {
    for(vec_iter cur = begin; cur != end; ++cur) {
        uint32_t val = *cur;
        bool write = isWrite(probability);
        if(write) {
            tbl.put(val, 1);
        }
        else {
            // TODO: Change this to get a valid value
            tbl.get(val);
        }
    }
}

template <class tbl_type>
void startTime(tbl_type& tbl, int amount, double probability, double* time, int trials, int workers) {
    bool sequential = is_same<tbl_type, Sequential>::value;
    int part = amount / workers + 1;
    time[0] = 0.0;
    auto begin = chrono::high_resolution_clock::now();
    for(int i = 0; i<trials; i++) {
        if(sequential) operation<tbl_type>(tbl, values.begin(), values.end(), probability, time);
        else {
            for(int w = 0; w<workers; w++) {
                // TODO: operation should take a slice of the data
                int start = w*part;
                int end = (w+1)*part;
                if(end > amount) end = amount;
                threads[w] = thread(operation<tbl_type>, ref(tbl), values.begin() + start, values.begin() + end, probability, time);
            }
            if(!sequential) {
                for(int w = 0; w<workers; w++)
                    threads[w].join();
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    time[0] += chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();


    time[0] /= amount;
}

// Runs the test multiple times and takes the average.
template <class tbl_type>
void measureTime(int trials, int seed, int workers) {
    int amount = values.size();
    srand(seed);
    bool sequential = is_same<tbl_type, Sequential>::value;
    assert(workers >= 1 && workers <= 16);
    if(sequential) cout << "Sequential timing\n";
    else {
        cout << "Parallel timing\n";
        threads.clear();
        threads.resize(workers);
    }

    cout << "Amount of trials: " << trials << "\n";
    tbl_type tbl;
    double* time = new double[1];

    // 100% Writes
    startTime<tbl_type>(tbl, amount, 1, time, trials, workers);
    cout << "(R/W 1.0) Average time per run in nanoseconds: " << time[0] / trials << " ns\n";

    // 50% Writes
    startTime<tbl_type>(tbl, amount, 0.5, time, trials, workers);
    cout << "(R/W 0.5) Average time per run in nanoseconds: " << time[0] / trials << " ns\n";

    // 25% Writes
    startTime<tbl_type>(tbl, amount, 0.25, time, trials, workers);
    cout << "(R/W 0.25) Average time per run in nanoseconds: " << time[0] / trials << " ns\n";

    // 0% Writes
    startTime<tbl_type>(tbl, amount, 0.0, time, trials, workers);
    cout << "(R/W 0.0) Average time per run in nanoseconds: " << time[0] / trials << " ns\n";

}

int main(int argc, char** argv) {
    std::cout << "Hello World\n";
    int workers = 1;
    int amount = 1;
    // Handle arguments
    int c;
    while(1) {
        static struct option long_options[] =
            {
                {"workers", required_argument, 0, 'w'},
                {"amount", required_argument, 0, 'a'},
                {0,0,0,0}
            };
        int optind = 0;
        c  = getopt_long(argc, argv, "w:", long_options, &optind);
        if(c == -1) break;
        switch(c) {
            case 'w':
                workers = std::stoi(optarg);
                break;
            case 'a':
                amount = std::stoi(optarg);
                break;
        }
    }

    cout << "Workers: " << workers << "\n";
    cout << "Amount: " << amount << "\n";

    // Generate data
    for(int i = 0; i<amount; i++) {
        int val = (rand() % 1000) + 1;
        values.push_back(val);
    }

    measureTime<Sequential>(5, 0x100, workers);
    measureTime<Coarse>(5, 0x100, workers);
    measureTime<STM>(5, 0x100, workers);
    measureTime<Fine>(5, 0x100, workers);
    return 0;
}
