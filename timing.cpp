#include <assert.h>
#include <chrono>
#include "coarse.h"
#include <cstdlib>
#include "fine.h"
#include "fine-spin.h"
#include <getopt.h>
#include <iostream>
#include <map>
#include "sequential.h"
#include "stm.h"
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
void operation(tbl_type& tbl, uint32_t start, uint32_t end, double probability, double* time) {
    for(uint32_t i = start; i <= end; i++) {
        uint32_t val = values[i];
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
    srand(0x100);
    auto begin = chrono::high_resolution_clock::now();
    for(int i = 0; i<trials; i++) {
        if(sequential) operation<tbl_type>(tbl, 0, values.size() - 1, probability, time);
        else {
            for(int w = 0; w<workers; w++) {
                // TODO: operation should take a slice of the data
                int start = w*part;
                int end = (w+1)*part;
                if(end >= amount) end = amount - 1;
                threads[w] = thread(operation<tbl_type>, ref(tbl), start, end, probability, time);
            }
            if(!sequential) {
                for(int w = 0; w<workers; w++)
                    threads[w].join();
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    //time[0] += chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    time[0] += chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

}


// Runs the test multiple times and takes the average.
template <class tbl_type>
void measureTime(int trials, int workers, bool resize) {
    int amount = values.size();

    bool sequential = is_same<tbl_type, Sequential>::value;
    string name = typeid(tbl_type).name();

    assert(workers >= 1 && workers <= 16);
    if(sequential) cout << "Sequential timing\n";
    else {
	cout << name << " timing\n";
        threads.clear();
        threads.resize(workers);
    }

    cout << "Amount of trials: " << trials << "\n";
    tbl_type tbl1(resize);
    for(int i = 0; i < amount; i++)
        tbl1.put(values[i], 1);
    double* time = new double[1];

    // 100% Writes
    startTime<tbl_type>(tbl1, amount, 1, time, trials, workers);
    cout << "(R/W 1.0) Average time per run: " << time[0] / trials << "\n";

    // 50% Writes
    tbl_type tbl2(resize);
    for(int i = 0; i<amount; i++)
        tbl2.put(values[i], 1);
    startTime<tbl_type>(tbl2, amount, 0.5, time, trials, workers);
    cout << "(R/W 0.5) Average time per run: " << time[0] / trials << "\n";

    
    // 25% Writes
    tbl_type tbl3(resize);
    for(int i = 0; i<amount; i++)
        tbl3.put(values[i], 1);
    startTime<tbl_type>(tbl3, amount, 0.25, time, trials, workers);
    cout << "(R/W 0.25) Average time per run: " << time[0] / trials << "\n";

    // 0% Writes
    tbl_type tbl4(resize);
    for(int i = 0; i<amount; i++)
        tbl4.put(values[i], 1);
    startTime<tbl_type>(tbl4, amount, 0.0, time, trials, workers);
    cout << "(R/W 0.0) Average time per run: " << time[0] / trials << "\n";
    
}

int main(int argc, char** argv) {
    std::cout << "Hello World\n";
    int workers = 1;
    int amount = 1;
    int resize = 1;
    // Handle arguments
    int c;
    while(1) {
        static struct option long_options[] =
            {
                {"workers", required_argument, 0, 'w'},
                {"amount", required_argument, 0, 'a'},
                {"resize", required_argument, 0, 'r'},
                {0,0,0,0}
            };
        int optind = 0;
        c  = getopt_long(argc, argv, "w:a:r:", long_options, &optind);
        if(c == -1) break;
        switch(c) {
            case 'w':
                workers = std::stoi(optarg);
                break;
            case 'a':
                amount = std::stoi(optarg);
                break;
           case 'r':
                resize = std::stoi(optarg);
                break;
        }
    }

    cout << "Workers: " << workers << "\n";
    cout << "Amount: " << amount << "\n";

    // Generate data
    srand(0x0);
    for(int i = 0; i<amount; i++) {
        uint32_t val = (((uint32_t) rand()) % 10000) + 1;
        values.push_back(val);
    }
    
    if(!resize) {
        cout << "Scalability without resizing\n";
        measureTime<Sequential>(1, workers, false);
        measureTime<Coarse>(1, workers, false);
        measureTime<STM>(1, workers, false);
        measureTime<Fine>(1, workers, false);
        measureTime<FineSpin>(1, workers, false);
    }
    else {
        cout << "Scalability with resizing\n";
        measureTime<Sequential>(1, workers, true);
        measureTime<Coarse>(1, workers, true);
        measureTime<STM>(1, workers, true);
        measureTime<Fine>(1, workers, true);
        measureTime<FineSpin>(1, workers, true);
    }
    return 0;
}
