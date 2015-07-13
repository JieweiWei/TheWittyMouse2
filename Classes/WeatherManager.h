#ifndef __WittedMouse__WeatherManager__
#define __WittedMouse__WeatherManager__

#include "cocos2d.h"
#include "Weather.h"

USING_NS_CC;

class WeatherManager : public Sprite {
public:
	bool init();

	CREATE_FUNC(WeatherManager);
private:
	Weather* weather;
};

#endif /* defined(__WittedMouse__WeatherManager__) */
