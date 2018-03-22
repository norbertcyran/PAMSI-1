#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <fstream>
#include "lib/IRunnable.h"
#include "lib/Stub.h"
#include "lib/MergeSort.h"
#include "lib/HeapSort.h"

using namespace std;
using namespace std::chrono;

auto measure_time(IRunnable& prog) {
    vector<double> times {};
    for (unsigned i = 0; i < 10; i++) {
        auto t1 = high_resolution_clock::now();
        prog.run();
        auto t2 = high_resolution_clock::now();
        duration<double> elapsed = t2 - t1;
        times.push_back(elapsed.count());
    }
    auto avg = accumulate(times.cbegin(), times.cend(), 0.0) / times.size();
    return avg;
}

int main() {
    ofstream data_file {"../mergesort.csv"};
    vector<unsigned> sizes {10, 100, 1000, 10000,
                       100000, 1000000, 10000000, 100000000};
    MergeSort mergeSort;
    for(const auto& size: sizes) {
        mergeSort.prepare(size);
        data_file << size << ", " << measure_time(mergeSort) << endl;
    }
    data_file.close();

    ofstream heapsort_data {"../heapsort.csv"};
    HeapSort heapSort;
    for(const auto& size: sizes) {
        heapSort.prepare(size);
        heapsort_data << size << ", " << measure_time(heapSort) << endl;
    }
    heapsort_data.close();
}
