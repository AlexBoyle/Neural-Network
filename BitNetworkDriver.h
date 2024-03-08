#ifndef BIT_NETWORK_DRIVER
#define BIT_NETWORK_DRIVER

#include "Matrix.h"
#include "BitNetwork.h"
#include "mnistHelper.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class BitNetworkDriver {
    public:
        BitNetworkDriver();
        void run();
        void trainNetwork();
        void checkNetwork();
    private:
        MNISTHelper mnistTestingSet;
        MNISTHelper mnistTrainingSet;
        BitNetwork bitNetwork;

};
#endif