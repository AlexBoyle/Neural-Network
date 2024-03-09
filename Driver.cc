#include "BasicNetworkDriver.h"
#include "BitNetworkDriver.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
    //BasicNetworkDriver basicNetworkDriver = BasicNetworkDriver();
    //basicNetworkDriver.run();
    BitNetworkDriver bitNetworkDriver = BitNetworkDriver();
    bitNetworkDriver.run();
}