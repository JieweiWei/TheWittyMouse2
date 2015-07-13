//
//  ActionController.cpp
//  WittedMouse
//
//  Created by wc on 15/2/28.
//
//

#include "ActionController.h"
#include "MainScene.h"
#include "Util.h"
#include "SimpleAudioEngine.h"

void ActionController::control(bool flag) {
	auto test = (MainScene*)Director::getInstance()->getRunningScene();
	MainScene *g1 = (MainScene*)(Director::getInstance()->getRunningScene()->getChildByTag(GAMETAG));
	if (flag) {
		g1->pauseSchedulerAndActions();
	}
	else {
		g1->resumeSchedulerAndActions();
	}
	for (int i = 0; i < g1->getChildrenCount(); i++) {
		Node *n = (Node *)(g1->getChildren().at(i));
		int nChild = n->getChildrenCount();
		if (nChild == 0) {
			if (flag) {
				n->pauseSchedulerAndActions();
			}
			else {
				n->resumeSchedulerAndActions();
			}
		}
		else {
			for (int j = 0; j != nChild; ++j) {
				Node *m = (Node *)(n->getChildren().at(j));
				if (flag)
					m->pauseSchedulerAndActions();
				else
					m->resumeSchedulerAndActions();
			}
		}
	}
	if (flag) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else {
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}