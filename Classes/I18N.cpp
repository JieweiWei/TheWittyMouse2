#include "I18N.h"

I18N* I18N::_I18N = NULL;

I18N* I18N::getInstance() {
	if (_I18N == NULL) {
		_I18N = new I18N();
		if (_I18N && _I18N->init()) {
			_I18N->autorelease();
			_I18N->retain();
		}
		else {
			CC_SAFE_DELETE(_I18N);
			_I18N = NULL;
		}
	}
	return _I18N;
}

bool I18N::init() {
	_language = "CN";
	loadStrings(JSON_PATH);
	return true;
}

const char* I18N::getString(std::string key) {
	return _stringMap[key].c_str();
}

void I18N::setLanguage(std::string language) {
	_language = language;
	_stringMap.clear();
	loadStrings(JSON_PATH);
}

void I18N::loadStrings(const char* path) {
	Json::Reader reader;
	Json::Value root;
	std::string data = FileUtils::getInstance()->getStringFromFile(path);
	if (reader.parse(data, root, false)) {
		auto keys = root.getMemberNames();
		for (auto key : keys) {
			if (key == "developer") {
				int num = root[key][_language].size();
				for (int i = 0; i < num; ++i) {
					_stringMap[key + Value(i).asString()] = root[key][_language][i].asString();
				}
				_stringMap["developerNum"] = Value(num).asString();
			}
			else {
				_stringMap[key] = root[key][_language].asString();
			}
		}
	}
}