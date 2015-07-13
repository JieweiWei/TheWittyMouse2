#include "Network.h"
#include "cmath"

Network::Network(int inNum, int hiddenNum, int outNum, int max, double demand) {
  hiddenLayer = new NetWorkLayer(inNum, hiddenNum);
  outLayer = new NetWorkLayer(hiddenNum, outNum);
  gRate = 0;
  maxTime = max;
  demandRate = demand;
}

Network::~Network() {
  delete hiddenLayer;
  delete outLayer;
}

double Network::dcmp(double a) {
    if (fabs(a) < 1e-6) {
        return 0;
    }
    return a;
}

vector<double> Network::getResult() {
    auto out = outLayer->GetOutputs();
    vector<double> result(2);
    if (out[0] < (-0.8)) {
        result[0] = -1;
    } else if (out[0] > 0.8) {
        result[0] = 1;
    } else {
        result[0] = 0;
    }
    
    if (out[0] > 0.8) {
        result[1] = 1;
    } else {
        result[1] = 0;
    }
    
    cout << "out: " << out[0] << " " << out[1] << endl;
    return result;
}

bool Network::IsExpect(const vector<double> &input_t) {
    auto result = getResult();
    return result[0] == input_t[3] && result[1] == input_t[4];
}

void Network::Training(const vector<vector<double> > &inputs) {
    int t = 0;
    while (t < inputs.size()) {
      //
      // feed-forward computing
      //
      // compute for hidden layer
      hiddenLayer->ComputeOutputs(inputs[t]);
      
      // compute output for output layer
      outLayer->ComputeOutputs(hiddenLayer->GetOutputs());
      
      // set the expected vector
      double expect[OUT_NUM];
      expect[0] = inputs[t][3];
      expect[1] = inputs[t][4];
      
      // back propagation from out to hidden
      vector<double> errors1;
      for (int i = 0; i < OUT_NUM; ++i) {
        double temp = 0;
        temp = outLayer->GetOutputs()[i] * (1 - outLayer->GetOutputs()[i]) * (expect[i] - outLayer->GetOutputs()[i]);
        errors1.push_back(temp);
      }
      outLayer->UpdateWeights(errors1, hiddenLayer->GetOutputs());
      
      // back propagation from hidden to input layer
      //
      vector<double> errors2;
      for (int j = 0; j < HIDDEN_NUM; ++j) {
        double back = 0;
        for (int i = 0; i < OUT_NUM; ++i) {
          back += (hiddenLayer->GetWeight(i, j) * errors1[i]);
        }
        errors2.push_back(hiddenLayer->GetOutputs()[j] * (1 - hiddenLayer->GetOutputs()[j]) * back);
      }
      hiddenLayer->UpdateWeights(errors2, inputs[t]);
      errors1.clear();
      errors2.clear();
      ++t;
    }
}

vector<double> Network::getOneByInput(const vector<double> &inputs) {
    // using the training weights to compute test input
    hiddenLayer->ComputeOutputs(inputs);
    outLayer->ComputeOutputs(hiddenLayer->GetOutputs());
    return getResult();
}