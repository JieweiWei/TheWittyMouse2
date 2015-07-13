/*
#ifndef __WittedMouse__NetworkManager__
#define __WittedMouse__NetworkManager__

#include "Network.h"
#include "MouseUtil.h"
#include <vector>

class NetworkManager {
public:
	static NetworkManager* getInstance();
	MouseAction getAction(EnvInfo env);
	void addTrainData(TrainData data);
private:
	NetworkManager();
	NetworkManager(const NetworkManager&);
	NetworkManager& operator=(const NetworkManager&);

	static NetworkManager* instance;
	vector< TrainData > datas;
	Network net;
};

#endif /* defined(__WittedMouse__NetworkManager__) */
