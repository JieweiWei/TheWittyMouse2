#include "NetWorkLayer.h"
#include <time.h>

double Sigmoid(double x) {
    return 1 / (1 + pow(2.71828, (x/300 * -1)));
}

NetWorkLayer::NetWorkLayer(int in, int out) {
  inputNum = in;
  outputNum = out;
  bias = 0.05;
  Init();
}

void NetWorkLayer::Init() {
  srand((int)time(0));
  vector<double> temp;
  for (int i = 0; i < outputNum; ++i) {
    for (int j = 0; j < inputNum; ++j) {
      temp.push_back(((double)(rand()%100))/2000);
    }
    weights.push_back(temp);
    temp.clear();
  }
}

double NetWorkLayer::AddUp(int n, const vector<double> &input) {
  double result = 0;
  // the last one is check
  // so the cycle size is input.size() - 1
  for(int i = 0; i < inputNum; ++i) {
    result += weights[n][i] * input[i];
  }
  //cout << "compute " << Sigmoid(result) << endl;
  return Sigmoid(result - bias);
}

void NetWorkLayer::ComputeOutputs(const vector<double> &input) {
  outputs.clear();
  for(int i = 0; i < outputNum; ++i) {
    outputs.push_back(AddUp(i, input));
  }
}

vector<double> NetWorkLayer::GetOutputs() {
  return outputs;
}

double NetWorkLayer::GetWeight(int i, int j) {
  return weights[i][j];
}

void NetWorkLayer::UpdateWeights(const vector<double> &errors, const vector<double> &input) {
  // update error using error
  for (int i = 0;  i < outputNum; ++i) {
    for (int j = 0; j < inputNum; ++j) {
      weights[i][j] += errors[i] * LEARNING_RATE * input[j];
    }
  }
}
