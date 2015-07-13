// 12330378
// Ye Wanyi
// class Layer

#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#define LEARNING_RATE 0.3

using namespace std;

class NetWorkLayer {
  public:
    NetWorkLayer(int in, int out);
    void Init();
    double AddUp(int n, const vector<double> &input);
    void ComputeOutputs(const vector<double> &input);
    vector<double> GetOutputs();
    void UpdateWeights(const vector<double> &errors, const vector<double> &input);
    double GetWeight(int i, int j);
  private:
    vector<double> outputs;
    vector<vector<double> > weights;
    int inputNum;
    int outputNum;
    double bias;
};

#endif