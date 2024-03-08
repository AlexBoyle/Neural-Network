#ifndef BASIC_NETWORK_DRIVER
#define BASIC_NETWORK_DRIVER

#include "Matrix.h"
#include "BasicNetwork.h"
#include "mnistHelper.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class BasicNetworkDriver {
    public:
        BasicNetworkDriver();
        void run();
        void trainNetwork();
        void checkNetwork();
    private:
        MNISTHelper mnistTestingSet;
        MNISTHelper mnistTrainingSet;
        BasicNetwork basicNetwork;

};
#endif