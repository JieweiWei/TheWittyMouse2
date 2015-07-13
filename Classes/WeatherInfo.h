#ifndef _WEATHERINFO_H_
#define _WEATHERINFO_H_

#include "cocos2d.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace cocos2d::network;
using std::string;

/* ������Ϣ�洢·�� */
#define WEATHER_DATA_FILE "data/weathers.xml"

#define WEATHER_STYLE_FILE "data/weatherStyle.json"

/* ������ȡIP */
#define GET_IP_URL "http://ip.dnsexit.com/"

/* ��ȡλ����Ϣ */
#define GET_CITY_INFO_URL "http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=json&ip=" // + "ip"

/* ������API */
#define WEATHER_API "http://api.map.baidu.com/telematics/v3/weather?location=%s&output=json&ak=EkQNeFX5u8kcWFqlNjnm8LCT" // %s is city name

enum WeatherStyle {rain, sunny, cloudy, windy, defaultStyle, none};

class WeatherInfo : public Ref {
public:
	static WeatherInfo* getInstance();
	virtual bool init();
	WeatherStyle getTodayWeather();

	// for debug
	void setTodayWeather(const WeatherStyle& curWeatherStyle);
private:
	WeatherInfo();
	WeatherStyle _getTodayWeather();
	void getWeatherInfo();
	inline int getDiffDay(string _date);
	void httpGet(string url, string notificationType);
	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response, string notificationType);

	void finishGetIp(Ref* data);
	void finishGetCityInfo(Ref* data);
	void finishGetWeatherInfo(Ref* data);

	void parseWeatherInfoAndSave(string jsonStr);
private:
	WeatherStyle _curWeatherStyle;
	static WeatherInfo* _weatherInfo;
	std::vector<string> _weatherStyleStr;
};

#endif // !_WEATHERINFO_H_