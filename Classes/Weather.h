#ifndef __WittedMouse__Weather__
#define __WittedMouse__Weather__

#include "cocos2d.h"
#include "WeatherInfo.h"

USING_NS_CC;

class Weather : public Sprite {
public:
	bool init();
	WeatherStyle getWeatherTypr() const;

	CREATE_FUNC(Weather);
private:
	void windyEffect();
	void rainEffect();
	void cloudyEffect();
	void sunnyEffect();
	WeatherStyle weatherType;
};

#endif /* defined(__WittedMouse__Weather__) */
