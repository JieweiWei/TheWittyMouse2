#ifndef _I18N_H_
#define _I18N_H_

#include "cocos2d.h"
#include "JSON\writer.h"
#include "JSON\reader.h"
#include "JSON\value.h"

USING_NS_CC;

#define JSON_PATH "i18n/public.json"

class I18N : public Ref {
public:
	static I18N* getInstance();
	virtual bool init();
	const char* getString(std::string key);
	void setLanguage(std::string language);

private:
	void loadStrings(const char* path);

private:
	static I18N* _I18N;
	std::map<std::string, std::string> _stringMap;
	std::string _language;
};

#endif // !_I18N_H_
