#include "MouseController.h"
#include "Mouse.h"

MouseController* MouseController::mouseController = NULL;

MouseController* MouseController::getInstance() {
	if (mouseController == NULL) {
		mouseController = new MouseController();
		if (mouseController && mouseController->init()) {
			mouseController->autorelease();
			mouseController->retain();
		}
		else {
			CC_SAFE_DELETE(mouseController);
			mouseController = NULL;
		}
	}
	return mouseController;
}

bool MouseController::init() {
	return true;
}

MouseAction MouseController::getMouseAction(float IQ, ItemType itemtype, Vec2 dis, Vec2 speed, float range) {
	if (rand_0_1() * maxIQ > IQ) {
		return RUN;
	}
	Vec2 _time((speed.x != 0 ? dis.x / speed.x : 99999), (speed.y != 0 ? dis.y / speed.y : 99999));
	switch (itemtype) {
	case HOLE:
		return JUMP;
		break;
	case DENGEROUS_CUCRBIT:
		if (cmpFloat(_time.x, _time.y, range) == 0) {
			if (dis.x > Mouse::mouseWidth)
				return SLOWDOWN;
			return SPEEDUP;
		}

		break;
	case BENEFICATE_CUCRBIT:
		if (cmpFloat(_time.x, _time.y, range) == 1) {
			return SPEEDUP;
		}
		else if (cmpFloat(_time.x, _time.y, range) == -1) {
			return SLOWDOWN;
		}
		break;
	case SCOOTER:
		return JUMP;
		break;
	default: break;
	}
	return RUN;
}

int MouseController::cmpFloat(float f1, float f2, float range) {
	if (range == -1)
		range = dt;
	if (f1 - f2 > range) {
		return 1;
	}
	if (f1 - f2 < -range) {
		return -1;
	}
	range = -1;
	return 0;
}