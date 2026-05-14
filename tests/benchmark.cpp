#include <iostream>
#include <vector>
#include <chrono>
#include "vektorius.h"

using namespace std::chrono;

double measure_std(unsigned int sz) {
    auto start = high_resolution_clock::now();
    std::vector<int> v1;
    for (unsigned int i = 1; i <= sz; ++i) v1.push_back(i);
    auto end = high_resolution_clock::now();
    return duration<double, std::milli>(end - start).count();
}

double measure_my(unsigned int sz) {
    auto start = high_resolution_clock::now();
    myVector<int> v2;
    for (unsigned int i = 1; i <= sz; ++i) v2.push_back(i);
    auto end = high_resolution_clock::now();
    return duration<double, std::milli>(end - start).count();
}

int main() {
    unsigned int sizes[] = {10000, 100000, 1000000, 10000000, 100000000};
    int runs = 5;

    std::cout << "| Elementų sk. | std::vector (ms) | myVector (ms) |\n";
    std::cout << "|---|---|---|\n";

    for (unsigned int sz : sizes) {
        double std_total = 0, my_total = 0;
        for (int r = 0; r < runs; r++) {
            std_total += measure_std(sz);
            my_total  += measure_my(sz);
        }
        std::cout << "| " << sz
                  << " | " << std_total / runs
                  << " | " << my_total / runs
                  << " |\n";
    }
    return 0;
}