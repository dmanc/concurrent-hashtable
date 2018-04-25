#include <chrono>
#include <cstdlib>
#include <iostream>
#include "sequential.h"
#include <thread>

using std::cout;

bool isWrite(double probability) {
    if(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) < probability)
        return true;
    return false;
}

// Performs the reads/writes one a hashtable with a given R/W ratio
template <class tbl_type>
void operation(tbl_type tbl, double probability) {
    // Replace sleep with actual read/write operations
    if(isWrite(probability)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    else {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// Runs the test multiple times and takes the average.
// TODO: Consider multiple threads
template <class tbl_type>
void measureTime(int trials, int amount) {
    cout << "Amount of trials: " << trials << "\n";
    tbl_type tbl;

    // 100% writes
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<trials; i++)
        operation(tbl, 1.0);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    cout << "(R/W 1.0) Average time per run in milliseconds: " << duration / trials << "\n";

    // 50% writes
    begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<trials; i++)
        operation(tbl, 0.5);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    cout << "(R/W 0.5) Average time per run in milliseconds: " << duration / trials << "\n";

    // 25% writes
    begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<trials; i++)
        operation(tbl, 0.25);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    cout << "(R/W 0.25) Average time per run in milliseconds: " << duration / trials << "\n";

    // 0% writes
    begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<trials; i++)
        operation(tbl, 0.0);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    cout << "(R/W 0.0) Average time per run in milliseconds: " << duration / trials << "\n";
}

int main() {
    std::cout << "Hello World\n";
    srand(0x100);
    measureTime<Sequential>(10, 1);
    return 0;
}
