#include "BasicNetworkDriver.h"
#include "BitNetworkDriver.h"
#include <iostream>
#include <iomanip>

#include <chrono>
using namespace std::chrono;
using namespace std;

int main(int argc, char *argv[]) {
    auto start = high_resolution_clock::now();

    BasicNetworkDriver basicNetworkDriver = BasicNetworkDriver();
    basicNetworkDriver.run();
    //BitNetworkDriver bitNetworkDriver = BitNetworkDriver();
    //bitNetworkDriver.run();

    auto  stop = high_resolution_clock::now();
    auto  duration = duration_cast<microseconds>(stop - start);
    cout << "Run took " << (duration.count()/1000000.0) << "s" << endl;
}