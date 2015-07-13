// 12330378
// Ye Wanyi
// class Network

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <vector>

#include "NetWorkLayer.h"

#define OUT_NUM 2
#define HIDDEN_NUM 5
#define IN_NUM 3
#define MAX_TRAINING 500
#define ACCURACY_RATE 0.95
#define OUT_PATH "out_rate.dat"

using namespace std;

class Network {
  public:
    Network(int inNum = IN_NUM, int hiddenNum = HIDDEN_NUM,
            int outNum = OUT_NUM, int max = MAX_TRAINING,
            double demandRate = ACCURACY_RATE);
    ~Network();
    void Training(const vector<vector<double> > &inputs);
    vector<double> getOneByInput(const vector<double> &inputs);
    bool IsExpect(const vector<double> &input_t);
    double dcmp(double a);
    vector<double> getResult();
  private:
    NetWorkLayer* outLayer;
    NetWorkLayer* hiddenLayer;
    double gRate;
    int maxTime;
    double demandRate;
};

#endif