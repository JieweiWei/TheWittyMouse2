//
//  Util.cpp
//  WittedMouse
//
//  Created by wc on 15/2/15.
//
//

#include "Util.h"

Util* Util::util = NULL;


void Util::init() {
	pauseMenuWidth = 0;
	dif = -1;
	distanceTravelled = 0.0;
	initMouseLife = 0;
}

Util* Util::getInstance() {
	if (util == NULL) {
		util = new Util();
		if (util) {
			util->autorelease();
			util->retain();
		}
		else {
			CC_SAFE_DELETE(util);
			util = NULL;
		}
	}
	return util;
}

void Util::setPauseMenuWidth(float pw) {
    pauseMenuWidth = pw;
}

float Util::getPauseMenuWidth() {
    return pauseMenuWidth;
}

float Util::getDif() {
    return dif;
}

void Util::setDif(float dif_) {
    dif = dif_;
}

void Util::setDistanceTravelled(float distanceTravelled_) {
	distanceTravelled = distanceTravelled_;
}

float Util::getDistanceTravelled() {
	return distanceTravelled;
}

void Util::setInitMouseLife(float initLife) {
	initMouseLife = initLife;
}

float Util::getInitMouseLife() {
	return initMouseLife;
}