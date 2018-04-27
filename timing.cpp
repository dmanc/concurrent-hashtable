#include <assert.h>
#include <chrono>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include "sequential.h"
#include <thread>
#include <type_traits>
#include <vector>

using std::cout;
std::vector<std::thread> threads;
std::vector<uint32_t> values;

bool isWrite(double probability) {
    if(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) < probability)
        return true;
    return false;
}

// Performs the reads/writes one a hashtable with a given R/W ratio
// TODO: operation should eventually take in a list of elements to operate on.
template <class tbl_type>
void operation(tbl_type& tbl, int amount, int pos, double probability, double* time) {
    // Replace sleep with actual read/write operations
    //double time = 0.0;
    for(int i = pos; i<amount; i++) {
        uint32_t val = values[pos];
        bool write = isWrite(probability);
        auto begin = std::chrono::high_resolution_clock::now();
        if(write) {
            tbl.put(val, 1);
        }
        else {
            // TODO: Change this to get a valid value
            tbl.get(val);
        }
        auto end = std::chrono::high_resolution_clock::now();
        time[0] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    }
}

template <class tbl_type>
void startTime(tbl_type& tbl, int amount, double probability, double* time, int trials, int workers) {
    bool sequential = std::is_same<tbl_type, Sequential>::value;
    time[0] = 0.0;
    for(int i = 0; i<trials; i++) {
        if(sequential) operation<tbl_type>(tbl, amount, 0, probability, time);
        else {
            for(int w = 0; w<workers; w++) {
                // TODO: operation should take a slice of the data
                threads[w] = std::thread(operation<tbl_type>, std::ref(tbl), amount, 0, probability, time);
            }
        }
    }

    if(!sequential) {
        for(int w = 0; w<workers; w++)
            threads[w].join();
    }

    time[0] /= amount;
}

// Runs the test multiple times and takes the average.
// TODO: Consider multiple threads
template <class tbl_type>
void measureTime(int trials, int seed, int workers) {
    int amount = values.size();
    srand(seed);
    bool sequential = std::is_same<tbl_type, Sequential>::value;
    assert(workers >= 1 && workers <= 16);
    if(sequential) cout << "Sequential timing\n";
    else {
        cout << "Parallel timing";
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
    startTime(tbl, amount, 0.5, time, trials, workers);
    cout << "(R/W 0.5) Average time per run in nanoseconds: " << time[0] / trials << " ns\n";

    // 25% Writes
    startTime(tbl, amount, 0.25, time, trials, workers);
    cout << "(R/W 0.25) Average time per run in nanoseconds: " << time[0] / trials << " ns\n";

    // 0% Writes
    startTime(tbl, amount, 0.0, time, trials, workers);
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

    //for(size_t i = 0; i<values.size(); i++)
    //  cout << values[i] << '\n';

    measureTime<Sequential>(10, 0x100, workers);

    return 0;
}
