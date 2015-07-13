#include "WeatherInfo.h"
#include "JSON\writer.h"
#include "JSON\reader.h"
#include "JSON\value.h"

WeatherInfo* WeatherInfo::_weatherInfo = NULL;

WeatherInfo::WeatherInfo() {
	_curWeatherStyle = none;
}

void WeatherInfo::setTodayWeather(const WeatherStyle& curWeatherStyle) {
	_curWeatherStyle = curWeatherStyle;
}

WeatherInfo* WeatherInfo::getInstance() {
	if (_weatherInfo == NULL) {
		_weatherInfo = new WeatherInfo();
		if (_weatherInfo && _weatherInfo->init()) {
			_weatherInfo->autorelease();
			_weatherInfo->retain();
		}
		else {
			CC_SAFE_DELETE(_weatherInfo);
			_weatherInfo = NULL;
		}
	}
	return _weatherInfo;
}

bool WeatherInfo::init() {
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(WeatherInfo::finishGetIp),
		"getIp",
		NULL
	);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(WeatherInfo::finishGetCityInfo),
		"getCityInfo",
		NULL
	);
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(WeatherInfo::finishGetWeatherInfo),
		"getWeatherInfo",
		NULL
	);
	Json::Reader reader;
	Json::Value root;
	string data = FileUtils::getInstance()->getStringFromFile(WEATHER_STYLE_FILE);
	if (reader.parse(data, root, false)) {
		for (auto styleStr : root["weatherStyle"]) {
			_weatherStyleStr.push_back(styleStr.asString());
		}
	}
	return true;
}

WeatherStyle WeatherInfo::getTodayWeather() {
	if (_curWeatherStyle == none) {
		_curWeatherStyle = _getTodayWeather();
	}
	return _curWeatherStyle;
}

WeatherStyle WeatherInfo::_getTodayWeather() {
	getWeatherInfo();
	ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(WEATHER_DATA_FILE);
	if (dict.empty()) {
		return defaultStyle;
	}
	string _date = dict["date"].asString();
	int diffDay = getDiffDay(_date);
	if (diffDay <= 3) {
		string curStyleStr = dict[StringUtils::format("weather%d", diffDay)].asString();
		for (int i = 0; i < _weatherStyleStr.size(); ++i) {
			if (curStyleStr.find(_weatherStyleStr[i]) != string::npos) {
				return (WeatherStyle)i;
			}
		}
	}
	return defaultStyle;
}

int WeatherInfo::getDiffDay(string _date) {
	time_t now;
	time(&now);
	struct tm recordTime = *localtime(&now);
	int _year, _mon, _day;
	sscanf(_date.c_str(), "%d-%d-%d", &_year, &_mon, &_day);
	recordTime.tm_year = _year - 1900;
	recordTime.tm_mon = _mon - 1;
	recordTime.tm_mday = _day;
	return difftime(now, mktime(&recordTime)) / (60 * 60 * 24);
}

void WeatherInfo::getWeatherInfo() {
	httpGet(GET_IP_URL, "getIp");
}

void WeatherInfo::httpGet(string url, string notificationType) {
	HttpRequest* request = new HttpRequest();
	request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl(url.c_str());
	request->setResponseCallback(CC_CALLBACK_2(WeatherInfo::onHttpRequestCompleted, this, notificationType));
	HttpClient::getInstance()->send(request);
	request->release();
}

void WeatherInfo::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response, string notificationType) {
	if (!response) {
		log("no response");
		return;
	}
	if (strlen(response->getHttpRequest()->getTag()) != 0) {
		log("%s completed", response->getHttpRequest()->getTag());
	}
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	log("response code: %s", statusString);
	if (!response->isSucceed()) {
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	/* dump data */
	string responseStr = "";
	std::vector<char> *buffer = response->getResponseData();
	for (unsigned int i = 0; i < buffer->size(); ++i) {
		responseStr += (*buffer)[i];
	}
	if (responseStr != "") {
		NotificationCenter::getInstance()->postNotification(notificationType, (Ref*)responseStr.c_str());
	}
	else {
		log("response empty");
	}
}

void WeatherInfo::finishGetIp(Ref* data) {
	if (data == NULL) {
		log("get ip fail");
		return;
	}
	httpGet(GET_CITY_INFO_URL + string((const char*)data), "getCityInfo");
}

void WeatherInfo::finishGetCityInfo(Ref* data) {
	if (data == NULL) {
		log("get city code fail");
		return;
	}
	string jsonStr = (const char*)data;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(jsonStr, root, false)) {
		root["city"].asString();
		httpGet(StringUtils::format(WEATHER_API, root["city"].asCString()), "getWeatherInfo");
	}
	else {
		log("parse city name fail");
	}
}

void WeatherInfo::finishGetWeatherInfo(Ref* data) {
	if (data == NULL) {
		log("get weather info fail");
		return;
	}
	parseWeatherInfoAndSave((const char*)data);
}

void WeatherInfo::parseWeatherInfoAndSave(string jsonStr) {
	if (jsonStr == "") {
		log("weather info empty");
		return;
	}
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(jsonStr, root, false)) {
		ValueMap dict;
		dict["date"] = Value(root["date"].asString());
		auto weatherInfo = root["results"][Json::UInt(0)]["weather_data"];
		for (int i = 0; i < weatherInfo.size(); ++i) {
			dict[StringUtils::format("weather%d", i)] = Value(weatherInfo[i]["weather"].asString());
		}
		FileUtils::getInstance()->writeToFile(dict, WEATHER_DATA_FILE);
	}
	else {
		log("parse weather info fail");
	}
}


