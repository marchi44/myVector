#include <iostream>
#include <vector>
#include "vektorius.h"

int main() {
    unsigned int sz = 100000000;

    // std::vector
    std::vector<int> v1;
    int std_realloc = 0;
    for (unsigned int i = 1; i <= sz; ++i) {
        if (v1.size() == v1.capacity()) std_realloc++;
        v1.push_back(i);
    }

    // myVector
    myVector<int> v2;
    int my_realloc = 0;
    for (unsigned int i = 1; i <= sz; ++i) {
        if (v2.size() == v2.capacity()) my_realloc++;
        v2.push_back(i);
    }

    std::cout << "std::vector perskirstymai: " << std_realloc << "\n";
    std::cout << "myVector perskirstymai:    " << my_realloc  << "\n";
    return 0;
}